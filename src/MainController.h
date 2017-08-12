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
namespace networkingLab {

class MainController :public HandlerManager
{
private:
	size_t listener_port;
	Listener * listener;

	public:
		MainController(size_t port);
		virtual ~MainController();
	// init methods
		virtual void initListener(Listener * oListener);
	// update methods
		virtual void update(const string & query);
		virtual void update(const TCPSocket * peer);
	// operational methods
		virtual void start();
		virtual void stop();
};

} /* namespace networkingLab */

#endif /* SRC_MAINCONTROLLER_H_ */
