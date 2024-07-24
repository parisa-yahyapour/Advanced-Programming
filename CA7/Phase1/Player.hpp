#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "Team.hpp"
#include "magic_number.hpp"

class Player
{

public:
    void print_player();
    Player(std ::string name, int post);
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
    bool is_player_banned(){return is_banned;};

private:
    std ::vector<bool> red_cards = std ::vector<bool>(NUM_WEEKS, false);
    std ::vector<bool> yellow_cards = std ::vector<bool>(NUM_WEEKS, false);
    std ::vector<bool> injured_weeks = std ::vector<bool>(NUM_WEEKS, false);
    std ::vector<double> scores_of_weeks = std ::vector<double>(NUM_WEEKS, EMPTY);
    std ::string post_player;
    std ::string name_player;
    std ::shared_ptr<RealTeam> player_real_team;
    std ::shared_ptr<FantasyTeam> player_fantasy_team;
    double score_player_till_this_week = 0;
    bool is_banned = false;
};

#endif