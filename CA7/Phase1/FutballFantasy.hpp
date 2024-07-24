#ifndef _FUTBALL_FANTASY_HPP_
#define _FUTBALL_FANTASY_HPP_

#include <string>
#include <vector>
#include <memory>
#include "User.hpp"
#include "WeekTable.hpp"
#include "Database.hpp"
#include "io_handler.hpp"
#include "magic_number.hpp"
#include "Admin.hpp"
#include "ErrorHandler.hpp"
#include <fstream>
#include <sstream>
#include <exception>

class FutballFantasy
{
public:
    void process_program();

private:
    std ::vector<std ::shared_ptr<User>> users;
    DataBase database;
    std ::shared_ptr<User> current_user = NULL;
    std ::shared_ptr<WeekTable> current_week = NULL;
    bool admin_registered = false;
    bool is_transfer_window_open = true;
    Admin admin;
    int recognize_operation_code(std ::string operation_word);
    int get_command_code(std ::string operation_word, const std ::vector<std ::string> &operation_words);
    void handle_get_command(std ::vector<std ::string> arguments);
    void handle_post_command(std ::vector<std ::string> arguments);
    std ::vector<std ::string> extract_info_from_file(std ::string address);
    std ::vector<std ::string> separate_by_delimiter(std ::string line, char delimiter);
    void handle_premier_league_data();
    void handle_weeks_data();
    void save_premier_data_in_database(std ::vector<std ::string> columns);
    std ::vector<std ::string> create_week_files_addresses();
    void save_week_data_in_database(std ::vector<std ::string> columns, int num_week, std ::vector<std ::shared_ptr<Match>> &week_matches);
    void update_player_info(std ::vector<std ::string> columns, int num_week);
    void update_injured_player_info(std ::vector<std ::string> name_players, int num_week);
    void update_yellow_card_info(std ::vector<std ::string> name_players, int num_week);
    void update_red_card_info(std ::vector<std ::string> name_players, int num_week);
    void handle_players_scores(std ::string scores_column, int num_week);
    void update_player_score(std ::string player_name_and_score, int num_week);
    void signup(std ::vector<std ::string> arguments);
    void assign_signup_and_login_values(std ::string &name, std ::string &password, std ::vector<std ::string> inputs);
    void create_new_user(std ::string name, std ::string password);
    void check_username_uniqueness(std ::string name);
    void login(std ::vector<std ::string> arguments);
    std ::shared_ptr<User> find_user(std ::string name, std ::string password);
    void register_admin(const std ::vector<std ::string> &arguments);
    void assign_register_admin_values(std ::string &name, std::string &password, std ::vector<std ::string> inputs);
    void close_transfer_window(const std ::vector<std ::string> &arguments);
    void open_transfer_window(const std ::vector<std ::string> &arguments);
    void pass_week(const std ::vector<std ::string> &arguments);
    void team_of_the_week(const std ::vector<std ::string> &arguments);
    void logout(const std ::vector<std ::string> &inputs);
    void users_ranking(const std ::vector<std ::string> &inputs);
    void rank_users();
    void sort_alphabetically(std ::shared_ptr<User> &user_1, std ::shared_ptr<User> &user_2);
    void print_ranked_users();
    void match_reault_league(const std ::vector<std ::string> &arguments);
    int assign_match_reault_league(const std ::vector<std ::string> &arguments);
    void league_standings(const std ::vector<std ::string> &arguments);
    void get_players(const std ::vector<std ::string> &arguments);
    int calculate_type_get_player(const std ::vector<std ::string> &arguments, std ::string &team_name, std ::string &post_player);
    std ::string create_team_name(std ::string input_team_name);
    void check_correctness_input_static_arguments(const std ::vector<std::string> &arguments, int num_arguments, std ::vector<std ::string> keywords);
    void check_allowable_request_for_admin();
    void check_allowable_request_for_user();
    void sell_player(const std :: vector<std :: string>& inputs);
    void assign_buy_and_sell_player_value(std :: string& name, const std :: vector<std :: string>& inputs);
    void buy_player(const std :: vector<std :: string>& inputs);
    void squad(const std :: vector<std :: string>& inputs);
    void assign_squad_values(std :: string& team_name, const std :: vector<std :: string>& inputs);
    void print_squad_by_name(std :: string team_name);
    void update_fantasy_teams_score_after_pass_week(int num_week);
    void update_fantasy_team_players_based_on_transfer_history();
    void update_banned_players();

    void check_correctness_input_optional_arguments(const std ::vector<std::string> &arguments, int min, int max, std ::vector<std ::string> keywords);
    
};
#endif