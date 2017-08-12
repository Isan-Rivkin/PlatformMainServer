/*
 * Listener.cpp
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#include "Listener.h"

namespace networkingLab {

Listener::~Listener()
{
}
networkingLab::Listener::Listener(size_t port,HandlerManager * oHandler):
		handler(oHandler),keepRunning(false)
{
	this->listenerSocket = new TCPSocket(port);
	port_listener = port;
}

void networkingLab::Listener::run()
{
	keepRunning = true;
	listenerSocket->listen();
	std::cout<<"Listener alive on port : "<<port_listener<<endl;

		while(keepRunning)
		{
			TCPSocket * peer = listenerSocket->accept();
			cout <<"[Listener:] new connection"<<endl;
			this->handler->update(peer);
		}
}

} /* namespace networkingLab */


