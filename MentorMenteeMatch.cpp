
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include "termcolor.hpp"

using namespace std;


struct Location {
    string city;
    string state;
    string country;
};

struct Mentor {
    string FirstName;
    string LastName;
    string PhoneNum;
    string email;
    string biography;
    string language;
    string contact_preference;
    string ref_language;
    Location curr_location;
    
    // unique to mentor
    vector<string> specialty;
};

struct Mentee {
    string FirstName;
    string LastName;
    string PhoneNum;
    string language;
    string email;
    string biography;
    string contact_preference;
    string ref_language;
    Location curr_location;
};


void new_user(Mentee &mentee) {
    string fName, lName, phoneNum, email, bio, contact_preference, ref_language;
    string ccity, cstate, ccountry, language;
    
    cout << "First Name: ";
    cin >> fName;
    mentee.FirstName = fName;
    cout << "Last Name: ";
    cin >> lName;
    mentee.LastName = lName;
    cout << "Phone Number: ";
    cin >> phoneNum;
    mentee.PhoneNum = phoneNum;
    cout << "Email: ";
    cin >> email;
    mentee.email = email;
    cout << "Biography: ";
    cin >> bio;
    mentee.biography = bio;
    cout << "Contact Preferences: ";
    cin >> contact_preference;
    mentee.contact_preference = contact_preference;
    cout << "Language: ";
    cin >> language;
    mentee.language = language;
    
    Location loc;
    cout << "Current City: ";
    cin >> ccity;
    loc.city =  ccity;
    cout << "Current State: ";
    cin >> cstate;
    loc.state = cstate;
    cout << "Current Country: ";
    cin >> ccountry;
    loc.country = ccountry;
    mentee.curr_location = loc;
    
    
    cout << "Refugee Language: ";
    cin >> ref_language;
    mentee.ref_language = ref_language;
    cout << endl;
}


void do_search(vector<Mentor> &mentors, Mentee &mentee) {
    // scale of 0 - 10
    int language_pref;
    cout << termcolor::bold;
    cout << "On a scale of 0 - 10 what is your Language Preference: ";
    cin >> language_pref;
    int location_pref;
    cout << "On a scale of 0 - 10 what is your Location Preference: ";
    cin >> location_pref;
    int refugee_pref;
    cout << "On a scale of 0 - 10 what is your Refugee Preference: ";
    cin >> refugee_pref;
    cout << endl;
    
    cout << "What type of advice are you looking for?" << endl;
    cout << "ex. General,Banking,Friends,Healthcare" << endl;
    cout << "% ";
    cout << termcolor::reset;
    string advice;
    cin >> advice;
    cout << endl;
    
    vector<string> advice_words;
    string to_push;
    for (size_t i = 0; i < advice.size(); ++i) {
        if (advice[i] == ',') {
            advice_words.push_back(to_push);
            to_push = "";
        }
        else {
            to_push += advice[i];
        }
    }
    
    
    vector<int> curr_values(mentors.size(), 0);
    for (size_t i = 0; i < mentors.size(); ++i) {
        if (mentors[i].curr_location.country == mentee.curr_location.country) {
            curr_values[i] += (0.25 * location_pref);
        }
        if (mentors[i].curr_location.state == mentee.curr_location.state) {
            curr_values[i] += (0.5 * location_pref);
        }
        if (mentors[i].curr_location.city == mentee.curr_location.city) {
            curr_values[i] += (location_pref);
        }
        if (mentors[i].language == mentee.language) {
            curr_values[i] += language_pref;
        }
        if (mentors[i].ref_language == mentee.ref_language) {
            curr_values[i] += refugee_pref;
        }
        // sponsor must have the same contact_preference
        if (mentors[i].contact_preference != mentee.contact_preference) {
            curr_values[i] -= 1000;
        }
    }
    
    for (size_t i = 0; i < mentors.size(); ++i) {
        bool is_expert = false;
        vector<string> mentor_special = mentors[i].specialty;
        for (size_t j = 0; j < mentor_special.size(); ++j) {
            for (size_t k = 0; k < advice_words.size(); ++k) {
                if (mentor_special[j] == advice_words[k]) {
                    is_expert = true;
                }
            }
        }
        if (!is_expert) {
            curr_values[i] -= 1000;
        }
    }
    
    
    vector<int> finals;
    for (size_t i = 0; i < 5; ++i) {
        int max = curr_values[0];
        int idx = 0;
        for (size_t j = 1; j < curr_values.size(); ++j) {
            if (max < curr_values[j]) {
                max = curr_values[j];
                idx = int(j);
            }
        }
        finals.push_back(idx);
        curr_values.erase(curr_values.begin() + idx);
    }
    
    cout << termcolor::bold << termcolor::red;
    int idx = 1;
    for (size_t i = 0; i < finals.size(); ++i) {
        cout << idx << ". ";
        ++idx;
        cout << mentors[size_t(finals[i])].FirstName << " " << mentors[size_t(finals[i])].LastName << " ";
        cout << mentors[size_t(finals[i])].PhoneNum << " " << mentors[size_t(finals[i])].email << endl << endl;
    }
    cout << termcolor::reset;
    
}

void add_person(string first, string last, string phone, string email, string bio, string language, string contact_pref, string ref_lang, string city, string state, string country, vector<Mentor> &mentors, vector<string> &special) {
    Mentor ment;
    ment.FirstName = first;
    ment.LastName = last;
    ment.PhoneNum = phone;
    ment.email = email;
    ment.biography = bio;
    ment.language = language;
    ment.contact_preference = contact_pref;
    ment.ref_language = ref_lang;
    Location loc;
    loc.city = city;
    loc.state = state;
    loc.country = country;
    ment.specialty = special;
    mentors.push_back(ment);
}


void populate_database(vector<Mentor> &mentors) {
    vector<string> special = {"General", "Friends"};
    add_person("Bob", "Billy", "(384) 345-5642", "bob@gmail.com", "Hello !", "English", "Phone", "Spanish", "Toronto", "Ontario", "Canada", mentors, special);
    special = {"Entertainment, Banking"};
    add_person("Joshua", "Lativski", "(267)456-9856", "josh@gmail.com", "Hello", "English", "Skype", "Spanish", "Toronto", "Ontario", "Canada", mentors, special);
    special = {"Banking, Housing"};
    add_person("Dimna", "Latviski", "(267)958-1309", "dima@hotmail.com", "Hello", "English", "Skype", "Spanish", "Iowa", "Ontario", "Canada", mentors, special);
    add_person("Jika", "Krytoi", "(276)4789843", "krutoi@comcast.net", "Hey", "Spanish", "Phone", "English", "Toronto", "Ontario", "Canada", mentors, special);
    special = {"Healthcare, Faith"};
    add_person("Denis", "Berzuk", "(267)438-1895", "jake@gmail.com", "HiThere", "English", "Email", "Spanish", "Dorval", "Quebec", "Canada", mentors, special);
    add_person("Roma", "Janik", "(264)891-4602", "rjanik@gmail.com", "Hello", "English", "Phone", "Spanish", "Beloeil", "Quebec", "Canada", mentors, special);
    special = {"Entertainment, General"};
    add_person("Vadim", "Bando", "(267)498-4901", "bando@gmail.com", "Hi", "Spanish", "Email", "Spanish", "Laval", "Quebec", "Canada", mentors, special);
    add_person("Salizo", "Metallo", "(467)975-9045", "zalizko@hotmail.com", "There", "Spanish", "Chat", "English", "Brooks", "Alberta", "Canada", mentors, special);
    special = {"Friends, Housing"};
    add_person("Bobik", "Tormozik", "(256)958-4091", "tormozik@gmail.com", "Hello", "English", "Phone", "Spanish", "Estevan", "Saskawatchewan", "Canada", mentors, special);
    add_person("Jika", "Jonski", "(564)894-1265", "jonski@comcast.net", "Hey", "Spanish", "Email", "English", "Dawson", "Yukon", "Canada", mentors, special);
    special = {"Employement, Genera"};
    add_person("Jukowsky", "Ganis", "(865)948-3027", "jenis@hotmail.com", "Hello", "English", "Phone", "English", "Barrie", "Ontario", "Canada", mentors, special);
    add_person("Valeria", "Kudovska", "(578)328-1957", "dima@rublovka.com", "Hey", "Spanish", "Phone", "English", "Brooks", "ALberta", "Canada", mentors, special);
    special = {"Healthcare, Entertainment"};
    add_person("Bobik", "Krytoi", "(658)091-3758", "bobchik@gmail.com", "Hello", "Spanish", "Email", "English", "Dorval", "Quebec", "Canada", mentors, special);
    add_person("Vadim", "Jenis", "(567)745-9013", "vadimchik@gmail.com", "Hey", "English", "Phone", "Spanish", "Chatham", "Ontario", "Canada", mentors, special);
    add_person("Joshua", "Lativski", "(267)456-9856", "josh@gmail.com", "Hello", "English", "Skype", "Spanish", "Toronto", "Ontario", "Canada", mentors, special);
    special = {"Banking, Housing"};
    add_person("Dimna", "Latviski", "(267)958-1309", "dima@hotmail.com", "Hello", "English", "Skype", "Spanish", "Iowa", "Ontario", "Canada", mentors, special);
    add_person("Jika", "Krytoi", "(276)478-9843", "krutoi@comcast.net", "Hey", "Spanish", "Phone", "English", "Toronto", "Ontario", "Canada", mentors, special);
    special = {"Healthcare, Faith"};
    add_person("Denis", "Berzuk", "(267)438-1895", "jake@gmail.com", "HiThere", "English", "Email", "Spanish", "Dorval", "Quebec", "Canada", mentors, special);
    add_person("Roma", "Janik", "(264)891-4602", "rjanik@gmail.com", "Hello", "English", "Phone", "Spanish", "Beloeil", "Quebec", "Canada", mentors, special);
    special = {"Entertainment, General"};
    add_person("Vadim", "Bando", "(267)498-4901", "bando@gmail.com", "Hi", "Spanish", "Email", "Spanish", "Laval", "Quebec", "Canada", mentors, special);
    add_person("Salizo", "Metallo", "(467)975-9045", "zalizko@hotmail.com", "There", "Spanish", "Chat", "English", "Brooks", "Alberta", "Canada", mentors, special);
    special = {"Friends, Employment"};
    add_person("Bobik", "Tormozik", "(256)958-4091", "tormozik@gmail.com", "Hello", "English", "Phone", "Spanish", "Estevan", "Saskawatchewan", "Canada", mentors, special);
    add_person("Jika", "Jonski", "(564)894-1260", "jonski@comcast.net", "Hey", "Spanish", "Email", "English", "Dawson", "Yukon", "Canada", mentors, special);
    special = {"Employement, Genera"};
    add_person("Jukowsky", "Ganis", "(865)948-3027", "jenis@hotmail.com", "Hello", "English", "Phone", "English", "Barrie", "Ontario", "Canada", mentors, special);
    add_person("Valeria", "Kudovska", "(578)328-1957", "dima@rublovka.com", "Hey", "Spanish", "Phone", "English", "Brooks", "ALberta", "Canada", mentors, special);
    special = {"Healthcare, Entertainment"};
    add_person("Bobik", "Krytoi", "(658)091-3758", "bobchik@gmail.com", "Hello", "Spanish", "Email", "English", "Dorval", "Quebec", "Canada", mentors, special);
    special = {"Banking"};
    add_person("Vadim", "Jenis", "(567)345-9013", "vadimchik@gmail.com", "Hey", "English", "Phone", "Spanish", "Chatham", "Ontario", "Canada", mentors, special);
}



int main() {
    vector<Mentor> mentors;
    Mentee mentee;
    populate_database(mentors);
    
    
    
    cout << termcolor::bold << termcolor::blue << termcolor::underline;
    cout << "The Refugee Mentor/Mentee Matcher!" << endl << endl;
    cout << termcolor::reset;
    cout << termcolor::bold;
    cout << "1: To Login" << endl;
    cout << "2: New User" << endl;
    
    int num;
    cout << "% ";
    cout << termcolor::reset;
    cin >> num;
    if (num == 1) {
        new_user(mentee);
    }
    else {
        new_user(mentee);
    }
    
    cout << termcolor::bold << termcolor::blue;
    cout << "There are " << mentors.size() << " in the network!" << endl;
    cout << termcolor::reset;
    cout << termcolor::bold;
    cout << "1: To do a search" << endl;
    cout << "2: To exit" << endl;
    cout << "% ";
    cout << termcolor::reset;
    while (cin >> num && num != 2) {
        cout << endl;
        do_search(mentors, mentee);
        cout << endl;
        cout << termcolor::bold;
        cout << "1: To do a search" << endl;
        cout << "2: To exit" << endl;
        cout << "% ";
        cout << termcolor::reset;
    }

    return 0;
}
