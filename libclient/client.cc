
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

std::string
Client::get(const std::string &path)
{
    std::unique_ptr<Result> result = client->get(path);
    if(result->discriminant() != 1) {
    	throw ClientException{ClientError::KEY_NOT_FOUND};
    }
    else {
    	return result->val();
    }
}

void
Client::set(const std::string &path, const std::string &val)
{
	kvpair arg;
	arg.key = path;
	arg.val = val;
    std::unique_ptr<Result> result = client->set(arg);
    if(result->error() == ServerError::KEY_NOT_FOUND_ERROR) {
    	throw ClientException{ClientError::KEY_NOT_FOUND};
    }
}

bool
Client::remove(const std::string &path)
{
	std::unique_ptr<Result> result = client->remove(path);
	switch(result->error()) {
	case ServerError::KEY_HAS_CHILDREN:
		throw ClientException{ClientError::HAS_CHILDREN};
		break;
	case ServerError::KEY_NOT_FOUND_ERROR:
		throw ClientException{ClientError::KEY_NOT_FOUND};
		break;
	default:
		return true;
	}

	return false;
}

std::set<string>
Client::list(const string &path)
{
    std::set<string> r;
    std::unique_ptr<Result> result = client->list(path);
    if(result->discriminant() == 2) {
    	for(auto &key : result->keys()) {
    		r.insert(key);
    	}
    }
    else {
    	throw ClientException{ClientError::KEY_NOT_FOUND};
    }

    return r;
}
