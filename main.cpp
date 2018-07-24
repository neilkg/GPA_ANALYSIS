
// Created by Neil Gollapudi 7/22/2018

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "csvstream.h"
//#include "parse_csv.cpp"
//#include "gpa_process.cpp"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "invalid arguments\n";
        return 1;
    }
    std::map<std::string, std::pair<std::string, std::string>> main_stuff;
    std::string class_type;
    std::string credits;
    std::string grade;
    
    
    
    std::string filename = argv[1];
    std::map<std::string, std::string> data;
    csvstream csvin(filename);
    while (csvin >> data) {
        for (auto &col:data) {
            if (col.first == "Class") {
                class_type = col.second;
                std::cout << "hi";
            }
            else if (col.first == "Credits") {
                credits = col.second;
            }
            else if (col.first == "Grades"){
                grade = col.second;
            }
        }
        std::cout << class_type << credits << grade << std::endl;
        main_stuff[class_type] = std::make_pair(credits, grade);
    }

    return 0;
}
