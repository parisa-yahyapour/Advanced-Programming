#ifndef _USER_HPP_
#define _USER_HPP_
#include <string>
#include <memory>
#include "Player.hpp"
#include "Team.hpp"
#include <iostream>

class User
{
public:
    User(std ::string new_name, std ::string new_password, std ::shared_ptr<FantasyTeam> new_team);
    bool has_name(std ::string name);
    bool has_password(std ::string _password);
    void print_info();
    bool can_sell_player();
    void eliminate_player(std :: string name);
    std :: string get_username();
    bool has_more_total_score_than(std :: shared_ptr<User> user_2, int week_num);
    double total_score(int week_num);
    bool has_equal_score_to(std :: shared_ptr<User> user_2, int week_num);
    void add_player(std :: shared_ptr<Player> new_player, int week_num);
    bool player_is_validated(std :: shared_ptr<Player> new_player, int week_num);
    bool team_needs_post(std :: string post);
    bool player_is_available(std :: shared_ptr<Player> new_player, int week_num);
    void print_team_info(int week_num);
    void update_user_score_after_pass_week(int num_week);
    void update_players_from_transfer_history();
    void check_number_of_players();

private:
    std ::string username;
    std ::string password;
    std ::shared_ptr<FantasyTeam> user_team;
    int sold_players_in_week = 0;
};
#endif