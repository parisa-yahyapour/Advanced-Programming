#include "mission.hpp"
const int MINUTUE_TO_SECOND = 60;

bool Mission ::is_time_correct(int start, int end)
{
    return (start >= start_timestamp) && (end <= end_timestamp);
}

int TimeMission ::check_effect_ride(const vector<int> &operation_parameters, bool is_first)
{
    if (is_time_correct(operation_parameters[RECORD_START_TIMESTAMP], operation_parameters[RECORD_END_TIMESTAMP]) &&
        is_completed == false)
    {
        int travel_time = (operation_parameters[RECORD_END_TIMESTAMP] - operation_parameters[RECORD_START_TIMESTAMP]) / MINUTUE_TO_SECOND;
        target_mission -= travel_time;
        if (check_end_mission())
        {
            is_completed = true;
            end_timestamp = operation_parameters[RECORD_END_TIMESTAMP];
            print_mission_for_record_ride(is_first);
            return COMPLETED_FOUND;
        }
    }
    return NO_COMPLETED_MISSION;
}

int DistanceMission ::check_effect_ride(const vector<int> &operation_parameters, bool is_first)
{
    if (is_time_correct(operation_parameters[RECORD_START_TIMESTAMP], operation_parameters[RECORD_END_TIMESTAMP]) &&
        is_completed == false)
    {
        target_mission -= operation_parameters[DISTANCE];
        if (check_end_mission())
        {
            is_completed = true;
            end_timestamp = operation_parameters[RECORD_END_TIMESTAMP];
            print_mission_for_record_ride(is_first);
            return COMPLETED_FOUND;
        }
    }
    return NO_COMPLETED_MISSION;
}

int CountMission ::check_effect_ride(const vector<int> &operation_parameters, bool is_first)
{
    if (is_time_correct(operation_parameters[RECORD_START_TIMESTAMP], operation_parameters[RECORD_END_TIMESTAMP]) &&
        is_completed == false)
    {
        target_mission -= 1;
        if (check_end_mission())
        {
            is_completed = true;
            end_timestamp = operation_parameters[RECORD_END_TIMESTAMP];
            print_mission_for_record_ride(is_first);
            return COMPLETED_FOUND;
        }
    }
    return NO_COMPLETED_MISSION;
}

bool Mission ::check_end_mission()
{
    return target_mission < 0 || target_mission == 0;
}

vector<int> Mission ::get_info() const
{
    vector<int> info;
    info.push_back(mission_id);
    info.push_back(start_timestamp);
    info.push_back(end_timestamp);
    info.push_back(target_mission);
    info.push_back(reward_amount);
    return info;
}

Mission *TimeMission ::copy_mission()
{
    TimeMission *copy_time_mission = new TimeMission(this->get_info());
    return copy_time_mission;
}

Mission *DistanceMission ::copy_mission()
{
    DistanceMission *copy_distance_mission = new DistanceMission(this->get_info());
    return copy_distance_mission;
}

Mission *CountMission ::copy_mission()
{
    CountMission *copy_count_mission = new CountMission(this->get_info());
    return copy_count_mission;
}

void Mission ::print_status_mission()
{
    if (is_completed)
    {
        cout << "status: completed" << endl;
    }
    else
    {
        cout << "status: ongoing" << endl;
    }
}

void Mission ::print_mission()
{
    cout << "mission: " << mission_id << endl;
    cout << "start timestamp: " << start_timestamp << endl;
    cout << "end timestamp: " << end_timestamp << endl;
    cout << "reward: " << reward_amount << endl;
}

void Mission ::print_mission_for_record_ride(bool is_first)
{
    if (!is_first)
    {
        cout << endl;
    }
    print_mission();
}

void Mission ::print_mission_for_show_missions()
{
    cout << "mission " << mission_id << ":" << endl;
    cout << "start timestamp: " << start_timestamp << endl;
    if (is_completed)
    {
        cout << "end timestamp: " << end_timestamp << endl;
    }
    else
    {
        cout << "end timestamp: -1" << endl;
    }
    cout << "reward: " << reward_amount << endl;
}