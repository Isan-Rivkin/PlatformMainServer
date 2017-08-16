/*
 * AuthManager.cpp
 *
 *  Created on: Aug 13, 2017
 *      Author: user
 */

#include "AuthManager.h"

namespace networkingLab {

AuthManager::AuthManager(HandlerManager * oHandler,AbstractDB * oDB_users)
:handler(oHandler),keepRunning(false),first_time(true)
{
	db_users = oDB_users;
	db_users->loadConfig();
	userInQueue = NULL;
	interrupt_socket = NULL;
	multipleListener = new MultipleTCPSocketsListener();
}

AuthManager::~AuthManager() {
}

void AuthManager::run()
{
	keepRunning = true;
	while(keepRunning)
	{
		SDKUtils utils;
		TCPSocket * peer =multipleListener->listenToSocket();
		int command;
		char * buffer;
		int len;
		int ret = peer->read((char*)&command,4);
		if(ret >0)
		{
			command = ntohl(command);
			switch(command)
			{
			case AUTH_INTERRUPT:
			{
				multipleListener->addSocket(userInQueue);
				break;
			}
			case AUTH_REQ_REGISTER:
			{
				// read user register details
				peer->read((char*)&len, 4);
				len=ntohl(len);
				buffer = new char[len];
				int bytes = peer->read(buffer, len);
				buffer[bytes] = '\0';
				// msg: username:password
				UserLoginDetails user  = utils.extractUserAuthDetails(buffer);
				user.port = peer->getRemoteDescriptor().sin_port;
				user.ip = inet_ntoa(peer->getRemoteDescriptor().sin_addr);
				vector<string> params;
				params.push_back(user.name);
				params.push_back(user.password);
				Entity * registrant = new Entity("",params);
				User * tryUser = dynamic_cast<User*>(peer);
				if(tryUser == NULL)
					cout << "[L&M:] ERROR CANNOT CONVERT USER "<<endl;
				// process user to next state:

				// existing user name or password - X
				if(db_users->isEntityExist(registrant))
				{
					// send nack
					utils.sendCommand(peer, AUTH_NACK_LOGIN, NULL);
				}
				// ok to register - V
				else
				{
					this->db_users->addToTable(registrant);
					// send ack to user
					 utils.sendCommand(peer, AUTH_ACK_LOGIN, NULL);
					// remove from queue
					 multipleListener->pullOut(peer);
					 tryUser->setUserDetails(user);
					handler->update(peer,AUTH_ID);
				}
				break;
			}
			case AUTH_REQ_LOGIN:
			{
				// read user login details
				peer->read((char*)&len, 4);
				len=ntohl(len);
				buffer = new char[len];
				int bytes = peer->read(buffer, len);
				buffer[bytes] = '\0';
				// msg: username:password
				UserLoginDetails user  = utils.extractUserAuthDetails(buffer);
				user.port = peer->getRemoteDescriptor().sin_port;
				user.ip = inet_ntoa(peer->getRemoteDescriptor().sin_addr);
				vector<string> params;
				params.push_back(user.name);
				params.push_back(user.password);
				Entity * registrant = new Entity("",params);
				User * tryUser = dynamic_cast<User*>(peer);
				if(tryUser == NULL)
					cout << "[L&M:] ERROR CANNOT CONVERT USER "<<endl;
				// process user to next state:
				if(db_users->isEntityExist(registrant))
				{
					tryUser->setUserDetails(user);
					handler->update(peer, AUTH_ID);
					multipleListener->pullOut(peer);
				}
				else
				{
					// send nack
					utils.sendCommand(peer, AUTH_NACK_LOGIN, NULL);
				}
				break;
			}
			default:
			{
				cout <<"[Authenticator:] unrecognized command " << command <<endl;
				break;
			}
			}
		}

	}
}

// handle a new socket pre-auth

void AuthManager::handle(TCPSocket* socket)
{
	if(first_time)
	{
		multipleListener->addSocket(socket);
		start();
		first_time = false;
	}
	else
	{
		userInQueue = socket;
		interrupt();
	}
}

void AuthManager::setInterrupter(TCPSocket* oInterrupter)
{
	this->interrupt_socket = oInterrupter;
}

void AuthManager::interrupt()
{
		int cmdNet = htonl(AUTH_INTERRUPT);
		int res =interrupt_socket->write((char*)&cmdNet,4);
		if(res <4)
		{
			cout<<"Error: interruption failed."<<endl;
		}
}

bool AuthManager::isUserExist(vector<string> user_details)
{

}

} /* namespace networkingLab */
