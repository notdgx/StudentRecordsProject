#pragma once 

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../headers/fields.hpp"

extern int  student_id_A;
extern int rollno_assigner_initial;

namespace recorddata{

    extern std::string session_file_path;
    extern std::string record_file_path;
    extern int rollno_assigner;

    namespace session{
        int add_data(const std::string & course);
        int update_data(const std::string & course, int index);
        int get_course_rollno(const std::string & course);
        int do_course_exists(const std::string & course);
        datafields::sub_rollno * get_data();
        int get_length();
        int get_student_id_A();
        int init_rollno_for_new_course();
        void init_session();
    }

    namespace record{
        int add_data(datafields::fields & data);
        int update_data(datafields::fields & data);
        int delete_data(datafields::fields & data);
        int do_exists(datafields::fields & data);
        int do_exists(int rollno);
        int get_length();
        int check_duplicate(datafields::fields & data);
        int init_record();
        int no_of_deleted();
    }

    namespace fetch{
        datafields::fields record_by_key(int key, bool flag);
        datafields::fields record_by_rollno(int rollno);
        datafields::fields record_by_id(int student_id);
        datafields::fields * all_record();
        datafields::fields * records_by_course(const std::string & course);
        int no_of_records_by_course(const std::string & course);
        int export_csv_by_course(const std::string & course);
        int export_csv_all();
    }

    namespace show{
        int all_records(int flag);
        int records_by_course(const std::string & course,int flag);
        int single_by_rollno(int rollno,int flag);
        int session_data();
        int single_by_rollno(datafields::fields data,int flag);
    }

    int init_files();
    int connect(datafields::fields & data);

}
