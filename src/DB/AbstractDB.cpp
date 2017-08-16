/*
 * AbstractDB.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "AbstractDB.h"

namespace networkingLab {

AbstractDB::AbstractDB(const string& pConfig_path):config_path(pConfig_path)
{
	this->configManager = new File(config_path);
	//loadConfig(config_path);
}

AbstractDB::~AbstractDB()
{
	this->configManager->close();
}

void AbstractDB::loadConfig(const string& path)
{
	int counter = 0;
	SDKUtils utils;
	char buffer[50000];
	size_t bytes = this->configManager->read(buffer, 50000);
	buffer[bytes] = '\0';
	vector<Entity*> configs = utils.extractAllEntities(buffer, bytes);
	// parse names
	for(size_t i =0; i<configs.size(); ++i)
	{
		if(configs[i]->getParams().size()>=2)
		{
			pair<string,string> route_name;
			route_name.first = configs[i]->getParams().at(0);
			route_name.second = configs[i]->getParams().at(1);
			if(counter == 0){instance_table = route_name.first;counter++;}
		}
	}
	//instance_table =
}
void AbstractDB::loadConfig()
{
	loadConfig(this->config_path);
}

void AbstractDB::createConfig(vector<pair<string, string> > tableRout_tableName)
{
		vector<pair<string,string> >::iterator it = tableRout_tableName.begin();
		while(it != tableRout_tableName.end())
		{
			pair<string,string> rout_name= *(it);
			string route = rout_name.first;
			string name = rout_name.second;
			string row = route +","+name + "\n";
			this->configManager->append(row);
			it++;
		}
		this->configManager->close();
}
} /* namespace networkingLab */
