#include "../headers/interface.hpp"

// Where where is loop : still need to add exit logic
namespace interface{
    namespace general{

        void show_recent(){
            int state;
            std::cout << "The Recent Data : \n";
            state = recorddata::show::all_records(2);
            if (state == 0){
                std::cout << "Data Doesnt Exist \n";
            }

        }
        
        void show_all_sub(){
            int state;
            std::cout << "All Subjects Data : \n";
            state = recorddata::show::all_records(1);
            if (state == 0){
                std::cout << "Data Doesnt Exist \n";
            }
        }


        void show_all_stu(){
            int state;
            std::cout << "All Students Data : \n";
            state = recorddata::show::all_records(0);
            if (state == 0){
                std::cout << "Data Doesnt Exist \n";
            }
        }
        
        void show_sub_by_rollno(){ // course data of student by rollno
            int roll , state;
            do {
            std::cout << "Enter  the Roll No : ";
            std::cin >> roll ;
            if (std::cin.fail()){
                state = 2;
                std::cout << "Enter a valid rollno ! \n";
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                continue;

            }

            state = recorddata::show::single_by_rollno(roll,1);
            if (state == 1){
                break;
            }
            else if (state == 0 || state == -1){
                std::cout << "Record Doesnt Exist \n";
            }
        }while(true);
        
        // exit the funct too be added
    }
    
    void show_std_by_rollno(){ // student data  by rollno
        int roll , state;
        do {
            std::cout << "Enter  the Roll No : ";
            std::cin >> roll ;
            // state = recorddata::show::single_by_rollno(roll,0);
            if (std::cin.fail()){
                state = 2;
                std::cout << "Enter a valid rollno ! \n";
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                continue;
            }


            state = recorddata::show::single_by_rollno(roll,0);

            if (state == 1){
                break;
            }
            else if (state == 0){
                std::cout << "Record Doesnt Exist \n";
            }
        } while(true);
        
        
    }
    
    void show_session(){
        int state;
        state = recorddata::show::session_data();
        if (state == 0 || state == -1){
            std::cout << "Session Data Doesnt Exist \n";
        }
    }
    
    void show_template_index(){
        int state;
        state = templates::show_template_index();
        if (state == 0){
            std::cout << "Template Index Doesnt Exist \n";
        }
        
    }
    
    
    void show_template_by_name(){
        std::string name;
        int state;
        cin.ignore(1000,'\n');
        do{
        std::cout << "Enter the course name :";
        // std::cin >> name;
        getline(cin,name);
        if (name.length() > 19){
            std::cout << "Too Long";
            continue;
        }
        state = templates::show_template(name);
        if (state == 0){
            std::cout << "Template Doesnt Exist \n";
        }
        else if (state == 1){
            break;
        }
    }while(true);
}

// _______________________________

    void add_template(){
        std::string name;
        int n,state;
        cin.ignore(1000,'\n');
        do {
        std::cout << "Enter the Template name :";
        std::getline(cin,name);
        if (name.length() > 19){
            std::cout << "Template name too long \n";
            continue;
        }
        break;
        } while(true);

        do {
        std::cout << "Enter the no of subjects  :";
        std::cin >> n;
        if (std::cin.fail() || n > 10){
                state = 2;
                std::cout << "Enter valid number of Subjects ! \n";
                std::cin.clear();
                std::cin.ignore(1000,'\n');
        }
        break;

        }while (true);

        cin.ignore(1000,'\n');
        state = templates::create_template(name,n);

        if (state == -1){
            std::cout << "Cant Create \n";
        }
        else if (state ==  1){
            std::cout << "Template Created \n";
        }


    }
    void delete_record(){
        int rollno;
        datafields::fields temp;

        do{
        std::cout << "Enter the Roll No :";
        std::cin >> rollno;
            if (std::cin.fail()){
                std::cout << "Enter a valid rollno ! \n";
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                continue;
            }


        temp = recorddata::fetch::record_by_rollno(rollno);

        if (temp.student_id == 0 && recorddata::record::do_exists(rollno) != 1){
            std::cout << "Record Doesnt Exist \n";
        }
        else {
            recorddata::record::delete_data(temp);
            std::cout << "Record Deleted \n";
            break;
        } 
            }while(true); 
    }

    void delete_template(){
        std::string name;
        int state;
        cin.ignore(1000,'\n');
        do{
        std::cout << "Enter the Template name :";
        std::getline(cin,name);
        if (name.length() > 19){
            std::cout << "Template name too long \n";
            continue;
        }
        state = templates::do_template_exist(name);
        if (state == -1){
            std::cout << "Template Doesnt Exist \n";
        }
        else {
            templates::delete_template(name);
            break;
        }
    }while(true);
} 

    void modify_template(){
        std::string name;
        int flag1,n,flag2,flag3;
        char replace;
        cin.ignore(1000,'\n');
        do{
        std::cout << "Enter the Template name to modify :";
        // std::cin >> name;
        std::getline(cin,name);
        if (name.length() > 19){
            std::cout << "Template name too long \n";
            continue;
        }
        break;  
        }while(true);
    
        flag1 = templates::do_template_exist(name);
        if (flag1 == -1){
            std::cout << "Template doesnt Exist \n";
        }

        if (flag1 != -1){
            std::cout << "Do you want to change Number of subjects ? (y/n) :";
            std::cin >> replace ;
            if (replace == 'Y' || replace == 'y' ){

                do {
                    std::cout << "Enter the number of Subjects :";
                    std::cin >> n;
                    if (cin.fail()){
                        std::cout << "Enter valid number \n";
                        cin.clear();
                        cin.ignore(1000,'\n');
                    }
                    break;
                }while(true);
                
                flag2 = templates::modify_template(name,n);
                if (flag2 == 0){
                    std::cout << "File not opened\n";
                }
                else if(flag2 == 1){
                    std::cout << "Template Modified\n";
                }
            }
            else {
                flag3 = templates::modify_template(name);
                if (flag3 == 0){
                    std::cout << "File not opened\n";
                }
                else if (flag3 == 1)
                std::cout << "Template Modified\n";
            }
        }

    }

    // _____________________________

    void export_csv(){
        int state;
        state = recorddata::fetch::export_csv_all();
        
        if (state == -1){
            std::cout << "Data Doesnt Exist \n";
        }
        else if (state == 0){
            std::cout << "Cant create Files \n";
        }
        else if (state == 1){
            std::cout << "Data Files Exported \n";
        }

        }


    void export_csv_by_course(){
        std::string name;
        int state;
        std::cin.ignore(1000,'\n');
        do{
        std::cout << "Enter the Course name :";
        std::getline(cin,name);
        if (name.length() > 19){
            std::cout << "Course name Too Long\n";
            continue;
        }
        state = recorddata::fetch::export_csv_by_course(name);
        if (state == -1){
            std::cout << "Cant Fetch Data \n";
        }
        else if (state == 2){
            std::cout << "Data Doesnt Exist \n";
        }
        else if (state == 0){
            std::cout << "Cant Create Files \n";
        }
        else if (state == 1){
            std::cout << "Data Files Exported \n";
            break;
        }
        }while(true);
    }

    // ___________________________________

    }


    // _______________________
    // Object 
    // _____________________

    namespace object{

    void add() {
        datafields::fields data;
        int flag,tempused=0;
        std::string input;
        int num;
        char ch;

        bool courset = false;
        

        std::cin.ignore();
        do {
            std::cout << "Enter Student Name : ";
            std::getline(std::cin, input);
            flag = validations::validate_name(input, sizeof(data.student_name));
            if      (flag == -1) std::cout << "Name too long\n";
            else if (flag ==  0) std::cout << "Not a Valid Name\n";
        } while (flag != 1);
        
        strcpy(data.student_name, input.c_str());
        
        
        // std::cin.ignore();
        int day, month, year;
        do {

            flag = 3;
            std::cout << "Enter Student DOB  -> \n";
            std::cout << "Enter Day : ";
            std::cin >> day;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "Enter a Number ! \n";
                continue;
            }
            std::cout << "Enter Month : ";
            std::cin >> month;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "Enter a Number ! \n";
                continue;
            }
            std::cout << "Enter Year : ";
            std::cin >> year;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "Enter a Number ! \n";
                continue;
            }
            flag = validations::validate_dob(day, month, year);
            if (flag != 1) std::cout << "Enter a valid DOB \n";

        } while (flag != 1);

        data.student_dob = {day, month, year};


        do {
            std::cout << "Enter Gender (M/F) : ";
            std::cin >> ch;
            flag = validations::validate_gender(ch);
            if (flag != 1) std::cout << "Enter a valid Gender \n";
        } while (flag != 1);

        data.student_gender = ch;

    
        std::cin.ignore();
        do{

        do {
            std::cout << "Enter Course : ";
            std::getline(std::cin, input);
            flag = validations::validate_course(input, sizeof(data.student_course));
            if (flag == -1) std::cout << "Course name too long\n";
            else if (flag ==  0) std::cout << "Enter a valid Course Name\n";
            
        } while (flag != 1);
        
        if (templates::do_template_exist(input) == -1){
            strcpy(data.student_course, input.c_str());
            courset = true;
        }
        else {
            std::cout << "Course Exist in Template , Do you want to use template ? (y/n) ";
            std::cin >> ch ;
            if (ch == 'y' || ch =='Y'){
                tempused = 1;
                strcpy(data.student_course, input.c_str());
                num = templates::give_number_of_subjects(input);
                data.student_number_of_subjects = num ;
                Subject * subs = templates::return_template_data(input);
                    for (int i = 0; i < num; i++) {
                        data.student_subjects[i] = subs[i];
                    }
                    courset = true;
                
            }
            else {
                std::cout << "Enter a different course name : \n";
            }

        }

        }while(!courset) ;



        do {
            std::cout << "Enter Section (A-Z) : ";
            std::cin >> ch;

            flag = validations::validate_section(ch);
            if (flag != 1) {
                std::cout << "Section must be A-Z\n";
            }

        } while (flag != 1);
        data.student_section = ch;


        // ______________


        if (tempused != 1){

        do {
            std::cout << "Enter Number of Subjects : ";
            std::cin >> num;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "Enter a Number ! \n";
                continue;
            }
            flag = validations::validate_number_of_subjects(num);
            if (flag != 1) std::cout << "Must be between 1 and 10\n";
        } while (flag != 1);
        data.student_number_of_subjects = num;


        for (int i = 0; i < data.student_number_of_subjects; i++) {
            std::cout << "Enter Subject " << i + 1 << " details\n";
            data.student_subjects[i] = templates::enter_and_return_sub();
        }

        }

        // ______________________



        do {
            std::cout << "Enter Enrollment Year : ";
            std::cin >> num;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "Enter a Number ! \n";
                continue;
            }
            flag = validations::validate_enrollement_year(num);
            if (flag != 1) {
                std::cout << "Invalid year\n";
            }

        } while (flag != 1);

        data.student_enrollement_year = num;


        do {
            std::cout << "Enter Pending Fee : ";
            std::cin >> num;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "Enter a Number ! \n";
                continue;
            }
            flag = validations::validae_pending_fee(num);
            if (flag != 1) {
                std::cout << "Fee cannot be negative\n";
            }

        } while (flag != 1);
        data.student_pending_fee = num;



        do {
            std::cout << "Enter Student 's Email : ";
            std::cin >> input;
            flag = validations::validate_email(input, sizeof(data.student_contacts.email));
            if (flag == -1) {
                std::cout << "Email too long \n";
            }
            else if (flag ==  0) {
                std::cout << "Invalid email format\n";
            }

        } while (flag != 1);
        strcpy(data.student_contacts.email, input.c_str());


        std::cin.ignore();
        do {
            std::cout << "Enter Phone No (10 digits) : ";
            std::cin >> input;

            flag = validations::validate_phone_no(input);
            if (flag == -1){
                std::cout << "Must be exactly 10 digits\n";
            }
            else if (flag ==  0) {
                std::cout << "Only digits allowed\n";
            }

        } while (flag != 1);
        strcpy(data.student_contacts.phone_no, input.c_str());


        std::string house, street, city, state, country, pincode;

        std::cout<<"Enter the Address Details : \n";
        std::cin.ignore();
        do {
            std::cout << "Enter House : ";
            std::getline(std::cin, house);
            flag = validations::validate_address_field(house, sizeof(data.student_address.house));
            if (flag == -1) {
                std::cout << "Too long \n";
            }
            else if (flag ==  0) {
                std::cout << "invalid Format \n";
            }
        } while (flag != 1);

        // std::cin.ignore();
        do {
            std::cout << "Enter Street : ";
            std::getline(std::cin, street);
            flag = validations::validate_address_field(street, sizeof(data.student_address.street));
            if (flag == -1) {
                std::cout << "Too long\n";
            }
            else if (flag ==  0) {
                std::cout << "Invalid Format \n";
            }
        } while (flag != 1);

        // std::cin.ignore();
        do {
            std::cout << "Enter City : ";
            std::getline(std::cin, city);
            flag = validations::validate_address_field(city, sizeof(data.student_address.city));
            if (flag == -1) {
                std::cout << "Too long \n";
            }
            else if (flag ==  0) {
                std::cout << "Invalid Format  \n";
            }
        } while (flag != 1);

        // std::cin.ignore();
        do {
            std::cout << "Enter State : ";
            std::getline(std::cin, state);
            flag = validations::validate_address_field(state, sizeof(data.student_address.state));
            if (flag == -1) {
                std::cout << "Too long\n";
            }
            else if (flag ==  0) {
                std::cout << "Invalid format \n";
            }
        } while (flag != 1);

        // std::cin.ignore();
        do {
            std::cout << "Enter Country : ";
            std::getline(std::cin, country);
            flag = validations::validate_address_field(country, sizeof(data.student_address.country));
            if(flag == -1) {
                std::cout << "Too long\n";
            }
            else if (flag ==  0) {
                std::cout << "Invalid format \n";
            }
        } while (flag != 1);

        do {
            std::cout << "Enter Pincode (6 digits) : ";
            std::cin >> pincode;
            flag = validations::validate_address_pincode(pincode);
            if (flag == -1) {
                std::cout << "Must be exactly 6 digits\n";
            }
            else if (flag ==  0) {
                std::cout << "Only digits are allowed\n";
            }
        } while (flag != 1);

        strcpy(data.student_address.house,   house.c_str());
        strcpy(data.student_address.street,  street.c_str());
        strcpy(data.student_address.city,    city.c_str());
        strcpy(data.student_address.state,   state.c_str());
        strcpy(data.student_address.country, country.c_str());
        strcpy(data.student_address.pincode, pincode.c_str());


        int result = recorddata::connect(data);
        if (result == 1) {
            std::cout << "Student Record saved successfully\n";
        } else {
            std::cout << "Failed to Save\n";
        }
    }

    // OPEN ________________________________________



    void open(){
        std::string input;
        int rollno,flag,choice,courset,num,exit=0;
        datafields::fields data{0};
        bool tempused;
        char ch;


        do{
        std::cout << "Enter the Student Roll no : ";
        std::cin >> rollno ;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "Enter a Number ! \n";
                continue;
            }
        data = recorddata::fetch::record_by_rollno(rollno);
        // flag = recorddata::record::do_exists(rollno);
        if (data.student_id == 0 || data.student_id  == -1){
            std::cout<< "The Record Doesnt Exists \n";
        }
        else{
            
            std::cout<< "Record Opened \n";
            break;
        }
    } while(true);
    
        recorddata::show::single_by_rollno(rollno,0);

        recorddata::show::single_by_rollno(rollno,1);
        
        std::cout << "What you want to do ? \n";
        std::cout << "1 -> Modify Record \n";
        std::cout << "2 -> Delete Record \n";

        do {
        std::cout << "Enter Your Choice : ";
        std::cin >> choice ;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "Enter a Number ! \n";
                continue;
            }
            break;

        }while(true);
        
        if (choice == 2 ){
            std::cout << "Record Deleted \n";
            recorddata::record::delete_data(data);
        }
        else if (choice == 1){

            do {

            
            std::cout << "What you want to Modify ? \n";
            std::cout << "1 -> Modify Name \n";
            std::cout << "2 -> Modify DOB \n";
            std::cout << "3 -> Modify Gender \n";
            std::cout << "4 -> Modify Course \n";
            std::cout << "5 -> Modify Section \n";
            std::cout << "6 -> Modify Enrollement Year\n";
            std::cout << "7 -> Modify Fee \n";
            std::cout << "8 -> Modify Email \n";
            std::cout << "9 -> Modify Phone No \n";
            std::cout << "10 -> Modify Address \n";
            std::cout << "11 -> Modify Number of Subjects \n";
            std::cout << "12 -> Modify Subjects Details \n";
            std::cout << "13 -> Show Record \n";

            std::cout << "0 -> Save & Exit  \n";
            std::cout << "14 -> Dont Save & Exit  \n";

            do{
            std::cout << "Enter Your Choice : ";
            std::cin >> choice ;
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    std::cout << "Enter a Number ! \n";
                    continue;
                }
            break;
            }while(true);


            switch (choice){
                case 1:
                {
                    std::cin.ignore();
                        do {
                            std::cout << "Enter Student Name : ";
                            std::getline(std::cin, input);
                            flag = validations::validate_name(input, sizeof(data.student_name));
                            if      (flag == -1) std::cout << "Name too long\n";
                            else if (flag ==  0) std::cout << "Not a Valid Name\n";
                        } while (flag != 1);

                        strcpy(data.student_name, input.c_str());

                        break;
                
                    }


                case 2:
                {
                        int day, month, year;
                        do {

                            std::cout << "Enter Student DOB  : \n";
                            std::cout << "Enter Day : ";
                            std::cin >> day;
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                std::cout << "Enter a Number ! \n";
                                continue;
                            }
                            std::cout << "Enter Month : ";
                            std::cin >> month;
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                std::cout << "Enter a Number ! \n";
                                continue;
                            }
                            std::cout << "Enter Year : ";
                            std::cin >> year;
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                std::cout << "Enter a Number ! \n";
                                continue;
                            }
                            flag = validations::validate_dob(day, month, year);
                            if (flag != 1) std::cout << "Enter a valid DOB \n";

                        } while (flag != 1);

                        data.student_dob = {day, month, year};

                        break;

                    }


                case 3:
                {
                        do {
                            std::cout << "Enter Gender (M/F) : ";
                            std::cin >> ch;
                            flag = validations::validate_gender(ch);
                            if (flag != 1) std::cout << "Enter a valid Gender \n";
                        } while (flag != 1);

                        data.student_gender = ch;


                        break;
                    }


                case 4:
                {
                    std::cin.ignore();
                        do{

                            do {
                                std::cout << "Enter Course : ";
                                std::getline(std::cin, input);
                                flag = validations::validate_course(input, sizeof(data.student_course));
                                if (flag == -1) std::cout << "Course name too long\n";
                                else if (flag ==  0) std::cout << "Enter a valid Course Name\n";
                                
                            } while (flag != 1);
                            
                            if (templates::do_template_exist(input) == -1){
                                strcpy(data.student_course, input.c_str());
                                for (int i = 0; i < data.student_number_of_subjects; i++) {
                                        data.student_subjects[i] = {};
                                    }
                                data.student_number_of_subjects = 0;
                                courset = true;
                                std::cout << "Course Updated , Number of subject is Zero now , Update them\n";
                                tempused = 0;
                                
                            }
                            else {
                                std::cout << "Course Exist in Template , Do you want to use template ? (y/n) ";
                                std::cin >> ch ;
                                if (ch == 'y' || ch =='Y'){
                                    tempused = 1;
                                    strcpy(data.student_course, input.c_str());
                                    num = templates::give_number_of_subjects(input);
                                    for (int i = 0; i < data.student_number_of_subjects; i++) {
                                        data.student_subjects[i] = {};
                                    }
                                    data.student_number_of_subjects = num ;
                                    Subject * subs = templates::return_template_data(input);
                                        for (int i = 0; i < num; i++) {
                                            data.student_subjects[i] = subs[i];
                                        }
                                        courset = true;
                                    
                                }
                                else {
                                    std::cout << "Enter a different course name : \n";
                                }

                            }

                            }while(!courset) ;

                            break;
                        }


                case 5:
                {
                        do {
                            std::cout << "Enter Section (A-Z) : ";
                            std::cin >> ch;

                            flag = validations::validate_section(ch);
                            if (flag != 1) {
                                std::cout << "Section must be A-Z\n";
                            }

                        } while (flag != 1);
                        data.student_section = ch;

                        break;

                    }


                case 6:
                {
                        do {
                            std::cout << "Enter Enrollment Year : ";
                            std::cin >> num;
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                std::cout << "Enter a Number ! \n";
                                continue;
                            }
                            flag = validations::validate_enrollement_year(num);
                            if (flag != 1) {
                                std::cout << "Invalid year\n";
                            }

                        } while (flag != 1);

                        data.student_enrollement_year = num;

                        break;

                    }

                case 7 :
                {
                
                        do {
                            std::cout << "Enter Pending Fee : ";
                            std::cin >> num;
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                std::cout << "Enter a Number ! \n";
                                continue;
                            }
                            flag = validations::validae_pending_fee(num);
                            if (flag != 1) {
                                std::cout << "Fee cannot be negative\n";
                            }

                        } while (flag != 1);
                        data.student_pending_fee = num;

                        break;

                    }


                case 8: 
                {
                    std::cin.ignore();
                        do {
                            std::cout << "Enter Student 's Email : ";
                            std::cin >> input;
                            flag = validations::validate_email(input, sizeof(data.student_contacts.email));
                            if (flag == -1) {
                                std::cout << "Email too long \n";
                            }
                            else if (flag ==  0) {
                                std::cout << "Invalid email format\n";
                            }

                        } while (flag != 1);
                        strcpy(data.student_contacts.email, input.c_str());

                        break;
                    }


                case 9:
                {
                    std::cin.ignore();
                        do {
                            std::cout << "Enter Phone No (10 digits) : ";
                            std::cin >> input;

                            flag = validations::validate_phone_no(input);
                            if (flag == -1){
                                std::cout << "Must be exactly 10 digits\n";
                            }
                            else if (flag ==  0) {
                                std::cout << "Only digits allowed\n";
                            }

                        } while (flag != 1);
                        strcpy(data.student_contacts.phone_no, input.c_str());

                        break;

                    }


                case 10:
                {
                    std::string house, street, city, state, country, pincode;

                    std::cout<<"Enter the Address Details : \n";
                    std::cin.ignore();
                    do {
                        std::cout << "Enter House : ";
                        std::getline(std::cin, house);
                        flag = validations::validate_address_field(house, sizeof(data.student_address.house));
                        if (flag == -1) {
                            std::cout << "Too long \n";
                        }
                        else if (flag ==  0) {
                            std::cout << "invalid Format \n";
                        }
                    } while (flag != 1);

                    // std::cin.ignore(1000,'\n');
                    do {
                        std::cout << "Enter Street : ";
                        std::getline(std::cin, street);
                        flag = validations::validate_address_field(street, sizeof(data.student_address.street));
                        if (flag == -1) {
                            std::cout << "Too long\n";
                        }
                        else if (flag ==  0) {
                            std::cout << "Invalid Format \n";
                        }
                    } while (flag != 1);

                    // std::cin.ignore(1000,'\n');
                    do {
                        std::cout << "Enter City : ";
                        std::getline(std::cin, city);
                        flag = validations::validate_address_field(city, sizeof(data.student_address.city));
                        if (flag == -1) {
                            std::cout << "Too long \n";
                        }
                        else if (flag ==  0) {
                            std::cout << "Invalid Format  \n";
                        }
                    } while (flag != 1);

                    // std::cin.ignore(1000,'\n');
                    do {
                        std::cout << "Enter State : ";
                        std::getline(std::cin, state);
                        flag = validations::validate_address_field(state, sizeof(data.student_address.state));
                        if (flag == -1) {
                            std::cout << "Too long\n";
                        }
                        else if (flag ==  0) {
                            std::cout << "Invalid format \n";
                        }
                    } while (flag != 1);

                    // std::cin.ignore(1000,'\n');
                    do {
                        std::cout << "Enter Country : ";
                        std::getline(std::cin, country);
                        flag = validations::validate_address_field(country, sizeof(data.student_address.country));
                        if(flag == -1) {
                            std::cout << "Too long\n";
                        }
                        else if (flag ==  0) {
                            std::cout << "Invalid format \n";
                        }
                    } while (flag != 1);

                    // std::cin.ignore();
                    do {
                        std::cout << "Enter Pincode (6 digits) : ";
                        std::cin >> pincode;
                        flag = validations::validate_address_pincode(pincode);
                        if (flag == -1) {
                            std::cout << "Must be exactly 6 digits\n";
                        }
                        else if (flag ==  0) {
                            std::cout << "Only digits are allowed\n";
                        }
                    } while (flag != 1);

                    strcpy(data.student_address.house,   house.c_str());
                    strcpy(data.student_address.street,  street.c_str());
                    strcpy(data.student_address.city,    city.c_str());
                    strcpy(data.student_address.state,   state.c_str());
                    strcpy(data.student_address.country, country.c_str());
                    strcpy(data.student_address.pincode, pincode.c_str());

                    break ; 
                }


                case 11:
                {
                    if (templates::do_template_exist(data.student_course) != -1 || tempused == 1){
                        std::cout << "Cant change Subjects as it is a template \n";
                        break;
                    }
                    do {
                        std::cout << "Enter Number of Subjects (1-10) : ";
                        std::cin >> num;
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                std::cout << "Enter a Number ! \n";
                                continue;
                            }
                        flag = validations::validate_number_of_subjects(num);
                        if (flag != 1) std::cout << "Must be between 1 and 10\n";
                    } while (flag != 1);
                    data.student_number_of_subjects = num;


                    break;


                }

                case 12:
                {
                    if (templates::do_template_exist(data.student_course)){
                        int i = 0;
                        // for (int i = 0; i < data.student_number_of_subjects; i++) {
                        do{
                            std::cout << "Enter Subject " << i + 1 << " Obtained Marks : ";
                            std::cin >> num;
                            if (std::cin.fail()){
                                std::cin.clear();
                                std::cin.ignore(1000,'\n');
                                std::cout<<"Enter A Number ! \n";
                                continue;
                            }
                            data.student_subjects[i].setsubobtainedmarks(num);
                            i++;

                        }while(i<data.student_number_of_subjects);
                        break;

                    }

                    if (data.student_number_of_subjects == 0){ break;}
                    for (int i = 0; i < data.student_number_of_subjects; i++) {
                        std::cout << "Enter Subject " << i + 1 << " details\n";
                        data.student_subjects[i] = templates::enter_and_return_sub();
                    }
                    
                    break;
                }
                
                case 0:
                {
                    std::cout << "Saved \n";
                    recorddata::connect(data);
                    exit = 1;
                    break;
                }
                
                case 13: //show
                {
                    recorddata::show::single_by_rollno(data,0);
                    recorddata::show::single_by_rollno(data,1);   
                    break;
                }
                
                case 14:
                {
                    std::cout << "Data not Saved\n";
                    exit = 1;
                    break;
                }

                default :
                {
                    std::cout << "Not a Valid Option \n";
                    break;
                }

            } // switch 

            } while (!exit); // do while

        } // esle if 




    } // open()

        } // objectt namespace
    
    } // interface namesapce 


    