/*
 * AuthManager.h
 *
 *  Created on: Aug 13, 2017
 *      Author: user
 */

#ifndef LANDR_AUTHMANAGER_H_
#define LANDR_AUTHMANAGER_H_
#include <stdio.h>
#include <arpa/inet.h>

#include <iostream>
#include "string.h"
#include "strings.h"
#include <vector>

#include "MultipleTCPSocketsListener.h"
#include "../HandlerManager.h"
#include "MThread.h"
#include "../Protocol.h"
#include "TCPSocket.h"
#include "../User.h"

//utils
#include "../SDKUtils/SDKUtils.h"
#include "../SDKUtils/MiniHashMap.h"
// db
#include "../DB/AbstractDB.h"
#include "../DB/Entity.h"


using namespace std;
namespace networkingLab
{

class AuthManager : public MThread
{
private:
	HandlerManager * handler;
	bool keepRunning,first_time;
	MultipleTCPSocketsListener * multipleListener;
	TCPSocket * interrupt_socket;
	TCPSocket * userInQueue;
	 AbstractDB * db_users;
	 MiniHashMap * _sessions_map;
public:
	AuthManager(HandlerManager * oHandler,AbstractDB * oDB_users);
	virtual ~AuthManager();
	virtual void run();
	// handler new user
	void handle(TCPSocket * socket);
	// delete user from session list
	void deleteSessionUser(const string session_name);
	// interruption related
	void setInterrupter(TCPSocket * oInterrupter);
	void interrupt();
public:
	bool isUserExist(vector<string> user_details);
};

} /* namespace networkingLab */

#endif /* LANDR_AUTHMANAGER_H_ */
