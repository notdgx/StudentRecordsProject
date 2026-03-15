#pragma once
#include <iostream>
#include <string>
#include "../headers/subjects.hpp"
#include "../headers/students.hpp"
#include "../headers/additionalfucntions.hpp"
#include "../headers/templates.hpp"
#include "../headers/fields.hpp"
#include "../headers/validations.hpp"

class Students {

private:
    static int student_rollno_A;
    static int student_id_A;

    datafields::fields data{};

    void generate_rollno();
    void generate_student_id();

public:
    // constructors
    Students();

    // seters
    int set_student_name(const std::string& student_name, int day, int month, int year, const char& student_gender);
    int set_student_dob(int day, int month, int year);
    int set_student_gender(const char& student_gender);
    int set_student_course(const std::string& student_course);
    int set_student_section(const char& student_section);
    int set_student_number_of_subjects(int student_number_of_subjects);
    int set_student_enrollement_year(int student_enrollement_year);
    int set_student_pending_fee(int student_pending_fee);
    int set_students_contacts_email(const std::string& email);
    int set_students_contacts_phone_no(const std::string& phone_no);
    int set_students_contacts_address( const std::string & house, const std::string & street, const std::string & city, const std::string & state, const std::string& country,const std::string& pincode);

    // gettersss
    int get_student_id();
    int get_student_rollno();
    std::string get_student_name();
    datafields::date get_student_dob();
    char get_student_gender();
    std::string get_student_course();
    char get_student_section();
    int get_student_number_of_subjects();
    int get_student_pending_fee();
    Subject* get_student_subjects();
    datafields::contact get_student_contacts();
    datafields::address get_student_address();
};