#include "Player.hpp"
using namespace std;
Player ::Player(vector<string> name_price, int post)
{
    name_player = name_price[0];
    player_price = stoi(name_price[1]);
    post_player = POST_PLAYERS[post - 1];
}

void Player ::print_player()
{
    cout << "name: " << name_player << " | role: " << post_player << " | score: " << fixed << setprecision(1) << score_player_till_this_week
         << " | cost: " << player_price;
}

void GoalKeeper::print_player()
{
    Player ::print_player();
    cout << " | clean sheets: " << num_clean_sheets_till_this_week << endl;
}

void Defender::print_player()
{
    Player ::print_player();
    cout << " | goals: " << goals_assist_till_this_week.first << " | assists: " << goals_assist_till_this_week.second
         << " | clean sheets: " << num_clean_sheets_till_this_week << endl;
}

void MidFielder::print_player()
{
    Player ::print_player();
    cout << " | goals: " << goals_assist_till_this_week.first << " | assists: " << goals_assist_till_this_week.second
         << " | clean sheets: " << num_clean_sheets_till_this_week << endl;
}

void Forward::print_player()
{
    Player ::print_player();
    cout << " | goals: " << goals_assist_till_this_week.first << " | assists: " << goals_assist_till_this_week.second << endl;
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
    return calculate_final_score_player(scores_of_weeks[num_week]);
}

double Player::get_captaion_score(int num_week)
{

    return calculate_final_score_player(2 * scores_of_weeks[num_week]);
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

double Player::calculate_final_score_player(double score)
{
    double power_neper = -(score / 6);
    double fraction = 1 / (1 + exp(power_neper));
    return fraction * 10;
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
        if (was_player_present(num_week))
        {
            num_matches++;
            sum_scores += calculate_final_score_player(scores_of_weeks[index_week]);
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

GoalKeeper ::GoalKeeper(std ::vector<std ::string> name_price, int post) : Player(name_price, post)
{
}

MidFielder ::MidFielder(std ::vector<std ::string> name_price, int post) : Player(name_price, post)
{
}

Forward ::Forward(std ::vector<std ::string> name_price, int post) : Player(name_price, post)
{
}

Defender ::Defender(std ::vector<std ::string> name_price, int post) : Player(name_price, post)
{
}

void Player::save_player_presence(int num_week, int post_in_match)
{
    was_in_match[num_week] = true;
    post_in_current_match = post_in_match;
}

void Player::score_goal_for_player(int num_week)
{
    num_goals[num_week]++;
    // player_real_team->score_goal_for_team(num_week);
}

void Player::assist_goal_for_player(int num_week)
{
    num_goals_assist[num_week]++;
}

int Player::post_player_in_current_match()
{
    return post_in_current_match;
}

void Player::apply_match_result_score(int num_week, int score_to_add)
{
    scores_of_weeks[num_week] = 0;
    scores_of_weeks[num_week] += score_to_add;
}

bool Player::was_player_present(int num_week)
{
    return was_in_match[num_week];
}

void Player::save_own_goal_for_player(int num_week)
{
    num_own_goals[num_week]++;
}

void Player::calculate_own_goal_score(int num_week)
{
    scores_of_weeks[num_week] += num_own_goals[num_week] * SCORE_OWN_GOAL;
}

void GoalKeeper::calculate_player_score_in_week(int num_week, int goals_against)
{
    scores_of_weeks[num_week] += DEFUALT_SCORE_GOALKEEPER;
    if (goals_against == 0)
    {
        scores_of_weeks[num_week] += SCORE_FOR_CLEAN_SHEET_GOALKEEPER;
        clean_sheet[num_week] = true;
    }
    scores_of_weeks[num_week] += SCORE_FOR_GOAL_AGAINST_GK * goals_against;
    calculate_own_goal_score(num_week);
}

void MidFielder::calculate_player_score_in_week(int num_week, int goals_against)
{
    if (goals_against == 0)
    {
        scores_of_weeks[num_week] += SCORE_CLEAN_SHEET_FOR_MIDFIELDER;
        clean_sheet[num_week] = true;
    }
    scores_of_weeks[num_week] += num_goals[num_week] * SCORE_GOAL_FOR_MIDFIELDER;
    scores_of_weeks[num_week] += num_goals_assist[num_week] * SCORE_ASSIST_GOAL_MIDFIELDER;
    calculate_own_goal_score(num_week);
}

void Forward::calculate_player_score_in_week(int num_week, int goals_against)
{
    scores_of_weeks[num_week] += num_goals_assist[num_week] * SCORE_ASSIST_GOAL_FOR_FORWARD;
    if (num_goals[num_week] == 0)
    {
        scores_of_weeks[num_week] += SCORE_NO_GOAL_FOR_FORWARD;
    }
    else
    {
        scores_of_weeks[num_week] += num_goals[num_week] * SCORE_GOAL_FOR_FORWARD;
    }
    calculate_own_goal_score(num_week);
}

void Defender::calculate_player_score_in_week(int num_week, int goals_against)
{
    scores_of_weeks[num_week] += DEFAULT_SCORE_DEFENDER;
    if (goals_against == 0)
    {
        scores_of_weeks[num_week] += SCORE_CLEAN_SHEET_FOR_DEFENDER;
        clean_sheet[num_week] = true;
    }
    scores_of_weeks[num_week] += num_goals[num_week] * SCORE_GOAL_FOR_DEFENDER;
    scores_of_weeks[num_week] += num_goals_assist[num_week] * SCORE_ASSIST_GOAL_FOR_DEFENDER;
    calculate_own_goal_score(num_week);
}

bool condition_for_defender_left(int attack_post)
{
    return (attack_post == FORWARD_RIGHT) || (attack_post == DEFENDER_RIGHT_CORNER);
}

bool condition_for_defender_right(int attack_post)
{
    return (attack_post == FORWARD_LEFT) || (attack_post == DEFENDER_LEFT_CORNER);
}

bool condition_for_defender_center(int attack_post)
{
    return (attack_post == FORWARD_CENTER) || (attack_post == DEFENDER_LEFT_CENTER) || (attack_post == DEFENDER_RIGHT_CENTER);
}

bool condition_for_midfieslders(int attack_post)
{
    return (attack_post == MIDFIELDER_CENTER) || (attack_post == MIDFIELDER_RIGHT) || (attack_post == MIDFIELDER_LEFT);
}

void Defender::calculate_score_attack_direction(vector<int> posts_that_attack, int num_week)
{
    int num_score_for_decreasing = 0;
    if (post_in_current_match == DEFENDER_LEFT_CORNER)
    {
        num_score_for_decreasing = calculate_num_attacks(condition_for_defender_left, posts_that_attack);
    }
    else if (post_in_current_match == DEFENDER_RIGHT_CORNER)
    {
        num_score_for_decreasing = calculate_num_attacks(condition_for_defender_right, posts_that_attack);
    }
    else
    {
        num_score_for_decreasing = calculate_num_attacks(condition_for_defender_center, posts_that_attack);
    }
    scores_of_weeks[num_week] += (num_score_for_decreasing * SCORE_FOR_GOAL_AGAINST_DEFENDER);
}

void MidFielder::calculate_score_attack_direction(vector<int> posts_that_attack, int num_week)
{
    int num_score_for_decreasing = calculate_num_attacks(condition_for_midfieslders, posts_that_attack);
    scores_of_weeks[num_week] += num_score_for_decreasing * SCORE_FOR_GOAL_AGAINST_MIDFIELDER;
}

int Player::calculate_num_attacks(condition func_ptr_condition, const vector<int> &posts_that_attack)
{
    int num_goals = 0;
    for (int index_attack = 0; index_attack < posts_that_attack.size(); index_attack++)
    {
        if (func_ptr_condition(posts_that_attack[index_attack]))
        {
            num_goals++;
        }
    }
    return num_goals;
}

void GoalKeeper::calculate_goals_assists_clean_sheet(int num_week)
{
    int num_clean_sheet = 0;
    for (int index_week = 0; index_week <= num_week; index_week++)
    {
        if (clean_sheet[index_week])
        {
            num_clean_sheet++;
        }
    }
    num_clean_sheets_till_this_week = num_clean_sheet;
}

void Defender::calculate_goals_assists_clean_sheet(int num_week)
{
    int num_clean_sheet = 0, goals = 0, assist = 0;
    for (int index_week = 0; index_week <= num_week; index_week++)
    {
        if (clean_sheet[index_week])
        {
            num_clean_sheet++;
        }
        goals += num_goals[index_week];
        assist += num_goals_assist[index_week];
    }
    num_clean_sheets_till_this_week = num_clean_sheet;
    goals_assist_till_this_week.first = goals;
    goals_assist_till_this_week.second = assist;
}

void MidFielder::calculate_goals_assists_clean_sheet(int num_week)
{
    int num_clean_sheet = 0, goals = 0, assist = 0;
    for (int index_week = 0; index_week <= num_week; index_week++)
    {
        if (clean_sheet[index_week])
        {
            num_clean_sheet++;
        }
        goals += num_goals[index_week];
        assist += num_goals_assist[index_week];
    }
    num_clean_sheets_till_this_week = num_clean_sheet;
    goals_assist_till_this_week.first = goals;
    goals_assist_till_this_week.second = assist;
}

void Forward::calculate_goals_assists_clean_sheet(int num_week)
{
    int goals = 0, assist = 0;
    for (int index_week = 0; index_week <= num_week; index_week++)
    {
        goals += num_goals[index_week];
        assist += num_goals_assist[index_week];
    }
    goals_assist_till_this_week.first = goals;
    goals_assist_till_this_week.second = assist;
}
