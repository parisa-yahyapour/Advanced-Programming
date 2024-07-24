#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

const string EMPLOYEES_INFO_FILE = "employees.csv";
const string TEAM_INFO_FILE = "teams.csv";
const string SALARY_INFO_FILE = "salary_configs.csv";
const string WORKING_HOUR_INFO_FILE = "working_hours.csv";

const string ADD_INTERVAL = "add_working_hours";
const string DELETE_INTERVAL = "delete_working_hours";
const string TOTAL_WORKING_HOUR = "report_total_hours_per_day";
const string REPORT_LEVEL_SALARY = "show_salary_config";
const string EMPLOYEE_SALARY = "report_employee_salary";
const string UPDATE_BONUS = "update_team_bonus";
const string UPDATE_LEVEL = "update_salary_config";
const string AVERAGE_EMPLOYEE_PER_HOUR = "report_employee_per_hour";
const string SALARY_ALL_EMPLOYEES = "report_salaries";
const string TEAM_SALARY = "report_team_salary";
const string FIND_BONUS_CAPABLE_TEAMS = "find_teams_for_bonus";

const int COLUMN_TEAM_ID = 0;
const int COLUMN_TEAM_HEAD_ID = 1;
const int COLUMN_MEMBERS_ID = 2;
const int COLUMN_BONUS_MIN_HOUR = 3;
const int COLUMN_MAX_VARIANCE = 4;
const int COLUMN_LEVEL = 0;
const int COLUMN_BASE_SALARY = 1;
const int COLUMN_SALARY_PER_HOUR = 2;
const int COLUMN_SALARY_EXTRA_HOUR = 3;
const int COLUMN_OFFICIAL_WORKING_HOUR = 4;
const int COLUMN_TAX = 5;
const int COLUMN_EMPLOYEE_ID = 0;
const int COLUMN_EMPLOYEE_NAME = 1;
const int COLUMN_EMPLOYEE_AGE = 2;
const int COLUMN_EMPLOYEE_LEVEL = 3;
const int COLUMN_DAY = 1;
const int COLUMN_START = 2;
const int COLUMN_END = 3;
const int COLUMN_WORKING_INTERVAL = 2;

const int MAX_HOUR = 24;
const int MIN_HOUR = 0;
const int MAX_DAY = 30;
const int MIN_DAY = 1;
const char DELIMITER_MEMBERS = '$';
const char DELIMITER_INTERVAL = '-';
const int SALARY_PARAMETER_NUM = 6;
const int LEVELS_NUM = 4;
const double ROUNDING_AMOUNT = 0.1;

const int ADD_WORKING_HOUR = 1;
const int DELETE_WORKING_HOUR = 2;
const int REPORT_TOTAL_WORKING_HOUR = 3;
const int SHOW_SALARY_CONFIG = 4;
const int REPORT_EMPLOYEE_SALARY = 5;
const int UPDATE_TEAM_BONUS = 6;
const int UPDATE_SALARY_CONFIG = 7;
const int REPORT_EMPLOYEE_PER_HOUR = 8;
const int REPORT_SALARIES = 9;
const int REPORT_TEAM_SALARY = 10;
const int FIND_TEAMS_FOR_BONUS = 11;

const int NO_EMPLOYEE = -1;
const int NOT_FOUND = -2;
const int INVALID_ARGUMENT = -3;
const int OVERLAP_FOUND = -4;
const int EMPTY = -5;
const int INVALID_LEVEL = -6;
const int NO_TEAM = -7;
const int NO_BONUS_TEAMS = -8;

const int OK = 1;
const int RESULT_PRINTED = 2;

const double POINT_ONE_PRECISION = 0.1;
const double POINT_ZERO_ZERO_ONE_PRECISION = 0.001;

struct interval_data
{
    int start;
    int end;
    double num_employees = 0;
};

double round_to(double init_number, double precision)
{
    return round(init_number / precision) * precision;
}

class Employee;
class Team;
class TimePlanning;
class Salary;

bool check_day_correctness(int day)
{
    return (day >= MIN_DAY) && (day <= MAX_DAY);
}

vector<interval_data> find_intervals(int start, int end)
{
    vector<interval_data> intervals;
    for (start; start < end; start++)
    {
        interval_data temp;
        temp.start = start;
        temp.end = start + 1;
        intervals.push_back(temp);
    }
    return intervals;
}

bool is_valid_bonus(int new_bonus)
{
    return new_bonus >= 0 && new_bonus <= 100;
}

vector<int> split_by_delimiter(string line, char delimiter)
{
    vector<int> splitted;
    string each_elment;
    stringstream data_stream(line);
    while (getline(data_stream, each_elment, delimiter))
    {
        splitted.push_back(stoi(each_elment));
    }
    return splitted;
}

int cast_parameters_to_change(string input_parameter_str)
{
    if (input_parameter_str == "-")
    {
        return EMPTY;
    }
    int parameter_amount = stoi(input_parameter_str);
    return parameter_amount;
}

bool check_hour_correctness(int start, int end)
{
    return (start <= MAX_HOUR) && (start >= MIN_HOUR) && (end <= MAX_HOUR) && (end >= MIN_HOUR) && (start < end);
}

vector<int> find_days(vector<string> arguments)
{
    int start_day = stoi(arguments[0]);
    int finish_day = stoi(arguments[1]);
    vector<int> days;
    if (check_day_correctness(start_day) && check_day_correctness(finish_day))
    {
        if (start_day > finish_day)
        {
            return days;
        }
        for (start_day; start_day <= finish_day; start_day++)
        {
            days.push_back(start_day);
        }
    }
    return days;
}

struct work_hour
{
    int start;
    int end;
};

struct one_day_working_hour_info
{
    int day;
    int sum_working_hour;
};

struct plan_each_day
{
    int day;
    vector<work_hour> time;
};

class OutputHandler
{
private:
    int status;

public:
    OutputHandler(int function_result)
    {
        status = function_result;
        print_result();
    }
    OutputHandler(pair<vector<one_day_working_hour_info>, pair<vector<int>, vector<int>>> final_report)
    {
        if (final_report.first.size() == 0)
        {
            status = INVALID_ARGUMENT;
            print_result();
        }
        else
        {
            for (int index_day = 0; index_day < final_report.first.size(); index_day++)
            {
                cout << "Day #" << final_report.first[index_day].day << ": " << final_report.first[index_day].sum_working_hour << endl;
            }
            cout << "---\n"
                 << "Day(s) with Max Working Hours: ";
            for (int index_max = 0; index_max < final_report.second.first.size() - 1; index_max++)
            {
                cout << final_report.second.first[index_max] << " ";
            }
            cout << final_report.second.first[final_report.second.first.size() - 1] << endl;
            cout << "Day(s) with Min Working Hours: ";
            for (int index_min = 0; index_min < final_report.second.second.size() - 1; index_min++)
            {
                cout << final_report.second.second[index_min] << " ";
            }
            cout << final_report.second.second[final_report.second.second.size() - 1] << endl;
        }
    }
    OutputHandler(pair<vector<string>, vector<int>> emplolyee_salary_data, pair<int, int> working_hour_absent)
    {
        cout << "ID: " << emplolyee_salary_data.first[0] << endl;
        cout << "Name: " << emplolyee_salary_data.first[1] << endl;
        cout << "Age: " << emplolyee_salary_data.first[2] << endl;
        cout << "Level: " << emplolyee_salary_data.first[3] << endl;
        if (stoi(emplolyee_salary_data.first[4]) == EMPTY)
        {
            cout << "Team ID: N/A" << endl;
        }
        else
        {
            cout << "Team ID: " << emplolyee_salary_data.first[4] << endl;
        }
        cout << "Total Working Hours: " << working_hour_absent.first << endl;
        cout << "Absent Days: " << working_hour_absent.second << endl;
        cout << "Salary: " << emplolyee_salary_data.second[0] << endl;
        cout << "Bonus: " << emplolyee_salary_data.second[1] << endl;
        cout << "Tax: " << emplolyee_salary_data.second[2] << endl;
        cout << "Total Earning: " << emplolyee_salary_data.second[3] << endl;
    }
    OutputHandler(vector<interval_data> intervals, vector<vector<interval_data>> min_max_employee_working_hours)
    {
        for (int interval_index = 0; interval_index < intervals.size(); interval_index++)
        {
            cout << intervals[interval_index].start << "-" << intervals[interval_index].end << ": " << fixed << setprecision(1) << intervals[interval_index].num_employees << endl;
        }
        cout << "---"<< endl;
        cout << "Period(s) with Max Working Employees: ";
        for (int max_vec_index = 0; max_vec_index < min_max_employee_working_hours[0].size(); max_vec_index++)
        {
            cout << min_max_employee_working_hours[0][max_vec_index].start << "-" << min_max_employee_working_hours[0][max_vec_index].end << " ";
        }
        cout << endl;
        cout << "Period(s) with Min Working Employees: ";
        for (int min_vec_index = 0; min_vec_index < min_max_employee_working_hours[1].size(); min_vec_index++)
        {
            cout << min_max_employee_working_hours[1][min_vec_index].start << "-" << min_max_employee_working_hours[1][min_vec_index].end << " ";
        }
        cout << endl;
    }
    OutputHandler(vector<string> employee_data, vector<int> salary_data, int working_hours)
    {
        cout << "ID: " << employee_data[0] << endl;
        cout << "Name: " << employee_data[1] << endl;
        cout << "Total Working Hours: " << working_hours << endl;
        cout << "Total Earning: " << salary_data[3] << endl;
        cout << "---" << endl;
    }
    OutputHandler(vector<string> team_data, vector<pair<int, int>> id_salary_members, int total_working_hour, double average, int bonus)
    {
        cout << "ID: " << team_data[0] << endl;
        cout << "Head ID: " << team_data[1] << endl;
        cout << "Head Name: " << team_data[2] << endl;
        cout << "Team Total Working Hours: " << total_working_hour << endl;
        cout << "Average Member Working Hours: " << fixed << setprecision(1) << average << endl;
        cout << "Bonus: " << bonus << endl;
        cout << "---" << endl;
        for (int index_member = 0; index_member < id_salary_members.size(); index_member++)
        {
            cout << "Member ID: " << id_salary_members[index_member].first << endl;
            cout << "Total Earning: " << id_salary_members[index_member].second << endl;
            cout << "---" << endl;
        }
    }
    OutputHandler(vector<pair<int,int>> capable_teams_for_bonus)
    {
        for (int capable_team_index = 0; capable_team_index < capable_teams_for_bonus.size(); capable_team_index++)
        {
            cout << "Team ID: " << capable_teams_for_bonus[capable_team_index].first << endl;
        }
    }
    void print_result();
};

void OutputHandler ::print_result()
{
    switch (status)
    {
    case NO_EMPLOYEE:
        cout << "EMPLOYEE_NOT_FOUND" << endl;
        break;
    case OK:
        cout << "OK" << endl;
        break;
    case INVALID_ARGUMENT:
        cout << "INVALID_ARGUMENTS" << endl;
        break;
    case OVERLAP_FOUND:
        cout << "INVALID_INTERVAL" << endl;
        break;
    case INVALID_LEVEL:
        cout << "INVALID_LEVEL" << endl;
        break;
    case NO_TEAM:
        cout << "TEAM_NOT_FOUND" << endl;
        break;
    case RESULT_PRINTED:
        break;
    case NO_BONUS_TEAMS:
        cout << "NO_BONUS_TEAMS" << endl;
        break;
    default:
        cout << "error2";
        break;
    }
}

class TimePlanning
{
private:
    vector<plan_each_day> month;
    bool check_existance_interval_day(interval_data chosen_interval, plan_each_day chosen_day);

public:
    int check_existence_of_day(int wanted_day);
    void add_new_day(int new_day);
    int put_new_interval_in_plan(int day, int start, int end);
    bool check_overlap(plan_each_day day_plan, int start, int finish);
    void print_plan_employee();
    int delete_interval_from_plan(int day);
    int get_sum_working_hour_one_day(int day);
    int get_sum_working_hours_month();
    int calculate_num_absent_days() { return (MAX_DAY - month.size()); };
    void check_each_day_working_hours(vector<interval_data> &intervals);
};

void TimePlanning ::check_each_day_working_hours(vector<interval_data> &intervals)
{
    for (int day_index = 0; day_index < month.size(); day_index++)
    {
        for (int intervals_index = 0; intervals_index < intervals.size(); intervals_index++)
        {
            if (check_existance_interval_day(intervals[intervals_index], month[day_index]))
            {
                (intervals[intervals_index].num_employees)++;
            }
        }
    }
}

bool TimePlanning ::check_existance_interval_day(interval_data chosen_interval, plan_each_day chosen_day)
{
    for (int time_index = 0; time_index < chosen_day.time.size(); time_index++)
    {
        if (chosen_interval.start >= chosen_day.time[time_index].start && chosen_interval.end <= chosen_day.time[time_index].end)
        {
            return true;
        }
    }
    return false;
}

int TimePlanning ::get_sum_working_hours_month()
{
    int sum_working_hours = 0;
    for (int index_month = 0; index_month < month.size(); index_month++)
    {
        sum_working_hours += get_sum_working_hour_one_day(month[index_month].day);
    }
    return sum_working_hours;
}

int TimePlanning ::check_existence_of_day(int wanted_day)
{
    for (int index_month = 0; index_month < month.size(); index_month++)
    {
        if (wanted_day == month[index_month].day)
        {
            return index_month;
        }
    }
    return NOT_FOUND;
}

int TimePlanning ::get_sum_working_hour_one_day(int day)
{
    int sum_working_hour = 0;
    int index_month = check_existence_of_day(day);
    if (index_month != NOT_FOUND)
    {
        for (int index_time = 0; index_time < month[index_month].time.size(); index_time++)
        {
            sum_working_hour += month[index_month].time[index_time].end - month[index_month].time[index_time].start;
        }
    }
    else
    {
        sum_working_hour = INVALID_ARGUMENT;
    }
    return sum_working_hour;
}

int TimePlanning ::delete_interval_from_plan(int wanted_day)
{
    if (check_day_correctness(wanted_day))
    {
        int index_month = check_existence_of_day(wanted_day);
        if (index_month != NOT_FOUND)
        {
            month.erase(month.begin() + index_month);
        }
        return OK;
    }
    return INVALID_ARGUMENT;
}

void TimePlanning ::print_plan_employee()
{
    for (int index_month = 0; index_month < month.size(); index_month++)
    {
        cout << "day: " << month[index_month].day << endl
             << "intervals: ";
        for (int index_interval = 0; index_interval < month[index_month].time.size(); index_interval++)
        {
            cout << "(" << month[index_month].time[index_interval].start << "," << month[index_month].time[index_interval].end << ")" << endl;
        }
    }
}

bool TimePlanning ::check_overlap(plan_each_day day_plan, int start, int finish)
{
    for (int index_interval = 0; index_interval < day_plan.time.size(); index_interval++)
    {
        if (start >= day_plan.time[index_interval].start && finish <= day_plan.time[index_interval].end)
        {
            return false;
        }
        if (start <= day_plan.time[index_interval].start && finish > day_plan.time[index_interval].start && finish <= day_plan.time[index_interval].end)
        {
            return false;
        }
        if (start >= day_plan.time[index_interval].start && start < day_plan.time[index_interval].end)
        {
            return false;
        }
        if (finish > day_plan.time[index_interval].start && finish <= day_plan.time[index_interval].end)
        {
            return false;
        }
        if (day_plan.time[index_interval].start >= start && day_plan.time[index_interval].end <= finish)
        {
            return false;
        }
    }
    return true;
}

void TimePlanning ::add_new_day(int new_day)
{
    plan_each_day temp;
    temp.day = new_day;
    month.push_back(temp);
}

int TimePlanning ::put_new_interval_in_plan(int day, int start, int end)
{
    int index_month = check_existence_of_day(day);
    if (index_month == NOT_FOUND)
    {
        add_new_day(day);
        index_month = month.size() - 1;
    }
    if (check_overlap(month[index_month], start, end))
    {
        work_hour temp;
        temp.start = start;
        temp.end = end;
        month[index_month].time.push_back(temp);
        return OK;
    }
    return OVERLAP_FOUND;
}

class Employee
{
private:
    TimePlanning working_time_plan;
    string employee_name;
    int employee_id;
    int emplolyee_age;
    string employee_level;
    int team_id = EMPTY;

public:
    Employee(int id, string name, int age, string level)
    {
        employee_id = id;
        employee_name = name;
        emplolyee_age = age;
        employee_level = level;
    }
    void print_employee_info();
    int get_id() { return employee_id; };
    int add_new_interval(int day, int start, int end) { return working_time_plan.put_new_interval_in_plan(day, start, end); };
    int delete_working_hour(int wanted_day) { return working_time_plan.delete_interval_from_plan(wanted_day); };
    void set_team_id(int team) { team_id = team; };
    int calculate_sum_hours_one_day(int day) { return working_time_plan.get_sum_working_hour_one_day(day); };
    int calculate_all_working_hours() { return working_time_plan.get_sum_working_hours_month(); };
    string get_level() { return employee_level; };
    int get_team_id() { return team_id; };
    void check_intervals_existance(vector<interval_data> &intervals) { working_time_plan.check_each_day_working_hours(intervals); };
    vector<string> get_employee_data();
    int get_num_absent_days() { return working_time_plan.calculate_num_absent_days(); };
    string get_name() { return employee_name; };
};

vector<string> Employee ::get_employee_data()
{
    vector<string> data;
    data.push_back(to_string(employee_id));
    data.push_back(employee_name);
    data.push_back(to_string(emplolyee_age));
    data.push_back(employee_level);
    data.push_back(to_string(team_id));
    return data;
}

void Employee ::print_employee_info()
{
    cout << "name: " << employee_name << endl;
    cout << "id: " << employee_id << endl;
    cout << "age: " << emplolyee_age << endl;
    cout << "level : " << employee_level << endl;
    cout << "plan:\n";
    working_time_plan.print_plan_employee();
    cout << "team id: ";
    if (team_id == EMPTY)
    {
        cout << "N/A\n";
    }
    else
    {
        cout << team_id << endl;
    }
}

class Team
{
private:
    vector<Employee *> members;
    int team_id;
    int team_head_id;
    int bonus_min_working_hour;
    double bonus_working_hours_max_variance;
    int bonus = 0;
    string get_head_name()
    {
        string name;
        for (int index_member = 0; index_member < members.size(); index_member++)
        {
            if (members[index_member]->get_id() == team_head_id)
            {
                name = members[index_member]->get_name();
            }
        }
        return name;
    }

public:
    Team(int id, int head_id, vector<Employee *> members_pointers, int bonus_min_hour, double max_variance)
    {
        team_id = id;
        team_head_id = head_id;
        bonus_min_working_hour = bonus_min_hour;
        bonus_working_hours_max_variance = max_variance;
        members = members_pointers;
    }
    void print_info_team();
    int get_id() { return team_id; };
    int get_bonus() { return bonus; };
    void update_bonus(int new_bonus_amount) { bonus = new_bonus_amount; };
    vector<string> get_team_data();
    vector<pair<int, string>> get_members_salary_data();
    int find_sum_of_team_working_hour();
    double find_team_working_hour_variance();
    bool is_team_capable_for_bonus(int sum_of_team_working_hour, double team_working_hour_variance);
};

vector<pair<int, string>> Team ::get_members_salary_data()
{
    vector<pair<int, string>> id_working_hour_level_members;
    for (int index_member = 0; index_member < members.size(); index_member++)
    {
        pair<int, string> temp;
        temp.first = members[index_member]->get_id();
        temp.second = members[index_member]->get_level();
        id_working_hour_level_members.push_back(temp);
    }
    return id_working_hour_level_members;
}

int Team ::find_sum_of_team_working_hour()
{
    int sum_of_team_working_hour = 0;
    for (int employee_index = 0; employee_index < members.size(); employee_index++)
    {
        sum_of_team_working_hour += members[employee_index]->calculate_all_working_hours();
    }
    return sum_of_team_working_hour;
}

double Team ::find_team_working_hour_variance()
{
    double sum_for_variance = 0;
    double average = double(find_sum_of_team_working_hour()) / double(members.size());
    for (int employee_index = 0; employee_index < members.size(); employee_index++)
    {
        sum_for_variance += pow(double(members[employee_index]->calculate_all_working_hours()) - average, 2);
    }
    double variance = round_to(sum_for_variance / double((members.size())), POINT_ZERO_ZERO_ONE_PRECISION);
    return variance;
}

bool Team ::is_team_capable_for_bonus(int sum_of_team_working_hour, double team_working_hour_variance)
{
    return (sum_of_team_working_hour > bonus_min_working_hour) && (team_working_hour_variance < bonus_working_hours_max_variance);
}

vector<string> Team ::get_team_data()
{
    vector<string> data;
    data.push_back(to_string(team_id));
    data.push_back(to_string(team_head_id));
    data.push_back(get_head_name());
    return data;
}

void Team ::print_info_team()
{
    cout << "team id: " << team_id << endl;
    cout << "head team id: " << team_head_id << endl;
    for (int index_member = 0; index_member < members.size(); index_member++)
    {
        (*members[index_member]).print_employee_info();
    }
    cout << "bonus min working hour: " << bonus_min_working_hour << endl;
    cout << "bonus working hours max variance: " << bonus_working_hours_max_variance << endl;
    cout << "bonus: " << bonus << endl;
}

class Salary
{
private:
    string level;
    int base_salary;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;

public:
    Salary(string level_name, int base, int per_hour, int extra_hour, int official, int tax)
    {
        level = level_name;
        base_salary = base;
        salary_per_hour = per_hour;
        salary_per_extra_hour = extra_hour;
        official_working_hours = official;
        tax_percentage = tax;
    }
    void print_info_salary();
    string get_level() { return level; };
    vector<int> calculate_salary_with_working_hours(int sum_working_hours, int bonus);
    void change_salary_parameters(vector<int> changed_parameter);
};

void Salary ::change_salary_parameters(vector<int> changed_parameter)
{
    if (changed_parameter[0] != EMPTY)
    {
        base_salary = changed_parameter[0];
    }
    if (changed_parameter[1] != EMPTY)
    {
        salary_per_hour = changed_parameter[1];
    }
    if (changed_parameter[2] != EMPTY)
    {
        salary_per_extra_hour = changed_parameter[2];
    }
    if (changed_parameter[3] != EMPTY)
    {
        official_working_hours = changed_parameter[3];
    }
    if (changed_parameter[4] != EMPTY)
    {
        tax_percentage = changed_parameter[4];
    }
}

vector<int> Salary ::calculate_salary_with_working_hours(int sum_working_hours, int bonus)
{
    vector<int> salary_bonus_tax_total;
    double salary = base_salary;
    if (sum_working_hours > official_working_hours)
    {
        salary += (official_working_hours * salary_per_hour) + ((sum_working_hours - official_working_hours) * salary_per_extra_hour);
    }
    else
    {
        salary += sum_working_hours * salary_per_hour;
    }
    salary_bonus_tax_total.push_back(round(salary));
    int salary_bonus = round(salary * bonus / 100);
    salary_bonus_tax_total.push_back(salary_bonus);
    salary += salary_bonus;
    int salary_tax = round(salary * tax_percentage / 100);
    salary_bonus_tax_total.push_back(salary_tax);
    salary -= salary_tax;
    salary_bonus_tax_total.push_back(salary);
    return salary_bonus_tax_total;
}

void Salary ::print_info_salary()
{
    cout << "Base Salary: " << base_salary << endl;
    cout << "Salary Per Hour: " << salary_per_hour << endl;
    cout << "Salary Per Extra Hour: " << salary_per_extra_hour << endl;
    cout << "Official Working Hours: " << official_working_hours << endl;
    cout << "Tax: " << tax_percentage << "%" << endl;
}

class EmployeeSalaryManagment
{
private:
    vector<Employee *> employees_info;
    vector<Team *> teams_info;
    vector<Salary *> levels_salary_info;
    vector<string> read_info_from_file(string folder_address, string file_name);
    vector<vector<string>> split_data_of_file(vector<string> data_of_input_file);
    vector<Employee *> save_employee_info_in_class(vector<vector<string>> splitted_employee_info);
    void set_employee_working_hour(vector<vector<string>> splitted_working_hour);
    Employee *find_employee_by_id(int id_wanted_employee);
    vector<Team *> save_team_info_in_class(vector<vector<string>> splitted_team_info);
    vector<Salary *> save_salary_info_in_class(vector<vector<string>> splitted_salary_info);
    vector<one_day_working_hour_info> calculate_total_hours_of_employees_per_day(vector<string> arguments);
    vector<int> find_days_with_max_hours(vector<one_day_working_hour_info> day_and_its_working_hour);
    vector<int> find_days_with_min_hours(vector<one_day_working_hour_info> day_and_its_working_hour);
    int find_level_by_name(string wanted_level);
    int find_team_by_id(int wanted_id);
    void sort_employees_by_id(vector<Employee *> &employees);
    vector<interval_data> intervals_selection_sort(vector<interval_data> intervals);
    vector<vector<interval_data>> sort_min_max_average_work(vector<vector<interval_data>> intervals);
    vector<vector<interval_data>> find_min_max_interval(vector<interval_data> intervals);
    vector<pair<int, int>> sort_chosen_bonus_teams(vector<pair<int, int>> chosen_teams);

public:
    void read_employee_info_from_csv(string folder_address, string file_name)
    {
        employees_info = save_employee_info_in_class(split_data_of_file(read_info_from_file(folder_address, file_name)));
    }
    void read_working_hour_info_from_csv(string folder_address, string file_name)
    {
        set_employee_working_hour(split_data_of_file(read_info_from_file(folder_address, file_name)));
    }
    void read_salary_info_from_csv(string folder_address, string file_name)
    {
        levels_salary_info = save_salary_info_in_class(split_data_of_file(read_info_from_file(folder_address, file_name)));
    }
    void read_team_info_from_csv(string folder_address, string file_name)
    {
        teams_info = save_team_info_in_class(split_data_of_file(read_info_from_file(folder_address, file_name)));
    }
    int add_new_working_hour(vector<string> command);
    int delete_interval(vector<string> arguments);
    pair<vector<one_day_working_hour_info>, pair<vector<int>, vector<int>>> report_total_working_hours(vector<string> arguments);
    int show_salary_config(vector<string> name_level)
    {
        int index_level = find_level_by_name(name_level[0]);
        if (index_level != INVALID_LEVEL)
        {
            levels_salary_info[index_level]->print_info_salary();
            return RESULT_PRINTED;
        }
        return INVALID_LEVEL;
    }
    int change_bonus(vector<string> command);
    int upgrade_salary_info(vector<string> changed_parameter);
    void report_average_employee_per_hour(vector<string> argument);
    void report_employee_salary(vector<string> arguments);
    void report_salaries();
    void report_team_salary(vector<string> arguments);
    void find_teams_for_bonus();
};

vector<pair<int, int>> EmployeeSalaryManagment ::sort_chosen_bonus_teams(vector<pair<int, int>> chosen_teams)
{
    int min_in;
    for (int team_index = 0; team_index < chosen_teams.size(); team_index++)
    {
        min_in = team_index;
        for (int j = team_index + 1; j < chosen_teams.size(); j++)
        {
            if (chosen_teams[j].second <= chosen_teams[min_in].second)
            {
                min_in = j;
            }
        }
        swap(chosen_teams[team_index], chosen_teams[min_in]);
    }
    return chosen_teams;
}

void EmployeeSalaryManagment ::find_teams_for_bonus()
{
    vector<pair<int, int>> capable_teams_id_working_hours;
    for (int team_index = 0; team_index < teams_info.size(); team_index++)
    {
        pair<int, int> id_working_hours_team;
        int sum_of_team_working_hour = teams_info[team_index]->find_sum_of_team_working_hour();
        double team_working_hour_variance = teams_info[team_index]->find_team_working_hour_variance();
        if (teams_info[team_index]->is_team_capable_for_bonus(sum_of_team_working_hour, team_working_hour_variance))
        {
            id_working_hours_team.first = teams_info[team_index]->get_id();
            id_working_hours_team.second = sum_of_team_working_hour;
            capable_teams_id_working_hours.push_back(id_working_hours_team);
        }
    }
    if (!capable_teams_id_working_hours.empty())
    {
        capable_teams_id_working_hours = sort_chosen_bonus_teams(capable_teams_id_working_hours);
        OutputHandler result(capable_teams_id_working_hours);
    }
    else
    {
        OutputHandler result(NO_BONUS_TEAMS);
    }
}

vector<vector<interval_data>> EmployeeSalaryManagment::sort_min_max_average_work(vector<vector<interval_data>> intervals)
{
    int min_in;
    for (int min_max_index = 0; min_max_index < 2; min_max_index++)
    {
        for (int interval_index = 0; interval_index < intervals[min_max_index].size(); interval_index++)
        {
            min_in = interval_index;
            for (int j = interval_index + 1; j < intervals[min_max_index].size(); j++)
                if (intervals[min_max_index][j].start < intervals[min_max_index][min_in].start)
                    min_in = j;
            swap(intervals[min_max_index][interval_index], intervals[min_max_index][min_in]);
        }
    }
    return intervals;
}

vector<vector<interval_data>> EmployeeSalaryManagment ::find_min_max_interval(vector<interval_data> intervals)
{
    vector<vector<interval_data>> min_max_employee_working_hours(2);
    for (int interval_index = 0; interval_index < intervals.size(); interval_index++)
    {
        min_max_employee_working_hours[1].push_back(intervals[interval_index]);
        if (intervals[interval_index + 1].num_employees > intervals[interval_index].num_employees)
            break;
    }
    for (int interval_index = intervals.size() - 1; interval_index >= 0; interval_index--)
    {
        min_max_employee_working_hours[0].push_back(intervals[interval_index]);
        if (intervals[interval_index - 1].num_employees < intervals[interval_index].num_employees)
            break;
    }
    return min_max_employee_working_hours;
}

vector<interval_data> EmployeeSalaryManagment ::intervals_selection_sort(vector<interval_data> intervals)
{
    int min_in;
    for (int interval_index = 0; interval_index < intervals.size(); interval_index++)
    {
        min_in = interval_index;
        for (int j = interval_index + 1; j < intervals.size(); j++)
        {
            if (intervals[j].num_employees <= intervals[min_in].num_employees)
            {
                min_in = j;
            }
        }
        swap(intervals[interval_index], intervals[min_in]);
    }
    return intervals;
}

void EmployeeSalaryManagment ::sort_employees_by_id(vector<Employee *> &employees_info)
{
    for (int i = 0; i < employees_info.size(); i++)
    {
        for (int j = i + 1; j < employees_info.size(); j++)
        {
            if (employees_info[i]->get_id() > employees_info[j]->get_id())
            {
                Employee *temp = employees_info[i];
                employees_info[i] = employees_info[j];
                employees_info[j] = temp;
            }
        }
    }
}

void EmployeeSalaryManagment ::report_team_salary(vector<string> arguments)
{
    int index_team = find_team_by_id(stoi(arguments[0]));
    if (index_team == NO_TEAM)
    {
        OutputHandler result(NO_TEAM);
        return;
    }
    vector<string> team_data = teams_info[index_team]->get_team_data();
    vector<pair<int, string>> id_level_members = teams_info[index_team]->get_members_salary_data();
    vector<pair<int, int>> members_id_salary;
    double total_working_hour = 0;
    for (int index_member = 0; index_member < id_level_members.size(); index_member++)
    {
        pair<int, int> temp;
        temp.first = id_level_members[index_member].first;
        Employee *temp_employee = find_employee_by_id(temp.first);
        int index_salary = find_level_by_name(id_level_members[index_member].second);
        vector<int> salary_data = levels_salary_info[index_salary]->calculate_salary_with_working_hours(temp_employee->calculate_all_working_hours(), teams_info[index_team]->get_bonus());
        temp.second = salary_data[3];
        members_id_salary.push_back(temp);
        total_working_hour += temp_employee->calculate_all_working_hours();
    }
    double average = round_to(total_working_hour / id_level_members.size(), POINT_ONE_PRECISION);
    OutputHandler result(team_data, members_id_salary, total_working_hour, average, teams_info[index_team]->get_bonus());
}

void EmployeeSalaryManagment ::report_salaries()
{
    for (int employee_index = 0; employee_index < employees_info.size(); employee_index++)
    {
        int team_index = find_team_by_id(employees_info[employee_index]->get_team_id());
        int level_index = find_level_by_name(employees_info[employee_index]->get_level());
        int bonus_team = 0;
        if (team_index != NO_TEAM)
        {
            bonus_team = teams_info[team_index]->get_bonus();
        }
        vector<int> salary_data = levels_salary_info[level_index]->calculate_salary_with_working_hours(employees_info[employee_index]->calculate_all_working_hours(), bonus_team);
        OutputHandler result(employees_info[employee_index]->get_employee_data(), salary_data, employees_info[employee_index]->calculate_all_working_hours());
    }
}

void EmployeeSalaryManagment::report_employee_salary(vector<string> arguments)
{
    Employee *temp = find_employee_by_id(stoi(arguments[0]));
    pair<vector<string>, vector<int>> employee_salary_data;
    if (temp == NULL)
    {
        OutputHandler result(NO_EMPLOYEE);
        return;
    }
    int index_team = find_team_by_id(temp->get_team_id());
    int level = find_level_by_name(temp->get_level());
    int bonus = 0;
    if (index_team != NO_TEAM)
    {
        bonus = teams_info[index_team]->get_bonus();
    }
    employee_salary_data.second = levels_salary_info[level]->calculate_salary_with_working_hours(temp->calculate_all_working_hours(), bonus);
    employee_salary_data.first = temp->get_employee_data();
    pair<int, int> working_hour_absent_days(temp->calculate_all_working_hours(), temp->get_num_absent_days());
    OutputHandler result(employee_salary_data, working_hour_absent_days);
    return;
}

void EmployeeSalaryManagment ::report_average_employee_per_hour(vector<string> argument)
{
    int start = stoi(argument[0]);
    int end = stoi(argument[1]);
    if (!check_hour_correctness(start, end))
    {
        OutputHandler result(INVALID_ARGUMENT);
        return;
    }
    vector<interval_data> intervals = find_intervals(start, end);
    for (int employee_index = 0; employee_index < employees_info.size(); employee_index++)
    {
        employees_info[employee_index]->check_intervals_existance(intervals);
    }
    for (int interval_index = 0; interval_index < intervals.size(); interval_index++)
    {
        intervals[interval_index].num_employees = round_to((intervals[interval_index].num_employees / MAX_DAY), POINT_ONE_PRECISION);
    }
    vector<vector<interval_data>> min_max_employee_working_hours = sort_min_max_average_work(find_min_max_interval(intervals_selection_sort(intervals)));
    OutputHandler result(intervals, min_max_employee_working_hours);
}

int EmployeeSalaryManagment ::upgrade_salary_info(vector<string> changed_parameter)
{
    vector<int> paramenters;
    int level = find_level_by_name(changed_parameter[0]);
    if (level == INVALID_LEVEL)
    {
        return INVALID_LEVEL;
    }
    for (int index_parameter = 1; index_parameter < changed_parameter.size(); index_parameter++)
    {
        paramenters.push_back(cast_parameters_to_change(changed_parameter[index_parameter]));
    }
    levels_salary_info[level]->change_salary_parameters(paramenters);
    return OK;
}

int EmployeeSalaryManagment ::change_bonus(vector<string> parameters_for_bonus_update)
{
    int new_bonus = stoi(parameters_for_bonus_update[1]);
    int team_id = find_team_by_id(stoi(parameters_for_bonus_update[0]));
    if (team_id == NO_TEAM)
    {
        return NO_TEAM;
    }
    if (!is_valid_bonus(new_bonus))
    {
        return INVALID_ARGUMENT;
    }
    teams_info[team_id]->update_bonus(new_bonus);
    return OK;
}

int EmployeeSalaryManagment ::find_team_by_id(int wanted_id)
{
    for (int index_team = 0; index_team < teams_info.size(); index_team++)
    {
        if (wanted_id == teams_info[index_team]->get_id())
        {
            return index_team;
        }
    }
    return NO_TEAM;
}

int EmployeeSalaryManagment ::find_level_by_name(string wanted_level)
{
    for (int index_level = 0; index_level < levels_salary_info.size(); index_level++)
    {
        if (wanted_level == levels_salary_info[index_level]->get_level())
        {
            return index_level;
        }
    }
    return INVALID_LEVEL;
}

vector<string> EmployeeSalaryManagment::read_info_from_file(string folder_address, string file_name)
{
    string file_address = folder_address + "/" + file_name;
    ifstream stream_csv_file(file_address);
    string temp_string;
    vector<string> data_of_csv_file;
    while (getline(stream_csv_file, temp_string))
    {
        data_of_csv_file.push_back(temp_string);
    }
    return data_of_csv_file;
}

vector<vector<string>> EmployeeSalaryManagment::split_data_of_file(vector<string> data_of_input_file)
{
    vector<vector<string>> splitted_data;
    string word;
    vector<string> data_of_each_element;
    for (int index_line = 1; index_line < data_of_input_file.size(); index_line++)
    {
        stringstream line_stream(data_of_input_file[index_line]);
        while (getline(line_stream, word, ','))
        {
            data_of_each_element.push_back(word);
        }
        splitted_data.push_back(data_of_each_element);
        data_of_each_element.clear();
    }
    return splitted_data;
}

vector<Employee *> EmployeeSalaryManagment::save_employee_info_in_class(vector<vector<string>> splitted_employee_info)
{
    vector<Employee *> employees_info_pointer;
    for (int index_employee_info = 0; index_employee_info < splitted_employee_info.size(); index_employee_info++)
    {
        string employee_name = splitted_employee_info[index_employee_info][COLUMN_EMPLOYEE_NAME];
        int employee_id = stoi(splitted_employee_info[index_employee_info][COLUMN_EMPLOYEE_ID]);
        int employee_age = stoi(splitted_employee_info[index_employee_info][COLUMN_EMPLOYEE_AGE]);
        string employee_level = splitted_employee_info[index_employee_info][COLUMN_EMPLOYEE_LEVEL];
        Employee *temp_employee = new Employee(employee_id, employee_name, employee_age, employee_level);
        employees_info_pointer.push_back(temp_employee);
    }
    sort_employees_by_id(employees_info_pointer);
    return employees_info_pointer;
}

void EmployeeSalaryManagment ::set_employee_working_hour(vector<vector<string>> splitted_working_hour)
{
    for (int index_splitted_working_hour = 0; index_splitted_working_hour < splitted_working_hour.size(); index_splitted_working_hour++)
    {
        Employee *temp = find_employee_by_id(stoi(splitted_working_hour[index_splitted_working_hour][COLUMN_EMPLOYEE_ID]));
        int day = stoi(splitted_working_hour[index_splitted_working_hour][COLUMN_DAY]);
        vector<int> interval = split_by_delimiter(splitted_working_hour[index_splitted_working_hour][COLUMN_WORKING_INTERVAL], DELIMITER_INTERVAL);
        temp->add_new_interval(day, interval[0], interval[1]);
    }
}

Employee *EmployeeSalaryManagment ::find_employee_by_id(int id_wanted_employee)
{
    for (int index_employee = 0; index_employee < employees_info.size(); index_employee++)
    {
        if (((*employees_info[index_employee]).get_id()) == id_wanted_employee)
        {
            return employees_info[index_employee];
        }
    }
    return NULL;
}

vector<Team *> EmployeeSalaryManagment ::save_team_info_in_class(vector<vector<string>> splitted_team_info)
{
    vector<Team *> teams;
    for (int index_team_info = 0; index_team_info < splitted_team_info.size(); index_team_info++)
    {
        int team_id = stoi(splitted_team_info[index_team_info][COLUMN_TEAM_ID]);
        int head_id = stoi(splitted_team_info[index_team_info][COLUMN_TEAM_HEAD_ID]);
        vector<int> members_id = split_by_delimiter(splitted_team_info[index_team_info][COLUMN_MEMBERS_ID], DELIMITER_MEMBERS);
        vector<Employee *> members;
        for (int index_member = 0; index_member < members_id.size(); index_member++)
        {
            Employee *temp_employee = find_employee_by_id(members_id[index_member]);
            temp_employee->set_team_id(team_id);
            members.push_back(temp_employee);
        }
        sort_employees_by_id(members);
        int bonus_min_working_hour = stoi(splitted_team_info[index_team_info][COLUMN_BONUS_MIN_HOUR]);
        double max_variance = stod(splitted_team_info[index_team_info][COLUMN_MAX_VARIANCE]);
        Team *temp_team = new Team(team_id, head_id, members, bonus_min_working_hour, max_variance);
        teams.push_back(temp_team);
    }
    return teams;
}

vector<Salary *> EmployeeSalaryManagment ::save_salary_info_in_class(vector<vector<string>> splitted_salary_info)
{
    vector<Salary *> levels_salary_pointer;
    for (int index_salary_info = 0; index_salary_info < splitted_salary_info.size(); index_salary_info++)
    {
        string level = splitted_salary_info[index_salary_info][COLUMN_LEVEL];
        int base_salary = stoi(splitted_salary_info[index_salary_info][COLUMN_BASE_SALARY]);
        int salary_per_hour = stoi(splitted_salary_info[index_salary_info][COLUMN_SALARY_PER_HOUR]);
        int salary_extra_hour = stoi(splitted_salary_info[index_salary_info][COLUMN_SALARY_EXTRA_HOUR]);
        int official_working_hour = stoi(splitted_salary_info[index_salary_info][COLUMN_OFFICIAL_WORKING_HOUR]);
        int tax_percentage = stoi(splitted_salary_info[index_salary_info][COLUMN_TAX]);
        Salary *temp_salary = new Salary(level, base_salary, salary_per_hour, salary_extra_hour, official_working_hour, tax_percentage);
        levels_salary_pointer.push_back(temp_salary);
    }
    return levels_salary_pointer;
}

int EmployeeSalaryManagment ::add_new_working_hour(vector<string> command)
{
    int status;
    Employee *temp = find_employee_by_id(stoi(command[COLUMN_EMPLOYEE_ID]));
    if (temp != NULL)
    {
        int day = stoi(command[COLUMN_DAY]);
        int start = stoi(command[COLUMN_START]);
        int end = stoi(command[COLUMN_END]);
        if (check_day_correctness(day) && check_hour_correctness(start, end))
        {
            status = temp->add_new_interval(day, start, end);
        }
        else
        {
            status = INVALID_ARGUMENT;
        }
    }
    else
    {
        status = NO_EMPLOYEE;
    }
    return status;
}

int EmployeeSalaryManagment ::delete_interval(vector<string> arguments)
{
    int employee_id = stoi(arguments[COLUMN_EMPLOYEE_ID]);
    int day = stoi(arguments[COLUMN_DAY]);
    Employee *temp = find_employee_by_id(employee_id);
    if (temp != NULL)
    {
        return (temp->delete_working_hour(day));
    }
    return NO_EMPLOYEE;
}

vector<one_day_working_hour_info> EmployeeSalaryManagment ::calculate_total_hours_of_employees_per_day(vector<string> arguments)
{
    vector<int> days = find_days(arguments);
    vector<one_day_working_hour_info> day_and_its_working_hour;
    if (days.size() == 0)
    {
        return day_and_its_working_hour;
    }
    for (int index_days = 0; index_days < days.size(); index_days++)
    {
        one_day_working_hour_info temp;
        temp.day = days[index_days];
        int sum_hours = 0;
        for (int index_employee = 0; index_employee < employees_info.size(); index_employee++)
        {
            int sum_one_day = employees_info[index_employee]->calculate_sum_hours_one_day(days[index_days]);
            if (sum_one_day != INVALID_ARGUMENT)
            {
                sum_hours += sum_one_day;
            }
        }
        temp.sum_working_hour = sum_hours;
        day_and_its_working_hour.push_back(temp);
    }
    return day_and_its_working_hour;
}

pair<vector<one_day_working_hour_info>, pair<vector<int>, vector<int>>> EmployeeSalaryManagment::report_total_working_hours(vector<string> arguments)
{
    pair<vector<one_day_working_hour_info>, pair<vector<int>, vector<int>>> final_report;
    pair<vector<int>, vector<int>> days_with_max_min_hours;
    final_report.first = calculate_total_hours_of_employees_per_day(arguments);
    if (final_report.first.size() != 0)
    {
        days_with_max_min_hours.first = find_days_with_max_hours(final_report.first);
        days_with_max_min_hours.second = find_days_with_min_hours(final_report.first);
    }
    final_report.second = days_with_max_min_hours;
    return final_report;
}

vector<int> EmployeeSalaryManagment ::find_days_with_max_hours(vector<one_day_working_hour_info> day_and_its_working_hour)
{
    vector<int> max_days;
    int max = day_and_its_working_hour[0].sum_working_hour;
    for (int index_report = 0; index_report < day_and_its_working_hour.size(); index_report++)
    {
        if (day_and_its_working_hour[index_report].sum_working_hour == max)
        {
            max_days.push_back(day_and_its_working_hour[index_report].day);
        }
        if (day_and_its_working_hour[index_report].sum_working_hour > max)
        {
            max_days.clear();
            max = day_and_its_working_hour[index_report].sum_working_hour;
            max_days.push_back(day_and_its_working_hour[index_report].day);
        }
    }
    return max_days;
}

vector<int> EmployeeSalaryManagment ::find_days_with_min_hours(vector<one_day_working_hour_info> day_and_its_working_hour)
{
    vector<int> min_days;
    int min = day_and_its_working_hour[0].sum_working_hour;
    for (int index_report = 0; index_report < day_and_its_working_hour.size(); index_report++)
    {
        if (day_and_its_working_hour[index_report].sum_working_hour == min)
        {
            min_days.push_back(day_and_its_working_hour[index_report].day);
        }
        if (day_and_its_working_hour[index_report].sum_working_hour < min)
        {
            min_days.clear();
            min = day_and_its_working_hour[index_report].sum_working_hour;
            min_days.push_back(day_and_its_working_hour[index_report].day);
        }
    }
    return min_days;
}

class InputHandler
{
private:
    string input_line;

public:
    InputHandler(string command)
    {
        input_line = command;
    };
    int recognize_operation();
    vector<string> remove_operation_word_from_command();
};

int InputHandler ::recognize_operation()
{
    if (input_line.find(ADD_INTERVAL) != input_line.npos)
    {
        return ADD_WORKING_HOUR;
    }
    if (input_line.find(DELETE_INTERVAL) != input_line.npos)
    {
        return DELETE_WORKING_HOUR;
    }
    if (input_line.find(TOTAL_WORKING_HOUR) != input_line.npos)
    {
        return REPORT_TOTAL_WORKING_HOUR;
    }
    if (input_line.find(REPORT_LEVEL_SALARY) != input_line.npos)
    {
        return SHOW_SALARY_CONFIG;
    }
    if (input_line.find(EMPLOYEE_SALARY) != input_line.npos)
    {
        return REPORT_EMPLOYEE_SALARY;
    }
    if (input_line.find(UPDATE_BONUS) != input_line.npos)
    {
        return UPDATE_TEAM_BONUS;
    }
    if (input_line.find(UPDATE_LEVEL) != input_line.npos)
    {
        return UPDATE_SALARY_CONFIG;
    }
    if (input_line.find(AVERAGE_EMPLOYEE_PER_HOUR) != input_line.npos)
    {
        return REPORT_EMPLOYEE_PER_HOUR;
    }
    if (input_line.find(SALARY_ALL_EMPLOYEES) != input_line.npos)
    {
        return REPORT_SALARIES;
    }
    if (input_line.find(TEAM_SALARY) != input_line.npos)
    {
        return REPORT_TEAM_SALARY;
    }
    if (input_line.find(FIND_BONUS_CAPABLE_TEAMS) != input_line.npos)
    {
        return FIND_TEAMS_FOR_BONUS;
    }
    return NOT_FOUND;
}

vector<string> InputHandler ::remove_operation_word_from_command()
{
    vector<int> position_space;
    vector<string> arguments;
    for (int index_charactor = 0; index_charactor < input_line.size(); index_charactor++)
    {
        if (input_line[index_charactor] == ' ')
        {
            position_space.push_back(index_charactor);
        }
    }
    position_space.push_back(input_line.size());
    for (int index_position = 0; index_position < position_space.size() - 1; index_position++)
    {
        arguments.push_back(input_line.substr(position_space[index_position] + 1, position_space[index_position + 1] - position_space[index_position] - 1));
    }
    return arguments;
}

int main(int argc, char const *argv[])
{
    EmployeeSalaryManagment employee_salary_managment;
    employee_salary_managment.read_employee_info_from_csv(argv[1], EMPLOYEES_INFO_FILE);
    employee_salary_managment.read_working_hour_info_from_csv(argv[1], WORKING_HOUR_INFO_FILE);
    employee_salary_managment.read_team_info_from_csv(argv[1], TEAM_INFO_FILE);
    employee_salary_managment.read_salary_info_from_csv(argv[1], SALARY_INFO_FILE);
    string command;
    while (getline(cin, command))
    {
        InputHandler input_line(command);
        vector<string> arguments = input_line.remove_operation_word_from_command();
        switch (input_line.recognize_operation())
        {
        case ADD_WORKING_HOUR:
        {
            OutputHandler result_of_operation(employee_salary_managment.add_new_working_hour(arguments));
        }
        break;
        case DELETE_WORKING_HOUR:
        {
            OutputHandler result_of_operation(employee_salary_managment.delete_interval(arguments));
        }
        break;
        case REPORT_TOTAL_WORKING_HOUR:
        {
            OutputHandler result_of_operation(employee_salary_managment.report_total_working_hours(arguments));
        }
        break;
        case SHOW_SALARY_CONFIG:
        {
            OutputHandler result_of_operation(employee_salary_managment.show_salary_config(arguments));
        }
        break;
        case REPORT_EMPLOYEE_SALARY:
        {
            employee_salary_managment.report_employee_salary(arguments);
        }
        break;
        case UPDATE_TEAM_BONUS:
        {
            OutputHandler result_of_operation(employee_salary_managment.change_bonus(arguments));
        }
        break;
        case UPDATE_SALARY_CONFIG:
        {
            OutputHandler result_of_operation(employee_salary_managment.upgrade_salary_info(arguments));
        }
        break;
        case REPORT_EMPLOYEE_PER_HOUR:
        {
            employee_salary_managment.report_average_employee_per_hour(arguments);
        }
        break;
        case REPORT_SALARIES:
        {
            employee_salary_managment.report_salaries();
        }
        break;
        case REPORT_TEAM_SALARY:
        {
            employee_salary_managment.report_team_salary(arguments);
        }
        break;
        case FIND_TEAMS_FOR_BONUS:
        {
            employee_salary_managment.find_teams_for_bonus();
        }
        break;
        default:
            cout << "error1\n";
            break;
        }
    }
    return 0;
}
