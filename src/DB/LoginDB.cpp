/*
 * LoginDB.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: user
 */

#include "LoginDB.h"

namespace networkingLab {


LoginDB::LoginDB(EntitityCoder* oCoder, const string &config_path):BasicDB(config_path) {
	coder= oCoder;
}


LoginDB::~LoginDB()
{
}

//vector<Entity*> LoginDB::getAllTable(const string& table_name)
//{
//	return coder->decode(BasicDB::getAllTable(table_name));
//}

vector<Entity*> LoginDB::getAllTable()
{
	return coder->decode(BasicDB::getAllTable());
}

//bool LoginDB::isEntityExist(string table_name, const Entity* entity)
//{
//	Entity * newEnt = new Entity("",entity->getParams());
//	return BasicDB::isEntityExist(table_name, coder->encodeEntity(newEnt));
//}

bool LoginDB::isEntityExist(const Entity* entity)
{
	Entity * newEnt = new Entity("",entity->getParams());
	return BasicDB::isNameExist(instance_table,coder->encodeEntity(newEnt));
}

//Entity* LoginDB::getEntity(string table_name, string id)
//{
//	return coder->decodeEntity(BasicDB::getEntity(table_name, id));
//}

//void LoginDB::initTable(string name, string path)
//{
//	BasicDB::initTable(name, path);
//}

//void LoginDB::addToTable(string table_name, const Entity* entity) {
//	Entity * newEnt = new Entity("",entity->getParams());
//	BasicDB::addToTable(table_name, coder->encodeEntity(newEnt));
//}

void LoginDB::addToTable(const Entity* entity)
{
	Entity * newEnt = new Entity("",entity->getParams());
	BasicDB::addToTable(coder->encodeEntity(newEnt));
}

//void LoginDB::deleteFromTable(string table_name, const Entity* entity) {
//	Entity * newEnt = new Entity("",entity->getParams());
//	BasicDB::deleteFromTable(table_name, coder->encodeEntity(newEnt));
//}


void LoginDB::deleteFromTable(const Entity* entity) {
	Entity * newEnt = new Entity("",entity->getParams());
	BasicDB::deleteFromTable(coder->encodeEntity(newEnt));
}

} /* namespace networkingLab */
