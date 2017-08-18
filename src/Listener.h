/*
 * Listener.h
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#ifndef SRC_LISTENER_H_
#define SRC_LISTENER_H_

#include "MThread.h"
#include "TCPSocket.h"
#include "HandlerManager.h"
#include <iostream>
#include "string.h"
#include "strings.h"
#include "User.h"
#include "Protocol.h"
namespace networkingLab {

class Listener : public MThread
{
private:
	bool keepRunning;
	TCPSocket * listenerSocket;
	 HandlerManager * handler;
	 size_t port_listener;
	 bool _first_LandR,_second_match,_third_busy;
public:
	Listener(size_t port, HandlerManager * oHandler);
	virtual ~Listener();
	virtual void run();
};

} /* namespace networkingLab */

#endif /* SRC_LISTENER_H_ */
