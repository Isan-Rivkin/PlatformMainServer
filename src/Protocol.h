/*
 * Protocol.h
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#ifndef SRC_PROTOCOL_H_
#define SRC_PROTOCOL_H_

/********************************************************************************
 ************************ Network Protocl ***************************************
 ********************************************************************************/
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7777
#define NEW_USER_LOGGED_IN 10
#define MAIN_ERROR_UNKOWN 40
// sent to matchier and busy both to exit completley
#define MAIN_CLIENT_EXIT 150
/********************************************************************************
 ************************ Listener Protocl **************************************
 ********************************************************************************/
#define LISTEN_ID 100
 // protocol specifics -> 3rd param
#define ROUTE_TO_AUTH 21
#define ROUTE_TO_MATCH 22
#define ROUTE_TO_BUSY 37
/********************************************************************************
 ************************ Authenthication Protocl *******************************
 ********************************************************************************/
// id used by controller to identify
#define AUTH_ID 101
// interrupt the listener on Auth
#define AUTH_INTERRUPT 11
// user asks to login
#define AUTH_REQ_LOGIN 12
// user asks to register
#define AUTH_REQ_REGISTER 13

// to user messages
// accept register/login
#define AUTH_ACK_LOGIN 14
// deny user login/register
#define AUTH_NACK_LOGIN 15

// params ----------------------------------------------------------------------
// delimeter seperating user name and password in a msg sent from client->server
#define AUTH_DELIMETER ":"

/********************************************************************************
 **************************** Matching Protocl **********************************
 ********************************************************************************/
// id used by controller to identify
#define MATCH_ID 102
// interrupt the listener on Match -> add a new socket
#define MATCH_INTERRUPT_NEW 16
// interrupt the listener on Match -> remove a socket
#define MATCH_INTERRUPT_REMOVE 17
// x asks for y
#define MATCH_MATCH_Y 18
// x asks for random
#define MATCH_RANDOM 19
// x asks for list
#define MATCH_LIST 20
// offer to play from x
#define MATCH_OFFER_FROM_X 25
// ack offer from player x to server
#define MATCH_ACK_OFFER_TO_X 26
// ack offer is accepted to the requester followed by other details {ip:port}
// from this point the requester will start game with the accepter using UDP
#define MATCH_OFFER_ACK_ACCEPTED_ 27
// nack to the ack above -> let the requester know other dont want to play.
#define MATCH_OFFER_NACK_REJECTED_ 28
// user asked to stop the game
#define MATCH_USER_EXIT 29
// identify command to handler manager -> pass to Busy
#define MATCH_ROUTE_TO_BUSY 30
/********************************************************************************
 ******************************** Busy Protocl **********************************
 ********************************************************************************/
// id
#define BUSY_ID 36
// identify command to handler manager -> pass to Matcher
#define BUSY_ROUTE_TO_MATCH 31
// user asks to stop the game
#define BUSY_STOP_GAME 32
// interrupt new players
#define BUSY_INTERRUPT_NEW 33
// player request high_scores
#define BUSY_REQ_HS 34
// each player sends : save game details {name:score}
#define BUSY_SAVE_HS 35
// start at 41!

#endif /* SRC_PROTOCOL_H_ */
