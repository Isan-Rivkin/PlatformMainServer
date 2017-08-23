/*
 * SDKUtils.cpp
 *
 *  Created on: Aug 14, 2017
 *      Author: user
 */

#include "SDKUtils.h"

namespace networkingLab {

SDKUtils::SDKUtils() {
	// TODO Auto-generated constructor stub

}

SDKUtils::~SDKUtils() {
	// TODO Auto-generated destructor stub
}

UserLoginDetails SDKUtils::extractUserAuthDetails(const string& userDetails)
{
		size_t seperateIdx = userDetails.find(AUTH_DELIMETER);
		string user_name = userDetails.substr(0,seperateIdx);
		string password = userDetails.substr(seperateIdx+1,userDetails.size());
		UserLoginDetails details(user_name,password);
		return details;
}

/**
	 * char * containins :
	 * param1,param2, ... paramn
	 * ...
	 * parse each row into vector<string>
	 * return collection: vector<vector<string>> ----> all the rows
	 */

vector<vector<string> > SDKUtils::extractTableRows(const char* buffer, size_t len)
{
	vector<vector<string> > all_rows;
	vector<string> unparsed_rows;
	string row="";
	// extract all rows
	for(size_t i=0;i<len;++i)
	{
		if(buffer[i] !='\n')
		{
			row+=buffer[i];
			if( i == len-1)
			{
				unparsed_rows.push_back(string(row));
			}
		}
		else
		{
			unparsed_rows.push_back(string(row));
			row.clear();
		}
	}
	//for each row -> create vector
	for(size_t i =0;i<unparsed_rows.size();++i)
	{
		vector<string> parsed_row;
		string aRow = unparsed_rows[i];
		string aParam="";
		for(size_t j=0;j<aRow.length();++j)
		{
			if(aRow[j] != ',')
			{
				aParam+=aRow[j];
				if(j== aRow.length()-1)
				{
					parsed_row.push_back(aParam);
					aParam.clear();
				}
			}
			else if(aRow[j]==',')
			{
				parsed_row.push_back(string(aParam));
				aParam.clear();
			}
		}
		all_rows.push_back(parsed_row);
	}
	return all_rows;
}
vector<Entity*> SDKUtils::extractAllEntities(const char* buffer, size_t len)
{
	vector<vector<string> > result = extractTableRows(buffer,len);
	vector<Entity*> entities;
	for(size_t i =0;i<result.size();++i)
	{
		entities.push_back(new Entity("",result[i]));
	}
	return entities;
}
int SDKUtils::sendCommand(TCPSocket * socket,int cmd,const char* buff)
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
int SDKUtils::generateRandom(int low_bound, int high_bound)
{
	return generateRandom(low_bound, high_bound,0);
}
int SDKUtils::generateRandom(int low_bound, int high_bound,int seed)
{
	int val;
	 /* initialize random seed: */
	if(seed==0)
	  srand(time(NULL));
	else
	  srand(time(NULL)+seed);
	  /* generate secret number between 1 and 10: */
	  val = rand() % high_bound + low_bound;
	  return val;
}
string SDKUtils::toString(size_t num)
{
	    std::stringstream ss;
	    ss <<num;
	    std::string sService = ss.str();
	    return sService;
}

int SDKUtils::readCommand(TCPSocket* sock) const
{
	int command;
			char * buffer;
			int len;
			int ret = sock->read((char*)&command,4);
			if(ret >0)
			{
				command = ntohl(command);
				return command;
			}
			return -1;
}

UserLoginDetails SDKUtils::extractPeerDetails(const char * name_port)const
{

	UserLoginDetails user;
	string u_name="";
	string u_port="";
	size_t idx;
	for(size_t i=0;i<strlen(name_port);++i)
	{
		if(name_port[i] == ':')
		{
			idx = i;
			i = strlen(name_port);
			break;
		}
	}
	size_t i=0;
	while(name_port[i] != ':')
	{
		u_name+=name_port[i];
		i++;
	}
	i++;
	while(i<strlen(name_port))
	{
		u_port+=name_port[i];
		i++;
	}
	user.name = u_name;
	std::istringstream iss(u_port);
	size_t p;
	iss >> p;
	user.port = p;
	return user;
}

char* SDKUtils::readBufferdCommand(TCPSocket* sock,char * deletee) const
{
	char * buffer;
	int len;
	sock->read((char*)&len, 4);
	len=ntohl(len);
	buffer = new char[len];
	int bytes = sock->read(buffer, len);
	buffer[bytes] = '\0';

	return buffer;
}

size_t SDKUtils::getClientPortFromList(const string& client_name, const char* list,size_t len) const
{
	using namespace std;
	size_t count_delim=0;
	string full_list_str="";
	string str_port="";
	for(size_t i=0;i<len;++i)
	{
		full_list_str +=list[i];
	}
	size_t nameIdx = full_list_str.find(client_name);
	while(list[nameIdx] != '\n')
	{
		if(list[nameIdx] == ':')
		{
			count_delim++;
			if(count_delim == 2)
			{
				count_delim++;
				nameIdx++;
				while(list[nameIdx] != '\n')
				{
					str_port+= list[nameIdx];
					nameIdx++;
				}
				break;
			}
		}
		nameIdx++;
	}
	return toSize(str_port);
}


size_t SDKUtils::toSize(const string number_str) const
{
	using namespace std;
	std::istringstream iss(number_str);
	size_t port;
	iss >> port;
	return port;
}

} /* namespace networkingLab */


