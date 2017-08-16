/*
 * User.h
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#ifndef USER_H_
#define USER_H_
#include "TCPSocket.h"
#include <iostream>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#include <inttypes.h>
#include <netdb.h>

#include <arpa/inet.h>
#include "SDKUtils/SDKUtils.h"
using namespace std;

namespace networkingLab
{
	class User : public TCPSocket
	{
	private:
		SDKUtils utils;
		UserLoginDetails user_details;
		public:
			// server ctor
			User(size_t pPort);
			// client ctor
			User(const std::string & pPeerIP, size_t pPort);
			//returned socket ctor
			User(int socket_fd, sockaddr_in * pLocal, sockaddr_in * pRemote);
			virtual ~User();
			// override @return instance of User*
			virtual TCPSocket* accept();
			// user details
			void setUserDetails(const UserLoginDetails details);
			UserLoginDetails getUserDetails()const;
	};

} /* namespace networkingLab */

#endif /* USER_H_ */
