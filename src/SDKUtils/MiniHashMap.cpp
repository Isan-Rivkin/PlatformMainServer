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
	vector<string>::iterator it = keys.begin();

	while(it != keys.end())
	{
		if((*it) == key)
		{
			return true;
		}
		it++;
	}
	return false;
}

vector<string> MiniHashMap::getAllKeys()
{
	return keys;
}

} /* namespace networkingLab */
