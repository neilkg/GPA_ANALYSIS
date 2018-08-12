#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include "read_csv.h"
#include "GPA.h"
#include "termcolor.hpp"

// Created by Neil Gollapudi 7/22/2018

void print_menu() {
    std::cout << termcolor::grey;
    std::cout << "1: Overall GPA\n";
    std::cout << "2: Category GPA\n";
    std::cout << "3: Modify GPA\n";
    std::cout << "4: View Transcript\n";
    std::cout << "5: Quit\n";
    std::cout << termcolor::reset;
    
}

void main_processing(int command, Overall &driver);



// driver is where the main instance of Overall class
// map of all data is stored here as well as total gpa and credits

// Raw data is stored in vector format from read_csv with
// Taken_Course data type = class name, grade, credits
// Will be converted into a map
// Key = department name, and Val = Category data type
// Ex class EECS 183, is put into EECS category
int main(int argc, char *argv[]) {
    std::cout << std::setprecision(4);
    if (argc != 2) {
        std::cerr << "invalid arguments\n";
        return 1;
    }
    

    Overall driver;
    
    std::vector<Taken_Course> raw_data;
    read_csv(argv[1], raw_data);
    
    driver.place_in_map(raw_data);
    driver.compute_category_GPA();
    driver.compute_total_GPA();
    
    print_menu();
    int command;
    std::cout << "% ";
    while(std::cin >> command && (command == 1 || command == 2 ||
                                  command == 3 || command == 4)) {
        std::cout << "\n";
        main_processing(command, driver);
        std::cout << "\n\n";
        print_menu();
        std::cout << "% ";
    }
    
    std::cout << termcolor::bold;
    std::cout << "\nThank you for using the GPA calculator\n" << std::endl;
    std::cout << termcolor::reset;
    return 0;
}





//************IMPLEMENTATION**************//

void main_processing(int command, Overall &driver) {
    if (command == 1) {
        std::cout << termcolor::underline << "Overall GPA" << termcolor::reset << "\n";
        std::cout << termcolor::bold;
        std::cout << "GPA: " << driver.get_total_GPA() << "\n";
        std::cout << "Credits: " << driver.get_total_credits();
        std::cout << termcolor::reset;
    }
    else if (command == 2) {
        std::vector<std::string> categories;
        std::cout << "What category(s) would you like to find the combined";
        std::cout << " GPA of?\n";
        std::cout << "% ";
        
        std::string s;
        std::string type = "";
        
        std::cin.ignore();
        std::getline(std::cin, s);
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') {
                categories.push_back(type);
                type = "";
            }
            else if (i == s.size() - 1) {
                type.push_back(s[i]);
                categories.push_back(type);
            }
            else {
                type.push_back(s[i]);
            }
        }
        std::cout << "\n";
        
        std::cout << termcolor::underline << s << " GPA" << termcolor::reset << "\n";
        std::cout << termcolor::bold;
        std::cout << "GPA: " << driver.get_category_GPA(categories) << "\n";
        std::cout << "Credits: " << driver.get_category_credits(categories);
        std::cout << termcolor::reset;
    }
    else if (command == 3) {
        int choice;
        std::cout << "1: Add data\n";
        std::cout << "2: Clear data\n";
        std::cout << "% ";
        std::cin >> choice;
        
        if (choice == 1) {
            std::string class1;
            int credits1;
            std::string grade1;
            
            std::cout << "\nClass Name: ";
            std::cin.ignore();
            std::getline(std::cin, class1);
            std::cout << "Credits: ";
            std::cin >> credits1;
            std::cout << "Grade: ";
            std::cin.ignore();
            std::getline(std::cin, grade1);
            
            driver.add_to_map(class1, credits1, grade1);
        }
        else {
            driver.remove_all_added();
        }
    }
    else if (command == 4) {
        driver.view_transcript();
    }
}


