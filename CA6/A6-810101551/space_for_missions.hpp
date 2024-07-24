#ifndef _SPACE_FOR_MISSIONS_
#define _SPACE_FOR_MISSIONS_

#include <vector>
#include <string>
#include<iostream>
#include "mission.hpp"
#include "error.hpp"
using namespace std;



class SpaceForMissions
{
private:
    vector<Mission *> added_missions;
    vector<int> used_ids;

public:
    void save_new_mission(Mission *new_mission);
    void check_duplicate_mission_id(int new_mission_id);
    Mission* find_mission_for_driver(int mission_id);
};


#endif