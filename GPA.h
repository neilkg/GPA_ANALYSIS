#ifndef GPA_H
#define GPA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>

// Created by Neil Gollapudi 7/22/2018

struct Taken_Course {
    
    std::string name;
    std::string grade;
    int credits;
};

class Category {
public:
    Category() : average_gpa(0), total_credits(0) {}
    
    std::vector<Taken_Course> sub_data;
    std::string key;
    double average_gpa;
    int total_credits;
};


// Used in place_in_map()
// Effects: removes all non uppercase characters in the string
// Modifies: str
void remove_nonuppercase(std::string &str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            str.erase(str.begin() + long(i), str.end());
            return;
        }
    }
}


// Requires: class name in Taken_Course has capital department name letters
//           ex. EECS is EECS department for 183 class
// Effects: takes raw data and converts it to map data format for future
//          processing convinience
//          For each category, only gives vector type, key, and total_credits
// Modifies: main_data
void place_in_map(const std::vector<Taken_Course> &raw_data, std::map<std::string, Category> &main_data) {
    for (auto i:raw_data) {
        std::string department_name = i.name;
        remove_nonuppercase(department_name);
        
        // department name maps to its respective category object
        Category *object = &main_data[department_name];
        object->sub_data.push_back(i);
        object->key = department_name;
        object->total_credits += i.credits;
    }
}














#endif
