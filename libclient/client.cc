
#include <unistd.h>
#include <sys/socket.h>

#include <iostream>
#include <set>
#include <string>

#include <xdrpp/srpc.h>
#include <xdrpp/rpcbind.hh>
#include <xdrpp/socket.h>

#include <include/rpcconfig.h>
#include <include/server.hh>
#include <include/client.h>

using namespace std;
using namespace xdr;

Client::Client()
{
    client = NULL;
}

Client::~Client()
{
    this->close();
}

void
Client::open(const std::string &host)
{
    if (isConnected()) {
        cout << "Already connected!" << endl;
        exit(1);
    }

    auto fd = tcp_connect(host.c_str(), UNIQUE_RPC_PORT);
    client = new srpc_client<api_v1>{fd.release()};
}

void
Client::close()
{
    if (isConnected()) {
        delete client;
        client = NULL;
    }
}

bool
Client::isConnected()
{
    return client != NULL;
}

bool
Client::create(const std::string &path, const std::string &val)
{
    kvpair args;
    args.key = path;
    args.val = val;

    std::unique_ptr<Result> r = client->create(args);
    switch(r->error()) {
    case ServerError::KEY_DUPLICATE:
    	throw ClientException{ClientError::DUPLICATE_KEY};
    	break;
    case ServerError::KEY_MALFORMED:
    	throw ClientException{ClientError::MALFORMED_KEY};
    	break;
    case ServerError::KEY_NO_PARENT:
    	throw ClientException{ClientError::NO_PARENT};
    	break;
    default:
    	return true;
    }

    return false;
}

bool
Client::remove(const std::string &path)
{
    // TODO: Fill me in
    return false;
}

std::string
Client::get(const std::string &path)
{
    // TODO: Fill me in
    return "";
}

void
Client::set(const std::string &path, const std::string &val)
{
    // TODO: Fill me in
}

std::set<string>
Client::list(const string &path)
{
    std::set<string> r;
    // TODO: Fill me in
    return r;
}

