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
	MiniHashMap map;
	vector<UserHighScoresData> parsed_users;
	vector<Entity*>::iterator it = entities_hs.begin();
	while(it != entities_hs.end())
	{
		string name = (*it)->getParams()[0];
		if(!map.contains(name))
		{
			map.addKey(name);
			parsed_users.push_back(parsePlayer(name, entities_hs));
		}
		it++;
	}

	return sortHighScores(parsed_users);
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
		vector<string> params= ((*it)->getParams());
		if(params.size()==2)
		{
			if((*it)->getParams()[0] == p_name)
			{
				using namespace std;
				string score_str="";
				score_str += (*it)->getParams()[1];
				score += (size_t)utils.toSize(score_str);
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

vector<UserHighScoresData> HighScoresLogic::sortHighScores(
		vector<UserHighScoresData> unsorted) const
{
	for(size_t i=0;i<unsorted.size();++i)
	{
		for(size_t j=0;j<unsorted.size()-1;++j)
		{
			if(unsorted[j].score < unsorted[j+1].score)
			{
				swap(unsorted[j], unsorted[j+1]);
			}
		}
	}
	return unsorted;
}

} /* namespace networkingLab */
