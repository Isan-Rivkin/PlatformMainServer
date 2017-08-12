/*
 * MainController.cpp
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#include "MainController.h"

namespace networkingLab {

MainController::MainController(size_t port):
		listener_port(port)
{
	listener = NULL;
}

MainController::~MainController() {
	// TODO Auto-generated destructor stub
}
void MainController::initListener(Listener* oListener) {
	this->listener = oListener;
}
void MainController::update(const string& query)
{
	cout <<"Main Controller: " << query <<endl;
}

void MainController::update(const TCPSocket* peer) {
}

void MainController::start()
{
	listener->start();
	listener->waitForThread();
	cout <<"[MainController:] listener thread has died." << endl;
}

void MainController::stop() {
}

} /* namespace networkingLab */

