#ifndef _MAGIC_NUMBER_HPP_
#define _MAGIC_NUMBER_HPP_

#include <string>
#include <vector>

const int NUM_GET_OPERATIONS = 7;
const int NUM_POST_OPERATIONS = 10;
const int NUM_OPERATIONS_TYPES = 4;
const int ERROR = -1;
const int EMPTY = -1;
const int NUM_WEEKS = 19;
const int EMPTY_LINE = 0;
const int NUM_OF_SIGNUP_INPUTS = 7;
const int NUM_OF_LOGIN_INPUTS = 7;
const int NUM_OF_ADMIN_INPUTS = 2;
const int NUM_TEAM_OF_THE_WEEK_INPUT = 3;
const int NUM_OF_LOGOUT_INPUTS = 2;
const int MAX_PLAYER_TO_SELL = 2;
const int NUMBER_OF_USERS_RANKING_INPUTS = 2;
const int MAX_NUM_ARGUMENTS_PLAYERS = 7;
const int MIN_NUM_ARGUMENTS_PLAYERS = 5;
const int MIN_NUM_ARGUMENTS_MATCH_RESULT_LEAGUE = 3;
const int MAX_NUM_ARGUMENTS_MATCH_RESULT_LEAGUE = 5;
const int NUM_ARGUMENTS_BUY_SELL_PLAYER = 5;
const int WINNER_SCORE = 3;
const int EQUAL_SCORE = 1;
const int LOSER_SCORE = 0;
const int DEFAULT_SECOND_MAX_SCORE = -2;
const int OK = 0;
const int BAD_REQUEST = -1;
const int PERMISSION_DENIED = -2;
const int NOT_FOUND = -3;
const int EMPTY_ERROR = -4;
const int NOT_AVAILABLE_FOR_NEXT_WEEK = -5;
const int NUM_OF_FANTASY_TEAM_PLAYERS = 5;
const int MIN_SQUAD_INPUTS = 3;
const int MAX_SQUAD_INPUTS = 5;
const int MIN_NUM_ARGUMENTS_TEAM_OF_THE_WEEK = 3;
const int MAX_NUM_ARGUMENTS_TEAM_OF_THE_WEEK = 5;
const int NUM_ARGUMENTS_LEAGUE_STANDINGS = 2;
const int NUM_ARGUMENTS_SIGNUP_LOGIN = 7;
const int NUM_PASS_WEEK_ARGUMENTD = 2;
const int NUM_TRANSFER_ARGUMENTD = 2;
const int MAX_LEGALL_NUM_YELLOW_CARDS = 3;
const int LEGALL_NUM_DEFENDERS = 2;
const int LEGALL_NUM_OTHER_POSTS = 1;
const int MAX_LEGALL_NUM_SOLD_PLAYER_IN_WEEK = 2;
const int DIFFULT_BUDGET = 2500;
const int DEFUALT_SCORE_GOALKEEPER = 3;
const int DEFUALT_SCORE_MIDFIELDER = 0;
const int WIN_SCORE_FOR_PLAYER = 5;
const int LOSE_SCORE_FOR_PLAYER = -1;
const int EQUAL_SCORE_FOR_PLAYER = 1;
const int SCORE_FOR_CLEAN_SHEET_GOALKEEPER = 5;
const int SCORE_FOR_GOAL_AGAINST_GK = -1;
const int SCORE_CLEAN_SHEET_FOR_MIDFIELDER = 1;
const int SCORE_GOAL_FOR_MIDFIELDER = 3;
const int SCORE_ASSIST_GOAL_MIDFIELDER = 2;
const int SCORE_GOAL_FOR_FORWARD = 3;
const int SCORE_ASSIST_GOAL_FOR_FORWARD = 1;
const int SCORE_NO_GOAL_FOR_FORWARD = -1;
const int DEFAULT_SCORE_DEFENDER = 1;
const int SCORE_CLEAN_SHEET_FOR_DEFENDER = 2;
const int SCORE_GOAL_FOR_DEFENDER = 4;
const int SCORE_ASSIST_GOAL_FOR_DEFENDER = 3;
const int SCORE_OWN_GOAL = -3;
const int SCORE_FOR_GOAL_AGAINST_DEFENDER = -1;
const int SCORE_FOR_GOAL_AGAINST_MIDFIELDER = -1;
const int NUM_ARGUMENTS_SET_CAPTAIN = 5;
const int NUM_ARGUMENTS_SHOW_BUDGET = 2;

const char DELIMITER = ' ';
const char DELIMITER_BETWEEN_PARTS_OF_TEAM_NAME = '_';

const std ::vector<std ::string> GET_OPERATIONS =
    {"team_of_the_week",
     "players",
     "league_standings",
     "users_ranking",
     "matches_result_league",
     "squad",
     "show_budget"};
const std ::vector<std ::string> POST_OPERATIONS =
    {
        "signup",
        "login",
        "register_admin",
        "logout",
        "sell_player",
        "buy_player",
        "close_transfer_window",
        "open_transfer_window",
        "pass_week",
        "set_captain"};
const std ::vector<std ::string> POST_PLAYERS =
    {
        "gk",
        "df",
        "md",
        "fw"};
const std ::vector<char> DELIMITERS =
    {
        ',',
        ';',
        ':',
        '$'};
const std ::vector<std ::string> SQUAD_PLAYER_POSTS =
    {
        "Goalkeeper: ",
        "Defender1: ",
        "Defender2: ",
        "Midfielder: ",
        "Striker: "};
const std ::string PREIMIER_LEAGUE_FILE_ADDRESS = "./data/premier_league.csv";
const std ::string WEEK_FILE_ADDRESS = "./data/weeks_stats/week_";
const std ::string FILE_TYPE = ".csv";
const std ::string TEAM_NAME = "team_name";
const std ::string USERNAME = "username";
const std ::string PASSWORD = "password";
const std ::string WEEK = "week_num";
const std ::string DEFAULT_ADMIN_USERNAME = "admin";
const std ::string DEFAULT_ADMIN_PASSWORD = "123456";
const std ::string DELIMITER_BETWEEN_OPERATION_ARGUMENTS = "?";
const std ::string OPERATION_TYPES[NUM_OPERATIONS_TYPES] = {"GET", "POST", "DELETE", "PUT"};
const std ::string WORD_DELIMITER = " ";
const std ::string RANK_KEYWORD = "ranks";
const std ::string NO_PLAYER_POST = "NO_POST";
const std ::string NAME_KEYWORD = "name";
const std ::string FANTASY_TEAM_KEYWORD = "fantasy_team";
const std ::string EMPTY_STRING = "";
const std ::string NUMBER_WORD_SEPERATOR = ". ";
const std ::string OWN_GOAL = "OWN_GOAL";
const std ::string CAPTAIN = " (CAPTAIN)";

const std ::vector<std ::string> KEYWORDS_TEAM_OF_THE_WEEK = {WEEK};
const std ::vector<std ::string> NO_ARGUMENT_VECTOR = {};
const std ::vector<std ::string> KEYWORDS_PLAYERS = {TEAM_NAME};
const std ::vector<std ::string> KEYWORDS_MATCHES_REAULT = {WEEK};
const std ::vector<std ::string> KEYWORDS_LOGIN_SIGNUP = {TEAM_NAME, PASSWORD};
const std ::vector<std ::string> KEYWORDS_REGISTER_ADMIN = {USERNAME, PASSWORD};
const std ::vector<std ::string> KEYWORDS_SELL_BUY_PLAYER = {NAME_KEYWORD};
const std ::vector<std ::string> KEYWORDS_SQUAD = {FANTASY_TEAM_KEYWORD};
const std ::vector<std ::string> KEYWORDS_SET_CAPTAIN = {NAME_KEYWORD};

const bool HAS_ARGUMENT = true;
const bool NO_ARGUMENT = false;
const bool BUY = true;
const bool SELL = false;

enum GetOperationCode
{
    CODE_TEAM_OF_THE_WEEK,
    CODE_PLAYERS,
    CODE_LEAGUE_STANDINGS,
    CODE_USERS_RANKING,
    CODE_MATCH_RESULT_LEAGUE,
    CODE_SQUAD,
    CODE_SHOW_BUDGET
};
enum PostOperationCode
{
    CODE_SIGNUP,
    CODE_LOGIN,
    CODE_REGISTER_ADMIN,
    CODE_LOGOUT,
    CODE_SELL_PLAYER,
    CODE_BUY_PLAYER,
    CODE_CLOSE_TRANSFER_WINDOW,
    CODE_OPEN_TRANSFER_WINDOW,
    CODE_PASS_WEEK,
    CODE_SET_CAPTAIN
};
enum CodeOperationType
{
    CODE_GET,
    CODE_POST,
    CODE_DELETE,
    CODE_PUT
};
enum IndexInputLine
{
    OPERATION_TYPE,
    COMMAND,
    QUESTION_MARK
};
enum ColumnsOFPremierLeague
{
    TEAM,
    GLOALKEEPER,
    DEFENDER,
    MIDFIELDER,
    FORWARD
};
enum DelimitersType
{
    DELIMITER_COLUMNS,
    DELIMITER_EACH_COLUMN_DATA,
    DELIMITER_NUMBERS,
    DELIMITER_PRICE
};
enum ColumnsOfWeekFile
{
    MATCH,
    RESULT,
    INJURED,
    YELLOW_CARD,
    RED_CARD,
    GOALS_WITH_ASSOST,
    PLAYERS_TEAM1,
    PLAYERS_TEAM2
};
enum PartsOfRegister
{
    TYPE,
    OPERATION,
    INPUT_DELIMITER,
    KEYWORD1,
    ARGUMENT_1,
    KEYWORD2,
    ARGUMENT_2
};
enum TeamOfTheWeek
{
    GET,
    METHOD,
    DELIMITER_QUESTION_MARK,
    KEYWORD_WEEK,
    WEEK_NUMBER
};
enum PostPlayers
{
    GK,
    DF,
    MD,
    FW
};
enum PartOfGetPlayer
{
    KEYWORD_TEAM_NAME = 3,
    ARGUMENT_NAME_TEAM,
    OPTIONAL_POST_PART,
    OPTIONAL_RANK
};
enum TypeOfGetPlayer
{
    TYPE_1,
    TYPE_2
};
enum PostPlayerInMatch
{
    MAIN_GOALKEEPER,
    DEFENDER_LEFT_CORNER,
    DEFENDER_LEFT_CENTER,
    DEFENDER_RIGHT_CENTER,
    DEFENDER_RIGHT_CORNER,
    MIDFIELDER_LEFT,
    MIDFIELDER_CENTER,
    MIDFIELDER_RIGHT,
    FORWARD_LEFT,
    FORWARD_CENTER,
    FORWARD_RIGHT
};
#endif