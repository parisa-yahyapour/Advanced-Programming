#include "io_handler.hpp"
using namespace std;
InputHandler ::InputHandler(string input)
{
    input_line = input;
}

vector<string> InputHandler ::seperate_words_in_input_line()
{
    if (input_line == EMPTY_STRING)
    {
        throw(ErrorHandler(NOT_FOUND));
    }
    stringstream line_stream(input_line);
    string temp;
    vector<string> words;
    while (line_stream >> temp)
    {
        words.push_back(temp);
    }
    return words;
}

OutputHandler ::OutputHandler(std ::vector<std ::shared_ptr<Player>> players, int num_week)
{
    cout << "team of the week:" << endl;
    cout << "GoalKeeper: " << players[0]->get_name() << " | "
         << "score: " << fixed << setprecision(1) << players[0]->get_score(num_week) << endl;
    cout << "Defender 1: " << players[1]->get_name() << " | "
         << "score: " << fixed << setprecision(1) << players[1]->get_score(num_week) << endl;
    cout << "Defender 2: " << players[2]->get_name() << " | "
         << "score: " << fixed << setprecision(1) << players[2]->get_score(num_week) << endl;
    cout << "Midfielder: " << players[3]->get_name() << " | "
         << "score: " << fixed << setprecision(1) << players[3]->get_score(num_week) << endl;
    cout << "Forward: " << players[4]->get_name() << " | "
         << "score: " << fixed << setprecision(1) << players[4]->get_score(num_week) << endl;
}

OutputHandler ::OutputHandler(int result)
{
    status = result;
}

void OutputHandler ::handle_function_result()
{
    if (status == OK)
    {
        cout << "OK" << endl;
    }
}

void OutputHandler ::print_ranked_users(int number_on_list, string team_name, double score)
{
    cout << number_on_list << ". "
         << "team_name: " << team_name << " | point: " << fixed << setprecision(1) << score << endl;
}

OutputHandler ::OutputHandler()
{
}
