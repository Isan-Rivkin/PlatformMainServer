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
						details.ip = inet_ntoa(peer->getRemoteDescriptor().sin_addr);
						user_list.push_back(details);
//						cout << "[Matcher:] New Player: "<<details.name <<endl;
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
						char* buff;
						buff = utils.readBufferdCommand(peer,buff);
						User * tryPlayer = dynamic_cast<User*>(peer);
						UserLoginDetails player_x_det = tryPlayer->getUserDetails();
						UserLoginDetails player_y_det = utils.extractPeerDetails(buff);
						player_x_det.ip = inet_ntoa(peer->getRemoteDescriptor().sin_addr);
						vector<TCPSocket*> list =multipleListener->getAll();
						vector<TCPSocket*>::iterator socket_it= list.begin();
						User * u=NULL;
						while(socket_it != list.end())
						{
							u = dynamic_cast<User*>((*socket_it));
							if(u != NULL)
							{
								UserLoginDetails dets = u->getUserDetails();
								if(dets.name == player_y_det.name && dets.port == player_y_det.port)
								{
									break;
								}
							}
							socket_it++;
						}
						// send offer message
						// requester = {name:port}
						if(u!= NULL)
						{
							string x_details_str = player_x_det.ip;
							x_details_str +=":";
							 x_details_str += player_x_det.name + ":";
							x_details_str+=utils.toString(player_x_det.port);
							// parse player_x_det to char * and send
							utils.sendCommand(u, MATCH_OFFER_FROM_X, x_details_str.c_str());
							// done until for the ack msg from the player Y
						}
						break;
					}
					case MATCH_RANDOM:
					{
						/**
						 * x ask random
						 * find random != x
						 * send request with x's data
						 */
						User* tryUser = dynamic_cast<User*>(peer);
						UserLoginDetails x_player = tryUser->getUserDetails();
						x_player.ip = inet_ntoa(peer->getRemoteDescriptor().sin_addr);
						UserLoginDetails rand_player_details;
						vector<TCPSocket*> _sockets = multipleListener->getAll();
						int low =0,high= _sockets.size()-1;
						User * rand_user = NULL;
						int _random = 0;
						TCPSocket * sock_random;
						int seed=1;
						bool searching= true;
						do{
							_random = utils.generateRandom(low, high,seed);
							sock_random = _sockets[_random];
							rand_user = dynamic_cast<User*>(sock_random);
							rand_player_details = rand_user->getUserDetails();
							if(sock_random->getSocketFileDescriptor() != interrupter_fd){
								if(rand_user !=  NULL && (rand_player_details.port != x_player.port)
										&&(rand_player_details.name != x_player.name))
								{
									searching = false;
								}
							}
							seed ++;
							_random ++;
						}while(searching);

						if(rand_user!= NULL)
						{
							//send request with x's data
							string x_details_str = x_player.ip;
							x_details_str += ":";
							x_details_str += x_player.name + ":";
							x_details_str+=utils.toString(x_player.port);
							// parse player_x_det to char * and send
							utils.sendCommand(rand_user, MATCH_OFFER_FROM_X, x_details_str.c_str());
						   // done until for the ack msg from the player Y
						}
 						break;
					}
					case MATCH_ACK_OFFER_TO_X:
					{
						/**
						 * user Y is sending ack and ready to play with x
						 * TODO::
						 * find x again (data in message {name:port})
						 * match x and y
						 * remove from multiple
						 * refresh users list
						 * on the client side: waiting for ack + details
						 */
						char * ackOffer;
						ackOffer = utils.readBufferdCommand(peer, ackOffer);
						// the details of the requester
						UserLoginDetails dets_requester = utils.extractPeerDetails(ackOffer);
						// find the requester socket
						vector<TCPSocket*> _socks = multipleListener->getAll();
						vector<TCPSocket*>::iterator it = _socks.begin();
						User * requester_ = NULL;
						bool found_other = false;
						while(it != _socks.end())
						{
							requester_ = dynamic_cast<User*>((*it));
							if(requester_ != NULL)
							{
								if(requester_->getUserDetails().name == dets_requester.name &&
										requester_->getUserDetails().port == dets_requester.port)
								{
									found_other = true;
									break;
								}
							}
							it++;
						}
						if(!found_other)
						{
							break;
						}
						// send cmd + accepter details to requester
						User * tryAccepter = dynamic_cast<User*>(peer);
						if(tryAccepter != NULL)
						{
							UserLoginDetails accepter_dets = tryAccepter->getUserDetails();
							string accepter_dets_str = inet_ntoa(peer->getRemoteDescriptor().sin_addr);
							accepter_dets_str+=":";
							accepter_dets_str+=utils.toString(accepter_dets.port);
							// let the requester know there is ack + details of accepter

							utils.sendCommand(requester_, MATCH_OFFER_ACK_ACCEPTED_
							,accepter_dets_str.c_str());;
							/******************************************
							 *********** ADD HANDLER UPDATE ************
							 *********** add to busy state
							 *******************************************/
							handler->updateTupple(requester_,tryAccepter, MATCH_ID, MATCH_ROUTE_TO_BUSY);
							multipleListener->pullOut(tryAccepter);
							multipleListener->pullOut(requester_);
						}
						this->refreshUserList();
						break;
					}
					case MATCH_OFFER_NACK_REJECTED_:
					{
						/**
						 * let the requester know that there is a game decline
						 * requester is found using the name:port msg from the response
						 */
						char * ackOffer;
						ackOffer = utils.readBufferdCommand(peer, ackOffer);
						// the details of the requester
						UserLoginDetails dets_requester = utils.extractPeerDetails(ackOffer);
						// find the requester socket
						vector<TCPSocket*> _socks = multipleListener->getAll();
						vector<TCPSocket*>::iterator it = _socks.begin();
						User * requester_ = NULL;
						while(it != _socks.end())
						{
							requester_ = dynamic_cast<User*>((*it));
							if(requester_ != NULL)
							{
								if(requester_->getUserDetails().name == dets_requester.name
										&& requester_->getUserDetails().port == dets_requester.port)
								{
									break;
								}
							}
							it++;
						}
						// send cmd + accepter details to requester
						User * tryAccepter = dynamic_cast<User*>(peer);
						if(tryAccepter != NULL)
						{
							UserLoginDetails accepter_dets = tryAccepter->getUserDetails();
							string accepter_dets_str = inet_ntoa(peer->getRemoteDescriptor().sin_addr);
							accepter_dets_str+=":";
							accepter_dets_str+=utils.toString(accepter_dets.port);
							// let the requester know there is ack + details of accepter
							utils.sendCommand(requester_, MATCH_OFFER_NACK_REJECTED_
							,NULL);;
						}
						this->refreshUserList();
						break;
					}
					case MATCH_USER_EXIT:
					{
						multipleListener->pullOut(peer);
						peer->close();
						refreshUserList();
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
		interrupter_fd = socket->getSocketFileDescriptor();
		multipleListener->addSocket(socket);
		start();
		first_time = false;
	}
	else
	{
		cout << "[Matcher:] just got a new socket ! " <<endl;
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
void MatchingManager::refreshUserList()
{
	vector<TCPSocket*> sockets = multipleListener->getAll();
	vector<TCPSocket*>::iterator it_sockets = sockets.begin();
	vector<UserLoginDetails> updated_list;
	while(it_sockets != sockets.end())
	{
		User* tryUser = dynamic_cast<User*>((*it_sockets));
		if(tryUser != NULL)
		{
			updated_list.push_back(tryUser->getUserDetails());
		}
		it_sockets++;
	}
	this->user_list = updated_list;
}
} /* namespace networkingLab */


