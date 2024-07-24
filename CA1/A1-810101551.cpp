#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define START_DAY "start_day"
#define CHECK "check"
#define SHOW_DAY "show_day"
#define LONG_DAY "show_the_longest_day"
#define BEST_DAY "show_the_best_day"
#define FILE_NAME "positive-words.txt"
using namespace std;

typedef struct date
{
    string day;
    string month;
    string year;
    int num_row;
} date;

int recognize_operation(string input_line);
void set_date(vector<date> *date_vec, vector<vector<string>> *diary, int *counter_days, string input_line);
void check(vector<date> date_vec, vector<vector<string>> diary, int counter_days);
void add_text(vector<vector<string>> *diary, int counter_days, string input_line);
void show_day(string input_line, vector<date> date_vec, vector<vector<string>> diary);
void longest_day(vector<vector<string>> diary, vector <date> date_vec);
void open_file(vector<string> *positive_word);
void best_day(vector<vector<string>> diary, vector<string> positive_words, vector<date> date_vec);

int main()
{
    vector < vector <string> > diary;/*keeping dates and thier texts in it*/
    vector < string > positive_words;/*save words from file to it*/
    vector < date > date_vec;/*save dates in comparable form in it*/
    string input_line, enter = "\n";
    int counter_days = -1, operation;
    open_file(&positive_words);
    while (cin.peek() != EOF)
    {
        getline(cin, input_line);
        operation = recognize_operation(input_line);
        switch (operation)
        {
        case 0:/*the line does not match with any operation so it is a text*/
            add_text(&diary, counter_days, input_line);
            break;
        case 1:/*separate date from line and save it*/
            set_date(&date_vec, &diary, &counter_days, input_line);
            break;
        case 2:/*print text of an specific date*/
            show_day(input_line, date_vec, diary);
            break;
        case 3:/*count char of each day then print short form of text*/
            longest_day(diary, date_vec);
            break;
        case 4:/*count words in each day print the best one*/
            best_day(diary, positive_words, date_vec);
            break;
        default:
            cout << "error1\n";
            break;
        }
    }
    return 0;
}
/*this function compare first word of input line with instructions, then return operation code*/
int recognize_operation(string input_line)
{
    if (input_line.find(START_DAY) != input_line.npos)
    {
        return 1; /*the user wants to set a date*/
    }
    if (input_line.find(SHOW_DAY) != input_line.npos)
    {
        return 2; /*the user wants to see past days' info*/
    }
    if (input_line.find(LONG_DAY) != input_line.npos)
    {
        return 3; /*the user wants to see the longet day*/
    }
    if (input_line.find(BEST_DAY) != input_line.npos)
    {
        return 4; /*the user wants to see the best day*/
    }
    else
    {
        return 0; /*the user wants to write text of the diary*/
    }
}
/*this function seperate date from input line and save it in two forms in two vectors*/
void set_date(vector < date > *date_vec, vector < vector < string > > *diary, int *counter_days, string input_line)
{
    vector < int > position_delimiters;
    vector < string > save2;
    date date_struct;
    string save, zero = "0", enter = "\n", slash = "/";
    position_delimiters.push_back(10); /*the positon that date starts*/
    int length_input = int(input_line.size()), index_input_string = 10, index_position = 0, counter = 0;
    while (index_input_string < length_input)/*recognize chars that are not number*/
    {
        if ((input_line[index_input_string] == '/') || (input_line[index_input_string] == '\n'))
        {
            position_delimiters.push_back(index_input_string);
        }
        index_input_string++;
    }
    while (counter < 3)/*seperate day month year based on delimiters' position*/
    {
        save = input_line.substr(position_delimiters[index_position], position_delimiters[index_position + 1] - position_delimiters[index_position]);
        save2.push_back(save);
        if (save.size() == 1)/*add 0 at the beginning to be comparable*/
        {
            save.insert(0, zero);
        }
        if (counter != 2)
        {
            save2.push_back(slash);
        }
        else
        {
            save2.push_back(enter);
        }
        position_delimiters[index_position + 1]++;
        index_position++;
        switch (counter)
        {
        case 0:
            date_struct.day = save;
            break;
        case 1:
            date_struct.month = save;
            break;
        case 2:
            date_struct.year = save;
            break;
        default:
            cout << "error2\n";
            break;
        }
        counter++;
    }
    (*counter_days)++;
    date_struct.num_row = *counter_days;
    (*date_vec).push_back(date_struct);
    (*diary).push_back(save2);
}
/*this function add text to the date that is active, each word in one sting separate from spaces and enters*/
void add_text(vector < vector < string > > *diary, int counter_days, string input_line)
{
    string save, enter = "\n", space = " ";
    int counter = 0;
    vector<int> position_delimiter;
    position_delimiter.push_back(0);
    input_line.append(enter);
    while (counter < int(input_line.size()))/*recognize delimiters*/
    {
        if ((input_line[counter] == ' ') || (input_line[counter] == '\n'))
        {
            position_delimiter.push_back(counter);
        }
        counter++;
    }
    counter = 0;
    while (counter < int(position_delimiter.size()) - 1)/*save words in one string*/
    {
        save = input_line.substr(position_delimiter[counter], position_delimiter[counter + 1] - position_delimiter[counter]);
        position_delimiter[counter + 1]++;
        (*diary)[counter_days].push_back(save);
        if (counter != int(position_delimiter.size()) - 2)
        {
            (*diary)[counter_days].push_back(space);
        }
        counter++;
    }
    (*diary)[counter_days].push_back(enter);
}
/*this function prints text of a date*/
void show_day(string input_line, vector < date > date_vec, vector < vector < string > > diary)
{
    input_line.append("\n");
    vector<int> position_delimiter;
    string zero = "0";
    position_delimiter.push_back(9);
    int length_input = int(input_line.size()), index_input_string = 9;
    while (index_input_string < length_input)/*reading date change it to comparable form*/
    {
        if ((input_line[index_input_string] == '/') || (input_line[index_input_string] == '\n'))
        {
            position_delimiter.push_back(index_input_string);
        }
        index_input_string++;
    }
    int index_position = 0, num_day, counter = 0;
    string day = input_line.substr(position_delimiter[index_position], position_delimiter[index_position + 1] - position_delimiter[index_position]);
    if (day.size() == 1)
    {
        day.insert(0, zero);
    }
    position_delimiter[index_position + 1]++;
    index_position++;
    string month = input_line.substr(position_delimiter[index_position], position_delimiter[index_position + 1] - position_delimiter[index_position]);
    if (int(month.size()) == 1)
    {
        month.insert(0, zero);
    }
    position_delimiter[index_position + 1]++;
    index_position++;
    string year = input_line.substr(position_delimiter[index_position], position_delimiter[index_position + 1] - position_delimiter[index_position]);
    while (counter < int(date_vec.size()))/*find the code of the day then search it in diary vector*/
    {
        if ((date_vec[counter].year == year) && (date_vec[counter].month == month) && (date_vec[counter].day == day))
        {
            num_day = date_vec[counter].num_row;
            break;
        }
        else
        {
            counter++;
        }
    }
    counter = 6;/*print the text*/
    while (counter < int(diary[num_day].size()))
    {
        cout << diary[num_day][counter];
        counter++;
    }
}
/*this function count chars of all days, then print the oldest one*/
void longest_day(vector < vector < string > > diary, vector < date > date_vec)
{
    int max_char = 0, counter = 0, counter2 = 6, sum = 0, longest_row = -1;
    vector< int > number_row;
    while (counter < int(diary.size()))/*counting chars*/
    {
        while (counter2 < int(diary[counter].size()))
        {
            sum += ((diary[counter][counter2]).size());
            counter2++;
        }
        if (sum > max_char)
        {
            max_char = sum;
            number_row.erase(number_row.begin(), number_row.end());
            number_row.push_back(counter);
        }
        else if (sum == max_char)
        {
            number_row.push_back(counter);
        }
        sum = 0;
        counter2 = 6;
        counter++;
    }
    int counter_date = 0, counter_row = 0, flag = 0;
    string day, month, year;
    for (counter_date = 0; counter_date < int(date_vec.size()); counter_date++)/*extract the first date for comparing*/
    {
        if (date_vec[counter_date].num_row == number_row[counter_row])
        {
            day = date_vec[counter_date].day;
            month = date_vec[counter_date].month;
            year = date_vec[counter_date].year;
            longest_row = date_vec[counter_date].num_row;
            break;
        }
    }
    counter_row++;
    while (counter_row < int(number_row.size()))/*comparing dates with this order: year month day*/
    {
        for (counter_date = 0; counter_date < int(date_vec.size()); counter_date++)
        {
            if (date_vec[counter_date].num_row == number_row[counter_row])
            {
                break;
            }
        }
        if (date_vec[counter_date].year < year)
        {
            flag = 1;
        }
        else if (date_vec[counter_date].year == year)
        {
            if (date_vec[counter_date].month < month)
            {
                flag = 1;
            }
            else if (date_vec[counter_date].month == month)
            {
                if (date_vec[counter_date].day < day)
                {
                    flag = 1;
                }
            }
        }
        if (flag == 1)/*there is an older date*/
        {
            day = date_vec[counter_date].day;
            month = date_vec[counter_date].month;
            year = date_vec[counter_date].year;
            longest_row = date_vec[counter_date].num_row;
        }
        flag = 0;
        counter_row++;
    }

    counter = 0;
    while (counter < 6)/*printing the date*/
    {
        cout << diary[longest_row][counter];
        counter++;
    }
    if (max_char <= 20)/*checking the format of text short or full*/
    {
        counter = 6;
        while (counter < int(diary[longest_row].size()))
        {
            cout << diary[longest_row][counter];
            counter++;
        }
    }
    else/*calculating short text*/
    {
        int last_char = -1, index = 0, last_row = -1;
        sum = 0;
        counter = 6;
        while (counter < int(diary[longest_row].size()))
        {
            while (index < int(diary[longest_row][counter].size()))
            {
                sum++;
                if (sum == 20)
                {
                    last_char = index;
                    last_row = counter;
                    break;
                }
                index++;
            }
            index = 0;
            counter++;
        }
        counter = 6;
        while (counter < last_row)
        {
            cout << diary[longest_row][counter];
            counter++;
        }
        index = 0;
        while (index <= last_char)
        {
            cout << diary[longest_row][last_row].at(index);
            index++;
        }
        cout << "...\n";
    }
}
/*this function opens the file which is related to positive words then save them a vector*/
void open_file(vector < string > *positive_word)
{
    ifstream words;
    words.open(FILE_NAME);
    string line;
    vector< int > position_delimiter;
    int flag = 0;
    while (words.peek() != EOF)/*exract lines from file, check two part words, out them into a vector*/
    {
        getline(words, line);
        int length_line = line.size(), counter = 0;
        for (counter = 0; counter < length_line; counter++)
        {
            if (line[counter] == ' ')
            {
                if (position_delimiter.size() == 0)
                {
                    position_delimiter.push_back(0);
                }

                flag = 1;
                position_delimiter.push_back(counter);
            }
        }
        if (flag == 0)
        {
            (*positive_word).push_back(line);
        }
        else
        {
            position_delimiter.push_back(line.size());
            string save;
            int index = 0;
            for (index = 0; index < int(position_delimiter.size()) - 1; index++)
            {
                save = line.substr(position_delimiter[index], position_delimiter[index + 1] - position_delimiter[index]);
                (*positive_word).push_back(save);
                position_delimiter[index + 1]++;
            }
        }
        flag = 0;
    }
    words.close();
}
/*this function count positive words, put their code in a vector, then find the oldest day*/
void best_day(vector < vector < string > > diary, vector < string > positive_words, vector < date > date_vec)
{
    vector< int > number_row;
    int max_repeat = -1, counter_1d = 0, counter_2d = 0, counter_words = 0, sum = 0;
    for (counter_1d = 0; counter_1d < int(diary.size()); counter_1d++)/*counting words*/
    {
        for (counter_words = 0; counter_words < int(positive_words.size()); counter_words++)
        {
            for (counter_2d = 6; counter_2d < int(diary[counter_1d].size()); counter_2d++)
            {
                if (diary[counter_1d][counter_2d] == positive_words[counter_words])
                {
                    sum++;
                }
            }
        }
        if (sum > max_repeat)
        {
            number_row.erase(number_row.begin(), number_row.end());
            number_row.push_back(counter_1d);
            max_repeat = sum;
        }
        else if (sum == max_repeat)
        {
            number_row.push_back(counter_1d);
        }
        sum = 0;
    }
    int counter_date = 0, best_row = -1, counter_row = 0, flag = 0;
    string day, month, year;
    for (counter_date = 0; counter_date < int(date_vec.size()); counter_date++)/*finding the oldest date*/
    {
        if (date_vec[counter_date].num_row == number_row[counter_row])
        {
            day = date_vec[counter_date].day;
            month = date_vec[counter_date].month;
            year = date_vec[counter_date].year;
            best_row = date_vec[counter_date].num_row;
            break;
        }
    }
    counter_row++;
    while (counter_row < int(number_row.size()))
    {
        for (counter_date = 0; counter_date < int(date_vec.size()); counter_date++)
        {
            if (date_vec[counter_date].num_row == number_row[counter_row])
            {
                break;
            }
        }
        if (date_vec[counter_date].year < year)
        {
            flag = 1;
        }
        else if (date_vec[counter_date].year == year)
        {
            if (date_vec[counter_date].month < month)
            {
                flag = 1;
            }
            else if (date_vec[counter_date].month == month)
            {
                if (date_vec[counter_date].day < day)
                {
                    flag = 1;
                }
            }
        }
        if (flag == 1)
        {
            day = date_vec[counter_date].day;
            month = date_vec[counter_date].month;
            year = date_vec[counter_date].year;
            best_row = date_vec[counter_date].num_row;
        }
        flag = 0;
        counter_row++;
    }
    int counter = 6, char_num = 0;/*printing*/
    while (counter < int(diary[best_row].size()))
    {
        char_num += diary[best_row][counter].size();
        counter++;
    }
    counter = 0;
    while (counter < 6)
    {
        cout << diary[best_row][counter];
        counter++;
    }
    if (char_num <= 20)
    {
        counter = 6;
        while (counter < int(diary[best_row].size()))
        {
            cout << diary[best_row][counter];
            counter++;
        }
    }
    else
    {
        int last_char = -1, index = 0, last_row = -1;
        sum = 0;
        counter = 6;
        while (counter < int(diary[best_row].size()))
        {
            while (index < int(diary[best_row][counter].size()))
            {
                sum++;
                if (sum == 20)
                {
                    last_char = index;
                    last_row = counter;
                    break;
                }
                index++;
            }
            index = 0;
            counter++;
        }
        counter = 6;
        while (counter < last_row)
        {
            cout << diary[best_row][counter];
            counter++;
        }
        index = 0;
        while (index <= last_char)
        {
            cout << diary[best_row][last_row].at(index);
            index++;
        }
        cout << "...\n";
    }
}
