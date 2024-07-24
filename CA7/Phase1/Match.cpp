#include "Match.hpp"
using namespace std;

Match ::Match(std ::pair<std ::shared_ptr<Team>, std ::shared_ptr<Team>> teams_ptr, std ::pair<int, int> goals)
{
    team1_team2 = teams_ptr;
    goals_team1_team2 = goals;
}

void Match ::print_match(int num_week)
{
    team1_team2.first->print_team(num_week);
    cout << " | ";
    team1_team2.second->print_team(num_week);
    cout << endl;
}