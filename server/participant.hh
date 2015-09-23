// -*- C++ -*-
// Scaffolding originally generated from include/participant.x.
// Edit to add functionality.

#ifndef __XDR_SERVER_PARTICIPANT_HH_INCLUDED__
#define __XDR_SERVER_PARTICIPANT_HH_INCLUDED__ 1

#include <map>

#include "xdrpp/srpc.h"
#include "xdrpp/socket.h"

#include "include/participant.hh"
#include "include/participant_server.hh"
#include "concurrentQueue.hh"

class participant_api_v1_server {
public:
	using rpc_interface_type = participant_api_v1;

	participant_api_v1_server();
	~participant_api_v1_server();

	 void start();

	void request_vote(std::unique_ptr<RequestInfo> arg);
	void request_response(std::unique_ptr<ResponseInfo> arg);
	void request_commit(std::unique_ptr<CommitInfo> arg);

protected:
	void process_request_vote();
	bool lookupCommitInfo();        // 通过查询其他机器的状态解决参与者ready状态的超时

private:
	participant_server *local;
	std::map<ParticipantId, participant_server> coordinators;
	std::map<ParticipantId, xdr::srpc_client<participant_api_v1>*> conns;

	std::thread process_request_thread;
	CQueue<RequestInfo> requests;

	OpInt response_seq;
	RequestInfo currentRequest;
	std::mutex ready;
	std::condition_variable commit_variable;
	int timeout;
};

#endif // !__XDR_SERVER_PARTICIPANT_HH_INCLUDED__
