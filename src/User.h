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

using namespace std;

namespace networkingLab
{
	class User : public TCPSocket
	{
	private:
		string user_name;
		public:
			//User();
			// client ctor
			User(const std::string & pPeerIP, size_t pPort);
			//returned socket ctor
			User(int socket_fd, sockaddr_in * pLocal, sockaddr_in * pRemote);
			virtual ~User();
			virtual TCPSocket* accept();
	};

} /* namespace networkingLab */

#endif /* USER_H_ */
