/*
 * MatchingManager.cpp
 *
 *  Created on: Aug 15, 2017
 *      Author: user
 */

#include "MatchingManager.h"

namespace networkingLab {


MatchingManager::MatchingManager(HandlerManager* oHandler)
:interrupt_socket(NULL),multipleListener(new MultipleTCPSocketsListener())
,keepRunning(false),first_time(true),handler(oHandler),userInQueue(NULL){}

MatchingManager::~MatchingManager() {
}

void MatchingManager::run()
{
	keepRunning = true;
	while(keepRunning)
	{
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
					case MATCH_INTERRUPT_NEW:
					{
						User* tryUser = dynamic_cast<User*>(userInQueue);
						UserLoginDetails details = tryUser->getUserDetails();
						user_list.push_back(details);
						cout << "[Matcher:] New Player: "<<details.name <<endl;
						multipleListener->addSocket(userInQueue);
						break;
					}
					case MATCH_INTERRUPT_REMOVE:
					{
						// read ip:port ->verify name
						//multipleListener->pullOut(ip,port)
						break;
					}
					case MATCH_LIST:
					{
						string raw_list = generateUserList();
						utils.sendCommand(peer, MATCH_LIST,raw_list.c_str());
						break;
					}
					case MATCH_MATCH_Y:
					{
						utils.readBufferdCommand(peer);
						break;
					}
					case MATCH_RANDOM:
					{

						break;
					}
					default:
					{
						cout <<"[Matcher:] unrecognized command " << command<<endl;
						break;
					}
					}
				}
	}
}

void MatchingManager::handle(TCPSocket* socket)
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
		interrupt(MATCH_INTERRUPT_NEW);
	}
}

void MatchingManager::setInterrupter(TCPSocket* oInterrupter)
{
	this->interrupt_socket = oInterrupter;
}

void MatchingManager::interrupt(int interrupt_cmd)
{
	int cmdNet = htonl(interrupt_cmd);
	int res =interrupt_socket->write((char*)&cmdNet,4);
	if(res <4)
	{
		cout<<"Error: interruption failed."<<endl;
	}
}

string MatchingManager::generateUserList()
{
		string str_buffer="";

		for(size_t i=0;i<user_list.size();++i)
		{
			str_buffer+=user_list[i].name;
			str_buffer+=":";
			str_buffer+=user_list[i].ip;
			str_buffer+=":";
			str_buffer+=utils.toString(user_list[i].port);
			str_buffer+="\n";
		}
		return str_buffer;
}

} /* namespace networkingLab */
