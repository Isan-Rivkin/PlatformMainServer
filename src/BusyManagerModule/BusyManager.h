/*
 * BusyManager.h
 *
 *  Created on: Aug 17, 2017
 *      Author: user
 */

#ifndef BUSYMANAGERMODULE_BUSYMANAGER_H_
#define BUSYMANAGERMODULE_BUSYMANAGER_H_
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
//db
#include "../DB/AbstractDB.h"
//utils
#include "../SDKUtils/SDKUtils.h"
#include "HighScoresLogic.h"

#include <stdio.h>
#include <arpa/inet.h>

namespace networkingLab {

class BusyManager : public MThread
{
	MultipleTCPSocketsListener * multipleListener;
	HandlerManager             * handler;
	vector<pair<UserLoginDetails,UserLoginDetails> > _pairs;
	TCPSocket * interrupt_socket;
	TCPSocket * playerA;
	TCPSocket * playerB;
	AbstractDB * db_highscores;
	HighScoresLogic hs_logic;
	bool keepRunning,first_time;
	SDKUtils utils;
public:
	BusyManager(HandlerManager * oHandler, AbstractDB * oDB_HS);
	virtual ~BusyManager();
public:
	virtual void run();
	// handler new user
	void handle(TCPSocket * playerA,TCPSocket * playB);
	// interruption related
	void setInterrupter(TCPSocket * oInterrupter);
	void interrupt(int interrupt_cmd);
private:
	const char * parseHighScores(vector<Entity*> entities);
	string parseHighScores(vector<UserHighScoresData> sorted_hs);
};

} /* namespace networkingLab */

#endif /* BUSYMANAGERMODULE_BUSYMANAGER_H_ */
