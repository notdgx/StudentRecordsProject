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
            state = recorddata::show::single_by_rollno(roll,1);
            if (state == 1){
                break;
            }
            else if (state == 0){
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
        do{
        state = templates::show_template_index();
        if (state == 0){
            std::cout << "Template Index Doesnt Exist \n";
        }
        else if (state == 1){
            break;
        }
        }while(true);
        
    }
    
    
    void show_template_by_name(){
        std::string name;
        int state;
        do{
        std::cout << "Enter the course name :";
        std::cin >> name;
        state = templates::show_template(name);
        if (state == 0){
            std::cout << "Template Doesnt Exist \n";
        }
        else if (state == 1){
            break;
        }
    }while(true);
    }

    void delete_record(){
        int rollno;
        datafields::fields temp;

        do{
        std::cout << "Enter the Roll No :";
        std::cin >> rollno;
        temp = recorddata::fetch::record_by_rollno(rollno);
        if (temp.student_id == 0){
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
        do{
        std::cout << "Enter the Template name :";
        std::cin >> name;
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
        
    }

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
        do{
        std::cout << "Enter the Course name :";
        std::cin >> name;
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
            break;
        }
        }while(true);
    }

    

    }
}