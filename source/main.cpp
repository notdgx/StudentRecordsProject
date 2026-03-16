#include <iostream>
#include <string>
#include "../headers/interface.hpp"
#include "../headers/subjects.hpp"
#include "../headers/students.hpp"
#include "../headers/additionalfucntions.hpp"
#include "../headers/templates.hpp"
#include "../headers/fields.hpp"
#include "../headers/validations.hpp"


int main(){

    // globla variables or inits 
    
    student_id_A = 1;
    rollno_assigner_initial = 1000;
    recorddata::rollno_assigner = 1000;

    // Variables

    int choice , exit = 0;


    std::cout << "Welcome to the Student Record Management System \n";
    std::cout << "Total Records : " << recorddata::record::get_length() << endl;
    
    do {
        std::cout << "What you Want to do ? \n";
        std::cout << "+-------------------------------------------------------------+\n";
        std::cout << "1     ->     Show Recent Records \n";
        std::cout << "2     ->     Show All Records \n";
        std::cout << "3     ->     Show All Records Subject Details \n";
        std::cout << "4     ->     Show Records by Roll No \n";
        std::cout << "5     ->     Show Records Subject Details by Roll No \n";
        std::cout << "6     ->     Show Status \n";
        std::cout << "7     ->     Show Templates \n";
        std::cout << "8     ->     Show Template Data\n";
        std::cout << "9     ->     Add Templaate \n";
        std::cout << "10    ->     Delete Templaate \n";
        std::cout << "11    ->     Modify Templaate \n";
        std::cout << "12    ->     Delete Record \n";
        std::cout << "13    ->     Export All Records \n";
        std::cout << "14    ->     Export Records by Course\n";
        std::cout << "15    ->     Add Record \n";
        std::cout << "16    ->     Open Record \n";
        std::cout << "0     ->     Exit \n";
        std::cout << "+-------------------------------------------------------------+\n";
        
        std::cout << "Enter Here \n";
        std::cin>> choice;

        switch (choice) {
            case 1:  interface::general::show_recent();           break;
            case 2:  interface::general::show_all_stu();          break;
            case 3:  interface::general::show_all_sub();          break;
            case 4:  interface::general::show_std_by_rollno();    break;
            case 5:  interface::general::show_sub_by_rollno();    break;
            case 6:  interface::general::show_session();          break;
            case 7:  interface::general::show_template_index();   break;
            case 8:  interface::general::show_template_by_name(); break;
            case 9:  interface::general::add_template();          break;
            case 10: interface::general::delete_template();       break;
            case 11: interface::general::modify_template();       break;
            case 12: interface::general::delete_record();         break;
            case 13: interface::general::export_csv();            break;
            case 14: interface::general::export_csv_by_course();  break;
            case 15: interface::object::add();                    break;
            case 16: interface::object::open();                   break;
            case 0:  std::cout << "Exiting   \n";  exit = 1;               break;         
            default: std::cout << "Invalid choice\n";            break;
        }


    }while (!exit);

    return 0;
}