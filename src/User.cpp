/*
 * User.cpp
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#include "User.h"

namespace networkingLab {

//User::User():TCPSocket(1555) {
//
//}

User::~User() {
	// TODO Auto-generated destructor stub
}

User::User(const std::string& pPeerIP, size_t pPort):TCPSocket(pPeerIP, pPort) {
}
User::User(int socket_fd, sockaddr_in* pLocal, sockaddr_in* pRemote):
		TCPSocket(socket_fd,pLocal,pRemote) {
}

TCPSocket* User::accept()
{
			socklen_t len = sizeof(mRemote);
			mCommunicationSockTCP = ::accept(socket_fd,(struct sockaddr *)&mRemote,&len);
			if(mCommunicationSockTCP<0)
			{
				perror("failed to accept connection");
				exit(1);
			}
			mPeerIP = mRemote.sin_addr.s_addr;
			mPeerPort = mRemote.sin_port;
			TCPSocket * connection_socket = new User(mCommunicationSockTCP,&mLocal, &mRemote);
			return connection_socket;
}

} /* namespace networkingLab */
