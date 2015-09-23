/*
 * participant_server.hh
 *
 *  Created on: 2015年9月10日
 *      Author: meteorgan
 */

#ifndef INCLUDE_PARTICIPANT_SERVER_HH_
#define INCLUDE_PARTICIPANT_SERVER_HH_

#include "two_phrase_commit_common.hh"

class participant_server {
public:
	participant_server(std::string &host, int port) : addr(host), port(port) {
		std::hash<std::string> hash_fn;
		id = hash_fn(host) + port;
	};

	std::string addr;
	int port;
	ParticipantId id;
};

#endif /* INCLUDE_PARTICIPANT_SERVER_HH_ */
