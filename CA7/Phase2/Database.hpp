#ifndef _DATABASE_HPP_
#define _DATABASE_HPP_
#include <vector>
#include <memory>
#include "WeekTable.hpp"
#include "Team.hpp"
#include "Player.hpp"

class DataBase
{
public:
    void add_new_player(std ::shared_ptr<Player> new_player);
    void add_new_real_team(std ::shared_ptr<RealTeam> new_team);
    void add_new_week(std ::shared_ptr<WeekTable> new_week);
    std ::shared_ptr<RealTeam> find_team_by_name(std ::string name);
    std ::shared_ptr<Player> find_player_by_name(std ::string name);
    std ::shared_ptr<WeekTable> find_next_week(std ::shared_ptr<WeekTable> current_week);
    std ::vector<std ::shared_ptr<Player>> find_best_players(int num_week);
    void print_matches_of_week(int num_week);
    void calculate_teams_score(int num_week);
    void sort_teams_by_score();
    void sort_teams_by_diffrence_goals();
    void sort_team_by_goals_for();
    void sort_teams_by_name();
    void print_teams_data();
    void ban_players_by_yellow_cards(int week_num);

private:
    std::vector<std::shared_ptr<RealTeam>> real_teams;
    std::vector<std::shared_ptr<FantasyTeam>> fantasy_teams;
    std::vector<std ::shared_ptr<WeekTable>> week_tables;
    std::vector<std::shared_ptr<Player>> players;
    void sort_players_by_score(int num_week);
    void sort_players_by_name(std ::vector<std ::shared_ptr<Player>> &chosen_players);
    std::shared_ptr<Player> find_best_player_in_post(std ::string post, int num_week);
    std::vector<std::shared_ptr<Player>> find_best_DFs(int num_week);
    double find_max_score(std ::string post, int num_week);
    void sort_teams_with_same_score_by_diffrence_goals(std ::pair<int, int> interval);
    void sort_teams_with_same_score_diffrence_goal_by_goals_for(std ::pair<int, int> interval);
    void sort_teams_with_same_score_diffrence_goal_goals_for_by_name(std ::pair<int, int> interval);
};

#endif