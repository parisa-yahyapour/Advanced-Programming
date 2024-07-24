#ifndef _WEEK_TABLE_HPP_
#define _WEEK_TABLE_HPP_
#include <vector>
#include <memory>
#include <iostream>
#include "Match.hpp"

class WeekTable
{
public:
    WeekTable(std::vector<std::shared_ptr<Match>> matches, int num_week);
    void print_week_data();
    bool check_invalid_week(int wanted_week);
    int get_num_week();
private:
    std::vector<std::shared_ptr<Match>> matches_played;
    int week_number;
};

#endif