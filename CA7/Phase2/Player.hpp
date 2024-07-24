#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <tgmath.h>
#include "Team.hpp"
#include "magic_number.hpp"

typedef bool (*condition)(int);

class Player
{

public:
    virtual void print_player();
    Player(std ::vector<std ::string> name_price, int post);
    void set_real_team_ptr(std ::shared_ptr<RealTeam> team);
    void update_injured_weeks(int num_week);
    void give_player_yellow_card(int num_week);
    void give_player_red_card(int num_week);
    bool check_name(std ::string name);
    void update_score(double score, int num_week);
    double get_score(int num_week);
    bool check_post_player(std ::string post);
    std ::string get_name();
    bool has_name(std ::string name);
    double get_week_score(int week_num);
    void calculate_avrage_score(int num_week);
    double get_average_score();
    void print_team_of_the_week(int num_week);
    bool has_been_injured_in_the_past_three_weeks(int week_num);
    bool has_received_three_yellow_cards(int week_num);
    bool has_received_red_card_last_week(int week_num);
    void update_yellow_cards(int week_num);
    std ::string get_post() { return post_player; };
    void clear_yellow_cards(int week_num);
    void change_player_ban_status();
    bool is_player_banned() { return is_banned; };
    void save_player_presence(int num_week, int post_current_match);
    void score_goal_for_player(int num_week);
    void assist_goal_for_player(int num_week);
    int post_player_in_current_match();
    void apply_match_result_score(int num_week, int score_to_add);
    bool was_player_present(int num_week);
    virtual void calculate_player_score_in_week(int num_week, int goals_against) = 0;
    void save_own_goal_for_player(int num_week);
    virtual void calculate_score_attack_direction(std ::vector<int> posts_that_attack, int num_week){};
    virtual void calculate_goals_assists_clean_sheet(int num_week) = 0;
    double get_captaion_score(int nuw_week);
    int get_price() {return player_price;};

protected:
    std ::vector<bool> red_cards = std ::vector<bool>(NUM_WEEKS, false);
    std ::vector<bool> yellow_cards = std ::vector<bool>(NUM_WEEKS, false);
    std ::vector<bool> injured_weeks = std ::vector<bool>(NUM_WEEKS, false);
    std ::vector<bool> was_in_match = std::vector<bool>(NUM_WEEKS, false);
    std ::vector<double> scores_of_weeks = std ::vector<double>(NUM_WEEKS, 0);
    std ::string post_player;
    std ::string name_player;
    std ::shared_ptr<RealTeam> player_real_team;
    std ::shared_ptr<FantasyTeam> player_fantasy_team;
    std ::vector<int> num_goals = std ::vector<int>(NUM_WEEKS, 0);
    std ::vector<int> num_goals_assist = std ::vector<int>(NUM_WEEKS, 0);
    std ::vector<int> num_own_goals = std ::vector<int>(NUM_WEEKS, 0);
    double score_player_till_this_week = 0;
    bool is_banned = false;
    int player_price;
    int post_in_current_match;
    void calculate_own_goal_score(int num_week);
    int calculate_num_attacks(condition func_ptr_condition, const std ::vector<int> &posts_that_attack);
    double calculate_final_score_player(double score);
    
};

class GoalKeeper : public Player
{
public:
    GoalKeeper(std ::vector<std ::string> name_price, int post);
    void calculate_player_score_in_week(int num_week, int goals_against);
    void calculate_goals_assists_clean_sheet(int num_week);
    void print_player();

private:
    std ::vector<bool> clean_sheet = std ::vector<bool>(NUM_WEEKS, false);
    int num_clean_sheets_till_this_week = 0;
};

class MidFielder : public Player
{
public:
    MidFielder(std ::vector<std ::string> name_price, int post);
    void calculate_player_score_in_week(int num_week, int goals_against);
    void calculate_score_attack_direction(std ::vector<int> posts_that_attack, int num_week);
    void calculate_goals_assists_clean_sheet(int num_week);
    void print_player();

private:
    std ::vector<bool> clean_sheet = std ::vector<bool>(NUM_WEEKS, false);
    int num_clean_sheets_till_this_week = 0;
    std ::pair<int, int> goals_assist_till_this_week = std ::pair<int, int>(0, 0);
};

class Forward : public Player
{
public:
    Forward(std ::vector<std ::string> name_price, int post);
    void calculate_player_score_in_week(int num_week, int goals_against);
    void calculate_goals_assists_clean_sheet(int num_week);
    void print_player();

private:
    std ::pair<int, int> goals_assist_till_this_week = std ::pair<int, int>(0, 0);
};

class Defender : public Player
{
public:
    Defender(std ::vector<std ::string> name_price, int post);
    void calculate_player_score_in_week(int num_week, int goals_against);
    void calculate_score_attack_direction(std ::vector<int> posts_that_attack, int num_week);
    void calculate_goals_assists_clean_sheet(int num_week);
    void print_player();

private:
    std ::vector<bool> clean_sheet = std ::vector<bool>(NUM_WEEKS, false);
    int num_clean_sheets_till_this_week = 0;
    std ::pair<int, int> goals_assist_till_this_week = std ::pair<int, int>(0, 0);
};

#endif