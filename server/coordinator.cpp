/*
 * coordinator.cpp
 *
 *  Created on: 2015年9月23日
 *      Author: meteorgan
 */

#include "coordinator.h"

#include <iostream>

#include <libconfig.h++>

#include "coordinator.h"
#include "include/rpcconfig.h"
#include "include/utils.hh"

coordinator::coordinator() {
	libconfig::Config config;
	config.readFile("server.cfg");
	if(!config.exists("servers")) {
		std::cerr << "do not have servers in server.cfg!" << std::endl;
		exit(1);
	}

	libconfig::Setting &settings = config.lookup("servers");
	int length = settings.getLength();
	for(int i = 0; i < length; ++i) {
		std::string host = "";
		int port = PARTICIPANT_DEFAULT_PORT;
		if(!settings[i].lookupValue("host", host)) {
			std::cerr << "do not have host in server.cfg!" << std::endl;
			exit(1);
		}

		settings[i].lookupValue("participant_port", port);
		participant_server server(host, port);
		servers.insert(std::make_pair(server.id, server));
	}

	if(!config.exists("ip")) {
		std::cerr << "do not have ip in server.cfg!" << std::endl;
	}
	std::string host = config.lookup("ip");
	int port = COORDINATOR_DEFAULT_PORT;
	config.lookupValue("participant_port", port);
	server = new participant_server(host, port);

	timeout = 3000;
	config.lookupValue("coordinator_timeout", timeout);
	response_number = 0;
	success = true;
}

coordinator::~coordinator() {
	delete server;
	for(auto conn : conns) {
		delete conn.second;
	}
}

coordinator& coordinator::getInstance() {
	static coordinator instance;   // thread safe in c++11

	return instance;
}


Result
coordinator::start_2pc(const CommitRequest &request) {
	Result res(3);

	std::cout << "coordinator receive request!" << std::endl;
	if(conns.empty()) {
		for(auto &server : servers) {
			std::string host = server.second.addr;
			int port = server.second.port;
			auto fd = xdr::tcp_connect(host.c_str(), std::to_string(port).c_str());
			xdr::srpc_client<participant_api_v1> *client = new xdr::srpc_client<participant_api_v1>{fd.release()};
			conns.insert(std::make_pair(server.first, client));
		}
	}

	RequestInfo requestInfo;
	requestInfo.kv = request.kv;
	requestInfo.opType = request.opType;
	requestInfo.opNum = seq++;
	requestInfo.participantId = server->id;

	response_number = 0;
	success = true;
	for(auto conn : conns) {
		auto client = conn.second;
		client->request_vote(requestInfo);
	}

	{
		std::unique_lock<std::mutex> lock(request_lock);
		while(response_number != conns.size()) {
			std::cv_status status = request_variable.wait_for(lock, std::chrono::milliseconds(timeout));
			if((status == std::cv_status::timeout) || (success == false)) {
				success = false;
				break;
			}
		}
	}

	CommitInfo commitInfo;
	commitInfo.opNum = requestInfo.opNum;
	commitInfo.commitOp = success ? CommitOp::GLOABL_COMMIT : CommitOp::GLOBAL_ABORT;
	commitInfo.participantId = server->id;

	for(auto conn : conns) {
		auto client = conn.second;
		client->request_commit(commitInfo);
	}

	res.error() = success ? ServerError::NONE : ServerError::QUORUM_NOT_REACHED;
	return res;
}

void
coordinator::response_vote(std::unique_ptr<ResponseInfo> arg) {
	ParticipantId participantId = arg->participantId;
	OpInt seq = arg->opNum;
	RequestResponse response = arg->response;
	printf("time: %f, coordinator %lu receive response from participant %lu, seq: %lu, response type: %u.\n",
			now(), server->id, participantId, seq, arg->response);

	{
		std::unique_lock<std::mutex> lock(request_lock);
		response_number++;
		if(response == RequestResponse::VOTE_ABORT)
			success = false;
		request_variable.notify_one();

	}
}
