#ifndef _MISSION_HPP_
#define _MISSION_HPP_

#include <string>
#include <vector>
#include <iostream>
#include "error.hpp"
using namespace std;

const int NUM_ARGUMENTS_FOR_ADDING_MISSION = 6;

enum StatusMissionCompleted
{
    COMPLETED_FOUND,
    NO_COMPLETED_MISSION
};
enum IntForamtOperationWords
{
    INT_MISSION_ID,
    INT_START,
    INT_END,
    INT_TARGET,
    INT_REWARD
};
enum PartIntRecordRide
{
    RECORD_START_TIMESTAMP,
    RECORD_END_TIMESTAMP,
    RECORD_ID_DRIVER,
    DISTANCE
};

class Mission
{
protected:
    int mission_id;
    int start_timestamp;
    int end_timestamp;
    int reward_amount;
    bool is_completed = false;
    int num_arguments;
    int target_mission;

public:
    Mission(int id, int start, int end, int reward, int target)
    {
        mission_id = id;
        start_timestamp = start;
        end_timestamp = end;
        reward_amount = reward;
        target_mission = target;
    }
    virtual Mission *copy_mission() = 0;
    void print_mission();
    void print_mission_for_record_ride(bool is_first);
    void print_mission_for_show_missions();
    int get_id() { return mission_id; };
    int get_start_hour() { return start_timestamp; };
    virtual int check_effect_ride(const vector<int> &operation_parameters, bool is_first) = 0;
    bool is_time_correct(int start, int end);
    virtual bool check_end_mission();
    vector<int> get_info() const;
    void print_status_mission();
    bool status_mission() { return is_completed; };
};

class TimeMission : public Mission
{
private:
public:
    TimeMission(vector<int> parameters)
        : Mission(parameters[INT_MISSION_ID], parameters[INT_START], parameters[INT_END], parameters[INT_REWARD], parameters[INT_TARGET])
    {
        num_arguments = NUM_ARGUMENTS_FOR_ADDING_MISSION;
    }
    int check_effect_ride(const vector<int> &operation_parameters, bool is_first);
    Mission *copy_mission();
};

class DistanceMission : public Mission
{
private:
public:
    DistanceMission(vector<int> parameters)
        : Mission(parameters[INT_MISSION_ID], parameters[INT_START], parameters[INT_END], parameters[INT_REWARD], parameters[INT_TARGET])
    {
        num_arguments = NUM_ARGUMENTS_FOR_ADDING_MISSION;
    }
    int check_effect_ride(const vector<int> &operation_parameters, bool is_first);
    Mission *copy_mission();
};

class CountMission : public Mission
{
private:
    int target_number;
    void decrease_cout() { target_number--; };

public:
    CountMission(vector<int> parameters)
        : Mission(parameters[INT_MISSION_ID], parameters[INT_START], parameters[INT_END], parameters[INT_REWARD], parameters[INT_TARGET])
    {
        num_arguments = NUM_ARGUMENTS_FOR_ADDING_MISSION;
    }
    int check_effect_ride(const vector<int> &operation_parameters, bool is_first);
    Mission *copy_mission();
};
#endif