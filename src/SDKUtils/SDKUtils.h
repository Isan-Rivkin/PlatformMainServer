/*
 * SDKUtils.h
 *
 *  Created on: Aug 14, 2017
 *      Author: user
 */

#ifndef SDKUTILS_SDKUTILS_H_
#define SDKUTILS_SDKUTILS_H_
#include <strings.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include "../Protocol.h"
#include "../DB/Entity.h"
#include "TCPSocket.h"
/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>

using namespace std;
namespace networkingLab
{
struct UserLoginDetails
{
	string name;
	string password;
	string ip;
	TCPSocket * _socket;
	size_t port;
	UserLoginDetails():ip(""),name(""),password(""),_socket(NULL),port(0){}
	UserLoginDetails(const UserLoginDetails& other)
	{
		name = other.name;
		ip=other.ip;
		port = other.port;
		_socket=other._socket;
	}
	UserLoginDetails(const string& oName, const string& pwd,TCPSocket *oSock = NULL)
	{
		ip="";
		port = 0;
		name = oName;
		password = pwd;
		_socket = oSock;
	}
	bool operator==(const UserLoginDetails other)
	{
		if(other.name != name || other.password != password || other.port != port || other.ip != ip )
			return false;
		return true;
	}
};
class SDKUtils {
public:
	SDKUtils();
	virtual ~SDKUtils();
	/**
	 * parse user name and password -> user_name:password
	 * return: struct with both of them.
	 */
	virtual UserLoginDetails extractUserAuthDetails(const string & userDetails);
	/**
	 * char * containins :
	 * param1,param2, ... paramn
	 * ...
	 * parse each row into vector<string>
	 * return collection: vector<vector<string>> ----> all the rows
	 */
	 vector<vector<string> > extractTableRows(const char * buffer, size_t len);
	 vector<Entity*> extractAllEntities(const char * buffer, size_t len);
	 /**
	  * send a command protocol over TCP
	  * Socket from, cmd protocol, buffer or NULL
	  */
	 int sendCommand(TCPSocket * socket,int cmd,const char* buff);
	 /**
	  * generate random number
	 */
	 int generateRandom(int low_bound,int high_bound);
	 int generateRandom(int low_bound,int high_bound,int seed);
	 /**
	  * cast size_t/int to string
	  */
	 string toString(size_t num);
	 /**
	  * prase MATCH_X_WITH_Y from name:port to struct
	  */
	 UserLoginDetails extractPeerDetails(const char * name_port)const;
	 /**
	  * read command from socket by protocol
	  */
	 int readCommand(TCPSocket * sock)const;
	 /**
	  * read bufferd command followed after protocol command
	  */
	 char* readBufferdCommand(TCPSocket * sock, char * deletee) const;
	 /**
	  * extract client port given a name from list {name:ip:port/n...}
	  */
	 size_t getClientPortFromList(const string& client_name,const char* list,size_t len)const;
	 /**
	  * cast string number to size_t
	  */
	 size_t toSize(const string& number_str)const;
};

} /* namespace networkingLab */

#endif /* SDKUTILS_SDKUTILS_H_ */
