#include "Team.hpp"
#include "Player.hpp"
using namespace std;

void Team ::print_team(int num_week)
{
    cout << team_name << " " << weeks_goals_for[num_week];
}

bool Team ::check_name(string name)
{
    return name == team_name;
}

void Team::update_goals_tables(int goals_for, int goals_against, int num_week)
{
    weeks_goals_against[num_week] = goals_against;
    weeks_goals_for[num_week] = goals_for;
}

RealTeam ::RealTeam(string name, vector<shared_ptr<Player>> players_list)
{
    team_name = name;
    players = players_list;
}

FantasyTeam ::FantasyTeam(string name, vector<shared_ptr<Player>> players_list)
{
    team_name = name;
    players = players_list;
}

void FantasyTeam ::eliminate_player_from_team(std ::string name)
{
    bool player_found = false;
    for (int index = 0; index < players.size(); index++)
    {
        if (players[index]->has_name(name))
        {
            player_found = true;
            transfer_history.add_new_transfer(players[index], SELL);
            transfer_history.update_needed_posts_after_sell(has_forward, has_goalkeeper, has_midfielder, num_defenders, players[index]->get_post());
            num_players--;
            return;
        }
    }
    player_found = transfer_history.find_wanted_player_in_transfer_history(name);
    if (!player_found)
    {
        throw(ErrorHandler(NOT_FOUND));
    }
}

double FantasyTeam ::calculate_total_score(int week_num)
{
    double total_score = 0;
    for (int index = 0; index <= week_num; index++)
    {
        if (week_scores[index] != EMPTY)
        {
            total_score += week_scores[index];
        }
    }
    return total_score;
}

double RealTeam ::calculate_one_match_score(int goals_for, int goals_against)
{
    if (goals_for > goals_against)
    {
        return WINNER_SCORE;
    }
    else if (goals_for == goals_against)
    {
        return EQUAL_SCORE;
    }
    return LOSER_SCORE;
}

void RealTeam ::calculate_score(int num_week)
{
    team_score = 0;
    goals_for_till_this_week = 0;
    goals_against_till_this_week = 0;
    for (int index_week = 0; index_week <= num_week; index_week++)
    {
        team_score += calculate_one_match_score(weeks_goals_for[index_week], weeks_goals_against[index_week]);
        goals_against_till_this_week += weeks_goals_against[index_week];
        goals_for_till_this_week += weeks_goals_for[index_week];
    }
}

double RealTeam ::get_real_team_score()
{
    return team_score;
}

void RealTeam ::print_real_team()
{
    cout << team_name << ": score: " << team_score << " | GF: " << goals_for_till_this_week << " | GA: " << goals_against_till_this_week << endl;
}

pair<int, int> RealTeam ::get_goals_for_goals_against()
{
    pair<int, int> goals;
    goals.first = goals_for_till_this_week;
    goals.second = goals_against_till_this_week;
    return goals;
}

string Team ::get_team_name()
{
    return team_name;
}

void Team ::calculte_players_score_in_team(int num_week)
{
    for (int index_player = 0; index_player < players.size(); index_player++)
    {
        players[index_player]->calculate_avrage_score(num_week);
    }
}

void Team::print_team_players(string wanted_post)
{
    cout << "list of players:" << endl;
    if (wanted_post == NO_PLAYER_POST)
    {
        for (int index_player = 0; index_player < players.size(); index_player++)
        {
            cout << index_player + 1 << NUMBER_WORD_SEPERATOR;
            players[index_player]->print_player();
        }
    }
    else
    {
        int counter = 1;
        for (int index_player = 0; index_player < players.size(); index_player++)
        {
            if (players[index_player]->check_post_player(wanted_post))
            {
                cout << counter << NUMBER_WORD_SEPERATOR;
                players[index_player]->print_player();
                counter++;
            }
        }
    }
}

void Team ::sort_team_players_alphabetically(vector<pair<int, int>> intervals)
{
    for (int index_interval = 0; index_interval < intervals.size(); index_interval++)
    {
        for (int index_player = intervals[index_interval].first; index_player <= intervals[index_interval].second; index_player++)
        {
            for (int j = index_player + 1; j <= intervals[index_interval].second; j++)
            {
                if (players[index_player]->get_name() > players[j]->get_name())
                {
                    shared_ptr<Player> temp = players[j];
                    players[j] = players[index_player];
                    players[index_player] = temp;
                }
            }
        }
    }
}

vector<pair<int, int>> Team ::make_interval_for_sorting(bool is_alphabetically)
{
    vector<pair<int, int>> intervals_for_sorting;
    pair<int, int> interval;
    if (is_alphabetically)
    {
        interval.first = 0;
        interval.second = players.size() - 1;
        intervals_for_sorting.push_back(interval);
    }
    else
    {
        interval.first = 0;
        double score_for_compare = players[0]->get_average_score();
        for (int i = 0; i < players.size(); i++)
        {
            if ((players[i]->get_average_score() == score_for_compare) && (i + 1 != players.size()))
            {
                continue;
            }
            else
            {
                interval.second = i - 1;
                if (i + 1 == players.size() && (players[i]->get_average_score() == score_for_compare))
                {
                    interval.second = players.size() - 1;
                }
                if (interval.first == interval.second)
                {
                    interval.first = i;
                    score_for_compare = players[i]->get_average_score();
                }
                else if (interval.first != interval.second)
                {
                    intervals_for_sorting.push_back(interval);
                    interval.first = i;
                    score_for_compare = players[i]->get_average_score();
                }
            }
        }
    }
    return intervals_for_sorting;
}

void Team ::sort_team_players_by_rank()
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < players.size(); j++)
        {
            if (players[i]->get_average_score() > players[j]->get_average_score())
            {
                shared_ptr<Player> temp = players[j];
                players[j] = players[i];
                players[i] = temp;
            }
        }
    }
}

void FantasyTeam ::add_new_player(std ::shared_ptr<Player> new_player)
{
    if (players.size() >= NUM_OF_FANTASY_TEAM_PLAYERS)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    transfer_history.add_new_transfer(new_player, BUY);
    transfer_history.update_needed_posts_after_buy(has_forward, has_goalkeeper, has_midfielder, num_defenders, new_player->get_post());
    num_players++;
    if (players.size() == NUM_OF_FANTASY_TEAM_PLAYERS)
    {
        is_completed = true;
        if (!is_created)
        {
            is_created = true;
        }
    }
}

bool FantasyTeam ::needs_post(string post)
{
    if (post == POST_PLAYERS[FW] && has_forward)
    {
        return false;
    }
    else if (post == POST_PLAYERS[GK] && has_goalkeeper)
    {
        return false;
    }
    else if (post == POST_PLAYERS[MD] && has_midfielder)
    {
        return false;
    }
    else if (post == POST_PLAYERS[DF] && num_defenders == LEGALL_NUM_DEFENDERS)
    {
        return false;
    }
    return true;
}

bool FantasyTeam ::player_is_qualified(shared_ptr<Player> player, int week_num)
{
    if (player->has_been_injured_in_the_past_three_weeks(week_num))
    {
        return false;
    }
    if (player->is_player_banned())
    {
        return false;
    }
    if (player->has_received_red_card_last_week(week_num))
    {
        return false;
    }
    return true;
}

void FantasyTeam ::print_info(int week_num)
{
    double total_score = calculate_total_score(week_num);
    vector<shared_ptr<Player>> defenders = sort_defenders_alphabetically();
    vector<string> defenders_names = {defenders[0]->get_name(), defenders[1]->get_name()};
    string goalkeeper = find_player_by_post(POST_PLAYERS[GK]);
    string midfielder = find_player_by_post(POST_PLAYERS[MD]);
    string striker = find_player_by_post(POST_PLAYERS[FW]);
    cout << "fantasy_team: " << team_name << endl;
    cout << "Goalkeeper: " << goalkeeper << endl;
    cout << "Defender1: " << defenders[0]->get_name() << endl;
    cout << "Defender2: " << defenders[1]->get_name() << endl;
    cout << "Midfielder: " << midfielder << endl;
    cout << "Striker: " << striker << endl;
    cout << "Total Points: " << total_score << endl;
}

vector<shared_ptr<Player>> FantasyTeam ::sort_defenders_alphabetically()
{
    vector<shared_ptr<Player>> defenders;
    for (int index = 0; index < NUM_OF_FANTASY_TEAM_PLAYERS; index++)
    {
        if (players[index]->get_post() == POST_PLAYERS[DF])
        {
            defenders.push_back(players[index]);
        }
    }
    if (defenders[0]->get_name() > defenders[1]->get_name())
    {
        shared_ptr<Player> tmp;
        tmp = defenders[0];
        defenders[0] = defenders[1];
        defenders[1] = tmp;
    }
    return defenders;
}

string FantasyTeam ::find_player_by_post(string post)
{
    for (shared_ptr<Player> player : players)
    {
        if (player->get_post() == post)
        {
            return player->get_name();
        }
    }
    return "";
}

void FantasyTeam::calculate_new_week_score(int num_week)
{
    if (is_completed)
    {
        double new_score = 0;
        for (int index_player = 0; index_player < players.size(); index_player++)
        {
            if (players[index_player]->get_score(num_week) != EMPTY)
            {
                new_score += players[index_player]->get_score(num_week);
            }
        }
        week_scores[num_week] = new_score;
    }
}

void FantasyTeam::apply_transfer_history()
{
    transfer_history.apply_transfers(players);
}

void FantasyTeam::change_status_team()
{
    if (players.size() == NUM_OF_FANTASY_TEAM_PLAYERS)
    {
        is_completed = true;
    }
    else
    {
        is_completed = false;
    }
}
