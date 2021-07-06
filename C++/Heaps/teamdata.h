#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_


#include <string>
#include <fstream>
#include <iostream>
#include "priorityqueue.h"
#include <cstdlib>

class TeamData {
 public:
 	TeamData(std::string filename);
    size_t numPlayers() const;
    nlohmann::json getFairTeam() const;
    //double winPercentages(int i, int j) const { return winPercentages_[i][j]; }

 private:
	// TODO: decide the type of this variable.
	// winPercentages_;
    size_t numPlayers_;
    void makeFairTeam();
    void removeDuplicates(PriorityQueue& team);
	PriorityQueue addToTeam(nlohmann::json jsonObj);
	std::vector<Value> currentPlayers;
    nlohmann::json  fairTeam;

};  // class TeamData

#endif  // _TEAMDATA_H_