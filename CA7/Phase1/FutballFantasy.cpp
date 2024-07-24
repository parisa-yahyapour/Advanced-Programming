#include "FutballFantasy.hpp"

using namespace std;

void FutballFantasy ::process_program()
{
    handle_premier_league_data();
    handle_weeks_data();
    string input_line;
    while (getline(cin, input_line))
    {
        try
        {
            int operation_type_code = EMPTY;
            vector<string> arguments = InputHandler(input_line).seperate_words_in_input_line();
            operation_type_code = recognize_operation_code(arguments[OPERATION_TYPE]);
            switch (operation_type_code)
            {
            case CODE_GET:
                handle_get_command(arguments);
                break;
            case CODE_POST:
                handle_post_command(arguments);
                break;
            case CODE_PUT:
                break;
            case CODE_DELETE:
                break;
            default:
                break;
            }
        }
        catch (const ErrorHandler error)
        {
            error.handle_error();
        }
    }
}

int FutballFantasy ::get_command_code(string operation_word, const vector<string> &operation_words)
{
    for (int i = 0; i < operation_words.size(); i++)
    {
        if (operation_words[i] == operation_word)
        {
            return i;
        }
    }
    throw(ErrorHandler(NOT_FOUND));
    return ERROR;
}

void FutballFantasy ::handle_get_command(vector<string> arguments)
{
    int operation_code = get_command_code(arguments[COMMAND], GET_OPERATIONS);
    switch (operation_code)
    {
    case CODE_TEAM_OF_THE_WEEK:
        this->team_of_the_week(arguments);
        break;
    case CODE_PLAYERS:
        this->get_players(arguments);
        break;
    case CODE_LEAGUE_STANDINGS:
        this->league_standings(arguments);
        break;
    case CODE_USERS_RANKING:
        this->users_ranking(arguments);
        break;
    case CODE_MATCH_RESULT_LEAGUE:
        this->match_reault_league(arguments);
        break;
    case CODE_SQUAD:
        this->squad(arguments);
        break;
    }
}

void FutballFantasy ::handle_post_command(vector<string> arguments)
{
    int operation_code = get_command_code(arguments[COMMAND], POST_OPERATIONS);
    switch (operation_code)
    {
    case CODE_SIGNUP:
        this->signup(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    case CODE_LOGIN:
        this->login(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    case CODE_REGISTER_ADMIN:
        this->register_admin(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    case CODE_LOGOUT:
        this->logout(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    case CODE_SELL_PLAYER:
        this->sell_player(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    case CODE_BUY_PLAYER:
        this->buy_player(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    case CODE_CLOSE_TRANSFER_WINDOW:
        this->close_transfer_window(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    case CODE_OPEN_TRANSFER_WINDOW:
        this->open_transfer_window(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    case CODE_PASS_WEEK:
        this->pass_week(arguments);
        OutputHandler(OK).handle_function_result();
        break;
    }
}

void FutballFantasy ::pass_week(const vector<string> &arguments)
{
    check_correctness_input_static_arguments(arguments, NUM_PASS_WEEK_ARGUMENTD, NO_ARGUMENT_VECTOR);
    check_allowable_request_for_admin();
    current_week = database.find_next_week(current_week);
    update_fantasy_team_players_based_on_transfer_history();
    update_banned_players();
    update_fantasy_teams_score_after_pass_week(current_week->get_num_week());
}

void FutballFantasy ::close_transfer_window(const vector<string> &arguments)
{
    check_correctness_input_static_arguments(arguments, NUM_TRANSFER_ARGUMENTD, NO_ARGUMENT_VECTOR);
    check_allowable_request_for_admin();
    is_transfer_window_open = false;
}

void FutballFantasy ::open_transfer_window(const vector<string> &arguments)
{
    check_correctness_input_static_arguments(arguments, NUM_TRANSFER_ARGUMENTD, NO_ARGUMENT_VECTOR);
    check_allowable_request_for_admin();
    is_transfer_window_open = true;
}

void FutballFantasy ::register_admin(const vector<string> &arguments)
{
    check_correctness_input_static_arguments(arguments, NUM_ARGUMENTS_SIGNUP_LOGIN, KEYWORDS_REGISTER_ADMIN);
    string name, password;
    this->assign_register_admin_values(name, password, arguments);
    if (admin.check_username_password_admin(name, password))
    {
        current_user = NULL;
        admin_registered = true;
    }
    else
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
}

int FutballFantasy ::recognize_operation_code(string operation_word)
{
    if (operation_word == OPERATION_TYPES[CODE_GET])
    {
        return CODE_GET;
    }
    if (operation_word == OPERATION_TYPES[CODE_POST])
    {
        return CODE_POST;
    }
    if (operation_word == OPERATION_TYPES[CODE_PUT])
    {
        return CODE_PUT;
    }
    if (operation_word == OPERATION_TYPES[CODE_DELETE])
    {
        return CODE_DELETE;
    }
    throw(ErrorHandler(BAD_REQUEST));
    return ERROR;
}

vector<string> FutballFantasy ::extract_info_from_file(string address)
{
    ifstream file_stream;
    vector<string> file_lines;
    string line;
    file_stream.open(address);
    while (getline(file_stream, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        file_lines.push_back(line);
    }
    file_stream.close();
    return file_lines;
}

vector<string> FutballFantasy ::separate_by_delimiter(string line, char delimiter)
{
    stringstream line_stream(line);
    string data_each_column;
    vector<string> separated_row;
    while (getline(line_stream, data_each_column, delimiter))
    {
        separated_row.push_back(data_each_column);
    }
    return separated_row;
}

void FutballFantasy ::handle_premier_league_data()
{
    vector<string> file_data = extract_info_from_file(PREIMIER_LEAGUE_FILE_ADDRESS);
    for (int row = 1; row < file_data.size(); row++)
    {
        vector<string> columns_of_each_row = separate_by_delimiter(file_data[row], DELIMITERS[DELIMITER_COLUMNS]);
        save_premier_data_in_database(columns_of_each_row);
    }
}

void FutballFantasy ::save_premier_data_in_database(vector<string> columns)
{
    vector<shared_ptr<Player>> team_players;
    for (int index_column = 1; index_column < columns.size(); index_column++)
    {
        vector<string> one_columns_data = separate_by_delimiter(columns[index_column], DELIMITERS[DELIMITER_EACH_COLUMN_DATA]);
        for (int i = 0; i < one_columns_data.size(); i++)
        {
            shared_ptr<Player> new_player = make_shared<Player>(one_columns_data[i], index_column);
            team_players.push_back(new_player);
            database.add_new_player(new_player);
        }
    }
    shared_ptr<RealTeam> new_team = make_shared<RealTeam>(columns[TEAM], team_players);
    for (int index_player = 0; index_player < team_players.size(); index_player++)
    {
        team_players[index_player]->set_real_team_ptr(new_team);
    }
    database.add_new_real_team(new_team);
}

vector<string> FutballFantasy::create_week_files_addresses()
{
    vector<string> addresses;
    string temp;
    for (int num_week = 1; num_week <= NUM_WEEKS; num_week++)
    {
        temp = WEEK_FILE_ADDRESS + to_string(num_week) + FILE_TYPE;
        addresses.push_back(temp);
    }
    return addresses;
}

void FutballFantasy ::handle_weeks_data()
{
    vector<string> addresses = create_week_files_addresses();
    for (int index_week = 0; index_week < NUM_WEEKS; index_week++)
    {
        vector<string> file_data = extract_info_from_file(addresses[index_week]);
        vector<shared_ptr<Match>> matches_of_week;
        for (int row = 1; row < file_data.size(); row++)
        {
            vector<string> columns_of_each_row = separate_by_delimiter(file_data[row], DELIMITERS[DELIMITER_COLUMNS]);
            save_week_data_in_database(columns_of_each_row, index_week, matches_of_week);
        }
        shared_ptr<WeekTable> new_week = make_shared<WeekTable>(matches_of_week, index_week);
        database.add_new_week(new_week);
    }
}

void FutballFantasy ::save_week_data_in_database(vector<string> columns, int num_week, vector<shared_ptr<Match>> &week_matches)
{
    vector<string> name_teams = separate_by_delimiter(columns[MATCH], DELIMITERS[DELIMITER_NUMBERS]);
    shared_ptr<Team> team1 = database.find_team_by_name(name_teams[0], true);
    shared_ptr<Team> team2 = database.find_team_by_name(name_teams[1], true);
    pair<shared_ptr<Team>, shared_ptr<Team>> team1_team2;
    team1_team2.first = team1;
    team1_team2.second = team2;
    vector<string> result = separate_by_delimiter(columns[RESULT], DELIMITERS[DELIMITER_NUMBERS]);
    pair<int, int> goal_team1_team2(stoi(result[0]), stoi(result[1]));
    team1_team2.first->update_goals_tables(goal_team1_team2.first, goal_team1_team2.second, num_week);
    team1_team2.second->update_goals_tables(goal_team1_team2.second, goal_team1_team2.first, num_week);
    update_player_info(columns, num_week);
    handle_players_scores(columns[SCORES], num_week);
    shared_ptr<Match> new_match = make_shared<Match>(team1_team2, goal_team1_team2);
    week_matches.push_back(new_match);
}

void FutballFantasy ::update_player_score(string player_name_and_score, int num_week)
{
    vector<string> name_and_score = separate_by_delimiter(player_name_and_score, DELIMITERS[DELIMITER_NUMBERS]);
    string player_name = name_and_score[0];
    double player_score = stod(name_and_score[1]);
    shared_ptr<Player> selected_player = database.find_player_by_name(player_name);
    selected_player->update_score(player_score, num_week);
}

void FutballFantasy ::handle_players_scores(string scores_column, int num_week)
{
    vector<string> scores_data = separate_by_delimiter(scores_column, DELIMITERS[DELIMITER_EACH_COLUMN_DATA]);
    for (int index_columns_data = 0; index_columns_data < scores_data.size(); index_columns_data++)
    {
        update_player_score(scores_data[index_columns_data], num_week);
    }
}

void FutballFantasy ::update_player_info(vector<string> columns, int num_week)
{
    for (int index_column = INJURED; index_column <= RED_CARD; index_column++)
    {
        vector<string> columns_data = separate_by_delimiter(columns[index_column], DELIMITERS[DELIMITER_EACH_COLUMN_DATA]);
        switch (index_column)
        {
        case INJURED:
            update_injured_player_info(columns_data, num_week);
            break;
        case YELLOW_CARD:
            update_yellow_card_info(columns_data, num_week);
            break;
        case RED_CARD:
            update_red_card_info(columns_data, num_week);
            break;
        default:
            break;
        }
    }
}

void FutballFantasy ::update_injured_player_info(vector<string> name_players, int num_week)
{
    for (int index_player = 0; index_player < name_players.size(); index_player++)
    {
        shared_ptr<Player> player = database.find_player_by_name(name_players[index_player]);
        player->update_injured_weeks(num_week);
    }
}

void FutballFantasy ::update_yellow_card_info(vector<string> name_players, int num_week)
{
    for (int index_player = 0; index_player < name_players.size(); index_player++)
    {
        shared_ptr<Player> player = database.find_player_by_name(name_players[index_player]);
        player->give_player_yellow_card(num_week);
    }
}

void FutballFantasy ::update_red_card_info(vector<string> name_players, int num_week)
{
    for (int index_player = 0; index_player < name_players.size(); index_player++)
    {
        shared_ptr<Player> player = database.find_player_by_name(name_players[index_player]);
        player->give_player_red_card(num_week);
    }
}

void FutballFantasy ::assign_signup_and_login_values(string &name, string &password, vector<string> inputs)
{
    name = inputs[4];
    password = inputs[6];
}

void FutballFantasy ::assign_register_admin_values(string &name, string &password, vector<string> inputs)
{
    name = inputs[ARGUMENT_1];
    password = inputs[ARGUMENT_2];
}

void FutballFantasy ::signup(vector<string> arguments)
{
    check_correctness_input_static_arguments(arguments, NUM_ARGUMENTS_SIGNUP_LOGIN, KEYWORDS_LOGIN_SIGNUP);
    if (current_user != NULL)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    string name, password;
    this->assign_signup_and_login_values(name, password, arguments);
    this->create_new_user(name, password);
}

void FutballFantasy ::create_new_user(string name, string password)
{
    this->check_username_uniqueness(name);
    vector<shared_ptr<Player>> players;
    shared_ptr<FantasyTeam> new_team = make_shared<FantasyTeam>(name, players);
    shared_ptr<User> new_user = make_shared<User>(name, password, new_team);
    current_user = new_user;
    users.push_back(new_user);
}

void FutballFantasy ::check_username_uniqueness(string name)
{
    for (shared_ptr<User> user : users)
    {
        if (user->has_name(name))
        {
            throw(ErrorHandler(BAD_REQUEST));
        }
    }
}

shared_ptr<User> FutballFantasy::find_user(string name, string password)
{
    bool team_found = false;
    bool password_is_correct = false;
    for (shared_ptr<User> user : users)
    {
        if (user->has_name(name))
        {
            team_found = true;
            if (user->has_password(password))
            {
                return user;
            }
            password_is_correct = false;
        }
    }
    if (!team_found)
    {
        throw(ErrorHandler(NOT_FOUND));
    }
    if (!password_is_correct)
    {
        throw(ErrorHandler(PERMISSION_DENIED));
    }
    return NULL;
}

void FutballFantasy ::login(vector<string> arguments)
{
    check_correctness_input_static_arguments(arguments, NUM_ARGUMENTS_SIGNUP_LOGIN, KEYWORDS_LOGIN_SIGNUP);
    if (current_user != NULL)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    string name, password;
    this->assign_signup_and_login_values(name, password, arguments);
    current_user = find_user(name, password);
}

void FutballFantasy::check_correctness_input_optional_arguments(const vector<string> &arguments, int min, int max, vector<string> keywords)
{
    if (arguments.size() < min ||
        arguments.size() > max ||
        arguments[QUESTION_MARK] != DELIMITER_BETWEEN_OPERATION_ARGUMENTS)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    int index_keyword = KEYWORD1;
    for (int i = 0; i < keywords.size(); i++)
    {
        if (arguments.size() > min &&
            arguments[index_keyword] != keywords[i])
        {
            throw(ErrorHandler(BAD_REQUEST));
        }
    }
}

void FutballFantasy ::team_of_the_week(const vector<string> &arguments)
{
    check_correctness_input_optional_arguments(arguments, MIN_NUM_ARGUMENTS_TEAM_OF_THE_WEEK, MAX_NUM_ARGUMENTS_TEAM_OF_THE_WEEK, KEYWORDS_TEAM_OF_THE_WEEK);
    vector<shared_ptr<Player>> best_players;
    int num_week;
    switch (arguments.size())
    {
    case NUM_TEAM_OF_THE_WEEK_INPUT:
    {
        if (current_week == NULL)
        {
            throw(ErrorHandler(BAD_REQUEST));
        }
        num_week = current_week->get_num_week();
        best_players = database.find_best_players(current_week->get_num_week());
    }
    break;
    case NUM_TEAM_OF_THE_WEEK_INPUT + 2:
        if (current_week->check_invalid_week(stoi(arguments[WEEK_NUMBER]) - 1))
        {
            num_week = stoi(arguments[WEEK_NUMBER]) - 1;
            best_players = database.find_best_players(stoi(arguments[WEEK_NUMBER]) - 1);
        }
        else
        {
            if (stoi(arguments[WEEK_NUMBER]) - 1 > NUM_WEEKS)
            {
                throw(ErrorHandler(NOT_FOUND));
            }
            else
            {
                throw(ErrorHandler(BAD_REQUEST));
            }
        }
        break;
    default:
        throw(ErrorHandler(BAD_REQUEST));
        break;
    }
    OutputHandler(best_players, num_week);
}

void FutballFantasy ::logout(const vector<string> &inputs)
{
    check_correctness_input_static_arguments(inputs, NUM_OF_LOGOUT_INPUTS, NO_ARGUMENT_VECTOR);
    if (admin_registered)
    {
        admin_registered = false;
    }
    else if (current_user != NULL)
    {
        current_user = NULL;
    }
    else
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
}

void FutballFantasy ::users_ranking(const vector<string> &inputs)
{
    check_correctness_input_static_arguments(inputs, NUMBER_OF_USERS_RANKING_INPUTS, NO_ARGUMENT_VECTOR);
    if (users.size() == 0)
    {
        throw(ErrorHandler(EMPTY_ERROR));
    }
    if (current_week == NULL)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    this->rank_users();
    this->print_ranked_users();
}

void FutballFantasy ::rank_users()
{
    for (int index_1 = 0; index_1 < users.size(); index_1++)
    {
        for (int index_2 = index_1 + 1; index_2 < users.size(); index_2++)
        {
            if (!users[index_1]->has_more_total_score_than(users[index_2], current_week->get_num_week()))
            {
                if (users[index_1]->has_equal_score_to(users[index_2], current_week->get_num_week()))
                {
                    sort_alphabetically(users[index_1], users[index_2]);
                }
                else
                {
                    shared_ptr<User> tmp = users[index_1];
                    users[index_1] = users[index_2];
                    users[index_2] = tmp;
                }
            }
            else
            {
                continue;
            }
        }
    }
}

void FutballFantasy ::sort_alphabetically(shared_ptr<User> &user_1, shared_ptr<User> &user_2)
{
    shared_ptr<User> tmp;
    if (user_1->get_username() > user_2->get_username())
    {
        tmp = user_1;
        user_1 = user_2;
        user_2 = tmp;
    }
    return;
}

void FutballFantasy ::print_ranked_users()
{
    for (int i = 0; i < users.size(); i++)
    {
        if (current_week != NULL)
        {
            OutputHandler().print_ranked_users(i + 1, users[i]->get_username(), users[i]->total_score(current_week->get_num_week()));
        }
        else
        {
            throw(ErrorHandler(BAD_REQUEST));
        }
    }
}

void FutballFantasy ::match_reault_league(const vector<string> &arguments)
{
    int num_week = assign_match_reault_league(arguments);
    database.print_matches_of_week(num_week);
}

int FutballFantasy ::assign_match_reault_league(const vector<string> &arguments)
{
    check_correctness_input_optional_arguments(arguments, MIN_NUM_ARGUMENTS_MATCH_RESULT_LEAGUE, MAX_NUM_ARGUMENTS_MATCH_RESULT_LEAGUE, KEYWORDS_MATCHES_REAULT);
    int num_week;
    if (arguments.size() > MIN_NUM_ARGUMENTS_MATCH_RESULT_LEAGUE && arguments[KEYWORD_WEEK] == WEEK)
    {
        int wanted_week = stoi(arguments[WEEK_NUMBER]) - 1;
        if (current_week->check_invalid_week(wanted_week))
        {
            num_week = wanted_week;
        }
        else
        {
            if (stoi(arguments[WEEK_NUMBER]) - 1 > NUM_WEEKS)
            {
                throw(ErrorHandler(NOT_FOUND));
            }
            else
            {
                throw(ErrorHandler(BAD_REQUEST));
            }
        }
    }
    else if (arguments.size() == MIN_NUM_ARGUMENTS_MATCH_RESULT_LEAGUE)
    {
        num_week = current_week->get_num_week();
    }
    return num_week;
}

void FutballFantasy ::league_standings(const vector<string> &arguments)
{
    check_correctness_input_static_arguments(arguments, NUM_ARGUMENTS_LEAGUE_STANDINGS, NO_ARGUMENT_VECTOR);
    int num_week;
    if (current_week == NULL)
    {
        throw(ErrorHandler(EMPTY_ERROR));
    }
    int num_current_week = current_week->get_num_week();
    database.calculate_teams_score(num_current_week);
    database.sort_teams_by_score();
    database.sort_teams_by_diffrence_goals();
    database.sort_team_by_goals_for();
    database.sort_teams_by_name();
    database.print_teams_data();
}

void FutballFantasy ::get_players(const vector<string> &arguments)
{
    check_correctness_input_optional_arguments(arguments, MIN_NUM_ARGUMENTS_PLAYERS, MAX_NUM_ARGUMENTS_PLAYERS, KEYWORDS_PLAYERS);
    string team_name, post_player = NO_PLAYER_POST;
    int type_get_player = calculate_type_get_player(arguments, team_name, post_player);
    shared_ptr<Team> wanted_team = database.find_team_by_name(team_name, true);
    if (wanted_team == NULL)
    {
        throw(ErrorHandler(NOT_FOUND));
    }
    int num_week;
    if (current_week == NULL)
    {
        num_week = EMPTY;
    }
    else
    {
        num_week = current_week->get_num_week();
    }
    wanted_team->calculte_players_score_in_team(num_week);
    switch (type_get_player)
    {
    case TYPE_1:
    {
        vector<pair<int, int>> intervals_for_sorting = wanted_team->make_interval_for_sorting(true);
        wanted_team->sort_team_players_alphabetically(intervals_for_sorting);
        wanted_team->print_team_players(post_player);
    }
    break;
    case TYPE_2:
    {
        wanted_team->sort_team_players_by_rank();
        vector<pair<int, int>> intervals_for_sorting = wanted_team->make_interval_for_sorting(false);
        wanted_team->sort_team_players_alphabetically(intervals_for_sorting);
        wanted_team->print_team_players(post_player);
    }
    break;
    default:
        break;
    }
}

int FutballFantasy ::calculate_type_get_player(const vector<string> &arguments, string &team_name, string &post_player)
{
    team_name = create_team_name(arguments[ARGUMENT_NAME_TEAM]);
    switch (arguments.size())
    {
    case MIN_NUM_ARGUMENTS_PLAYERS:
        return TYPE_1;
        break;
    case MIN_NUM_ARGUMENTS_PLAYERS + 1:
    {
        if (arguments[MIN_NUM_ARGUMENTS_PLAYERS] == POST_PLAYERS[GK] ||
            arguments[MIN_NUM_ARGUMENTS_PLAYERS] == POST_PLAYERS[MD] ||
            arguments[MIN_NUM_ARGUMENTS_PLAYERS] == POST_PLAYERS[FW] ||
            arguments[MIN_NUM_ARGUMENTS_PLAYERS] == POST_PLAYERS[DF])
        {
            post_player = arguments[MIN_NUM_ARGUMENTS_PLAYERS];
            return TYPE_1;
        }
        else if (arguments[MIN_NUM_ARGUMENTS_PLAYERS] == RANK_KEYWORD)
        {
            return TYPE_2;
        }
        else
        {
            throw(ErrorHandler(BAD_REQUEST));
        }
    }
    break;
    case MAX_NUM_ARGUMENTS_PLAYERS:
        post_player = arguments[MIN_NUM_ARGUMENTS_PLAYERS];
        if (arguments[MIN_NUM_ARGUMENTS_PLAYERS + 1] != RANK_KEYWORD)
        {
            throw(ErrorHandler(BAD_REQUEST));
        }
        return TYPE_2;
        break;
    default:
        break;
    }
    return ERROR;
}

string FutballFantasy::create_team_name(string input_team_name)
{
    vector<string> parts_of_team_name = separate_by_delimiter(input_team_name, DELIMITER_BETWEEN_PARTS_OF_TEAM_NAME);
    if (parts_of_team_name.size() != 1)
    {
        string created_team_name;
        for (int part = 0; part < parts_of_team_name.size(); part++)
        {
            created_team_name += parts_of_team_name[part];
            if (part != parts_of_team_name.size() - 1)
            {
                created_team_name += WORD_DELIMITER;
            }
        }
        return created_team_name;
    }
    return input_team_name;
}

void FutballFantasy::check_correctness_input_static_arguments(const vector<string> &arguments, int num_arguments, vector<string> keywords)
{
    if (arguments.size() < num_arguments || arguments.size() > num_arguments)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    int index_first_keyword = KEYWORD1, index_keyword = 0;
    if (keywords == NO_ARGUMENT_VECTOR)
    {
        return;
    }
    if (arguments[QUESTION_MARK] != DELIMITER_BETWEEN_OPERATION_ARGUMENTS)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    for (index_keyword = 0; index_keyword < keywords.size(); index_keyword++)
    {
        if (arguments[index_first_keyword] != keywords[index_keyword])
        {
            throw(ErrorHandler(BAD_REQUEST));
        }
        index_first_keyword += 2;
    }
}

void FutballFantasy ::check_allowable_request_for_admin()
{
    if (!admin_registered)
    {
        throw(ErrorHandler(PERMISSION_DENIED));
    }
}
void FutballFantasy ::check_allowable_request_for_user()
{
    if (current_user == NULL)
    {
        throw(ErrorHandler(PERMISSION_DENIED));
    }
}

void FutballFantasy ::sell_player(const vector<string> &inputs)
{
    check_allowable_request_for_user();
    if (inputs[KEYWORD1] != NAME_KEYWORD ||
        inputs.size() < NUM_ARGUMENTS_BUY_SELL_PLAYER)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    if ((!is_transfer_window_open) || !(current_user->can_sell_player()))
    {
        throw(ErrorHandler(PERMISSION_DENIED));
    }
    string name;
    assign_buy_and_sell_player_value(name, inputs);
    current_user->eliminate_player(name);
}

void FutballFantasy ::assign_buy_and_sell_player_value(string &name, const vector<string> &inputs)
{
    for (int index = 4; index < inputs.size(); index++)
    {
        name += inputs[index];
        if (index == inputs.size() - 1)
        {
            break;
        }
        name += WORD_DELIMITER;
    }
}

void FutballFantasy ::buy_player(const vector<string> &inputs)
{
    check_allowable_request_for_user();
    if (inputs[KEYWORD1] != NAME_KEYWORD ||
        inputs.size() < NUM_ARGUMENTS_BUY_SELL_PLAYER)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    if (!is_transfer_window_open)
    {
        throw(ErrorHandler(PERMISSION_DENIED));
    }
    string name;
    assign_buy_and_sell_player_value(name, inputs);
    shared_ptr<Player> selected_player = database.find_player_by_name(name);
    if (selected_player == NULL)
    {
        throw(ErrorHandler(NOT_FOUND));
    }
    int num_week;
    if (current_week == NULL)
    {
        num_week = EMPTY;
    }
    else
    {
        num_week = current_week->get_num_week();
    }
    current_user->add_player(selected_player, num_week);
}

void FutballFantasy ::squad(const vector<string> &inputs)
{
    check_allowable_request_for_user();
    check_correctness_input_optional_arguments(inputs, MIN_SQUAD_INPUTS, MAX_SQUAD_INPUTS, KEYWORDS_SQUAD);
    if (current_week == NULL)
    {
        throw(ErrorHandler(BAD_REQUEST));
    }
    string team_name;
    this->assign_squad_values(team_name, inputs);
    if (team_name == EMPTY_STRING)
    {
        team_name = current_user->get_username();
    }
    this->print_squad_by_name(team_name);
}

void FutballFantasy ::assign_squad_values(string &team_name, const vector<string> &inputs)
{
    if (inputs.size() == MIN_SQUAD_INPUTS)
    {
        team_name = EMPTY_STRING;
    }
    else
    {
        team_name = inputs[ARGUMENT_1];
    }
    return;
}

void FutballFantasy ::print_squad_by_name(string team_name)
{
    bool team_found = false;
    for (shared_ptr<User> user : users)
    {

        if (user->has_name(team_name))
        {
            team_found = true;
            user->print_team_info(current_week->get_num_week());
        }
    }
    if (!team_found)
    {
        throw(ErrorHandler(NOT_FOUND));
    }
}

void FutballFantasy::update_fantasy_teams_score_after_pass_week(int num_week)
{
    for (int index_user = 0; index_user < users.size(); index_user++)
    {
        users[index_user]->update_user_score_after_pass_week(num_week);
    }
}

void FutballFantasy::update_fantasy_team_players_based_on_transfer_history()
{
    for (int index_user = 0; index_user < users.size(); index_user++)
    {
        users[index_user]->update_players_from_transfer_history();
    }
}

void FutballFantasy::update_banned_players()
{
    database.ban_players_by_yellow_cards(current_week->get_num_week());
}
