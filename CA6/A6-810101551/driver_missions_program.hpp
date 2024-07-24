#ifndef _DRIVER_MISSIONS_PROGRAM_
#define _DRIVER_MISSIONS_PROGRAM_

#include "mission.hpp"
#include "driver.hpp"
#include "space_for_missions.hpp"
#include "error.hpp"
#include <sstream>
#include <iostream>
using namespace std;


class DriverMissionProgram
{
private:
    vector<Driver *> drivers;
    SpaceForMissions mission_space;

public:
    int recognize_operation(string operation_word);
    vector<string> split_operation_words(string input_line);
    void process_program();
    void do_operation(int operation_code, const vector<string> &operation_words);
    void create_new_time_mission(const vector<int> &operation_parameters);
    void create_new_distance_mission(const vector<int> &operation_parameters);
    void create_new_count_mission(const vector<int> &operation_parameters);
    vector<int> convert_operation_words_to_int_add_missions(const vector<string> &operation_words);
    void check_correctness_num_arguments(const vector<string> &operation_words, int true_num);
    void check_correctness_amount_parameters(const vector<int>& operation_parameters, int num_arguments);
    vector<int> prepare_operation_arguments_adding_mission(const vector<string> &operation_words);
    vector<int> prepare_operation_arguments_for_assigning(const vector<string> &operation_words);
    vector<int> prepare_operation_arguments_for_record_ride(const vector<string> &operation_words);
    vector<int> convert_operation_words_to_int_assign(const vector<string> &operation_words);
    vector<int> convert_operation_words_to_int_record_ride(const vector<string> &operation_words);
    void assign_mission_to_driver(const vector<int> &operation_parameters);
    Driver* find_driver(int driver_id);
    Driver* add_new_driver(int driver_id);
    void check_amount_arguments_record_ride(const vector<int> &operation_parameters);
    void record_ride(const vector<int> &operation_parameters);
    void show_driver_mission(int driver_id);
};

#endif