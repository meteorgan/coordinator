#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <thread>

#include <libconfig.h++>

#include <xdrpp/srpc.h>
#include <xdrpp/socket.h>

#include "include/rpcconfig.h"
#include "include/participant.hh"
#include "serverimpl.hh"
#include "participant.hh"

using namespace std;
using namespace xdr;

static void runListener(rpc_tcp_listener &listener) {
	try {
		listener.run();
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
}

int main(int argc, const char *argv[]) {
    libconfig::Config config;
    config.readFile("server.cfg");
    int participant_port = PARTICIPANT_DEFAULT_PORT;
    config.lookupValue("participant_port", participant_port);

    participant_api_v1_server participant;
    participant.start();
    rpc_tcp_listener participant_listener(tcp_listen(std::to_string(participant_port).c_str(), AF_INET));
    participant_listener.register_service(participant);
    std::thread participant_thread(runListener, ref(participant_listener));

	api_v1_server s;
	int server_port = UNIQUE_RPC_PORT;
	config.lookupValue("server_port", server_port);
    rpc_tcp_listener rl(tcp_listen(std::to_string(server_port).c_str(), AF_INET));
    rl.register_service(s);
    std::thread api_thread(runListener, ref(rl));

    participant_thread.join();
    api_thread.join();

    return 0;
}
