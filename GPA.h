#ifndef GPA_H
#define GPA_H

#include <string>
#include <map>
#include <vector>
#include <utility>

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
    
    // EFFECTS: Returns GPA by category
    double get_category_GPA(const std::string &category);
    
    // EFFECTS: Returns total GPA
    double get_total_GPA();
    
private:
    std::map<std::string, Category> main_data;
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



double Overall::get_category_GPA(const std::string &ctgy) {
    if (main_data.find(ctgy) != main_data.end()) {
        return main_data[ctgy].category_gpa;
    }
    else {
        std::cout << "Category Does Not Exist\n";
        return 0;
    }
}


double Overall::get_total_GPA() {
    return total_average_gpa;
}









#endif
