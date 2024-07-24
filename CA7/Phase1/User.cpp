#include "User.hpp"
using namespace std;

User ::User(string new_name, string new_password, shared_ptr<FantasyTeam> new_team)
{
    username = new_name;
    password = new_password;
    user_team = new_team;
}

bool User ::has_name(string name)
{
    return username == name;
}

bool User ::has_password(std ::string _password)
{
    return password == _password;
}

void User::print_info()
{
    cout << "name: " << username << endl;
    cout << "password: " << password << endl;
}

bool User ::can_sell_player()
{
    return sold_players_in_week <= MAX_PLAYER_TO_SELL;
}

void User ::eliminate_player(std ::string name)
{
    if (sold_players_in_week == MAX_LEGALL_NUM_SOLD_PLAYER_IN_WEEK)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    user_team->eliminate_player_from_team(name);
    if (user_team->is_already_created())
    {
        sold_players_in_week++;
    }
}

string User ::get_username()
{
    return username;
}

bool User ::has_more_total_score_than(shared_ptr<User> user_2, int week_num)
{
    return this->total_score(week_num) > user_2->total_score(week_num);
}

double User ::total_score(int week_num)
{
    return user_team->calculate_total_score(week_num);
}

bool User ::has_equal_score_to(std ::shared_ptr<User> user_2, int week_num)
{
    return this->total_score(week_num) == user_2->total_score(week_num);
}

void User ::add_player(shared_ptr<Player> new_player, int week_num)
{
    check_number_of_players();
    if (week_num == EMPTY &&
        team_needs_post(new_player->get_post()))
    {
        user_team->add_new_player(new_player);
    }
    else if (this->player_is_validated(new_player, week_num) && week_num != EMPTY)
    {
        user_team->add_new_player(new_player);
    }
    else
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
}

void User::check_number_of_players()
{
    if (user_team->needs_more_player())
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
}

bool User ::player_is_validated(shared_ptr<Player> new_player, int week_num)
{
    if (this->team_needs_post(new_player->get_post()))
    {
        if (this->player_is_available(new_player, week_num))
        {
            return true;
        }
        else
        {
            throw(ErrorHandler(NOT_AVAILABLE_FOR_NEXT_WEEK));
        }
    }
    else
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    return false;
}

bool User ::team_needs_post(string post)
{
    return user_team->needs_post(post);
}

bool User ::player_is_available(shared_ptr<Player> new_player, int week_num)
{
    return user_team->player_is_qualified(new_player, week_num);
}

void User ::print_team_info(int week_num)
{
    if (!user_team->is_team_completed())
    {
        throw(ErrorHandler(EMPTY_ERROR));
    }
    user_team->print_info(week_num);
}

void User::update_user_score_after_pass_week(int num_week)
{
    if (user_team->is_team_completed())
    {
        user_team->calculate_new_week_score(num_week);
    }
}

void User::update_players_from_transfer_history()
{
    user_team->apply_transfer_history();
    user_team->change_status_team();
    sold_players_in_week = 0;
}