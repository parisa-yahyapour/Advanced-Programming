#include "Database.hpp"
using namespace std;

void DataBase ::add_new_player(shared_ptr<Player> new_player)
{
    players.push_back(new_player);
}

void DataBase ::add_new_real_team(shared_ptr<RealTeam> new_team)
{
    real_teams.push_back(new_team);
}

shared_ptr<RealTeam> DataBase ::find_team_by_name(string name)
{

    for (int index_team = 0; index_team < real_teams.size(); index_team++)
    {
        if (real_teams[index_team]->check_name(name))
        {
            return real_teams[index_team];
        }
    }
    return NULL;
}

shared_ptr<Player> DataBase::find_player_by_name(string name)
{
    for (int index_player = 0; index_player < players.size(); index_player++)
    {
        if (players[index_player]->check_name(name))
        {
            return players[index_player];
        }
    }
    return NULL;
}

void DataBase ::add_new_week(std ::shared_ptr<WeekTable> new_week)
{
    week_tables.push_back(new_week);
}

shared_ptr<WeekTable> DataBase ::find_next_week(shared_ptr<WeekTable> current_week)
{
    if (current_week == NULL)
    {
        return week_tables[0];
    }
    int index_week = 0;
    for (index_week = 0; index_week < NUM_WEEKS; index_week++)
    {
        if (current_week == week_tables[index_week])
        {
            index_week++;
            break;
        }
    }
    return week_tables[index_week];
}

vector<shared_ptr<Player>> DataBase ::find_best_players(int num_week)
{
    vector<shared_ptr<Player>> best_players;
    sort_players_by_score(num_week);
    shared_ptr<Player> best_gk = find_best_player_in_post(POST_PLAYERS[GK], num_week);
    vector<shared_ptr<Player>> best_df = find_best_DFs(num_week);
    shared_ptr<Player> best_md = find_best_player_in_post(POST_PLAYERS[MD], num_week);
    shared_ptr<Player> best_fw = find_best_player_in_post(POST_PLAYERS[FW], num_week);
    best_players.push_back(best_gk);
    best_players.push_back(best_df[0]);
    best_players.push_back(best_df[1]);
    best_players.push_back(best_md);
    best_players.push_back(best_fw);
    return best_players;
}

void DataBase ::sort_players_by_score(int num_week)
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = i + 1; j < players.size(); j++)
        {
            if (players[i]->get_score(num_week) < players[j]->get_score(num_week))
            {
                shared_ptr<Player> temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }
}

void DataBase ::sort_players_by_name(vector<shared_ptr<Player>> &chosen_players)
{
    for (int i = 0; i < chosen_players.size(); i++)
    {
        for (int j = i + 1; j < chosen_players.size(); j++)
        {
            if (chosen_players[i]->get_name() > chosen_players[j]->get_name())
            {
                shared_ptr<Player> temp = chosen_players[i];
                chosen_players[i] = chosen_players[j];
                chosen_players[j] = temp;
            }
        }
    }
}

shared_ptr<Player> DataBase ::find_best_player_in_post(string post, int num_week)
{
    vector<shared_ptr<Player>> top_players;
    double max_score = find_max_score(post, num_week);
    for (int index_player = 0; index_player < players.size(); index_player++)
    {
        if ((players[index_player]->get_score(num_week) == max_score) && (players[index_player]->check_post_player(post)))
        {
            top_players.push_back(players[index_player]);
        }
    }
    sort_players_by_name(top_players);
    return top_players[0];
}

vector<shared_ptr<Player>> DataBase ::find_best_DFs(int num_week)
{
    vector<shared_ptr<Player>> two_best_defenders, top_defenders1, top_defenders2;
    double max_score = find_max_score(POST_PLAYERS[DF], num_week), second_max_score = DEFAULT_SECOND_MAX_SCORE;
    int index_player;
    for (index_player = 0; index_player < players.size(); index_player++)
    {
        if (players[index_player]->check_post_player(POST_PLAYERS[DF]) && players[index_player]->get_score(num_week) == max_score)
        {
            top_defenders1.push_back(players[index_player]);
        }
        if (players[index_player]->check_post_player(POST_PLAYERS[DF]) && players[index_player]->get_score(num_week) != max_score)
        {
            second_max_score = players[index_player]->get_score(num_week);
            break;
        }
    }
    for (index_player; index_player < players.size(); index_player++)
    {
        if (players[index_player]->check_post_player(POST_PLAYERS[DF]) && players[index_player]->get_score(num_week) == second_max_score)
        {
            top_defenders2.push_back(players[index_player]);
        }
    }
    if (top_defenders1.size() == 1)
    {
        two_best_defenders.push_back(top_defenders1[0]);
        sort_players_by_name(top_defenders2);
        two_best_defenders.push_back(top_defenders2[0]);
    }
    else
    {
        sort_players_by_name(top_defenders1);
        two_best_defenders.push_back(top_defenders1[0]);
        two_best_defenders.push_back(top_defenders1[1]);
    }
    return two_best_defenders;
}

double DataBase ::find_max_score(string post, int num_week)
{
    int index_player = 0;
    for (index_player = 0; index_player < players.size(); index_player++)
    {
        if (players[index_player]->check_post_player(post))
        {
            break;
        }
    }
    return players[index_player]->get_score(num_week);
}

void DataBase ::print_matches_of_week(int num_week)
{
    week_tables[num_week]->print_week_data();
}

void DataBase ::calculate_teams_score(int num_week)
{
    if (num_week == EMPTY)
    {
        return;
    }

    for (int index_team = 0; index_team < real_teams.size(); index_team++)
    {
        real_teams[index_team]->calculate_score(num_week);
    }
}

void DataBase ::sort_teams_by_score()
{
    for (int i = 0; i < real_teams.size(); i++)
    {
        for (int j = i + 1; j < real_teams.size(); j++)
        {
            if (real_teams[i]->get_real_team_score() < real_teams[j]->get_real_team_score())
            {
                shared_ptr<RealTeam> temp = real_teams[i];
                real_teams[i] = real_teams[j];
                real_teams[j] = temp;
            }
        }
    }
}

void DataBase ::sort_team_by_goals_for()
{
    double score_for_compare = real_teams[0]->get_real_team_score();
    pair<int, int> interval, goals_for_comparsion;
    goals_for_comparsion = real_teams[0]->get_goals_for_goals_against();
    int diffrence_goal_for_comparsion = goals_for_comparsion.first - goals_for_comparsion.second;
    interval.first = 0;
    for (int i = 0; i < real_teams.size(); i++)
    {
        pair<int, int> goals = real_teams[i]->get_goals_for_goals_against();
        int diffrence_goal = goals.first - goals.second;
        if ((real_teams[i]->get_real_team_score() == score_for_compare) &&
            (diffrence_goal == diffrence_goal_for_comparsion) &&
            (i + 1 != real_teams.size()))
        {
            continue;
        }
        else
        {
            interval.second = i - 1;
            if (i + 1 == real_teams.size() &&
                (real_teams[i]->get_real_team_score() == score_for_compare) &&
                (diffrence_goal == diffrence_goal_for_comparsion))
            {
                interval.second = i;
            }
            if (interval.first != interval.second)
            {
                sort_teams_with_same_score_diffrence_goal_by_goals_for(interval);
            }
            score_for_compare = real_teams[i]->get_real_team_score();
            goals_for_comparsion = real_teams[i]->get_goals_for_goals_against();
            diffrence_goal_for_comparsion = goals_for_comparsion.first - goals_for_comparsion.second;
            interval.first = i;
        }
    }
}

void DataBase ::sort_teams_by_name()
{
    double score_for_compare = real_teams[0]->get_real_team_score();
    pair<int, int> interval, goals_for_comparsion = real_teams[0]->get_goals_for_goals_against();
    int diffrence_goal_for_comparsion = goals_for_comparsion.first - goals_for_comparsion.second, goals_for_team1 = goals_for_comparsion.first;
    interval.first = 0;
    for (int i = 0; i < real_teams.size(); i++)
    {
        pair<int, int> goals = real_teams[i]->get_goals_for_goals_against();
        int diffrence_goal = goals.first - goals.second, goals_for_team2 = goals.first;
        if ((real_teams[i]->get_real_team_score() == score_for_compare) &&
            (diffrence_goal == diffrence_goal_for_comparsion) &&
            (goals_for_team1 == goals_for_team2) &&
            (i + 1 != real_teams.size()))
        {
            continue;
        }
        else
        {
            interval.second = i - 1;
            if ((i + 1 == real_teams.size()) &&
                (real_teams[i]->get_real_team_score() == score_for_compare) &&
                (diffrence_goal == diffrence_goal_for_comparsion) &&
                (goals_for_team1 == goals_for_team2))
            {
                interval.second = i;
            }
            if (interval.first != interval.second)
            {
                sort_teams_with_same_score_diffrence_goal_goals_for_by_name(interval);
            }
            score_for_compare = real_teams[i]->get_real_team_score();
            goals_for_comparsion = real_teams[i]->get_goals_for_goals_against();
            diffrence_goal_for_comparsion = goals_for_comparsion.first - goals_for_comparsion.second;
            goals_for_team1 = goals_for_comparsion.first;
            interval.first = i;
        }
    }
}

void DataBase ::sort_teams_by_diffrence_goals()
{
    double score_for_compare = real_teams[0]->get_real_team_score();
    pair<int, int> interval;
    interval.first = 0;
    for (int i = 0; i < real_teams.size(); i++)
    {
        if (real_teams[i]->get_real_team_score() == score_for_compare && i + 1 != real_teams.size())
        {
            continue;
        }
        else
        {
            interval.second = i - 1;
            if (i + 1 == real_teams.size() && real_teams[i]->get_real_team_score() == score_for_compare)
            {
                interval.second = i;
            }
            if (interval.first != interval.second)
            {
                sort_teams_with_same_score_by_diffrence_goals(interval);
            }
            score_for_compare = real_teams[i]->get_real_team_score();
            interval.first = i;
        }
    }
}

void DataBase ::sort_teams_with_same_score_by_diffrence_goals(std ::pair<int, int> interval)
{
    for (int index_team = interval.first; index_team <= interval.second; index_team++)
    {
        pair<int, int> goals_team1, goals_team2;
        int diffrence_goal1, diffrence_goal2;
        for (int j = index_team + 1; j <= interval.second; j++)
        {
            goals_team1 = real_teams[index_team]->get_goals_for_goals_against();
            diffrence_goal1 = goals_team1.first - goals_team1.second;
            goals_team2 = real_teams[j]->get_goals_for_goals_against();
            diffrence_goal2 = goals_team2.first - goals_team2.second;
            if (diffrence_goal1 < diffrence_goal2)
            {
                shared_ptr<RealTeam> temp = real_teams[j];
                real_teams[j] = real_teams[index_team];
                real_teams[index_team] = temp;
            }
        }
    }
}

void DataBase ::sort_teams_with_same_score_diffrence_goal_by_goals_for(pair<int, int> interval)
{
    for (int index_team = interval.first; index_team <= interval.second; index_team++)
    {
        int goals_for_team1;
        for (int j = index_team + 1; j <= interval.second; j++)
        {
            goals_for_team1 = real_teams[index_team]->get_goals_for_goals_against().first;
            int goals_for_team2 = real_teams[j]->get_goals_for_goals_against().first;
            if (goals_for_team1 < goals_for_team2)
            {
                shared_ptr<RealTeam> temp = real_teams[j];
                real_teams[j] = real_teams[index_team];
                real_teams[index_team] = temp;
            }
        }
    }
}

void DataBase ::sort_teams_with_same_score_diffrence_goal_goals_for_by_name(pair<int, int> interval)
{
    for (int index_team = interval.first; index_team <= interval.second; index_team++)
    {
        for (int j = index_team + 1; j <= interval.second; j++)
        {
            string name_team1 = real_teams[index_team]->get_team_name();
            string name_team2 = real_teams[j]->get_team_name();
            if (name_team1 > name_team2)
            {
                shared_ptr<RealTeam> temp = real_teams[j];
                real_teams[j] = real_teams[index_team];
                real_teams[index_team] = temp;
            }
        }
    }
}

void DataBase ::print_teams_data()
{
    cout << "league standings:" << endl;
    for (int i = 0; i < real_teams.size(); i++)
    {
        cout << i + 1 << NUMBER_WORD_SEPERATOR;
        real_teams[i]->print_real_team();
    }
}

void DataBase::ban_players_by_yellow_cards(int week_num)
{
    for (int index_player = 0; index_player < players.size(); index_player++)
    {
        if (players[index_player]->has_received_three_yellow_cards(week_num))
        {
            players[index_player]->clear_yellow_cards(week_num);
        }
        else
        {
            players[index_player]->change_player_ban_status();
        }
    }
}
