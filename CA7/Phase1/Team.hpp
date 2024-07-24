#ifndef _TEAM_HPP_
#define _TEAM_HPP_
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "magic_number.hpp"
#include "ErrorHandler.hpp"
#include "TransferTable.hpp"

class Player;

class Team
{
public:
    void print_team(int num_week);
    bool check_name(std ::string name);
    void update_goals_tables(int goals_for, int goals_against, int num_week);
    std ::string get_team_name();
    void calculte_players_score_in_team(int num_week);
    void sort_team_players_by_rank();

    void print_team_players(std ::string wanted_post);
    void sort_team_players_alphabetically(std ::vector<std ::pair<int, int>> intervals);
    std ::vector<std ::pair<int, int>> make_interval_for_sorting(bool is_alphabetically);

protected:
    std::string team_name;
    std ::vector<std ::shared_ptr<Player>> players;
    std ::vector<int> weeks_goals_for = std ::vector<int>(NUM_WEEKS, EMPTY);
    std ::vector<int> weeks_goals_against = std ::vector<int>(NUM_WEEKS, EMPTY);
    double team_score = 0;
    void sort_team_players_alphabetically(std ::vector<std ::shared_ptr<Player>> &players_for_sorting, std ::vector<std ::pair<int, int>> intervals);
};

class RealTeam : public Team
{
public:
    RealTeam(std ::string name, std ::vector<std ::shared_ptr<Player>> players_list);
    void calculate_score(int num_week);
    double get_real_team_score();
    void print_real_team();
    std ::pair<int, int> get_goals_for_goals_against();

private:
    double calculate_one_match_score(int goals_for, int goals_against);
    int goals_for_till_this_week = 0;
    int goals_against_till_this_week = 0;
};

class FantasyTeam : public Team
{
public:
    FantasyTeam(std ::string name, std ::vector<std ::shared_ptr<Player>> players_list);
    void eliminate_player_from_team(std ::string name);
    bool is_already_created() { return is_created; };
    double calculate_total_score(int week_num);
    void add_new_player(std ::shared_ptr<Player> new_player);
    bool needs_post(std ::string post);
    bool player_is_qualified(std ::shared_ptr<Player> player, int week_num);
    bool is_team_completed() { return is_completed; };
    void print_info(int week_num);
    std ::vector<std ::shared_ptr<Player>> sort_defenders_alphabetically();
    std ::string find_player_by_post(std ::string post);
    void calculate_new_week_score(int num_week);
    void apply_transfer_history();
    bool needs_more_player() { return num_players == NUM_OF_FANTASY_TEAM_PLAYERS; };
    void change_status_team();

private:
    bool is_completed = false;
    bool is_created = false;
    std ::vector<double> week_scores = std ::vector<double>(NUM_WEEKS, EMPTY);
    TransferTable transfer_history;
    int num_players = 0;
    bool has_forward = false;
    bool has_goalkeeper = false;
    bool has_midfielder = false;
    int num_defenders = 0;
};

#endif