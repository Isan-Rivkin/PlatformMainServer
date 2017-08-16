/*
 * MainController.h
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#ifndef SRC_MAINCONTROLLER_H_
#define SRC_MAINCONTROLLER_H_
#include "HandlerManager.h"
#include "Protocol.h"
#include "TCPSocket.h"
#include "Listener.h"
#include "LAndR/AuthManager.h"
#include "Matching/MatchingManager.h"
#include <string.h>
#include <strings.h>
#include <iostream>

using namespace std;
namespace networkingLab {

class MainController :public HandlerManager,public MThread
{
private:
	size_t listener_port;
	Listener * listener;
	AuthManager * authenthicator;
	MatchingManager * matcher;

	public:
		MainController(size_t listener_port);
		virtual ~MainController();
	// init methods
		 virtual void initListener(Listener * oListener);
		 virtual void initAuthenthicator(AuthManager * oAuthenthicator);
		 virtual void initMatcher(MatchingManager * oManager);
		 virtual void generateListenerInterrupter();
		 virtual void generateMatcherInterrupter();
	public:
	// update methods
		virtual void update(const string & query);
		virtual void update(TCPSocket * peer, int protocol_id, int protocol_specific);
	public:
	// operational methods
		virtual void startController();
		virtual void stop();
		virtual void run();
};

} /* namespace networkingLab */

#endif /* SRC_MAINCONTROLLER_H_ */
