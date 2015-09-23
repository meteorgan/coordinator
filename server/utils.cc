/*
 * utils.cc
 *
 *  Created on: 2015年9月22日
 *      Author: meteorgan
 */

#include "include/utils.hh"

double now() {
	struct timeval val;
	gettimeofday(&val, nullptr);
	return (val.tv_sec + (val.tv_usec * 1.0) / 1000000);
}
