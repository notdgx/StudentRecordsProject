#include <iostream>
#include <fstream>
#include <string>
#include "./subjects.cpp"

namespace templates{

    void create_template(const std::string & template_name , int number_of_subjects = 10){

        Subject subs[number_of_subjects];
        for (int i = 0 ; i < number_of_subjects ; i++){
            std::cout << "Enter the Subject " << i << " Details : \n" ;
            std::cout << "-----------------------------\n\n" ;
            
            std::cout << "-----------------------------\n\n" ;
        }

    }


    Subject enter_and_return(){

        Subject sub;

        std::string Esub_name;
        int Esub_code;
        int Esub_totalmarks;
        int Esub_obtainedmarks;
        int Esub_credits;

    do {
        cout << "Enter the Subject Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // .
        getline(cin, Esub_name);

        if (!Subject::verifyname(Esub_name)) {
            cout << "Subject Name Too Long , try again"<< endl;
        } else {
            break;
        }
    
    } while (true);

    sub.setsubname(Esub_name);

        std::cout << "Enter the Subject Code : " ;
        std::cin >> Esub_code ;
        sub.setsubcode(Esub_code);

        std::cout << "Enter the Subject Total Marks : " ;
        std::cin >> Esub_totalmarks ;
        sub.setsubtotalmarks(Esub_totalmarks);

        std::cout << "Enter the Subject Obtained Marks : " ;
        std::cin >> Esub_obtainedmarks ;
        sub.setsubobtainedmarks(Esub_obtainedmarks);

        std::cout << "Enter the Subject Credits : " ;
        std::cin >> Esub_credits ;
        sub.setsubcredits(Esub_credits);

        return sub;
    }


}