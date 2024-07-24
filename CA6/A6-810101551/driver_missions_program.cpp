#include "driver_missions_program.hpp"

const int NUM_RECORD_RIDE_ARGUMENTS = 5;
const int NUM_ARGUMENTS_SHOW_MISSIONS = 2;
const int NOT_FOUND = -1;
const int INDEX_DRIVER_ID = 2;
const string TIME_MISSION = "add_time_mission";
const string DISTANCE_MISSION = "add_distance_mission";
const string COUNT_MISSION = "add_count_mission";
const string ASSIGN = "assign_mission";
const string RECORD = "record_ride";
const string SHOW_MISSION_INFO = "show_missions_status";

enum PartsOfRecodRide
{
    OPERATION,
    RECORD_START,
    RECORD_END,
    RECORD_DRIVER_ID,
    RECORD_DIATANCE
};
enum PartOfAssign
{
    ASSIGN_MISSIN_ID,
    ASSIGN_DRIVER_ID
};
enum OperationCode
{
    ADD_TIME_MISSION,
    ADD_DISTANCE_MISSION,
    ADD_COUNT_MISSION,
    ASSIGN_MISSION,
    RECORD_RIDE,
    SHOW_MISSION_STATUS
};
enum PartOfAddingMissions
{
    OPERATION_WORD,
    MISSION_ID,
    START_TIMESTAMP,
    END_TIMESTAMP,
    TARTGET,
    REWARD
};

void DriverMissionProgram ::process_program()
{
    string input_line;
    while (getline(cin, input_line))
    {
        vector<string> splitted_operation_words = split_operation_words(input_line);
        int operation_code = recognize_operation(splitted_operation_words[OPERATION_WORD]);
        try
        {
            do_operation(operation_code, splitted_operation_words);
        }
        catch (const ErrorHandler error)
        {
            error.handle_error();
        }
    }
}

void DriverMissionProgram ::do_operation(int operation_code, const vector<string> &operation_words)
{
    if (operation_code == ADD_TIME_MISSION)
    {
        vector<int> operation_parameters = prepare_operation_arguments_adding_mission(operation_words);
        create_new_time_mission(operation_parameters);
    }
    if (operation_code == ADD_DISTANCE_MISSION)
    {
        vector<int> operation_parameters = prepare_operation_arguments_adding_mission(operation_words);
        create_new_distance_mission(operation_parameters);
    }
    if (operation_code == ADD_COUNT_MISSION)
    {
        vector<int> operation_parameters = prepare_operation_arguments_adding_mission(operation_words);
        create_new_count_mission(operation_parameters);
    }
    if (operation_code == ASSIGN_MISSION)
    {
        vector<int> operation_parameters = prepare_operation_arguments_for_assigning(operation_words);
        assign_mission_to_driver(operation_parameters);
    }
    if (operation_code == RECORD_RIDE)
    {
        vector<int> operation_parameters = prepare_operation_arguments_for_record_ride(operation_words);
        record_ride(operation_parameters);
    }
    if (operation_code == SHOW_MISSION_STATUS)
    {
        check_correctness_num_arguments(operation_words, NUM_ARGUMENTS_SHOW_MISSIONS);
        show_driver_mission(stoi(operation_words[1]));
    }
}

void DriverMissionProgram ::show_driver_mission(int driver_id)
{
    Driver *wanted_driver = find_driver(driver_id);
    if (wanted_driver == NULL)
    {
        throw(ErrorHandler(MISSION_NOT_FOUND));
    }
    wanted_driver->print_missions_driver();
}

void DriverMissionProgram ::record_ride(const vector<int> &operation_parameters)
{
    Driver *wanted_driver = find_driver(operation_parameters[RECORD_ID_DRIVER]);
    wanted_driver->add_new_ride(operation_parameters);
}

vector<int> DriverMissionProgram ::prepare_operation_arguments_for_assigning(const vector<string> &operation_words)
{
    check_correctness_num_arguments(operation_words, NUM_ARGUMENTS_FOR_ASSIGN);
    vector<int> parameters = convert_operation_words_to_int_assign(operation_words);
    return parameters;
}

vector<int> DriverMissionProgram ::prepare_operation_arguments_for_record_ride(const vector<string> &operation_words)
{
    check_correctness_num_arguments(operation_words, NUM_RECORD_RIDE_ARGUMENTS);
    vector<int> parameters = convert_operation_words_to_int_record_ride(operation_words);
    return parameters;
}

void DriverMissionProgram ::check_amount_arguments_record_ride(const vector<int> &operation_parameters)
{
    if (operation_parameters[RECORD_START_TIMESTAMP] > operation_parameters[RECORD_END_TIMESTAMP])
    {
        throw(ErrorHandler(INVALID_ARGUMENT));
    }
}

vector<int> DriverMissionProgram ::convert_operation_words_to_int_record_ride(const vector<string> &operation_words)
{
    vector<int> parameters;
    int start = stoi(operation_words[RECORD_START]);
    int end = stoi(operation_words[RECORD_END]);
    int driver_id = stoi(operation_words[RECORD_DRIVER_ID]);
    int distance = stoi(operation_words[RECORD_DIATANCE]);
    parameters.push_back(start);
    parameters.push_back(end);
    parameters.push_back(driver_id);
    parameters.push_back(distance);
    check_amount_arguments_record_ride(parameters);
    return parameters;
}

void DriverMissionProgram ::assign_mission_to_driver(const vector<int> &operation_parameters)
{
    Mission *wanted_mission = mission_space.find_mission_for_driver(operation_parameters[ASSIGN_MISSIN_ID]);
    Driver *wanted_driver = find_driver(operation_parameters[ASSIGN_DRIVER_ID]);
    if (wanted_driver != NULL)
    {
        wanted_driver->add_new_mission_for_driver(wanted_mission);
    }
    else
    {
        Driver *new_driver = add_new_driver(operation_parameters[ASSIGN_DRIVER_ID]);
        new_driver->add_new_mission_for_driver(wanted_mission);
    }
}

Driver *DriverMissionProgram ::add_new_driver(int driver_id)
{
    Driver *new_driver = new Driver(driver_id);
    drivers.push_back(new_driver);
    return new_driver;
}

Driver *DriverMissionProgram ::find_driver(int driver_id)
{
    for (int index_driver = 0; index_driver < drivers.size(); index_driver++)
    {
        if (driver_id == drivers[index_driver]->get_dtiver_id())
        {
            return drivers[index_driver];
        }
    }
    return NULL;
}

vector<int> DriverMissionProgram ::prepare_operation_arguments_adding_mission(const vector<string> &operation_words)
{
    check_correctness_num_arguments(operation_words, NUM_ARGUMENTS_FOR_ADDING_MISSION);
    vector<int> operation_parameters = convert_operation_words_to_int_add_missions(operation_words);
    check_correctness_amount_parameters(operation_parameters, NUM_ARGUMENTS_FOR_ADDING_MISSION);
    return operation_parameters;
}

void DriverMissionProgram ::create_new_time_mission(const vector<int> &operation_parameters)
{
    TimeMission *new_time_mission = new TimeMission(operation_parameters);
    mission_space.save_new_mission(new_time_mission);
}

void DriverMissionProgram ::create_new_distance_mission(const vector<int> &operation_parameters)
{
    DistanceMission *new_distance_mission = new DistanceMission(operation_parameters);
    mission_space.save_new_mission(new_distance_mission);
}

void DriverMissionProgram ::create_new_count_mission(const vector<int> &operation_parameters)
{
    CountMission *new_count_mission = new CountMission(operation_parameters);
    mission_space.save_new_mission(new_count_mission);
}

int DriverMissionProgram ::recognize_operation(string operation_word)
{
    if (operation_word == TIME_MISSION)
    {
        return ADD_TIME_MISSION;
    }
    if (operation_word == DISTANCE_MISSION)
    {
        return ADD_DISTANCE_MISSION;
    }
    if (operation_word == COUNT_MISSION)
    {
        return ADD_COUNT_MISSION;
    }
    if (operation_word == ASSIGN)
    {
        return ASSIGN_MISSION;
    }
    if (operation_word == RECORD)
    {
        return RECORD_RIDE;
    }
    if (operation_word == SHOW_MISSION_INFO)
    {
        return SHOW_MISSION_STATUS;
    }

    return NOT_FOUND;
}

vector<int> DriverMissionProgram ::convert_operation_words_to_int_add_missions(const vector<string> &operation_words)
{
    vector<int> operation_parameters;
    int mission_id = stoi(operation_words[MISSION_ID]);
    int start_timestamp = stoi(operation_words[START_TIMESTAMP]);
    int end_timestamp = stoi(operation_words[END_TIMESTAMP]);
    int reward = stoi(operation_words[REWARD]);
    int target = stoi(operation_words[TARTGET]);
    operation_parameters.push_back(mission_id);
    operation_parameters.push_back(start_timestamp);
    operation_parameters.push_back(end_timestamp);
    operation_parameters.push_back(target);
    operation_parameters.push_back(reward);
    return operation_parameters;
}

vector<int> DriverMissionProgram ::convert_operation_words_to_int_assign(const vector<string> &operation_words)
{
    vector<int> parameters;
    int mission_id = stoi(operation_words[MISSION_ID]);
    int driver_id = stoi(operation_words[INDEX_DRIVER_ID]);
    parameters.push_back(mission_id);
    parameters.push_back(driver_id);
    return parameters;
}

vector<string> DriverMissionProgram ::split_operation_words(string input_line)
{
    stringstream line_stream(input_line);
    string temp;
    vector<string> words;
    while (line_stream >> temp)
    {
        words.push_back(temp);
    }
    return words;
}

void DriverMissionProgram ::check_correctness_num_arguments(const vector<string> &operation_words, int true_num)
{
    if (operation_words.size() < true_num ||
        operation_words.size() > true_num)
    {
        throw(ErrorHandler(INVALID_ARGUMENT));
    }
}

void DriverMissionProgram ::check_correctness_amount_parameters(const vector<int> &operation_parameters, int num_arguments)
{
    if (num_arguments == NUM_ARGUMENTS_FOR_ADDING_MISSION)
    {
        if (operation_parameters[INT_START] > operation_parameters[INT_END] ||
            operation_parameters[INT_TARGET] < 0 ||
            operation_parameters[INT_REWARD] < 0)
        {
            throw(ErrorHandler(INVALID_ARGUMENT));
        }
    }
}
