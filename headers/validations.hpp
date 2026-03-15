#pragma once
#include <iostream>
#include <string>

namespace validations{

    int validate_name(const std::string name , int size);
    int validate_dob(int day, int month, int year);
    int validate_gender(char gender);
    int validate_course(const std::string & course , int size );
    int validate_section(const char & section);
    int validate_number_of_subjects(int n);
    int validate_enrollement_year(int year);
    int validae_pending_fee(int fee);
    int validate_email(const std::string & email , int size);
    int validate_phone_no(const std::string & phone_no);
    int validate_address_field(const std::string & address_field , int size);
    int validate_address_pincode(const std::string & pincode );

}
