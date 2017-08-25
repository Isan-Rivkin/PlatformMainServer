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
#include "BusyManagerModule/BusyManager.h"
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
	BusyManager * busy_manager;
	public:
		MainController(size_t listener_port);
		virtual ~MainController();
	// init methods
		 virtual void initListener(Listener * oListener);
		 virtual void initAuthenthicator(AuthManager * oAuthenthicator);
		 virtual void initMatcher(MatchingManager * oManager);
		 virtual void initBusy(BusyManager * oBusy);
		 virtual void generateListenerInterrupter();
		 virtual void generateMatcherInterrupter();
		 virtual void generateBusyInterrupter();
	public:
	// update methods
		virtual void update(const string & query);
		virtual void update(TCPSocket * peer, int protocol_id, int protocol_specific);
		virtual void updateTupple(TCPSocket * peerA,TCPSocket * peerB ,int protocol_id, int protocol_specific);
		virtual void updateDeleteSession(const string peer_name);
	public:
	// operational methods
		virtual void startController();
		virtual void stop();
		virtual void run();
};

} /* namespace networkingLab */

#endif /* SRC_MAINCONTROLLER_H_ */
