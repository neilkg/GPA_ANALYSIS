#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include "read_csv.h"
#include "GPA.h"

// Created by Neil Gollapudi 7/22/2018

using namespace std;


int main(int argc, char *argv[]) {
    setprecision(3);
    if (argc != 2) {
        cerr << "invalid arguments\n";
        return 1;
    }
    
    // driver is where the main instance of Overall class
    // map of all data is stored here as well as total gpa and credits
    Overall driver;
    
    // Raw data is stored in vector format from read_csv with
    // Taken_Course data type = class name, grade, credits
    // Will be converted into a map
    // Key = department name, and Val = Category data type
    // Ex class EECS 183, is put into EECS category
    vector<Taken_Course> raw_data;
    read_csv(argv[1], raw_data);
    
    place_in_map(raw_data, driver);
    compute_category_GPA(driver);
    compute_total_GPA(driver);
    
    
    // Finished storing all information in data structures and precomputing
    
    // TODO
    // Still need to create a user interface and make all of the settings
    // described in read me
    
    
    
    return 0;
}

