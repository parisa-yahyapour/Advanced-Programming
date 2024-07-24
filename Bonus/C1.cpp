#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const int COLUMN_NAMES_LINE = 0;
const int FAILED = -1;
const int NAME = 0;
const int OPENTIME = 1;
const int CLOSETIME = 2;
const int RANK = 3;
const int NOT_EXITSTENT = -1;
const int EXISTENT = 0;
const int LESS_THAN_SUITABLE_DURATION = -1;
const int START_OF_DAY = 480;
const int HAVE = 1;
const int NOT_HAVE = 0;
const int AN_HOUR = 60;
const int TIME_TO_ARRIVE = 30;
const int LEAST_POSSIBLE_DURATION = 15;

struct locations
{
	int code_location;
	string name_location;
	int opening_time;
	int closing_time;
	int rank;
};

struct visit_info
{
	string name_location;
	string start;
	string end;
};

int searcher(vector<string> sequence_columns, string wanted_word)
{
	for (int index_column = 0; index_column < sequence_columns.size(); index_column++)
	{
		if (sequence_columns[index_column] == wanted_word)
		{
			return index_column;
		}
	}
	return FAILED;
}

vector<int> find_index_column_name_opentime_closetime_rank(vector<string> sequence_of_columns)
{
	int name_index = searcher(sequence_of_columns, "name");
	int opentime_index = searcher(sequence_of_columns, "openingTime");
	int closetime_index = searcher(sequence_of_columns, "closingTime");
	int rank_index = searcher(sequence_of_columns, "rank");
	vector<int> sorted_index_of_columns = {name_index, opentime_index, closetime_index, rank_index};
	return sorted_index_of_columns;
}

vector<vector<string>> split_data_of_locations(vector<string> data_of_input_file)
{
	vector<vector<string>> splitted_data_location;
	string word;
	vector<string> data_of_each_location;
	for (int index_line = 1; index_line < data_of_input_file.size(); index_line++)
	{
		stringstream line_stream(data_of_input_file[index_line]);
		while (getline(line_stream, word, ','))
		{
			data_of_each_location.push_back(word);
		}
		splitted_data_location.push_back(data_of_each_location);
		data_of_each_location.clear();
	}
	return splitted_data_location;
}

vector<int> create_time_vector(vector<vector<string>> location_data, int column_index)
{
	vector<int> times, temp;
	string time;
	for (int index_location = 0; index_location < location_data.size(); index_location++)
	{
		stringstream stream_time(location_data[index_location][column_index]);
		while (getline(stream_time, time, ':'))
		{
			stringstream time_stream(time);
			int temp_clock = 0;
			time_stream >> temp_clock;
			temp.push_back(temp_clock);
		}
		int time_in_minute_format = temp[0] * 60 + temp[1];
		temp.clear();
		times.push_back(time_in_minute_format);
	}
	return times;
}

vector<locations> put_locations_data_in_struct(vector<vector<string>> locations_data, pair<vector<int>, vector<int>> times_data, vector<int> sorted_column_index)
{
	vector<locations> locations_structs;
	for (int index_location = 0; index_location < locations_data.size(); index_location++)
	{
		locations temp;
		temp.code_location = index_location + 1;
		temp.name_location = locations_data[index_location][sorted_column_index[NAME]];
		temp.opening_time = times_data.first[index_location];
		temp.closing_time = times_data.second[index_location];
		temp.rank = stoi(locations_data[index_location][sorted_column_index[RANK]]);
		locations_structs.push_back(temp);
	}
	return locations_structs;
}

int find_min(vector<int> times)
{
	vector<string> nearest_times;
	if (times.size() > 1)
	{
		int last_time = times[times.size() - 1];
		times.pop_back();
		if (last_time <= find_min(times))
		{
			return last_time;
		}
		else
		{
			return find_min(times);
		}
	}
	else
	{
		return times[0];
	}
}
int check_existent_of_second_in_first(vector<int> numbers, int wanted_number)
{
	for (int index_number = 0; index_number < numbers.size(); index_number++)
	{
		if (numbers[index_number] == wanted_number)
		{
			return HAVE;
		}
	}
	return NOT_HAVE;
}
vector<int> find_suitable_locations(pair<vector<locations>, vector<int>> locations_data_and_unsuitable_ones, int nearest_time, vector<int> location_check)
{
	vector<int> suitable_locations_code;
	for (int index_location = 0; index_location < (locations_data_and_unsuitable_ones.first).size(); index_location++)
	{
		if (locations_data_and_unsuitable_ones.first[index_location].opening_time == nearest_time)
		{
			int existence = check_existent_of_second_in_first(location_check, (locations_data_and_unsuitable_ones.first[index_location].code_location - 1));
			int unsuitable = check_existent_of_second_in_first(locations_data_and_unsuitable_ones.second, index_location);
			if ((existence == NOT_HAVE) && (unsuitable == NOT_HAVE))
			{
				suitable_locations_code.push_back(index_location);
			}
		}
	}
	return suitable_locations_code;
}

int find_location_code_by_rank(vector<locations> locations_data_struct, int rank)
{
	for (int index_location = 0; index_location < locations_data_struct.size(); index_location++)
	{
		if (locations_data_struct[index_location].rank == rank)
		{
			return index_location;
		}
	}
	return NOT_EXITSTENT;
}
int find_best_rank_location(vector<int> suitable_indexs, vector<locations> locations_data_struct)
{
	vector<int> ranks;
	for (int index_suitable = 0; index_suitable < suitable_indexs.size(); index_suitable++)
	{
		ranks.push_back(locations_data_struct[suitable_indexs[index_suitable]].rank);
	}
	int best_rank = find_min(ranks);
	return best_rank;
}

int calculate_new_current_time(int previous_time, int duration)
{
	if (duration >= AN_HOUR)
	{
		duration = AN_HOUR;
	}
	return (previous_time + duration + TIME_TO_ARRIVE);
}

int calculate_endtime(int previous_time, int duration)
{
	if (duration >= AN_HOUR)
	{
		duration = AN_HOUR;
	}
	return previous_time + duration;
}

vector<int> find_open_locs(pair<int &, vector<int>> current_and_open_times, vector<int> gone_locations, vector<int> unsuitable_locations_code)
{
	vector<int> suitable_locations_code;
	for (int index_time = 0; index_time < (current_and_open_times.second).size(); index_time++)
	{
		int existence = check_existent_of_second_in_first(gone_locations, index_time);
		if (((current_and_open_times.second)[index_time] <= current_and_open_times.first) && (existence == NOT_HAVE))
		{
			int unsuitable_check = check_existent_of_second_in_first(unsuitable_locations_code, index_time);
			if (unsuitable_check == NOT_HAVE)
			{
				suitable_locations_code.push_back(index_time);
			}
		}
	}
	return suitable_locations_code;
}
int find_nearest(int current_time, vector<int> opentimes)
{
	vector<int> late_opentimes;
	for (int i = 0; i < opentimes.size(); i++)
	{
		if (opentimes[i] > current_time)
		{
			late_opentimes.push_back(opentimes[i]);
		}
	}
	int min = find_min(late_opentimes);
	return min;
}

vector<int> find_opened_locations_in_future(vector<int> open_times, int current_time)
{
	vector<int> future_open_times;
	for (int index_open_time = 0; index_open_time < open_times.size(); index_open_time++)
	{
		if (open_times[index_open_time] > current_time)
		{
			future_open_times.push_back(open_times[index_open_time]);
		}
	}
	return future_open_times;
}

int find_next_destination_code(pair<int &, vector<int>> current_and_open_times, vector<int> gone_locations, pair<vector<locations>, vector<int>> locations_data_and_unsuitable_ones)
{
	int rank, chosen_location_code, index_open_times = 0;
	while (true)
	{
		vector<int> suitable_codes;
		if ((current_and_open_times.first >= find_min(current_and_open_times.second)) && (index_open_times < current_and_open_times.second.size()))
		{
			suitable_codes = find_open_locs(current_and_open_times, gone_locations, locations_data_and_unsuitable_ones.second);
			index_open_times++;
		}
		else
		{
			vector<int> future_open_times = find_opened_locations_in_future(current_and_open_times.second, current_and_open_times.first);
			int nearest_open_time = find_min(future_open_times);
			suitable_codes = find_suitable_locations(locations_data_and_unsuitable_ones, nearest_open_time, gone_locations);
			current_and_open_times.first = nearest_open_time;
		}
		if (suitable_codes.size() > 0)
		{
			rank = find_best_rank_location(suitable_codes, locations_data_and_unsuitable_ones.first);
			chosen_location_code = find_location_code_by_rank(locations_data_and_unsuitable_ones.first, rank);
			break;
		}
	}
	return chosen_location_code;
}

int calculate_duration_of_visit(locations possible_location, int current_time)
{
	int duration = possible_location.closing_time - current_time;
	if (duration > LEAST_POSSIBLE_DURATION)
	{
		return duration;
	}
	else
	{
		return NOT_EXITSTENT;
	}
}

int find_max_close_times(vector<int> close_times)
{
	if (close_times.size() == 1)
		return close_times[0];
	else
	{
		int last_close_time = close_times[close_times.size() - 1];
		close_times.pop_back();
		if (last_close_time >= find_max_close_times(close_times))
		{
			return last_close_time;
		}
		else
		{
			return find_max_close_times(close_times);
		}
	}
}

string convert_int_time_to_clockform(int time)
{
	int hour = time / AN_HOUR;
	int minute = time - (hour * AN_HOUR);
	string hour_str = to_string(hour);
	string minute_str = to_string(minute);
	if (hour < 10)
	{
		hour_str = "0" + hour_str;
	}
	if (minute < 10)
	{
		minute_str = "0" + minute_str;
	}
	return (hour_str + ":" + minute_str);
}

void print_tour_plan(vector<visit_info> tour_plan)
{
	for (int index_plan = 0; index_plan < tour_plan.size(); index_plan++)
	{
		cout << "Location " << tour_plan[index_plan].name_location << endl
			 << "Visit from " << tour_plan[index_plan].start << " until " << tour_plan[index_plan].end << endl
			 << "---" << endl;
	}
}

vector<string> read_from_csv_file(string file_name)
{
	ifstream input_csv_file(file_name);
	string temp_string;
	vector<string> data_of_csv_file;
	while (getline(input_csv_file, temp_string))
	{
		data_of_csv_file.push_back(temp_string);
	}
	return data_of_csv_file;
}

vector<string> extract_sequence_of_columns(vector<string> data_of_input_file)
{
	vector<string> splitted_first_line;
	string column_name;
	stringstream column_names_stream(data_of_input_file[COLUMN_NAMES_LINE]);
	while (getline(column_names_stream, column_name, ','))
	{
		splitted_first_line.push_back(column_name);
	}

	return splitted_first_line;
}

void save_plan(vector<visit_info> &tour_plan, locations chosen_location, pair<int, int> start_time_duration)
{
	visit_info temp;
	temp.name_location = chosen_location.name_location;
	temp.start = convert_int_time_to_clockform(start_time_duration.first);
	temp.end = convert_int_time_to_clockform(calculate_endtime(start_time_duration.first, start_time_duration.second));
	tour_plan.push_back(temp);
}

int main(int argc, char *argv[])
{
	vector<visit_info> tour_plan;
	vector<int> gone_location, unsuitable_locations_code;
	vector<string> data_of_input_file = read_from_csv_file(argv[1] + 2);
	vector<string> sequence_of_columns = extract_sequence_of_columns(data_of_input_file);
	vector<int> sorted_index_of_columns = find_index_column_name_opentime_closetime_rank(sequence_of_columns);
	vector<vector<string>> locations_data = split_data_of_locations(data_of_input_file);
	vector<int> open_times = create_time_vector(locations_data, sorted_index_of_columns[OPENTIME]);
	vector<int> close_times = create_time_vector(locations_data, sorted_index_of_columns[CLOSETIME]);
	pair<vector<int>, vector<int>> times_data(open_times, close_times);
	vector<locations> locations_data_struct = put_locations_data_in_struct(locations_data, times_data, sorted_index_of_columns);
	int current_time = START_OF_DAY, index_locations = 0;
	while ((current_time < find_max_close_times(close_times)) && (index_locations < locations_data_struct.size()))
	{
		pair<vector<locations>, vector<int>> locations_data_and_unsuitable_ones(locations_data_struct, unsuitable_locations_code);
		pair<int &, vector<int>> current_and_open_times(current_time, open_times);
		int possible_location_code = find_next_destination_code(current_and_open_times, gone_location, locations_data_and_unsuitable_ones);
		pair<int, int> start_time_and_duration(current_time, calculate_duration_of_visit(locations_data_struct[possible_location_code], current_time));
		int existence = check_existent_of_second_in_first(gone_location, possible_location_code);
		if ((existence == (NOT_HAVE)) && (start_time_and_duration.second != (LESS_THAN_SUITABLE_DURATION)))
		{
			gone_location.push_back(possible_location_code);
			save_plan(tour_plan, locations_data_struct[possible_location_code], start_time_and_duration);
			current_time = calculate_new_current_time(current_time, start_time_and_duration.second);
		}
		else
		{
			unsuitable_locations_code.push_back(possible_location_code);
		}
		index_locations++;
	}
	print_tour_plan(tour_plan);
}
