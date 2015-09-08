// -*- C++ -*-
// Scaffolding originally generated from include/participant.x.
// Edit to add functionality.

#ifndef __XDR_SERVER_PARTICIPANTIMPL_HH_INCLUDED__
#define __XDR_SERVER_PARTICIPANTIMPL_HH_INCLUDED__ 1

#include "include/participant.hh"

class participantApi_v1_server {
public:
  using rpc_interface_type = participantApi_v1;

  // coordinator send vote-request message to all participants
  void request_vote(std::unique_ptr<RequestInfo> arg);

  // participants send response to coordinator(vote-commit or vote-abort)
  void response_vote(std::unique_ptr<ReponseInfo> arg);

  // coordinator send commit information to all participants(global commit or global abort)
  void request_commit(std::unique_ptr<CommitInfo> arg);
};

#endif // !__XDR_SERVER_PARTICIPANTIMPL_HH_INCLUDED__
