#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include "csvstream.h"
#include "GPA.h"

// Created by Neil Gollapudi 7/22/2018

using namespace std;


// Requires: Valid csv file
// Effects: Reads all data from colums of "Class", "Credits", and "Grades"
//          and places them in a Taken_Course data type in a vector
// Modifies: data
void read_csv(const string &filename, vector<Taken_Course> &data) {
    csvstream csv(filename);
    map<string, string> credits_data;
    
    string name_in;
    int credits_in;
    string grade_in;
    
    while (csv >> credits_data) {
        for (auto &col:credits_data) {
            string label = col.first;
            string datum = col.second;
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

// Effects: Prints out all raw_data in data vector
//          (used for debugging purposes)
void view_raw_data(const vector<Taken_Course> &data) {
    for (auto i:data) {
        std::cout << i.name << " " << i.credits << " " << i.grade << endl;
    }
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "invalid arguments\n";
        return 1;
    }
    // Raw data is stored in vector format from read_csv with
    // Taken_Course data type = class name, grade, credits
    // Will be converted into a map
    // Key = department name, and Val = Category data type
    // Ex class EECS 183, is put into EECS category
    vector<Taken_Course> raw_data;
    read_csv(argv[1], raw_data);
    //view_raw_data(raw_data);
    
    
    map<string, Category> main_data;
    place_in_map(raw_data, main_data);
    
    for (auto i:main_data) {
        std::string key = i.first;
        Category c = i.second;
        std::cout << "*****" << c.key << " " << c.total_credits << std::endl;
        for (auto i:c.sub_data) {
            std::cout << i.name << " " << i.grade << " " << i.credits << std::endl;
        }
    }

    return 0;
}
