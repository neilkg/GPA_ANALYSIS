#ifndef GPA_H
#define GPA_H

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include "termcolor.hpp"

// Created by Neil Gollapudi 7/22/2018

// Used in Category class
struct Taken_Course {
    std::string name;
    std::string grade;
    int credits;
};

// Used in Overall class
class Category {
public:
    Category() : category_gpa(0), category_credits(0) {}
    
    std::vector<Taken_Course> sub_data;
    std::string key;
    double category_gpa;
    int category_credits;
};


class Overall {
public:
    Overall() : total_average_gpa(0), total_credits(0) {}
    
    // Requires: class name in Taken_Course has capital department name letters
    //           ex. EECS is EECS department for 183 class
    // Effects: takes raw data and converts it to map data format for future
    //          processing convinience
    //          For each category, only gives vector type, key, and total_credits
    // Modifies: main_data, total_credits
    void place_in_map(const std::vector<Taken_Course> &raw_data);
    
    
    // EFFECTS: Computes GPA for each category in the Overall class main_data map
    //          Precomputation allows for easy access later
    // MODIFIES: main_data
    void compute_category_GPA();

    // EFFECTS: Computes total overall GPA for student
    // MODIFIES: total_average_gpa
    void compute_total_GPA();
    
    // EFFECTS: Returns total GPA
    double get_total_GPA();
    
    // EFFECTS: Returns GPA by different categories
    double get_category_GPA(std::vector<std::string> &categories);
    
    // EFFECTS: Returns total credits
    int get_total_credits();
    
    // EFFECTS: Returns combined credits from categories
    int get_category_credits(std::vector<std::string> &categories);
    
    // EFFECTS: Displays all raw data to cout
    void view_transcript();
    
    // EFFECTS: Places new temporary data in map and recomputes the total GPA
    //          and GPA for a particular category and credits
    void add_to_map(const std::string &class_name_in, int credits_in, const std::string &grade_in);
    
    // EFFECTS: Removes all previous temporarily added grade data
    void remove_all_added();
    
private:
    std::map<std::string, Category> main_data;
    std::vector<Taken_Course> added_data;
    std::map<std::string, double> grade_to_gpa = {{"A+", 4.0}, {"A", 4.0},
        {"A-", 3.7}, {"B+", 3.3}, {"B", 3.0}, {"B-", 2.7}, {"C+", 2.3},
        {"C", 2.0}, {"C-", 1.7}, {"D", 1}, {"E", 0}};
    double total_average_gpa;
    int total_credits;
    
    // Used in place_in_map()
    // Effects: removes all non uppercase characters in the string
    // Modifies: str
    void remove_nonuppercase(std::string &str);
};




//********************IMPLEMENTATION_BELOW***********************//


void Overall::remove_nonuppercase(std::string &str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            str.erase(str.begin() + long(i), str.end());
            return;
        }
    }
}


void Overall::place_in_map(const std::vector<Taken_Course> &raw_data) {
    
    for (auto i:raw_data) {
        std::string department_name = i.name;
        remove_nonuppercase(department_name);
        
        // department name maps to its respective category object
        Category *object = &main_data[department_name];
        object->sub_data.push_back(i);
        object->key = department_name;
        object->category_credits += i.credits;
        
        total_credits += i.credits;
    }
}


void Overall::compute_category_GPA() {
    for (auto &ctgy:main_data) {
        double total_MTP = 0;
        for (auto &course:ctgy.second.sub_data) {
            total_MTP += (course.credits * grade_to_gpa[course.grade]);
        }
        ctgy.second.category_gpa = total_MTP / ctgy.second.category_credits;
    }
}


void Overall::compute_total_GPA() {
    double total_MTP = 0;
    for (auto &ctgy:main_data) {
        total_MTP += (ctgy.second.category_credits * ctgy.second.category_gpa);
    }
    total_average_gpa = total_MTP / total_credits;
}



double Overall::get_total_GPA() {
    return total_average_gpa;
}

int Overall::get_total_credits() {
    return total_credits;
}

double Overall::get_category_GPA(std::vector<std::string> &categories) {
    double MTP = 0;
    int credits = 0;
    for (auto i:categories) {
        if (main_data.find(i) != main_data.end()) {
            credits += main_data[i].category_credits;
            MTP += main_data[i].category_credits * main_data[i].category_gpa;
        }
    }
    return MTP / credits;
}

int Overall::get_category_credits(std::vector<std::string> &categories) {
    int credits = 0;
    for (auto i:categories) {
        if (main_data.find(i) != main_data.end()) {
            credits += main_data[i].category_credits;
        }
    }
    return credits;
}

// for seperation of transcript tables
template<typename T> void printElement(T t, const int& width)
{
    std::cout << std::left << std::setw(width) << std::setfill(' ') << t;
}

void Overall::view_transcript() {
    int x = 0;
    std::cout << termcolor::bold << termcolor::red << termcolor::underline;
    std::cout << "Transcript";
    std::cout << termcolor::reset << "\n";
    for (auto i:main_data) {
        std::cout << termcolor::reset;
        std::cout << termcolor::bold;
        int num = 4;
        if (x%num == 0) {
            std::cout << termcolor::green;
        }
        else if (x%num == 1) {
            std::cout << termcolor::magenta;
        }
        else if (x%num == 2) {
            std::cout << termcolor::cyan;
        }
        else if (x%num == 3) {
            std::cout << termcolor::yellow;
        }
        for (auto j:i.second.sub_data) {
            printElement(j.name, 15);
            printElement(j.grade, 5);
            printElement(j.credits, 10);
            std::cout << std::endl;
        }
        ++x;
    }
    std::cout << termcolor::reset;
    
}

void Overall::add_to_map(const std::string &class_name_in, int credits_in, const std::string &grade_in) {
    std::string department_name = class_name_in;
    remove_nonuppercase(department_name);
    Category *ctgy = &main_data[department_name];
    
    Taken_Course object;
    
    object.name = class_name_in;
    object.credits = credits_in;
    object.grade = grade_in;
    
    ctgy->sub_data.push_back(object);
    added_data.push_back(object);
    
    
    double MTP = ctgy->category_gpa * ctgy->category_credits;
    MTP += credits_in * grade_to_gpa[grade_in];
    ctgy->category_credits += credits_in;
    ctgy->category_gpa = MTP / ctgy->category_credits;
    
    MTP = total_credits * total_average_gpa;
    MTP += credits_in * grade_to_gpa[grade_in];
    total_credits += credits_in;
    total_average_gpa = MTP / total_credits;
}

void Overall::remove_all_added() {
    for (size_t i = 0; i < added_data.size(); ++i) {
        Taken_Course *course = &added_data[i];
        std::string department_name = course->name;
        remove_nonuppercase(department_name);
        
        Category *ctgy = &main_data[department_name];
        ctgy->category_credits -= course->credits;
        total_credits -= course->credits;
        
        for (size_t i = 0; i < ctgy->sub_data.size(); ++i) {
            if (ctgy->sub_data[i].name == course->name &&
                ctgy->sub_data[i].credits == course->credits &&
                ctgy->sub_data[i].grade == course->grade) {
                ctgy->sub_data.erase(ctgy->sub_data.begin() + long(i));
                break;
            }
        }
        
        if (ctgy->sub_data.size() == 0) {
            main_data.erase(department_name);
        }
    }
    
    compute_category_GPA();
    compute_total_GPA();
}









#endif
