/*
 * BusyManager.cpp
 *
 *  Created on: Aug 17, 2017
 *      Author: user
 */

#include "BusyManager.h"

namespace networkingLab {

BusyManager::BusyManager(HandlerManager* oHandler, AbstractDB * oDB_HS)
	:interrupt_socket(NULL),multipleListener(new MultipleTCPSocketsListener())
	,keepRunning(false),first_time(true),handler(oHandler),playerA(NULL)
	,playerB(NULL),db_highscores(oDB_HS)
{
	db_highscores->loadConfig();
}

BusyManager::~BusyManager() {
}

void BusyManager::run()
{
	keepRunning = true;
		while(keepRunning)
		{
			TCPSocket * peer =multipleListener->listenToSocket();
			int cmd = utils.readCommand(peer);
			if(cmd >0)
			{
				switch(cmd)
				{
				case BUSY_INTERRUPT_NEW:
				{
					cout <<"[Busy:] got 2 clients !" <<endl;
					if(playerA == NULL || playerB == NULL)
					{
						cout <<"[Busy:] Error: no 2 players."<<endl;
					}
					// player a
					User* tryUserA = dynamic_cast<User*>(playerA);
					UserLoginDetails detailsA = tryUserA->getUserDetails();
					detailsA.ip = inet_ntoa(tryUserA->getRemoteDescriptor().sin_addr);
					detailsA.port = tryUserA->getUserDetails().port;
					detailsA.name = tryUserA->getUserDetails().name;
					multipleListener->addSocket(playerA);
					// player b
					User* tryUserB = dynamic_cast<User*>(playerB);
					UserLoginDetails detailsB = tryUserB->getUserDetails();
					detailsB.ip = inet_ntoa(tryUserA->getRemoteDescriptor().sin_addr);
					detailsB.port = tryUserB->getUserDetails().port;
					detailsB.name = tryUserB->getUserDetails().name;
					multipleListener->addSocket(playerB);
					// add users as a pair to list
					pair<UserLoginDetails,UserLoginDetails> pair;
					pair.first = detailsA;
					pair.second = detailsB;
					_pairs.push_back(pair);
					break;
				}
				case BUSY_REQ_HS:
				{
					break;
				}
				case BUSY_SAVE_HS:
				{
					/**
					 * read peer score
					 * identify peer name
					 * save to db{name:score}
					 * send to user the high_scores
					 * return the user back to the Matcher
					 */
					char * score_buff;
					score_buff = utils.readBufferdCommand(peer, score_buff);
					string str_score = "";
					string str_name ="";
					for(size_t i = 0; i<strlen(score_buff);++i)
					{
						str_score+=score_buff[i];
					}
					User* tryUser = dynamic_cast<User*>(peer);
					if(tryUser != NULL)
					{
						str_name = tryUser->getUserDetails().name;
						vector<string> params;
						params.push_back(str_name);
						params.push_back(str_score);
						Entity * entity = new Entity("",params);
						db_highscores->addToTable(entity);
					}
					vector<Entity*> all_table = db_highscores->getAllTable();
					parseHighScores(all_table);
					utils.sendCommand(peer,BUSY_REQ_HS,parseHighScores(all_table));
					handler->update(peer, BUSY_ID);
					break;
				}
				case BUSY_STOP_GAME:
				{
					break;
				}
				default:
				{
					cout <<"[Busy:] unrecognized command."<<endl;
					break;
				}
				}
			}
		}

}

void BusyManager::handle(TCPSocket* playerA,TCPSocket * playerB)
{
	if(first_time)
	{
		multipleListener->addSocket(playerA);
		start();
		first_time = false;
	}
	else
	{
		this->playerA = playerA;
		this->playerB = playerB;
		interrupt(BUSY_INTERRUPT_NEW);
	}
}

void BusyManager::setInterrupter(TCPSocket* oInterrupter)
{
	this->interrupt_socket = oInterrupter;
}

void BusyManager::interrupt(int interrupt_cmd)
{
	int cmdNet = htonl(interrupt_cmd);
		int res =interrupt_socket->write((char*)&cmdNet,4);
		if(res <4)
		{
			cout<<"Error: interruption failed."<<endl;
		}
}

const char* BusyManager::parseHighScores(vector<Entity*> entities)
{
	vector<Entity*>::iterator it = entities.begin();
	string str_hs="";
	while(it!= entities.end())
	{
		vector<string> params = (*it)->getParams();
		if(params.size()<=2)
		{
			str_hs+= params[0];
			str_hs+=",";
			str_hs+=params[1];
			str_hs+='\n';
		}
		it++;
	}
	return str_hs.c_str();
}

} /* namespace networkingLab */
