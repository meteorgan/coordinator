// -*- C++ -*-
// Scaffolding originally generated from include/server.x.
// Edit to add functionality.

#ifndef __XDR_SERVER_SERVERIMPL_HH_INCLUDED__
#define __XDR_SERVER_SERVERIMPL_HH_INCLUDED__ 1

#include "include/server.hh"
#include "serverdb.h"

class api_v1_server {
public:
  using rpc_interface_type = api_v1;

  api_v1_server();
  ~api_v1_server() {};

  std::unique_ptr<Result> create(std::unique_ptr<kvpair> arg);
  std::unique_ptr<Result> remove(std::unique_ptr<longstring> arg);
  std::unique_ptr<Result> set(std::unique_ptr<kvpair> arg);
  std::unique_ptr<Result> get(std::unique_ptr<longstring> arg);
  std::unique_ptr<Result> list(std::unique_ptr<longstring> arg);

  static void set(std::string &key, std::string &value);
  static void remove(std::string &path);

private:
  static ServerDB db;
};

#endif // !__XDR_SERVER_SERVERIMPL_HH_INCLUDED__
