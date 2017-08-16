/*
 * AbstractDB.h
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#ifndef ABSTRACTDB_H_
#define ABSTRACTDB_H_

#include "Entity.h"
#include <vector>
#include <iostream>
#include <string.h>
#include <strings.h>
#include "File.h"
#include "../SDKUtils/SDKUtils.h"
using namespace std;

namespace networkingLab {

class AbstractDB
{
protected:
	File * configManager;
	string config_path,instance_table;
	vector<File*> tables;
public:
	AbstractDB(const string & pConfig_path);
	virtual ~AbstractDB();
	/**
	 * READ operations
	 */
		virtual void loadConfig(const string & path);
		virtual void loadConfig();
		virtual vector<Entity*> getAllTable(const string& table_name)=0;
		virtual vector<Entity*> getAllTable()=0;
		virtual bool isEntityExist(string table_name,const Entity *entity)=0;
		virtual bool isEntityExist(const Entity* entity)=0;
		virtual Entity* getEntity(string table_name,string id)=0;
	/**
	 * WRITE operations
	 */
		virtual void createConfig(vector<pair<string,string> > tableRout_tableName);
		virtual void initTable(string name, string path)=0;
		virtual void addToTable(string table_name, const Entity * entity)=0;
		virtual void addToTable(const Entity* entity)=0;
		virtual void deleteFromTable(string table_name,const Entity * entity)=0;
		virtual void deleteFromTable(const Entity *entity)=0;
};

} /* namespace networkingLab */

#endif /* ABSTRACTDB_H_ */
