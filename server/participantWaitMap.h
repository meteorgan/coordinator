/*
 * participantWaitMap.h
 *
 *  Created on: 2015年9月21日
 *      Author: meteorgan
 */

#ifndef SERVER_PARTICIPANTWAITMAP_H_
#define SERVER_PARTICIPANTWAITMAP_H_

#include <map>


class participantWaitMap {
public:
	participantWaitMap();
	virtual ~participantWaitMap();

private:
	std::mutex mutex;
	std::condition_variable cv;
};

#endif /* SERVER_PARTICIPANTWAITMAP_H_ */
