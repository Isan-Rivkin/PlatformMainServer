/*
 * BasicDB.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "BasicDB.h"

namespace networkingLab {



BasicDB::BasicDB(const string& config_path):AbstractDB(config_path){}

BasicDB::~BasicDB() {
	// TODO Auto-generated destructor stub
}

vector<Entity*> BasicDB::getAllTable(const string& table_name) {
	SDKUtils utils;
	vector<Entity*> ret;
	File * reader = new File(table_name);
	size_t buff_size = 5000;
	char buffer[buff_size];
	int bytes = reader->read(buffer, buff_size);
	 buffer[bytes] = '\0';
	//ret = utils.extractAllEntities(buffer, strlen(buffer));
	ret = utils.extractAllEntities(buffer, strlen(buffer));
	return ret;
}

vector<Entity*> BasicDB::getAllTable()
{
	return getAllTable(instance_table);
}

bool BasicDB::isEntityExist(string table_name,const Entity* entity)
{
	vector<Entity*> entities = getAllTable(table_name);
	for(size_t i=0;i<entities.size();++i)
	{
		if(entities[i]->equals(entity))
		{
			return true;
		}
	}
	return false;
}
bool BasicDB::isNameExist(string table_name, const Entity* entity) {
	vector<Entity*> entities =BasicDB::getAllTable(table_name);
	for(size_t i=0;i<entities.size();++i)
	{
		if(entities[i]->getParams()[0] == entity->getParams()[0])
		{
			return true;
		}
	}
	return false;
}

bool BasicDB::isEntityExist(const Entity* entity)
{
	return isEntityExist(instance_table, entity);
}
bool BasicDB::isValidatedAllParams(const Entity* entity)
{
	return isEntityExist(instance_table,entity);
}
Entity* BasicDB::getEntity(string table_name, string id)
{
	cout <<"[ERROR ERROR ERROR ] BasicDB: getEntity method not implemented!" <<endl;
	return NULL;
}

void BasicDB::initTable(string name, string path)
{
	BasicDB::initTable(name, path);
}

void BasicDB::addToTable(string table_name,const Entity* entity)
{
	string row_str;
	File * writer = new File(table_name);
	vector<string> cols = entity->getParams();
	for(size_t i =0; i<cols.size()-1;++i)
	{
		row_str += string(cols[i] + ",");
	}
	row_str +=cols[cols.size()-1] + "\n";
	writer->append(row_str);
}

void BasicDB::addToTable(const Entity* entity)
{
	addToTable(instance_table, entity);
}

void BasicDB::deleteFromTable(string table_name, const Entity *entity)
{
	vector<Entity*> rows =getAllTable(table_name);
	vector<Entity*>::iterator it = rows.begin();
	bool stop = false;
	while(it != rows.end() && !stop)
	{
		if((*it)->equals(entity))
		{
			rows.erase(it);
			stop = true;
		}
		it++;
	}
	it = rows.begin();
	while(it != rows.end())
	{
		addToTable(table_name, *it);
		it++;
	}
}


void BasicDB::deleteFromTable(const Entity* entity)
{
	deleteFromTable(instance_table, entity);
}

} /* namespace networkingLab */


