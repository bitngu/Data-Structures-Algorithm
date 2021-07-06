#include "teamdata.h"

TeamData::TeamData(std::string filename) {
    std::ifstream file {filename};
    if(!file){
        std::cout << "File cannot be read" << std::endl;
    }
    nlohmann::json jsonObj;
    //Get content from file to json object
    file >> jsonObj;
    //Get number of players from file
    numPlayers_ = jsonObj["metadata"]["numPlayers"];
    //Make teams for each player
        //1. Should i add each player on the queue? Yes
        //2. Then find the team that has win percentage CLOSEST to 50%
        //3. Then remove each duplicate players, while keep track of the distinct teams

    //add all players to queue
    PriorityQueue fullTeam = addToTeam(jsonObj);
    size_t totalTeams = numPlayers_/2;//total possible teams without duplicates
    size_t i = 0;
    //We know the maximum amount of teams is n/2; therefore we replace until we get to that possible amount of teams
    while(i < totalTeams) {
        removeDuplicates(fullTeam);
        ++i;
    }
    makeFairTeam();//make json format

}

size_t numTeams(size_t n){
    //Get the total sized team
    //For example, 4 players = 6 total teams -> 3+2+1
    //           , 6 players = 15 total teams -> 5+4+3+2+1
    size_t teams = 0;
    for (size_t i = n-1; i > 0; --i) {
        teams += i;
    }
    return teams;
}

double nearFifty(double x){
    //get the value closet to 50.0
    if (x - 50.0 < 0){
        return -1* (x-50);
    }
    else{
        return  x - 50.0;
    }
}


PriorityQueue TeamData::addToTeam(nlohmann::json jsonObj) {
    PriorityQueue teams {numTeams(numPlayers_)};
    for (auto itr = jsonObj["teamStats"].begin(); itr != jsonObj["teamStats"].end(); ++itr) {
        //get the key and values
        Key key = nearFifty((*itr)["winPercentage"]);
        int player1 = (*itr)["playerOne"];
        int player2 = (*itr)["playerTwo"];
        Value val = std::pair<int,int> {player1,player2};
        KeyValuePair kv {key, val};
        //add each team to queue
        teams.insert(kv);
    }
    return teams;

}


void TeamData::removeDuplicates(PriorityQueue &team) {
    //From our priorityQueue, we know the team with the closest value to 50% is the first node
    currentPlayers.push_back(team.min().second);//Add to current players that are in a distinct team
    team.removeMin();//remove the team with the value closest value to 50%
    for (size_t i = 0; i < currentPlayers.size(); ++i) {
        int player1 = currentPlayers.at(i).first;
        int player2 = currentPlayers.at(i).second;
        for (size_t j = 1; j <= team.size(); ++j) {
            if (team.getValue(j).first == player1 || team.getValue(j).first == player2 ||
                team.getValue(j).second == player1 ||team.getValue(j).second == player2) {
                team.removeNode(j);// remove the duplicate team with duplicate player(s)
                j = 0;//As we remove, the size of the array shrinks as well. This means that new values are updated at the top;
                //so we need to go back to the beginingval  and remove. Also j = 0 because of hte ++ at the end;
            }
        }
    }
}

void TeamData::makeFairTeam() {
    //Make output in json format
    for (size_t i = 0; i < currentPlayers.size() ; ++i) {
        fairTeam["teams"][i] = currentPlayers.at(i);
    }
}

nlohmann::json TeamData::getFairTeam() const {
    return fairTeam;
}

size_t TeamData::numPlayers() const {
    return numPlayers_;
}
