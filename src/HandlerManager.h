/*
 * HandlerManager.h
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#ifndef SRC_HANDLERMANAGER_H_
#define SRC_HANDLERMANAGER_H_

#include <iostream>
#include <string.h>
#include <strings.h>
#include "TCPSocket.h"
using namespace std;

namespace networkingLab {

class HandlerManager {
public:
	HandlerManager();
	virtual ~HandlerManager();
	//init
	// update methods
	virtual void update(const string & query)=0;
	virtual void update(const TCPSocket * peer)=0;
	// operational methods
	virtual void start()=0;
	virtual void stop()=0;
};

} /* namespace networkingLab */

#endif /* SRC_HANDLERMANAGER_H_ */
