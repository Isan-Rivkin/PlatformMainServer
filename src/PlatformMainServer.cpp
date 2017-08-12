//============================================================================
// Name        : PlatformMainServer.cpp
// Author      : Isan and Daniel
// Version     :
// Copyright   : Isan Rivkin and Daniel Hake
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TCPSocket.h"
#include "MainController.h"
#include "HandlerManager.h"
#include "Listener.h"
#include "MThread.h"
#include "User.h"

using namespace std;
using namespace networkingLab;

class Extended :public MThread
{
	virtual void run()
	{
		cout <<"zzz..."<<endl;
		sleep(1);
		cout<<"client: trying to connet" <<endl;

		User * client = new User("127.0.0.1",5555);
		cout <<"connected"<<endl;
	}
};
int main()
{
	cout <<"staring test ---- " <<endl;

	size_t port = 5555;
	HandlerManager * handler = new MainController(port);
	Listener * listener = new Listener(port,handler);
	MainController * d = (MainController*)handler;
	d->initListener(listener);
	Extended * client = new Extended();
	client->start();
	d->start();
	client->waitForThread();
	cout << "test finished -----"<<endl;
	return 0;
}
