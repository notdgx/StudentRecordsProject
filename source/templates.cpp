#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "./subjects.cpp"

namespace templates{

    Subject enter_and_return_sub();
    ofstream file_exists_check(const std::string & file_name );

    // CREATE TEMPLATE 

    int create_template(const std::string & template_name , int number_of_subjects = 10){


        ofstream file = file_exists_check(template_name);
        if (file.is_open()){

            for (int i = 0 ; i < number_of_subjects ; i++){
            std::cout << "Enter the Subject " << i+1 << " Details : \n" ;
            std::cout << "-----------------------------\n\n" ;
            Subject sub = templates::enter_and_return_sub();
            file.write(reinterpret_cast<char*>(& sub),sizeof(sub));
            std::cout << "-----------------------------\n\n" ;
        
        }
        }
        else {
            return -1;
        }
    }

    ofstream file_exists_check(const std::string & file_name ){
        char replace;
        ofstream file1;
        ifstream file(file_name);

        if (!file.is_open()){
            file1.open(file_name, ios::binary | ios::out | ios::trunc);
            return file1;
        }
        else if(file.is_open())
        {
            cout << "File Exists Do You want to replace it ? (y/n) :";
            cin >> replace ;

            if (replace == 'Y' || replace == 'y' || replace == ' ' || replace == '\n' ){
                file1.open(file_name, ios::binary | ios::out | ios::trunc);
                return file1;
            }
            else {
                return file1;
            }
        }
    }


    Subject enter_and_return_sub(){

        Subject sub;

        std::string Esub_name;
        int Esub_code;
        int Esub_totalmarks;
        int Esub_obtainedmarks;
        int Esub_credits;

    do {
        cout << "Enter the Subject Name: ";
        getline(cin, Esub_name);
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // .

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

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // .

        return sub;
    }

    // TEMPLATE INDEX

    void add_template_index(const std::string & template_name , int number_of_subjects){

        ofstream file("../templates/00_templateindex" , ios::binary | ios::app );



    }

    int do_template_exist(const std::string & template_name){

        ifstream file("../templates/00_templateindex", ios::binary);
        
        struct templateindex{
        char template_name_in_index[20];
        int template_N_in_index;
        } T ;

        int index=0;


        if (!file){
            return -1;
        }

        while(file.read(reinterpret_cast<char*>(&T), sizeof(T))){

            file.read(reinterpret_cast<char*>(&T), sizeof(T));

            if (std::string(T.template_name_in_index) == template_name){
                return (int)file.tellg() - 24;
            }
        }

        return -2;


    }


}

int main(){
    templates::create_template("aaa" ,2);
}