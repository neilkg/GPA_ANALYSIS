
// Created by Neil Gollapudi 7/22/2018

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include "csvstream.h"

using namespace std;

struct Taken_Course {
    string name;
    string grade;
    int credits;
};

/*
class Category {
    vector<Taken_Course> sub_data;
    string key;
    double average_gpa;
    int total_credits;
};
 */

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

void view_raw_data(vector<Taken_Course> &data) {
    for (auto i:data) {
        std::cout << i.name << " " << i.credits << " " << i.grade << endl;
    }
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "invalid arguments\n";
        return 1;
    }
    vector<Taken_Course> raw_data;
    read_csv(argv[1], raw_data);
    view_raw_data(raw_data);

    return 0;
}
