/*
 * MainController.cpp
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#include "MainController.h"

namespace networkingLab {

MainController::MainController(size_t listener_port):
		listener_port(listener_port)
{
	matcher = NULL;
	listener = NULL;
	authenthicator = NULL;
	busy_manager = NULL;
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

void MainController::updateTupple(TCPSocket* peerA, TCPSocket* peerB, int protocol_id,
		int protocol_specific=-1)
{
	switch(protocol_id)
	{
	case MATCH_ID:
	{
		busy_manager->handle(peerA, peerB);
		break;
	}
	default:
	{
		break;
	}
	}
}

void MainController::update(TCPSocket * peer, int protocol_id, int protocol_specific=-1)
{
	int flag = 0;
	switch(protocol_id)
	{
	case AUTH_ID:
	{
		matcher->handle(peer);
		flag =1;
		break;
	}
	case LISTEN_ID:
	{
		switch(protocol_specific)
		{
			case ROUTE_TO_AUTH:
			{
				authenthicator->handle(peer);
				break;
			}
			case ROUTE_TO_MATCH:
			{
				matcher->handle(peer);
				break;
			}
			case ROUTE_TO_BUSY:
			{
 				busy_manager->handle(peer, NULL);
				break;
			}
		}
		break;
	}
	case BUSY_ID:
	{
		matcher->handle(peer);
		break;
	}
	}
}

void MainController::startController()
{
	this->start();
}

void MainController::generateListenerInterrupter()
{
	TCPSocket * interrupter = new TCPSocket(SERVER_IP,listener_port);
	authenthicator->setInterrupter(interrupter);
}

void MainController::generateMatcherInterrupter()
{
	TCPSocket * interrupter = new TCPSocket(SERVER_IP,listener_port);
	matcher->setInterrupter(interrupter);
}
void MainController::generateBusyInterrupter()
{
	TCPSocket * interrupter = new TCPSocket(SERVER_IP,listener_port);
	busy_manager->setInterrupter(interrupter);
}
void MainController::initBusy(BusyManager* oBusy)
{
	this->busy_manager = oBusy;
}
void MainController::initAuthenthicator(AuthManager* oAuthenthicator)
{
	this->authenthicator = oAuthenthicator;
}

void MainController::initMatcher(MatchingManager* oManager)
{
	this->matcher = oManager;
}

void MainController::stop() {
}

void MainController::updateDeleteSession(const string peer_name)
{
	authenthicator->deleteSessionUser(peer_name);
}

void MainController::run() {
		listener->start();
		sleep(0.5);
		generateListenerInterrupter();
		generateMatcherInterrupter();
		generateBusyInterrupter();
		listener->waitForThread();
		authenthicator->waitForThread();
		matcher->waitForThread();
		busy_manager->waitForThread();
		cout <<"[MainController:] XXX listener/authenthicator thread has died. XXX" << endl;
}

} /* namespace networkingLab */



