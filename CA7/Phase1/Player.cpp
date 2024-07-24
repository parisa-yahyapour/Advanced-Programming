#include "Player.hpp"
using namespace std;
Player ::Player(string name, int post)
{
    name_player = name;
    post_player = POST_PLAYERS[post - 1];
}

void Player ::print_player()
{
    cout << "name: " << name_player << " | role: " << post_player << " | score: " << fixed << setprecision(1) << score_player_till_this_week << endl;
}

void Player ::set_real_team_ptr(shared_ptr<RealTeam> team)
{
    player_real_team = team;
}

void Player ::update_injured_weeks(int num_week)
{
    injured_weeks[num_week] = true;
}
void Player ::give_player_yellow_card(int num_week)
{
    yellow_cards[num_week] = true;
}
void Player ::give_player_red_card(int num_week)
{
    red_cards[num_week] = true;
}

bool Player ::check_name(std ::string name)
{
    return name == name_player;
}

void Player ::update_score(double score, int num_week)
{
    scores_of_weeks[num_week] = score;
}

double Player::get_score(int num_week)
{
    return scores_of_weeks[num_week];
}

bool Player ::check_post_player(string post)
{
    return post == post_player;
}

string Player ::get_name()
{
    return name_player;
}

bool Player ::has_name(std ::string name)
{
    return name_player == name;
}

double Player ::get_week_score(int week_num)
{
    return scores_of_weeks[week_num - 1];
}

void Player::calculate_avrage_score(int num_week)
{
    if (num_week == EMPTY)
    {
        return;
    }
    int num_matches = 0;
    double sum_scores = 0;
    for (int index_week = 0; index_week <= num_week; index_week++)
    {
        if (scores_of_weeks[index_week] != EMPTY)
        {
            num_matches++;
            sum_scores += scores_of_weeks[index_week];
        }
    }
    if (sum_scores != 0)
    {
        score_player_till_this_week = sum_scores / num_matches;
    }
}

double Player ::get_average_score()
{
    return score_player_till_this_week;
}

void Player ::print_team_of_the_week(int num_week)
{
    cout << "name: " << name_player << "  post: " << post_player << "  score: " << scores_of_weeks[num_week] << endl;
}

bool Player ::has_been_injured_in_the_past_three_weeks(int week_num)
{
    for (int index = (week_num - 1); (index > (week_num - 4) && index > 0); index--)
    {
        if (injured_weeks[index])
        {
            return true;
        }
    }
    return false;
}

bool Player ::has_received_three_yellow_cards(int week_num)
{
    int total_yellow_cards = 0;
    for (int index = 0; index < week_num; index++)
    {
        if (yellow_cards[index])
        {
            total_yellow_cards++;
        }
    }
    if (total_yellow_cards >= MAX_LEGALL_NUM_YELLOW_CARDS)
    {
        this->update_yellow_cards(week_num);
        return true;
    }
    return false;
}

bool Player ::has_received_red_card_last_week(int week_num)
{
    if (red_cards[week_num])
    {
        return true;
    }
    return false;
}

void Player ::update_yellow_cards(int week_num)
{
    for (int index = 0; index < week_num; index++)
    {
        yellow_cards[index] = false;
    }
    return;
}

void Player::clear_yellow_cards(int week_num)
{
    for (int index_week = 0; index_week <= week_num; index_week++)
    {
        if (yellow_cards[index_week])
        {
            yellow_cards[index_week] = false;
        }
    }
    is_banned = true;
}

void Player::change_player_ban_status()
{
    if (is_banned)
    {
        is_banned = false;
    }
}
