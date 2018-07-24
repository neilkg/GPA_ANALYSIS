#ifndef READ_CSV_H
#define READ_CSV_H

#include "csvstream.h"
#include "GPA.h"
#include <string>
#include <vector>
#include <map>

// Created by Neil Gollapudi 7/22/2018



// Requires: Valid csv file
// Effects: Reads all data from colums of "Class", "Credits", and "Grades"
//          and places them in a Taken_Course data type in a vector
// Modifies: data
void read_csv(const std::string &filename, std::vector<Taken_Course> &data);

// Effects: Prints out all raw_data in data vector
//          (used for debugging purposes)
void view_raw_data(const std::vector<Taken_Course> &data);

// Effects: Prints out all main_data in data map
//          (used for debugging purposes)
void view_main_data(const std::map<std::string, Category> &data);


//*************IMPLEMENTATION_BELOW**********************//

void read_csv(const std::string &filename, std::vector<Taken_Course> &data) {
    csvstream csv(filename);
    std::map<std::string, std::string> credits_data;
    
    std::string name_in;
    int credits_in;
    std::string grade_in;
    
    while (csv >> credits_data) {
        for (auto &col:credits_data) {
            std::string label = col.first;
            std::string datum = col.second;
            if (label == "Credits") {
                credits_in = stoi(datum);
            }
            else if (label == "Grades") {
                grade_in = datum;
            }
            else {
                name_in = datum;
            }
        }
        Taken_Course object;
        object.name = name_in;
        object.grade = grade_in;
        object.credits = credits_in;
        data.push_back(object);
    }
}



void view_raw_data(const std::vector<Taken_Course> &data) {
    for (auto i:data) {
        std::cout << i.name << " " << i.credits << " " << i.grade << std::endl;
    }
}


void view_main_data(const std::map<std::string, Category> &data) {
    for (auto i:data) {
        std::string key = i.first;
        Category c = i.second;
        std::cout << "*****" << c.key << " " << c.category_credits << std::endl;
        for (auto i:c.sub_data) {
            std::cout << i.name << " " << i.grade << " " << i.credits << std::endl;
        }
    }
}

#endif
