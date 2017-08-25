/*
 * LoginDB.h
 *
 *  Created on: Aug 24, 2017
 *      Author: user
 */

#ifndef DB_LOGINDB_H_
#define DB_LOGINDB_H_

#include "AbstractDB.h"
#include "Entity.h"
#include "BasicDB.h"
#include <vector>
#include "../SDKUtils/SDKUtils.h"
#include "../Coder/EntitityCoder.h"

namespace networkingLab {

class LoginDB : public BasicDB
{
	EntitityCoder * coder;
public:
	LoginDB(EntitityCoder * oCoder,const string &config_path);
	virtual ~LoginDB();
	/**
	 * override
	 */
	/**
	 * READ operations
	 */
	//	virtual vector<Entity*> getAllTable(const string& table_name);
		virtual vector<Entity*> getAllTable();
		//virtual bool isEntityExist(string table_name,const Entity* entity);
		virtual bool isEntityExist(const Entity *entity);
		//virtual Entity* getEntity(string table_name,string id);
	/**
	 * WRITE operations
	 */
		//virtual void initTable(string name, string path);
		//virtual void addToTable(string table_name, const Entity* entity);
		virtual void addToTable(const Entity* entity);
		//virtual void deleteFromTable(string table_name,const Entity *entity);
		virtual void deleteFromTable(const Entity *entity);
};

} /* namespace networkingLab */

#endif /* DB_LOGINDB_H_ */
