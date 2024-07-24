#ifndef _IO_HANDLER_HPP_
#define _IO_HANDLER_HPP_
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "magic_number.hpp"
#include "Player.hpp"

class InputHandler
{
public:
    InputHandler(std :: string input);
    std::vector<std ::string> seperate_words_in_input_line();

private:
    std::string input_line;
};

class OutputHandler
{
public:
    OutputHandler();
    OutputHandler(std ::vector<std ::shared_ptr<Player>> players, int num_week);
    OutputHandler(int reault);
    void handle_function_result();
    void print_ranked_users(int number_on_list, std :: string team_name, double score);
    void print_budget(int budget);
    void print_squad_info(std :: string team_name, std :: vector<std :: string> player_names, std :: string captain_name, 
        int team_cost, double team_score);

private:
    int status;
};

#endif