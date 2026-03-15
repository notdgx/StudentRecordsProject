#include <string>
#include "../headers/subjects.hpp"

namespace datafields{

struct date{
    int day;
    int month;
    int year;
};

struct address {
    char house[20];
    char street[60];
    char city[40];
    char state[40];
    char country[40];
    char pincode[7];
};

struct contact{
    char email[40];
    char phone_no[11];
    };



struct fields{

    int student_id;
    int student_rollno;
    char student_name[60];
    date student_dob{0,0,0};
    char student_gender; 
    char student_course[20];
    char student_section;
    int student_number_of_subjects;
    int student_enrollement_year;
    int student_pending_fee=0;
    contact student_contacts{"N/A","N/A"};
    address student_address{0};
    Subject student_subjects[10]; // max is 10 stubjects allowed

};

struct sub_rollno{
    char student_course[20];
    int student_rollno_A;
};


}