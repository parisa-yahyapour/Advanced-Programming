#include "space_for_missions.hpp"
#include <iostream>

void SpaceForMissions ::save_new_mission(Mission *new_mission)
{
    int new_mission_id = new_mission->get_id();
    check_duplicate_mission_id(new_mission_id);
    added_missions.push_back(new_mission);
    used_ids.push_back(new_mission_id);
    cout << "OK" << endl;
}

void SpaceForMissions ::check_duplicate_mission_id(int new_mission_id)
{
    for (int index = 0; index < used_ids.size(); index++)
    {
        if (new_mission_id == used_ids[index])
        {
            throw(ErrorHandler(DUPLICATE_MISSION_ID));
        }
    }
}

Mission *SpaceForMissions ::find_mission_for_driver(int mission_id)
{
    bool status_existence = false;
    for (int index_mission = 0; index_mission < used_ids.size(); index_mission++)
    {
        if (used_ids[index_mission] == mission_id)
        {
            status_existence = true;
            break;
        }
    }
    if (status_existence == false)
    {
        throw(ErrorHandler(MISSION_NOT_FOUND));
    }
    Mission *wanted_mission;
    for (int index_mission = 0; index_mission < added_missions.size(); index_mission++)
    {
        if (mission_id == added_missions[index_mission]->get_id())
        {
            wanted_mission = added_missions[index_mission];
            break;
        }
    }
    return wanted_mission;
}