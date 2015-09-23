/*
 * coordinator.h
 *
 *  Created on: 2015年9月23日
 *      Author: meteorgan
 */

#ifndef SERVER_COORDINATOR_H_
#define SERVER_COORDINATOR_H_

#include <mutex>
#include <condition_variable>

#include "xdrpp/srpc.h"
#include "xdrpp/socket.h"

#include "include/participant_server.hh"
#include "include/participant.hh"

class coordinator {
public:
	static coordinator& getInstance();

	~coordinator();

	Result start_2pc(const CommitRequest &request);

	void response_vote(std::unique_ptr<ResponseInfo> arg);

private:
	coordinator();

	participant_server *server;
	std::map<ParticipantId, participant_server> servers;
	std::map<ParticipantId, xdr::srpc_client<participant_api_v1>*> conns;
	OpInt seq = 1;
	OpInt response_seq = 0;
	std::mutex request_lock;
	std::condition_variable request_variable;
	uint16_t response_number;
	int timeout;
	bool success;
};

#endif /* SERVER_COORDINATOR_H_ */
