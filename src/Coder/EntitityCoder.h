/*
 * EntitityCoder.h
 *
 *  Created on: Aug 24, 2017
 *      Author: user
 */

#ifndef CODER_ENTITITYCODER_H_
#define CODER_ENTITITYCODER_H_
#include "../DB/Entity.h"
#include <iostream>
#include <string>
#include <string.h>
#include <strings.h>
#include <vector>
#include <map>

using namespace std;

namespace networkingLab
{

class EntitityCoder
{
private:
	map<char,char> map_decode;
	map<char,char> map_encode;
public:
	EntitityCoder();
	virtual ~EntitityCoder();
	/**
	 * encode
	 */
	virtual vector<Entity*> encode(vector<Entity*> decoded);
	virtual Entity* encodeEntity(Entity* decoded);
	virtual string encodeStr(string decoded);
	/**
	 * decode
	 */
	virtual vector<Entity*> decode(vector<Entity*> encoded);
	virtual Entity* decodeEntity(Entity* encoded);
	virtual string decodeStr(string encoded);
private:
	void initDecodeMap();
	void initEncodeMap();
};

} /* namespace networkingLab */

#endif /* CODER_ENTITITYCODER_H_ */
