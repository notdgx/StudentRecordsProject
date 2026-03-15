#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "subjects.hpp"
#include <iomanip>
#include <filesystem>

namespace templates{

    struct templateindex{
        char template_name_in_index[20];
        int template_N_in_index;
    };

    Subject enter_and_return_sub();
    std::ofstream file_exists_check(const std::string & file_name , int number_of_subjects );
    int do_template_exist(const std::string & template_name);
    void add_template_index(const std::string & template_name , int number_of_subjects);
    void replace_template_index(const std::string & template_name , int number_of_subjects , int index);
    void delete_template_index(int index);
    templateindex give_template_data_at_index(int index);
    int give_number_of_subjects(const std::string & template_name);

    int create_template(const std::string & template_name , int number_of_subjects );
    void delete_template(const std::string & template_name);
    Subject * return_template_data(const std::string & template_name);
    void show_template(const std::string & template_name);
    void show_template_index();

}