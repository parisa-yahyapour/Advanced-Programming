#ifndef _MATCH_HPP_
#define _MATCH_HPP_
#include <memory>
#include <iostream>
#include "Team.hpp"

class Match
{
public:
    Match(std ::pair<std ::shared_ptr<Team>, std ::shared_ptr<Team>> teams_ptr, std ::pair<int, int> goals);
    void print_match(int num_week);

private:
    std ::pair<std ::shared_ptr<Team>, std ::shared_ptr<Team>> team1_team2;
    std ::pair<int, int> goals_team1_team2;
};

#endif