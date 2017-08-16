/*
 * BasicDB.h
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#ifndef BASICDB_H_
#define BASICDB_H_

#include "AbstractDB.h"
#include "Entity.h"
#include <vector>
#include "../SDKUtils/SDKUtils.h"

namespace networkingLab {

class BasicDB: public AbstractDB {
public:
	BasicDB(const string& config_path);
	virtual ~BasicDB();

	/**
	 * READ operations
	 */
		virtual vector<Entity*> getAllTable(const string& table_name);
		virtual vector<Entity*> getAllTable();
		virtual bool isEntityExist(string table_name,const Entity* entity);
		virtual bool isEntityExist(const Entity *entity);
		virtual Entity* getEntity(string table_name,string id);
	/**
	 * WRITE operations
	 */
		virtual void initTable(string name, string path);
		virtual void addToTable(string table_name, const Entity* entity);
		virtual void addToTable(const Entity* entity);
		virtual void deleteFromTable(string table_name,const Entity *entity);
		virtual void deleteFromTable(const Entity *entity);

};

} /* namespace networkingLab */

#endif /* BASICDB_H_ */
