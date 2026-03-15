#pragma once
#include "../headers/additionalfucntions.hpp"
#include "../headers/datafile.hpp"
#include "../headers/fields.hpp"
#include "../headers/subjects.hpp"
#include "../headers/templates.hpp"
#include "../headers/validations.hpp"




namespace interface{

    namespace general{
        void show_recent();
        void show_all_sub();
        void show_all_stu();
        void show_sub_by_rollno();
        void show_std_by_rollno();
        void show_session();
        void show_template_index();
        void show_template_by_name();


        void add_template();
        void delete_record();
        void delete_template();
        void modify_template();

        void export_csv();
        void export_csv_by_course();

        void open_record();

    } 

    namespace object{
        void add();
        void open();
    }
}