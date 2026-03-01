#include <iostream>
#include <string>
#include "subjects.cpp"
#include "courses.cpp"
#include "additionalfunctions.cpp"
#include "templates.cpp"
#include "forstudents.cpp"



class Students
{

private:

    int student_id;
    int student_rollno;
    string student_name;
    forstudents::date student_dob{0,0,0};
    char student_gender; 
    char student_course[20];
    char student_section;
    int student_number_of_subjects;
    int student_enrollement_year;
    int student_pending_fee=0;
    forstudents::contact student_contacts{"N/A","N/A","N/A"};
    Subject sub[10];

    void generate_rollno()
    {

    }

    void generate_student_id(){
        student_id = forstudents::student_id_A;
        forstudents::student_id_A++;
    }

public:

    //SETTERS

    void set_student_name(const string & student_name){
        this->student_name = student_name;
    }

    void set_student_dob(int day, int month, int year){
        student_dob.day = day;
        student_dob.month = month;
        student_dob.year = year;
    }

    void set_student_gender(const char & student_gender){
        this->student_gender = student_gender;
    }

    void set_student_course(const string & student_course){
        strcpy(this->student_course, student_course.c_str());
    }

    void set_student_section(const char & student_section){
        this->student_section = student_section;
    }

    void set_student_number_of_subjects(int student_number_of_subjects){
        this->student_number_of_subjects = student_number_of_subjects;
    }

    void set_student_enrollement_year(int student_enrollement_year){
        this->student_enrollement_year = student_enrollement_year;
    }

    void set_student_pending_fee(int student_pending_fee){
        this->student_pending_fee = student_pending_fee;
    }


    void set_students_contacts_email(const string & email){
        student_contacts.email = email;
    }

    void set_students_contacts_phoneno(const string & phone_no){
        strcpy(student_contacts.phone_no,phone_no.c_str());
    }

    void set_students_contacts_address(const string & address){
        student_contacts.address = address;
    }









};



