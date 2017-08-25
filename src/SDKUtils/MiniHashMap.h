/*
 * MiniHashMap.h
 *
 *  Created on: Aug 18, 2017
 *      Author: user
 */

#ifndef SDKUTILS_MINIHASHMAP_H_
#define SDKUTILS_MINIHASHMAP_H_

#include <iostream>
#include <strings.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
namespace networkingLab
{

class MiniHashMap
{
private:
	vector<string> keys;
public:
	MiniHashMap();
	virtual ~MiniHashMap();
public:
	virtual const MiniHashMap& addKey(const string& key);
	virtual bool contains(const string& key)const;
	virtual vector<string> getAllKeys();
	virtual bool removeKey(const string key);
};

} /* namespace networkingLab */

#endif /* SDKUTILS_MINIHASHMAP_H_ */
