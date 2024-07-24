#include "WeekTable.hpp"
using namespace std;

WeekTable ::WeekTable(vector<shared_ptr<Match>> matches, int num_week)
{
    matches_played = matches;
    week_number = num_week;
}

void WeekTable ::print_week_data()
{
    for (int i = 0; i < matches_played.size(); i++)
    {

        matches_played[i]->print_match(week_number);
    }
}

bool WeekTable :: check_invalid_week(int wanted_week)
{
    return wanted_week <= week_number;
}

int WeekTable :: get_num_week()
{
    return week_number;
}