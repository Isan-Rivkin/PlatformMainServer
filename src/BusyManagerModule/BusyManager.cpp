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
						break;
				}
				case BUSY_STOP_GAME:
				{
					/**
					 * read peer score
					 * identify peer name
					 * save to db{name:score}
					 * send to user the high_scores
					 * return the user back to the Matcher
					 */
					string hs_peer_name="";
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
						hs_peer_name = str_name;
						vector<string> params;
						params.push_back(str_name);
						params.push_back(str_score);
						Entity * entity = new Entity("",params);
						db_highscores->addToTable(entity);
					}
					else
					{
						cout <<"[Busy:] Couldn't find/cast the requested peer" <<endl;
					}
					vector<Entity*> all_table = db_highscores->getAllTable();
					vector<UserHighScoresData> orderd_hs = hs_logic.parseHighscores(all_table);
//					const char * hs_net = parseHighScores(orderd_hs);
					string hs_net =  parseHighScores(orderd_hs);;
					/**
					 * send full highscores list to player
					 */
					utils.sendCommand(peer,BUSY_STOP_GAME,hs_net.c_str());

					// deleted now temporary
					//
					// delete the pair from list
//					vector<pair<UserLoginDetails,UserLoginDetails> >::iterator it = _pairs.begin();
//					size_t peerPort = tryUser->getUserDetails().port;
//					while(it != _pairs.end())
//					{
//						string f_p = (*it).first.name;
//						string s_p = (*it).second.name;
//						size_t f_port =(*it).first.port;
//						size_t s_port = (*it).second.port;
//						if((f_p == hs_peer_name && f_port == peerPort)
//								|| (s_p == hs_peer_name && s_port == peerPort))
//						{
//							_pairs.erase(it);
//							it = _pairs.end();
//							break;
//						}
//						it++;
//					}
					handler->update(peer, BUSY_ID);
					multipleListener->pullOut(peer);
					break;
				}
				default:
				{
					cout <<"[Busy:] unrecognized command:"<< cmd <<endl;
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

string BusyManager::parseHighScores(vector<UserHighScoresData> sorted_hs)
{
	vector<UserHighScoresData>::iterator it = sorted_hs.begin();
	string str_hs="";
	while(it!= sorted_hs.end())
	{
			str_hs+= (*it).name;
			str_hs+=",";
			str_hs+=utils.toString((*it).score);
			str_hs+=",";
			str_hs+=utils.toString((*it).winnings);
			str_hs+='\n';
			it++;

	}
	return str_hs;
}



} /* namespace networkingLab */
