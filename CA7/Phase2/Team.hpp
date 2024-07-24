#ifndef _TEAM_HPP_
#define _TEAM_HPP_
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include<cmath>
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
    std ::vector<int> weeks_goals_for = std ::vector<int>(NUM_WEEKS, 0);
    std ::vector<int> weeks_goals_against = std ::vector<int>(NUM_WEEKS, 0);
    double team_score = 0;
    std ::vector<int> posts_score_goal_against_team;
};

class RealTeam : public Team
{
public:
    RealTeam(std ::string name, std ::vector<std ::shared_ptr<Player>> players_list);
    void calculate_score(int num_week);
    double get_real_team_score();
    void print_real_team();
    std ::pair<int, int> get_goals_for_goals_against();
    void update_players_presence_in_week(int num_week, std ::vector<std::string> team_players_name);
    std ::shared_ptr<Player> find_player_by_name_in_team(std ::string name);
    void add_post_that_attack(int code_post_player);
    void apply_win_effect(int num_week);
    void apply_loose_effect(int num_week);
    void apply_equal_effect(int num_week);
    void calculate_real_team_player_week_score(int num_week, int goals_against);
    void calculate_goal_assist_clean_sheets_team_players(int num_week);

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
    std :: shared_ptr<Player> find_player_by_name(std :: string name);
    void set_captain(std :: shared_ptr<Player> new_captain);
    std :: shared_ptr<Player> get_captain(){return team_captain;};
    std:: shared_ptr<Player> find_player_in_transform_table(std :: string name);


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
    std :: shared_ptr<Player> team_captain = NULL;
    int calculate_total_team_cost();
};

#endif