#include "driver.hpp"

void Driver ::add_new_mission_for_driver(Mission *new_mission)
{
    int new_mission_id = new_mission->get_id();
    check_duplicate_missions(new_mission_id);
    driver_missions.push_back(new_mission->copy_mission());
    id_missions.push_back(new_mission_id);
    cout << "OK" << endl;
    sort_driver_missions_with_start_time();
}

void Driver ::check_duplicate_missions(int mission_id)
{
    for (int index_mission = 0; index_mission < id_missions.size(); index_mission++)
    {
        if (id_missions[index_mission] == mission_id)
        {
            throw(ErrorHandler(DUPLICATE_DRIVER_MISSION));
        }
    }
}

void Driver ::sort_driver_missions_with_start_time()
{
    for (int i = 0; i < driver_missions.size() - 1; i++)
    {
        for (int j = i + 1; j < driver_missions.size(); j++)
        {
            if (driver_missions[i]->get_start_hour() > driver_missions[j]->get_start_hour())
            {
                Mission *temp = driver_missions[i];
                driver_missions[i] = driver_missions[j];
                driver_missions[j] = temp;
            }
        }
    }
}

void Driver ::add_new_ride(const vector<int> &operation_parameters)
{
    cout << "completed missions for driver " << driver_id << ":" << endl;
    int num_completed_missions = 0;
    bool is_first = true;
    for (int index_mission = 0; index_mission < driver_missions.size(); index_mission++)
    {
        int status = driver_missions[index_mission]->check_effect_ride(operation_parameters, is_first);
        if (status == COMPLETED_FOUND && num_completed_missions == 0)
        {
            is_first = false;
            num_completed_missions++;
        }
    }
}

void Driver ::print_missions_driver()
{
    if (driver_missions.size() == 0)
    {
        throw(ErrorHandler(DRIVER_MISSION_NOT_FOUND));
    }
    cout << "missions status for driver " << driver_id << ":" << endl;
    for (int index_mission = 0; index_mission < driver_missions.size(); index_mission++)
    {
        driver_missions[index_mission]->print_mission_for_show_missions();
        driver_missions[index_mission]->print_status_mission();
        if (index_mission != driver_missions.size() - 1)
        {
            cout << endl;
        }
    }
}