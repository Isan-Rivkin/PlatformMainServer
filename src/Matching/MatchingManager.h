/*
 * MatchingManager.h
 *
 *  Created on: Aug 15, 2017
 *      Author: user
 */

#ifndef MATCHING_MATCHINGMANAGER_H_
#define MATCHING_MATCHINGMANAGER_H_
#include "MultipleTCPSocketsListener.h"
#include "../HandlerManager.h"
#include "MThread.h"
#include "../Protocol.h"
#include "TCPSocket.h"
#include "../User.h"
#include <iostream>
#include "string.h"
#include "strings.h"
#include <vector>
//utils
#include "../SDKUtils/SDKUtils.h"

#include <stdio.h>
#include <arpa/inet.h>

namespace networkingLab
{

class MatchingManager : public MThread
{
private:
	TCPSocket * interrupt_socket;
	TCPSocket * userInQueue;
	HandlerManager * handler;
	MultipleTCPSocketsListener * multipleListener;
	vector<UserLoginDetails> user_list;
	bool keepRunning,first_time;
	SDKUtils utils;

public:
	MatchingManager(HandlerManager * oHandler);
	virtual ~MatchingManager();
public:

	virtual void run();
	// handler new user
	void handle(TCPSocket * socket);
	// interruption related
	void setInterrupter(TCPSocket * oInterrupter);
	void interrupt(int interrupt_cmd);

private:
	// generate list by request from UserLoginDetails -> char* <name:ip:port:/n>
	string generateUserList();
};

} /* namespace networkingLab */

#endif /* MATCHING_MATCHINGMANAGER_H_ */
