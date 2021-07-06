
#include "teamdata.h"

int main(int argc, char** argv) {
    TeamData team {argv[1]};
    std::cout << team.getFairTeam();
    return 0;
}
