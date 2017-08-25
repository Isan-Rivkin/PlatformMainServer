/*
 * Entity.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "Entity.h"


namespace networkingLab
{
networkingLab::Entity::Entity(const string& id)
{
	this->id = id;
}


networkingLab::Entity::Entity(const string& id, const vector<string> oParams)
{
	this->id = id;
	this->params = oParams;
}

void networkingLab::Entity::setParams(vector<string> oParams)
{
	if(params.size()!=0)
	{
		params.clear();
	}
	for(size_t i=0;i<oParams.size();++i)
	{
		this->params.push_back(oParams[i]);
	}
//	vector<string>::iterator it = oParams.begin();
//	while(it != params.end())
//	{
//			string p ="";
//			p+=*(it);
//			this->params.push_back(p);
//		it++;
//	}
}

vector<string> networkingLab::Entity::getParams() const
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

