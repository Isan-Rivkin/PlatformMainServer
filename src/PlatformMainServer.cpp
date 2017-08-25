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
#include "BusyManagerModule/BusyManager.h"
#include "BusyManagerModule/HighScoresLogic.h"
#include "Matching/MatchingManager.h"
#include "Protocol.h"
// db includes
#include "DB/AbstractDB.h"
#include "DB/BasicDB.h"
#include "DB/Entity.h"
#include <vector>
#include "File.h"
#include <string.h>
#include "DB/LoginDB.h"
// utils
#include "SDKUtils/SDKUtils.h"
// hashing
#include "Coder/EntitityCoder.h"

// random port
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


#define TEST_PORT 14487

using namespace std;
using namespace networkingLab;
static size_t MAIN_PORT=0;
class LoginDBTester : public MThread
{
	File * file;
public:
	void run(){}
	void print(vector<Entity*> ents)
	{
		for(size_t i=0;i<ents.size();++i)
		{
			cout << "Entity #"<<i<<" ";
			for(size_t j=0;j<ents[i]->getParams().size();++j)
			{
				cout <<ents[i]->getParams()[j]<<" , ";
			}
			cout <<endl;
		}
	}
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
		BasicDB * db_hs = new BasicDB("src/DB/hs_config.txt");
		db_hs->loadConfig();
		vector<string> params;

		//add entities highscores

//		params.push_back("avi");
//		params.push_back("21");
//		vector<string> params2;
//	    params2.push_back("yarden");
//		params2.push_back("69");
//		Entity * e = new Entity("",params);
//		Entity * e2 = new Entity("",params2);
//		db_hs->addToTable(e);
//		db_hs->addToTable(e2);
		HighScoresLogic logic;
		vector<UserHighScoresData> hs = logic.parseHighscores(db_hs->getAllTable());
		for(size_t i=0;i<hs.size();++i)
		{
			cout << "=============" <<endl;
			cout << "name: " << hs[i].name<<endl;
			cout << "score: " <<hs[i].score<<endl;
			cout << "winnings: " <<hs[i].winnings <<endl;
			cout << "=============" <<endl;
		}
//

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
	/**
	 * connect 2 x,y
	 * login
	 * x asks for y
	 * y send ack
	 * x read ack
	 * passed to busy
	 * declare end game on x,y + send each score
	 * print hs result x,y
	 */
	void runEndGame()
	{
		sleep(1.5);
								TCPSocket * client_x = new User("127.0.0.1",MAIN_PORT);
								details = "ronen:123456";
								sleep(1.5);
								sendCommand(client_x, AUTH_REQ_LOGIN, details.c_str());
								sleep(2);
								// connect y
								TCPSocket * client_y = new User("127.0.0.1",MAIN_PORT);
								sleep(1.5);
								details ="haimke:123456";
								sendCommand(client_y, AUTH_REQ_LOGIN, details.c_str());
								sleep(2);
								sendCommand(client_x, MATCH_RANDOM, NULL);
								sleep(3);
								// random t reads the offer :
								int cmd = utils.readCommand(client_y);
								char buffer[1000];
								char * offer= utils.readBufferdCommand(client_y, buffer);
								cout << "offer details |" <<offer<<"|"<<endl;
								sleep(1);
								cout << " sended ack " <<endl;
								utils.sendCommand(client_y, MATCH_ACK_OFFER_TO_X, offer);
								sleep(1.5);
								// x reads the ack and details of the accepter
								utils.readCommand(client_x);
								char * b;
								b = utils.readBufferdCommand(client_x, b);
								cout << b << " has accepted to play with you(x) ! "<<endl;
								sleep(5);
								/**********************************************
								 **************Actual end game test ***********
								 **********************************************/
								// update end game
								string scores_x = "56";
								int sended = utils.sendCommand(client_x, BUSY_STOP_GAME, scores_x.c_str());
								if(sended != 1)
									cout << "did not send the command" <<endl;
								else
									cout << " success sending the cmd " <<endl;
								// read scores for x :
								cout << "readin "<<endl;
								utils.readCommand(client_x);
								cout << "readed cmd " <<endl;
		char * buff_hs;
		buff_hs = utils.readBufferdCommand(client_x, buff_hs);
		cout << " got highscores: " <<endl;
		cout <<buff_hs<<endl;
		sleep(1);
		string scores_y = "69";
		sleep(1);
		utils.sendCommand(client_y, BUSY_STOP_GAME, scores_y.c_str());

	}
	/**
	 * connect 2 x,y
	 * x asks random
	 * server offers y to play
	 * y ack
	 * x accept the ack
	 * x and y are passed to the busy.
	 */
	virtual void RunBusyLoginTest()
	{

		sleep(1.5);
							TCPSocket * client_x = new User("127.0.0.1",MAIN_PORT);
							details = "ronen:123456";
							sleep(1.5);
							sendCommand(client_x, AUTH_REQ_LOGIN, details.c_str());
							sleep(2);
							// connect y
							TCPSocket * client_y = new User("127.0.0.1",MAIN_PORT);
							sleep(1.5);
							details ="haimke:123456";
							sendCommand(client_y, AUTH_REQ_LOGIN, details.c_str());
							sleep(2);
							sendCommand(client_x, MATCH_RANDOM, NULL);
							sleep(3);
							// random t reads the offer :
							int cmd = utils.readCommand(client_y);
							char buffer[1000];
							char * offer= utils.readBufferdCommand(client_y, buffer);
							cout << "offer details |" <<offer<<"|"<<endl;
							sleep(1);
							cout << " sended ack " <<endl;
							utils.sendCommand(client_y, MATCH_ACK_OFFER_TO_X, offer);
							sleep(1.5);
							// x reads the ack and details of the accepter
							utils.readCommand(client_x);
							char * b;
							b = utils.readBufferdCommand(client_x, b);
							cout << b << " has accepted to play with you ! "<<endl;

	}
	/**
	 * connect 2 x and y
	 * x asks random
	 * server offers y to play
	 * y nack/ack-.startSession
	 */
	virtual void RunRandomMatchTest()
	{
		sleep(1.5);
						TCPSocket * client_x = new User("127.0.0.1",MAIN_PORT);
						details = "ronen:123456";
						sleep(1.5);
						sendCommand(client_x, AUTH_REQ_LOGIN, details.c_str());
						sleep(2);
						// connect y
						TCPSocket * client_y = new User("127.0.0.1",MAIN_PORT);
						sleep(1.5);
						details ="haimke:123456";
						sendCommand(client_y, AUTH_REQ_LOGIN, details.c_str());
						sleep(2);
						sendCommand(client_x, MATCH_RANDOM, NULL);
						sleep(3);
						// random t reads the offer :
						int cmd = utils.readCommand(client_y);
						char buffer[1000];
						char * offer= utils.readBufferdCommand(client_y, buffer);
						cout << "offer details |" <<offer<<"|"<<endl;
						sleep(1);
						cout << "sended nack " <<endl;
						utils.sendCommand(client_y, MATCH_OFFER_NACK_REJECTED_, offer);
						sleep(1.5);
						int recived_nack = utils.readCommand(client_x);
						if(recived_nack == MATCH_OFFER_NACK_REJECTED_)
						{
							cout << "User has rejected you ! :(" <<endl;
						}
//						cout << " sended ack " <<endl;
//						utils.sendCommand(client_y, MATCH_ACK_OFFER_TO_X, offer);
						sleep(1.5);
						// x reads the ack and details of the accepter
//						utils.readCommand(client_x);
//						char * b;
//						b = utils.readBufferdCommand(client_x, b);
//						cout << b << " has accepted to play with you ! "<<endl;
	}
	// add 2 players
	// x offer y to play
	// y reads the offer and prints
	virtual void runMatcherXOfferYTest()
	{
//		// connect x
//			sleep(1.5);
//			TCPSocket * client_x = new User("127.0.0.1",MAIN_PORT);
//			details = "ronen:123456";
//			sleep(1.5);
//			sendCommand(client_x, AUTH_REQ_LOGIN, details.c_str());
//			sleep(2);
//			// connect y
//			TCPSocket * client_y = new User("127.0.0.1",MAIN_PORT);
//			sleep(1.5);
//			details ="haimke:123456";
//			sendCommand(client_y, AUTH_REQ_LOGIN, details.c_str());
//			sleep(1);
//			// ask for the players list :
//			utils.sendCommand(client_x, MATCH_LIST, NULL);
//			utils.readCommand(client_x);
//			char * b;
//			b = utils.readBufferdCommand(client_x, b);
//			cout << " LIST OF PLAYERS FROM THE SERVER: " <<endl;
//			cout<<b<<endl;
//			// x offer y to play
//			string y_details = details;
//			size_t haimkes_port =utils.getClientPortFromList("haimke", b, strlen(b));
//			y_details = "haimke:";
//			y_details+=utils.toString(haimkes_port);
//			utils.sendCommand(client_x, MATCH_MATCH_Y, y_details.c_str());
//			sleep(3);
//			// y prints the offer
//			int cmd2 = utils.readCommand(client_y);
//			char buffer[1000];
//			char * offer= utils.readBufferdCommand(client_y, buffer);
//			cout << "offer details |" <<offer<<"|"<<endl;
//			sleep(1);
//			cout << " sended ack " <<endl;
//			utils.sendCommand(client_y, MATCH_ACK_OFFER_TO_X, offer);
//			sleep(1.4);
	}
	virtual void run()
	{
		//RunBusyLoginTest();
		runEndGame();
	}
//	virtual void run()
//	{
//		sleep(1.5);
//		TCPSocket * client = new User("127.0.0.1",TEST_PORT);
//		sleep(1.5);
//		sendCommand(client, AUTH_REQ_LOGIN, details.c_str());
//		sleep(1.5);
//		string other = "666.666.666:12546";
//		sendCommand(client, MATCH_MATCH_Y, other.c_str());
//		int cmd = utils.readCommand(client);
//		cout <<"command " << cmd <<endl;
//		cout<<" list : "<<endl;
//		char buffer[1000]
//		cout <<utils.readBufferdCommand(client,buffer)<<endl;
//	}
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
	test.UtilsAndParsing();
//  test.UtilsDBtoVec();
//	test.testAPI();
	return true;
}

bool runMatcherTest()
{
	cout <<"staring test ---- " <<endl;
	//initAllConfig();
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
bool initAllConfig()
{
	// server initialization
	SDKUtils utils;

//	int p1 = utils.generateRandom(2500, 9000);
//	MAIN_PORT = (size_t)p1;
	MainController * handler = new MainController(SERVER_PORT);
	Listener * listener = new Listener(SERVER_PORT,handler);
	EntitityCoder * coder= new EntitityCoder();
	//LoginDB * db = new LoginDB(coder,"src/DB/config.txt");
	LoginDB * db = new LoginDB(coder,"config.txt");
	AuthManager * authenticator = new AuthManager(handler,db);
	MatchingManager * matcher = new MatchingManager(handler);
	//BasicDB * db_hs = new BasicDB("src/DB/hs_config.txt");
	BasicDB * db_hs = new BasicDB("hs_config.txt");
	BusyManager * busy = new BusyManager(handler,db_hs);
	handler->initListener(listener);
	handler->initAuthenthicator(authenticator);
	handler->initMatcher(matcher);
	handler->initBusy(busy);
	handler->startController();
	handler->waitForThread();
	return true;
}
bool runMatcherPeerTest()
{

	initAllConfig();
	UsersTest * test = new UsersTest();
	sleep(2);
	test->run();
	cout << " peer test has ended ------ >> " <<endl;
	return 0;
}
bool runCoderTest()
{
// init few entities
	vector<string> e1_p,e2_p;
	e1_p.push_back("isan");
	e1_p.push_back("123");
	e2_p.push_back("nuni");
	e2_p.push_back("321");
	Entity * e1 = new Entity("",e1_p);
	Entity * e2 = new Entity("",e2_p);
	vector<Entity*> ents;
	ents.push_back(e1);
	ents.push_back(e2);

	// start hashing
	EntitityCoder coder;

	// encode
	coder.encode(ents);
	LoginDBTester ut;
	cout <<"Encoded:" <<endl;
	ut.print(ents);
	cout << "bbottom line : " << endl;
			cout << ents[0]->getParams()[1] <<endl;
	coder.decode(ents);
	cout << "Decoded:" <<endl;
	ut.print(ents);
	cout << "bbottom line : " << endl;
	cout << ents[0]->getParams()[1] <<endl;
}
int main()
{
	cout << "staring MAIN  test ---- > "<<endl;
	//runLoginTest();
	//runListenerTest();
	//runMatcherPeerTest();
	// cruacial so that main wont die.
	initAllConfig();
	//runCoderTest();
	cout << "finished MAIN test ---- > "<<endl;
	return 0;
}
