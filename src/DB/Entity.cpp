/*
 * Entity.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "Entity.h"


namespace networkingLab
{
Entity::Entity(const string& id):id(id){}

Entity::Entity(const string& id, const vector<string> oParams):id(id),params(oParams){}

void Entity::setParams(vector<string> oParams)
{
	vector<string>::iterator it = oParams.begin();
	while(it != params.end())
	{
		string p =*(it);
		this->params.push_back(p);
		it++;
	}
}

vector<string> Entity::getParams() const
{
	return this->params;
}
bool networkingLab::Entity::equals(const Entity* other)
{
	vector<string> other_params = other->getParams();
	if(other_params.size() != params.size())
	{
		return false;
	}
	bool flag = true;
	for(size_t i =0; i<params.size();++i)
	{
		if(other_params[i] != params[i])
		{
			return false;
		}
	}
	return flag;
}
Entity::~Entity(){}

} /* namespace networkingLab */


