/*
 * HighScoresLogic.h
 *
 *  Created on: Aug 18, 2017
 *      Author: user
 */

#ifndef BUSYMANAGERMODULE_HIGHSCORESLOGIC_H_
#define BUSYMANAGERMODULE_HIGHSCORESLOGIC_H_

#include <iostream>
#include <string>
#include <strings.h>
#include <string.h>
#include <vector>
#include <algorithm>
//db
#include "../DB/AbstractDB.h"
#include "../DB/Entity.h"
// utils
#include "../SDKUtils/SDKUtils.h"
#include "../SDKUtils/MiniHashMap.h"
using namespace std;

namespace networkingLab {
struct UserHighScoresData
{
	string name;
	size_t score;
	size_t winnings;
	UserHighScoresData()
		:name(""),score(0),winnings(0){}
	UserHighScoresData(string oName,size_t oScore, size_t oWinnings)
	:name(oName),score(oScore),winnings(oWinnings){}
	UserHighScoresData(const UserHighScoresData & other)
	{
		name = other.name;
		score = other.score;
		winnings = other.winnings;
	}
};
class HighScoresLogic
{
private:
	SDKUtils utils;
public:
	HighScoresLogic();
	virtual ~HighScoresLogic();
public:
	virtual vector<UserHighScoresData> parseHighscores(vector<Entity*> entities_hs)const;
	virtual UserHighScoresData parsePlayer(const string & p_name, vector<Entity*> entities)const;
	virtual vector<UserHighScoresData> sortHighScores(vector<UserHighScoresData> unsorted)const;
};

} /* namespace networkingLab */

#endif /* BUSYMANAGERMODULE_HIGHSCORESLOGIC_H_ */
