#ifndef _DRIVER_HPP
#define _DRIVER_HPP

#include <string>
#include <vector>
#include "mission.hpp"
#include "error.hpp"
using namespace std;

const int NUM_ARGUMENTS_FOR_ASSIGN = 3;

class Driver
{
    private:
    int driver_id;
    vector<int> id_missions;
    vector<Mission *> driver_missions;
    int num_arguments;
    public:
    int get_dtiver_id(){return driver_id;};
    public:
    Driver(int id)
    {
        driver_id = id;
    }
    void add_new_mission_for_driver(Mission* new_mission);
    void check_duplicate_missions(int mission_id);
    void sort_driver_missions_with_start_time();
    void add_new_ride(const vector<int> &operation_parameters);
    void print_missions_driver();
};

#endif