#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int Saturday = 0;
const int Sunday = 1;
const int Monday = 2;
const int Tuesday = 3;
const int Wednesday = 4;
const int NumClass = 2;
const int DoubleDot = 2;
const string Empty = "E";
const string Full = "F";
const int NotFound = -1;
const int DaysOfWeek = 5;
const int NumPeriods = 3;
const int Start_7_30 = 450;
const int Finnish_9 = 540;
const int Start_9_30 = 570;
const int Finnish_11 = 660;
const int Start_11_30 = 690;
const int Finnish_13 = 780;
const int OneOption = 1;

typedef struct Teacher
{
    string name;
    int num_free_days;
    vector<int> free_days;
    int num_courses;
    vector<string> course;
} Teacher;

typedef struct Course
{
    string name_course;
    int day1;
    int day2;
    int strat_time;
    int finish_time;
} Course;

typedef struct Plan
{
    string name_course;
    vector<string> name_teacher = vector<string>(NumClass, Empty);
    vector<int> part = vector<int>(NumClass, NotFound);
} FinalPlan;

typedef struct TableTeacher
{
    vector<vector<string>> table = vector<vector<string>>(DaysOfWeek, vector<string>(NumPeriods, Empty));
} TableTeacher;

vector<Course> input_courses(int &num_course);
int convert_time_to_minute(string time);
vector<Teacher> input_teachers(int &num_teachers);
int find_day_of_week(string day);
void sort_day1_day2(Course &course);
vector<Course> sort_course_by_name(vector<Course> info_courses);
vector<Plan> create_table_class_plan(vector<Course> info_courses);
bool check_possibility_course(int current_day, int currrent_part, Course course, vector<vector<string>> class_table, vector<string> used_courses);
vector<int> find_suitable_teachers(Course course, vector<Teacher> info_teachers, int current_period, vector<TableTeacher> teachers_table);
vector<int> find_least_freeday(vector<int> suitable_teachers_index, vector<Teacher> info_teachers);
int find_first_teacher_by_alphabet(vector<int> suitable_teachers, vector<Teacher> info_teachers);
void update_final_plan(int final_teacher, vector<Teacher> info_teacher, int period, Course course, vector<Plan> &plan_courses, int index_class);
void update_table_teachers(int final_teacher, int period, int day1, int day2, vector<TableTeacher> &table_teachers);
void update_class_table(vector<vector<string>> &class_table, int period, int day1, int day2);
vector<TableTeacher> create_table_teacher(int num_teachers);
void print_final_plan(vector<Plan> plan_courses);
int choose_the_final_teacher(vector<int> index_suitable_teachers, vector<Teacher> info_teachers);
bool check_not_used(vector<string> used_courses, Course course);
bool check_day1_day2_tobe_free(vector<vector<string>> class_table, Course course, int currrent_part);
void recognize_start_finish(int &start, int &finish, int current_part);
bool check_time_limit(int start_lesson, int finish_lesson, int start_part, int finish_part);

int main()
{
    int num_teachers, num_courses;
    vector<Teacher> info_teachers = input_teachers(num_teachers);
    vector<Course> info_courses = input_courses(num_courses);
    for (int index_course = 0; index_course < num_courses; index_course++)
    {
        sort_day1_day2(info_courses[index_course]);
    }
    info_courses = sort_course_by_name(info_courses);
    vector<Plan> plan_courses = create_table_class_plan(info_courses);
    vector<TableTeacher> table_teachers = create_table_teacher(num_teachers);
    for (int index_class = 0; index_class < NumClass; index_class++)
    {
        vector<vector<string>> class_table(DaysOfWeek, vector<string>(NumPeriods, Empty));
        vector<string> used_courses;
        for (int index_day = 0; index_day < DaysOfWeek; index_day++)
        {
            for (int index_period = 0; index_period < NumPeriods; index_period++)
            {
                int flag = 0;
                for (int index_course = 0; index_course < num_courses; index_course++)
                {
                    if (check_possibility_course(index_day, index_period, info_courses[index_course], class_table, used_courses))
                    {
                        vector<int> suitable_teachers_index = find_suitable_teachers(info_courses[index_course], info_teachers, index_period, table_teachers);
                        if (suitable_teachers_index.size() != 0)
                        {
                            int final_teacher = choose_the_final_teacher(suitable_teachers_index, info_teachers);
                            update_final_plan(final_teacher, info_teachers, index_period, info_courses[index_course], plan_courses, index_class);
                            update_table_teachers(final_teacher, index_period, info_courses[index_course].day1, info_courses[index_course].day2, table_teachers);
                            update_class_table(class_table, index_period, info_courses[index_course].day1, info_courses[index_course].day2);
                            used_courses.push_back(info_courses[index_course].name_course);
                            flag = 1;
                        }
                    }
                    if (flag == 1)
                    {
                        break;
                    }
                }
            }
        }
    }
    print_final_plan(plan_courses);
    return 0;
}

void print_final_plan(vector<Plan> plan_courses)
{
    for (int code_course = 0; code_course < plan_courses.size(); code_course++)
    {
        cout << plan_courses[code_course].name_course << endl;
        for (int index_class = 0; index_class < NumClass; index_class++)
        {
            if (plan_courses[code_course].name_teacher[index_class] == Empty)
            {
                cout << "Not Found\n";
            }
            else
            {
                cout << plan_courses[code_course].name_teacher[index_class] << ": ";
                switch (plan_courses[code_course].part[index_class])
                {
                case 0:
                    cout << "07:30 09:00\n";
                    break;
                case 1:
                    cout << "09:30 11:00\n";
                    break;
                case 2:
                    cout << "11:30 13:00\n";
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void update_class_table(vector<vector<string>> &class_table, int period, int day1, int day2)
{
    class_table[day1][period] = Full;
    class_table[day2][period] = Full;
}

void update_table_teachers(int final_teacher, int period, int day1, int day2, vector<TableTeacher> &table_teachers)
{
    table_teachers[final_teacher].table[day1][period] = Full;
    table_teachers[final_teacher].table[day2][period] = Full;
}

void update_final_plan(int final_teacher, vector<Teacher> info_teacher, int period, Course course, vector<Plan> &plan_courses, int index_class)
{
    for (int index_plan_course = 0; index_plan_course < plan_courses.size(); index_plan_course++)
    {
        if (plan_courses[index_plan_course].name_course == course.name_course)
        {
            plan_courses[index_plan_course].name_teacher[index_class] = info_teacher[final_teacher].name;
            plan_courses[index_plan_course].part[index_class] = period;
            return;
        }
    }
}

int choose_the_final_teacher(vector<int> index_suitable_teachers, vector<Teacher> info_teachers)
{
    int choosen_index;
    if (index_suitable_teachers.size() == OneOption)
    {
        choosen_index = index_suitable_teachers[0];
    }
    else
    {
        vector<int> least_free_day = find_least_freeday(index_suitable_teachers, info_teachers);
        if (least_free_day.size() == OneOption)
        {
            choosen_index = least_free_day[0];
        }
        else
        {
            choosen_index = find_first_teacher_by_alphabet(least_free_day, info_teachers);
        }
    }
    return choosen_index;
}

int find_first_teacher_by_alphabet(vector<int> suitable_teachers, vector<Teacher> info_teachers)
{
    int choosen;
    vector<string> name_teachers;
    for (int index_suitable = 0; index_suitable < suitable_teachers.size(); index_suitable++)
    {
        name_teachers.push_back(info_teachers[suitable_teachers[index_suitable]].name);
    }
    sort(name_teachers.begin(), name_teachers.end());
    for (int index_teacher = 0; index_teacher < info_teachers.size(); index_teacher++)
    {
        if (info_teachers[index_teacher].name == name_teachers[0])
        {
            choosen = index_teacher;
            break;
        }
    }
    return choosen;
}

vector<int> find_least_freeday(vector<int> suitable_teachers_index, vector<Teacher> info_teachers)
{
    vector<int> choosen;
    vector<int> empty;
    int min = info_teachers[suitable_teachers_index[0]].num_free_days;
    for (int index_suitable = 0; index_suitable < suitable_teachers_index.size(); index_suitable++)
    {
        if (info_teachers[suitable_teachers_index[index_suitable]].num_free_days == min)
        {
            choosen.push_back(suitable_teachers_index[index_suitable]);
        }
        else if (info_teachers[suitable_teachers_index[index_suitable]].num_free_days < min)
        {
            min = info_teachers[suitable_teachers_index[index_suitable]].num_free_days;
            choosen = empty;
            choosen.push_back(suitable_teachers_index[index_suitable]);
        }
    }
    return choosen;
}

vector<int> find_suitable_teachers(Course course, vector<Teacher> info_teachers, int current_period, vector<TableTeacher> teachers_table)
{
    vector<int> teachers_index;
    for (int index_teacher = 0; index_teacher < info_teachers.size(); index_teacher++)
    {
        int flag = 0;
        for (int index_course = 0; index_course < info_teachers[index_teacher].num_courses; index_course++)
        {
            if (info_teachers[index_teacher].course[index_course] == course.name_course)
            {
                int counter_days = 0;
                for (int index_day = 0; index_day < info_teachers[index_teacher].num_free_days; index_day++)
                {
                    if ((info_teachers[index_teacher].free_days[index_day] == course.day1) || (info_teachers[index_teacher].free_days[index_day] == course.day2))
                    {
                        counter_days++;
                    }
                }
                if (counter_days == 2)
                {
                    if ((teachers_table[index_teacher].table[course.day1][current_period] == Empty) && (teachers_table[index_teacher].table[course.day2][current_period] == Empty))
                    {
                        teachers_index.push_back(index_teacher);
                    }
                }
                else
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                break;
            }
        }
    }
    return teachers_index;
}

bool check_time_limit(int start_lesson, int finish_lesson, int start_part, int finish_part)
{
    return (start_part >= start_lesson) && (finish_part <= finish_lesson);
}

void recognize_start_finish(int &start, int &finish, int current_part)
{
    switch (current_part)
    {
    case 0:
        start = Start_7_30;
        finish = Finnish_9;
        break;
    case 1:
        start = Start_9_30;
        finish = Finnish_11;
        break;
    case 2:
        start = Start_11_30;
        finish = Finnish_13;
        break;
    default:
        break;
    }
}

bool check_day1_day2_tobe_free(vector<vector<string>> class_table, Course course, int currrent_part)
{
    bool status;
    if ((class_table[course.day1][currrent_part] == Empty) && (class_table[course.day2][currrent_part] == Empty))
    {
        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}

bool check_not_used(vector<string> used_courses, Course course)
{
    bool status = true;
    for (int index_used = 0; index_used < used_courses.size(); index_used++)
    {
        if (used_courses[index_used] == course.name_course)
        {
            status = false;
            break;
        }
    }
    return status;
}

bool check_possibility_course(int current_day, int currrent_part, Course course, vector<vector<string>> class_table, vector<string> used_courses)
{
    bool status = check_not_used(used_courses, course);
    if (status)
    {
        if ((current_day == course.day1) || (current_day == course.day2))
        {
            int start, finish;
            recognize_start_finish(start, finish, currrent_part);
            if (check_time_limit(course.strat_time, course.finish_time, start, finish))
            {
                status = check_day1_day2_tobe_free(class_table, course, currrent_part);
            }
            else
            {
                status = false;
            }
        }
        else
        {
            status = false;
        }
    }
    return status;
}

vector<TableTeacher> create_table_teacher(int num_teachers)
{
    vector<TableTeacher> table;
    for (int index_teacher = 0; index_teacher < num_teachers; index_teacher++)
    {
        TableTeacher draft;
        table.push_back(draft);
    }
    return table;
}

vector<Plan> create_table_class_plan(vector<Course> info_courses)
{
    vector<Plan> table;
    for (int index_course = 0; index_course < info_courses.size(); index_course++)
    {
        Plan draft;
        draft.name_course = info_courses[index_course].name_course;
        table.push_back(draft);
    }
    return table;
}

vector<Course> sort_course_by_name(vector<Course> info_courses)
{
    vector<string> name_courses;
    vector<Course> sorted_courses;
    for (int index_course = 0; index_course < info_courses.size(); index_course++)
    {
        name_courses.push_back(info_courses[index_course].name_course);
    }
    sort(name_courses.begin(), name_courses.end());
    for (int index_sorted = 0; index_sorted < name_courses.size(); index_sorted++)
    {
        for (int index_course = 0; index_course < info_courses.size(); index_course++)
        {
            if (name_courses[index_sorted] == info_courses[index_course].name_course)
            {
                sorted_courses.push_back(info_courses[index_course]);
                break;
            }
        }
    }
    return sorted_courses;
}

void sort_day1_day2(Course &course)
{
    if (course.day1 > course.day2)
    {
        int draft = course.day1;
        course.day1 = course.day2;
        course.day2 = draft;
    }
    else
    {
        return;
    }
}

vector<Course> input_courses(int &num_course)
{
    cin >> num_course;
    Course draft;
    vector<Course> info_courses;
    string start, finish;
    for (int i = 0; i < num_course; i++)
    {
        string draft_day;
        cin >> draft.name_course >> draft_day;
        draft.day1 = find_day_of_week(draft_day);
        cin >> draft_day >> start >> finish;
        draft.day2 = find_day_of_week(draft_day);
        draft.strat_time = convert_time_to_minute(start);
        draft.finish_time = convert_time_to_minute(finish);
        info_courses.push_back(draft);
    }
    return info_courses;
}

int convert_time_to_minute(string time)
{
    int hour = stoi((time.substr(0, DoubleDot)));
    int minute = stoi((time.substr(DoubleDot + 1)));
    return (hour * 60) + minute;
}

vector<Teacher> input_teachers(int &num_teachers)
{
    cin >> num_teachers;
    vector<Teacher> info_teachers;
    for (int i = 0; i < num_teachers; i++)
    {
        Teacher draft;
        cin >> draft.name >> draft.num_free_days;
        for (int j = 0; j < draft.num_free_days; j++)
        {
            string free_day_draft;
            cin >> free_day_draft;
            draft.free_days.push_back(find_day_of_week(free_day_draft));
        }
        cin >> draft.num_courses;
        for (int k = 0; k < draft.num_courses; k++)
        {
            string draft_course;
            cin >> draft_course;
            draft.course.push_back(draft_course);
        }
        info_teachers.push_back(draft);
    }
    return info_teachers;
}

int find_day_of_week(string day)
{
    if (day == "Saturday")
    {
        return Saturday;
    }
    if (day == "Sunday")
    {
        return Sunday;
    }
    if (day == "Monday")
    {
        return Monday;
    }
    if (day == "Tuesday")
    {
        return Tuesday;
    }
    if (day == "Wednesday")
    {
        return Wednesday;
    }
    return -1;
}
