/*
 * MiniHashMap.cpp
 *
 *  Created on: Aug 18, 2017
 *      Author: user
 */

#include "MiniHashMap.h"

namespace networkingLab {

MiniHashMap::MiniHashMap() {
	// TODO Auto-generated constructor stub

}

MiniHashMap::~MiniHashMap() {
	// TODO Auto-generated destructor stub
}

const MiniHashMap& MiniHashMap::addKey(const string& key)
{

	if(!contains(key))
	{
		keys.push_back(key);
	}

	return *this;
}

bool MiniHashMap::contains(const string& key) const
{
	for(size_t i=0; i<keys.size();++i)
	{
		if(keys[i] == key)
			return true;
	}
	return false;
}

vector<string> MiniHashMap::getAllKeys()
{
	return keys;
}

bool networkingLab::MiniHashMap::removeKey(const string key)
{
	vector<string>::iterator it = keys.begin();
	while(it != keys.end())
	{
		if((*it) == key)
		{
			keys.erase(it);
			return true;
		}
		it++;
	}
	return false;
}

} /* namespace networkingLab */

