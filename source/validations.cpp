#include "../headers/validations.hpp"


namespace validations{

    int validate_name(std::string name , int size){

        if (name.size()+1 > size){
            return -1;
        }
        for (int i = 0; i < name.size(); i++){
            if (!((name[i] >= 'A' && name[i] <='Z' ) || (name[i] >= 'a' && name[i] <='z' ) || name[i] == ' ')){
                return 0;
            }
        }
        return 1;

    }


    int validate_dob(int day, int month, int year){
        return 1;
    }
    

    int validate_gender(char gender){

        if (gender == 'M' || gender == 'F'){
            return 1;
        }
        else{
            return 0;
        }
    }

    int validate_course(const std::string & course , int size ){

        if (course.size()+1 > size){
            return -1;
        }
        for (int i = 0; i < course.size(); i++){
            if (!((course[i] >= 'A' && course[i] <='Z' ) || (course[i] >= 'a' && course[i] <='z' ) || course[i] == ' ')){
                return 0;
            }
        }
        return 1;

    }

    int validate_section(const char & section){

        if (!(section >= 'A' && section <='Z' )){
            return 0;
        }
        return 1;
    }

    int validate_number_of_subjects(int n){
        if (n > 10 || n < 0){
            return 0;
        }
        return 1;
    }

    int validate_enrollement_year(int year){
        return 1;
    }

    int validae_pending_fee(int fee){
        if (fee >= 0){
            return 1;
        }
        return 0;
    }

    int validate_email(const std::string & email , int size){

        if (email.size()+1 > size){
            return -1;
        }
        for (int i = 0; i < email.size(); i++){
            if (!((email[i] >= 'A' && email[i] <='Z' ) || (email[i] >= 'a' && email[i] <='z' ) || email[i] == '@'|| email[i] == '.'|| email[i] == '_'|| email[i] == '-')){
                return 0;
            }
        }
        return 1;
    }

    int validate_phone_no(const std::string & phone_no){
        if (phone_no.size() != 10 ){
            return -1;
        }
        for (int i = 0; i < phone_no.size(); i++){
            if (!(phone_no[i] >= '0' && phone_no[i] <='9' )){
                return 0;
            }
        }
        return 1;
    }

    int validate_address_field(const std::string & address_field , int size){
        if (address_field.size() + 1 > size){
            return -1;
        }
        for (int i=0 ; i < address_field.size() ; i++){
            if (!((address_field[i] >= 'A' && address_field[i] <='Z' ) || (address_field[i] >= '0' && address_field[i] <='9' ) || (address_field[i] >= 'a' && address_field[i] <='z' ) || address_field[i] == ' ' || address_field[i] == ',' )){
                return 0;
            }
        }
        return 1;
    }

    int validate_address_pincode(const std::string & pincode ){
        if (pincode.size() != 6 ){
            return -1;
        }
        for (int i = 0; i < pincode.size(); i++){
            if (!(pincode[i] >= '0' && pincode[i] <='9' )){
                return 0;
            }
        }
        return 1;
    }

};