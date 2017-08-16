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
networkingLab::Listener::Listener(size_t port,HandlerManager * oHandler)
	:handler(oHandler),keepRunning(false),_first_LandR(true),_second_match(false)
{
	this->listenerSocket = new User(port);
	port_listener = port;
}

void networkingLab::Listener::run()
{
	keepRunning = true;
	listenerSocket->listen();
	std::cout<<"Listener alive on port : "<<port_listener<<endl;

		while(keepRunning)
		{
			if(_first_LandR)
			{
				TCPSocket * peer = listenerSocket->accept();
				cout <<"[Listener:] Authentication interrupter plugged."<<endl;
				this->handler->update(peer,LISTEN_ID,ROUTE_TO_AUTH);
				_first_LandR = false;
				_second_match = true;
			}
			else if(_second_match)
			{

				TCPSocket * peer = listenerSocket->accept();
				cout <<"[Listener:] Matcher interrupter plugged."<<endl;
				this->handler->update(peer,LISTEN_ID,ROUTE_TO_MATCH);
				_second_match = false;
			}
			else
			{
				TCPSocket * peer = listenerSocket->accept();
				cout <<"[Listener:] new connection"<<endl;
				this->handler->update(peer,LISTEN_ID,ROUTE_TO_AUTH);
			}
		}
}

} /* namespace networkingLab */


