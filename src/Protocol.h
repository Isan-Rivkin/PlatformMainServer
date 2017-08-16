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
#define NEW_USER_LOGGED_IN 10
/********************************************************************************
 ************************ Listener Protocl **************************************
 ********************************************************************************/
#define LISTEN_ID 100
 // protocol specifics -> 3rd param
#define ROUTE_TO_AUTH 21
#define ROUTE_TO_MATCH 22

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
#endif /* SRC_PROTOCOL_H_ */
