// Scaffolding originally generated from include/participant.x.
// Edit to add functionality.

#include "server/participant.hh"

#include <include/utils.hh>
#include <iostream>

#include <libconfig.h++>

#include "server/participant.hh"
#include "include/rpcconfig.h"
#include "serverimpl.hh"
#include "coordinator.h"

participant_api_v1_server::participant_api_v1_server() {
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
		coordinators.insert(std::make_pair(server.id, server));
	}

	if(!config.exists("ip")) {
		std::cerr << "do not have ip in server.cfg!" << std::endl;
		exit(1);
	}
	std::string ip = config.lookup("ip");
	int port = PARTICIPANT_DEFAULT_PORT;
	config.lookupValue("participant_port", port);
	local = new participant_server(ip, port);
	response_seq = 0;

	timeout = 3000;
	config.lookupValue("coordinator_timeout", timeout);
}

participant_api_v1_server::~participant_api_v1_server() {
	process_request_thread.join();

	delete local;
	for(auto conn : conns) {
		delete conn.second;
	}
}

void
participant_api_v1_server::start() {
	std::thread process_request(&participant_api_v1_server::process_request_vote, this);
	process_request_thread = std::move(process_request);
}

void
participant_api_v1_server::request_vote(std::unique_ptr<RequestInfo> arg) {
	ParticipantId coordinatorId = arg->participantId;
	OpInt seq = arg->opNum;
	printf("time: %f, participant %lu receive request vote from coordinator %lu, seq: %lu, op type: %u, key: %s\n",
			now(), local->id, coordinatorId, seq, arg->opType, arg->kv.key.c_str());

	requests.push(*(arg.get()));
}

void
participant_api_v1_server::request_response(std::unique_ptr<ResponseInfo> arg) {
	coordinator::getInstance().response_vote(std::move(arg));
}

void
participant_api_v1_server::request_commit(std::unique_ptr<CommitInfo> arg) {
	OpInt seq = arg->opNum;
	CommitOp op = arg->commitOp;
	ParticipantId coordinatorId = arg->participantId;
	printf("time: %f, participant %lu receive commit info from coordinator %lu, seq: %lu, commit type: %u.\n",
			now(), local->id, coordinatorId, seq, op);

	{
		std::unique_lock<std::mutex> lock(ready);
		response_seq = seq;
		commit_variable.notify_one();
	}

	std::string key;
	std::string value;
	std::string path;
	if(op == CommitOp::GLOABL_COMMIT) {
		OpType opType = currentRequest.opType;
		switch(opType) {
		case OpType::SET:
		case OpType::CREATE:
			key = currentRequest.kv.key;
			value = currentRequest.kv.val;
			api_v1_server::set(key, value);
			break;
		case OpType::REMOVE:
			path = currentRequest.kv.key;
			api_v1_server::remove(path);
			break;
		}
	}
}

void
participant_api_v1_server::process_request_vote() {
	while(true) {
		RequestInfo request = requests.pop();

		if(conns.empty()) {
			for(auto &entry : coordinators) {
				ParticipantId id = entry.first;
				participant_server server = entry.second;
				auto fd = xdr::tcp_connect(server.addr.c_str(), std::to_string(server.port).c_str());
				auto s = new xdr::srpc_client<participant_api_v1>{fd.release()};
				conns.insert(std::make_pair(id, s));
			}
		}

		ParticipantId participantId = request.participantId;
		OpInt seq = request.opNum;

		ResponseInfo response;
		response.participantId = local->id;
		response.opNum = seq;
		response.response = RequestResponse::VOTE_COMMIT;
		if(conns.find(participantId) == conns.end()) {
			std::cerr << "not connect to coordinator: " << participantId << std::endl;
			return;
		}
		auto participant = conns.find(participantId)->second;
		participant->request_response(response);

		std::unique_lock<std::mutex> lock(ready);
		response_seq = 0;
		currentRequest = request;
		while(response_seq != seq) {
			std::cv_status status = commit_variable.wait_for(lock, std::chrono::milliseconds(timeout));
			if(status == std::cv_status::timeout) {
				break;
			}
		}
	}
}

bool
participant_api_v1_server::lookupCommitInfo() {
	return true;
}
