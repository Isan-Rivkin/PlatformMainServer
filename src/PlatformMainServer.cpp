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
#include "LAndR/AuthManager.h"
#include "Matching/MatchingManager.h"
#include "Protocol.h"
// db includes
#include "DB/AbstractDB.h"
#include "DB/BasicDB.h"
#include "DB/Entity.h"
#include <vector>
#include "File.h"
#include <string.h>
// utils
#include "SDKUtils/SDKUtils.h"
// random port
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


#define TEST_PORT 91196

using namespace std;
using namespace networkingLab;
class LoginDBTester : public MThread
{
	File * file;
public:
	void run(){}
	bool testEqualUser()
	{
		UserLoginDetails u1("isan","123"),u2("isan","123");
		u1.ip = "111";
		u1.port =222;
		u2.ip = "111";
		u2.port =222;
		if(u1 == u2)
			return true;
		return false;
	}
	bool testAPI()
	{
		AbstractDB * db = new BasicDB("src/DB/config.txt");
		db->loadConfig();
		// add a new entity. <param1,param2,...,param_n>
		vector<string> params;
		params.push_back("first");
		params.push_back("second");
		params.push_back("third");
		Entity * e = new Entity("1",params);
		db->addToTable(e);
		// print all entities
		vector<Entity*> entities =db->getAllTable();
		vector<Entity*>::iterator it = entities.begin();
		while(it != entities.end())
		{
			vector<string> _params = (*it)->getParams();
			vector<string>::iterator str_it = _params.begin();
			while(str_it != _params.end())
			{
				cout << (*str_it)<<",";
				str_it++;
			}
			cout<<endl;
			it++;
		}
		// is entity exist?

		vector<string> check;
		check.push_back("first");
		check.push_back("second");
		check.push_back("third");
		bool result = db->isEntityExist(new Entity("2",check));
		cout <<"Found Entity ? " << result <<endl;

		return true;
	}
	bool testFile(std::string & path,std::string & content)
	{
		file = new File(path);
		size_t written = file->write(content);
		char buffer[1024];
		size_t readen = file->read(buffer, sizeof(buffer));
		buffer[readen]='\0';
		file->close();
		if(strcmp(buffer,content.c_str()) == 0)
		{
			return true;
		}
		return false;
	}
	void createDBConfig()
	{
		BasicDB * db = new BasicDB("src/DB/config.txt");
		vector<pair<string,string> > config;
		pair<string,string> p1,p2,p3;
		p1.first = "table1.txt";
		p1.second="table1_name";
//		p2.first = "table2.txt";
//		p2.second="table2_name";
//		p3.first = "table3.txt";
//		p3.second="table3_name";
		config.push_back(p1);
//		config.push_back(p2);
//		config.push_back(p3);
		db->createConfig(config);
	}
	void loadDBConfig()
	{
		BasicDB * db = new BasicDB("src/DB/config.txt");
		db->loadConfig("src/DB/config.txt");
	}
	void UtilsAndParsing()
	{
		SDKUtils utils;
		UserLoginDetails details = utils.extractUserAuthDetails("ronen:123456");
		cout << "username->"<<details.name<<"pwd->"<<details.password<<endl;
	}
	void UtilsDBtoVec()
	{
		char buffer[500]={'a','b','c',',','1','2','3','\n','d','e','f',',','4','5','6','\n','\0'};
		SDKUtils utils;
		vector<vector<string> > rows =utils.extractTableRows(buffer, strlen(buffer));
		for(int i=0;i<rows.size();++i)
		{
			vector<string> row = rows.at(i);
			for(int j=0;j<row.size();++j)
			{
				cout << row.at(j)<<",";
			}
			cout <<endl;
		}
	}

};
class UsersTest : public MThread
{	public:
	SDKUtils utils;
	string details;
	virtual void run()
	{
		sleep(1.5);
		TCPSocket * client = new User("127.0.0.1",TEST_PORT);
		sleep(1.5);
		sendCommand(client, AUTH_REQ_LOGIN, details.c_str());
		sleep(1.5);
		sendCommand(client, MATCH_LIST, NULL);
		int cmd = utils.readCommand(client);
		cout <<"command " << cmd <<endl;
		cout<<" list : "<<endl;
		cout <<utils.readBufferdCommand(client)<<endl;;
	}
	int sendCommand(TCPSocket * socket,int cmd,const char* buff)
		{
			int cmdNet = htonl(cmd);
			int res = socket->write((char*)&cmdNet,4);
			if(res < 4)
			{
				return -1;
			}
			if(buff != NULL)
			{
				int len = strlen(buff);
				int lenNet = htonl(len);
				res= socket->write((char*)&lenNet,4);
				if(res < 0)
				{
					return -1;
				}
				res = socket->write(buff,len);
				if(res < len)
				{
					return -1;
				}
			}
			return 1;
		}

};
class Extended :public MThread
{
	virtual void run()
	{
		sleep(2);
		TCPSocket * client = new User("127.0.0.1",TEST_PORT);
		sleep(2);
		char buffer[100];
		buffer[0]='h';
		buffer[1]='i';
		buffer[2]='\0';
		string details = "shlomi:123456";
		sendCommand(client, AUTH_REQ_LOGIN, details.c_str());
	}
	int sendCommand(TCPSocket * socket,int cmd,const char* buff)
	{
		int cmdNet = htonl(cmd);
		int res = socket->write((char*)&cmdNet,4);
		if(res < 4)
		{
			return -1;
		}
		if(buff != NULL)
		{
			int len = strlen(buff);
			int lenNet = htonl(len);
			res= socket->write((char*)&lenNet,4);
			if(res < 0)
			{
				return -1;
			}
			res = socket->write(buff,len);
			if(res < len)
			{
				return -1;
			}
		}
		return 1;
	}
};
bool runListenerTest()
{
	cout <<"staring test ---- " <<endl;

	// server initialization
	MainController * handler = new MainController(TEST_PORT);
	Listener * listener = new Listener(TEST_PORT,handler);
	BasicDB * db = new BasicDB("src/DB/config.txt");
	AuthManager * authenticator = new AuthManager(handler,db);
	handler->initListener(listener);
	handler->initAuthenthicator(authenticator);
	handler->startController();
	// client 1
	Extended * client = new Extended();
	client->start();
	//handler->start();

	// client 2
	Extended * client2 = new Extended();
	client2->start();
//

	client2->waitForThread();
	client->waitForThread();
	cout << "test finished -----"<<endl;
	return true;
}


bool runLoginTest()
{
//	string path="testFile.txt";
//	string content = "this is a test of writing and reading to a file";
	LoginDBTester test;
//	if(test.testFile(path, content))
//	{
//		std::cout<<"Success ! writing/reading to file"<<std::endl;
//	}
//	else
//	{
//		std::cout<<"Failure ! writing/reading to file"<<std::endl;
//	}
//	test.loadDBConfig();
//	test.UtilsAndParsing();
//  test.UtilsDBtoVec();
//	test.testAPI();
	return true;
}
bool runMatcherTest()
{
	cout <<"staring test ---- " <<endl;

	// server initialization
	SDKUtils utils;
	int p = utils.generateRandom(2000, 9000);
	MainController * handler = new MainController(TEST_PORT);
	Listener * listener = new Listener(TEST_PORT,handler);
	BasicDB * db = new BasicDB("src/DB/config.txt");
	AuthManager * authenticator = new AuthManager(handler,db);
	MatchingManager * matcher = new MatchingManager(handler);
	handler->initListener(listener);
	handler->initAuthenthicator(authenticator);
	handler->initMatcher(matcher);
	handler->startController();
	// client 1
	UsersTest * client = new UsersTest();
	client->details="ronen:123456";
	sleep(2);
	client->start();
	sleep(9);
	// client 2
	UsersTest * client2 = new UsersTest();
	client2->details="haimke:123456";
	sleep(1);
	client2->start();
//

	//client2->waitForThread();
	client->waitForThread();
	cout << "test finished -----"<<endl;
	return true;

}
int main()
{
	cout << "staring MAIN  test ---- > "<<endl;
	//runLoginTest();
	//runListenerTest();
	runMatcherTest();
	// cruacial so that main wont die.
	sleep(25);
	cout << "finished MAIN test ---- > "<<endl;
	return 0;
}
