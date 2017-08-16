/*
 * User.cpp
 *
 *  Created on: Aug 12, 2017
 *      Author: user
 */

#include "User.h"

namespace networkingLab {



User::User(size_t pPort):TCPSocket(pPort){}
User::User(const std::string& pPeerIP, size_t pPort):TCPSocket(pPeerIP, pPort){}
User::User(int socket_fd, sockaddr_in* pLocal, sockaddr_in* pRemote)
:TCPSocket(socket_fd,pLocal,pRemote){}


User::~User() {
	// TODO Auto-generated destructor stub
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

void User::setUserDetails(const UserLoginDetails details)
{
	this->user_details.name = details.name;
	this->user_details.password=details.password;
	this->user_details._socket = details._socket;
	this->user_details.port = details.port;
}


UserLoginDetails User::getUserDetails()const
{
	return user_details;
}

} /* namespace networkingLab */

