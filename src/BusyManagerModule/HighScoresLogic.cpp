/*
 * HighScoresLogic.cpp
 *
 *  Created on: Aug 18, 2017
 *      Author: user
 */

#include "HighScoresLogic.h"

namespace networkingLab {

HighScoresLogic::HighScoresLogic() {
	// TODO Auto-generated constructor stub

}

HighScoresLogic::~HighScoresLogic() {
	// TODO Auto-generated destructor stub
}

vector<UserHighScoresData> HighScoresLogic::parseHighscores(
		vector<Entity*> entities_hs) const
{
	vector<UserHighScoresData> parsed_users;
	vector<Entity*>::iterator it = entities_hs.begin();
	while(it != entities_hs.end())
	{

		it++;
	}
	return parsed_users;
}

UserHighScoresData HighScoresLogic::parsePlayer(const string& p_name,
		vector<Entity*> entities) const
{
	vector<Entity*>::iterator it = entities.begin();
	size_t score=0;
	size_t appearances = 0;
	UserHighScoresData user;

	while(it != entities.end())
	{
		if((*it)->getParams().size()==2)
		{
			if((*it)->getParams()[0] == p_name)
			{
				score= utils.toSize((*it)->getParams()[1]);
				appearances++;
			}
		}
		it++;
	}
	user.name = p_name;
	user.score = score;
	user.winnings = appearances;
	return user;
}

} /* namespace networkingLab */
