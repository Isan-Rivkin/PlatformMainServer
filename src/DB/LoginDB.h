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
		virtual vector<Entity*> getAllTable();
		virtual bool isEntityExist(const Entity *entity);
	/**
	 * WRITE operations
	 */
		virtual void addToTable(const Entity* entity);
		virtual void deleteFromTable(const Entity *entity);
};

} /* namespace networkingLab */

#endif /* DB_LOGINDB_H_ */
