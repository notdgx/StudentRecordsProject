#include "../headers/templates.hpp"


namespace templates{


    Subject enter_and_return_sub();
    ofstream file_exists_check(const std::string & file_name , int number_of_subjects );
    int do_template_exist(const std::string & template_name);
    void add_template_index(const std::string & template_name , int number_of_subjects);
    void replace_template_index(const std::string & template_name , int number_of_subjects , int index);
    void delete_template_index(int index);
    templateindex give_template_data_at_index(int index);
    int give_number_of_subjects(const std::string & template_name);

    // CREATE TEMPLATE 

int create_template(const std::string & template_name , int number_of_subjects = 10){
        ofstream file = file_exists_check(template_name ,number_of_subjects);
        if (file.is_open()){
            for (int i = 0 ; i < number_of_subjects ; i++){
                std::cout << "\n────────────────────────────\n" ;
            std::cout << "Enter the Subject " << i+1 << " Details : \n" ;
            std::cout << "────────────────────────────\n" ;
            Subject sub = templates::enter_and_return_sub();
            cin.ignore(1000,'\n');
            file.write(reinterpret_cast<char*>(& sub),sizeof(sub));
            std::cout << "\n────────────────────────────\n\n" ;
            
        }
        return 1;
        }
        else {
            return -1;
        }
    }

// overloading 1 
    int modify_template(const std::string & template_name){
        char replace;
        int index,n;
        index = templates::do_template_exist(template_name);
        string path = "templates/" + template_name + ".template";
        ifstream file(path,ios::in | ios::binary);
        if (!file.is_open() || index == -1){
            return 0;
        } 
        file.close();
        ofstream file1(path,ios::out | ios::binary);
        templates::templateindex data = templates::give_template_data_at_index(index);
        n = data.template_N_in_index;
            
        for (int i = 0 ; i < n ; i++){
            std::cout << "\n────────────────────────────\n" ;
            std::cout << "Enter the Subject " << i+1 << " Details : \n" ;
            std::cout << "────────────────────────────\n" ;
            std::cin.ignore(1000,'\n');
            Subject sub = templates::enter_and_return_sub();
            file1.write(reinterpret_cast<char*>(& sub),sizeof(sub));
            std::cout << "\n────────────────────────────\n\n" ;
        }
            return 1;
    }
    // overloading 2
    int modify_template(const std::string & template_name, int n){
        char replace;
        int index;
        index = templates::do_template_exist(template_name);
        string path = "templates/" + template_name + ".template";
        ifstream file(path,ios::in | ios::binary);
        if (!file.is_open() || index == -1){
            return 0;
        } 
        file.close();
        ofstream file1(path,ios::out | ios::binary);
        templates::templateindex data ;
        std::strcpy(data.template_name_in_index,template_name.c_str());
        data.template_N_in_index = n;
            
        for (int i = 0 ; i < n ; i++){
            std::cout << "\n────────────────────────────\n" ;
            std::cout << "Enter the Subject " << i+1 << " Details : \n" ;
            std::cout << "────────────────────────────\n" ;
            std::cin.ignore(1000,'\n');
            Subject sub = templates::enter_and_return_sub();
            file1.write(reinterpret_cast<char*>(& sub),sizeof(sub));
            std::cout << "\n────────────────────────────\n\n" ;
        }
        file1.close();
        templates::replace_template_index(template_name,n,index);
        return 1;
    }


    // DELETEING TEMPLATE 

    void delete_template(const std::string & template_name){
        string path = "templates/" + template_name + ".template";
        ifstream file(path);
        char choice;
        if (file.is_open()){
            cout << "   -> Are you Sure You want to delete this template ? (y/n) :";
            cin >> choice ;
            if (choice == 'y' || choice == 'Y'){
                filesystem::remove(path);
                templates::delete_template_index(do_template_exist(template_name));
                cout << "      -> Template Deleted ‖ \n";
            }
            else{
                cout << "      -> Template Not Deleted\n";
            }
        }
        
    }

    ofstream file_exists_check(const std::string & file_name, int number_of_subjects = -1)
    // adding in index will active when no of subjects pssed
    {
        char replace;
        string path = "templates/" + file_name + ".template";
        // char replaceT;
        string template_name;
        ofstream file1;
        ifstream file(path);

        if (!file.is_open()){
            file1.open(path, ios::binary | ios::out | ios::trunc);
            if (number_of_subjects != -1){
                add_template_index(file_name , number_of_subjects);
            }
            return file1;
        }

        else if(file.is_open())
        {
            cout << "   -> Template Exists Do You want to replace it ? (y/n) :";
            cin >> replace ;

            if (replace == 'Y' || replace == 'y' ){
                file1.open(path, ios::binary | ios::out | ios::trunc);

                // if (number_of_subjects != -1){
                //     cout << "Do you want to change template name ? (Y/n):";
                //     cin >> replaceT ;
                //         if (replaceT == 'Y' || replaceT == 'y' ){
                //             cout << "Enter new name of Template : ";
                //             // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // .
                //             cin >> template_name;
                //             replace_template_index(template_name , number_of_subjects , do_template_exist(file_name));}
                //         // else {
                //         //     replace_template_index(file_name , number_of_subjects , do_template_exist(file_name));}
                //         }
                //     // file index will always exists if we are replacing a file
                
                return file1;
            }
            else {
                return file1;
            }
        }

        return file1;
    }

    // Return Tempalte for use

    Subject * return_template_data(const std::string & template_name){
        string path = "templates/" + template_name + ".template";
        fstream file(path , ios::binary | ios::in);
        templateindex indexdata;
        int exist = do_template_exist(template_name);
        if ( exist != -1 && file.is_open()){
            indexdata=give_template_data_at_index(exist);
            Subject * subjects_data = new Subject[indexdata.template_N_in_index];
            file.read(reinterpret_cast<char*>(subjects_data), sizeof(Subject) * indexdata.template_N_in_index);
            file.close();
            return subjects_data;

            // i was first trying to get the returned data pointer and put it in place of pointer 
            // to the poijnter of the array 

            // sizeof(subjects_data) will give the size of a pointer not the class size
        }

        else if (exist == -1 || !file.is_open()){
            return nullptr;
        }

        return nullptr;

    }


    /// SHOW TEMPLATE 
    int show_template(const std::string & template_name){
        Subject * data = return_template_data(template_name);
        if (data == nullptr){
            return 0;
        }
        cout << "┌─────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << "│ Template Name : " << std::left << std::setw(65) << template_name << "   │" << endl;
        cout << "├──────────────────────┬──────────┬────────────────┬────────────────┬─────────────────┤" << endl;
        cout << "│ Name                 │ Code     │ Total Marks    │ Obt. Marks     │ Credits         │" << endl;
        cout << "├──────────────────────┼──────────┼────────────────┼────────────────┼─────────────────┤" << endl;
        
        for ( int i = 0 ; i < templates::give_number_of_subjects(template_name) ; i++){
            cout << "│ " << std::left << setw(20) << data[i].getsubname() << " │ " << setw(8) << data[i].getsubcode() 
            << " │ " << setw(14) << data[i].getsubtotalmarks() << " │ " << setw(14) << data[i].getsubobtainedmarks() 
            << " │ " << setw(14) << data[i].getsubcredits() << "  │" << endl;
        }
            cout << "└──────────────────────┴──────────┴────────────────┴────────────────┴─────────────────┘" << endl;
            delete[] data;
            return 1;
    }


    Subject enter_and_return_sub(){

        Subject sub;

        std::string Esub_name;
        int Esub_code;
        int Esub_totalmarks;
        int Esub_obtainedmarks;
        int Esub_credits;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // .
    do {
        cout << "   -> Enter the Subject Name: ";
        getline(cin, Esub_name);

        if (!Subject::verifyname(Esub_name)) {
            cout << "      -> Subject Name Too Long , try again"<< endl;
        } else {
            break;
        }
    
    } while (true);

        sub.setsubname(Esub_name);

        do{
        std::cout << "   -> Enter the Subject Code : " ;
        std::cin >> Esub_code ;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "       -> Enter a Number ! \n";
                continue;
            }
        sub.setsubcode(Esub_code);
        break;
        }while(true);

        do{
        std::cout << "   -> Enter the Subject Total Marks : " ;
        std::cin >> Esub_totalmarks ;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "     -> Enter a Number ! \n";
                continue;
            }

        sub.setsubtotalmarks(Esub_totalmarks);
        break;
        }while(true);

        do{
        std::cout << "   -> Enter the Subject Obtained Marks : " ;
        std::cin >> Esub_obtainedmarks ;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "     -> Enter a Number ! \n";
                continue;
            }

        sub.setsubobtainedmarks(Esub_obtainedmarks);
        break;
        }while(true);

        do{
        std::cout << "   -> Enter the Subject Credits : " ;
        std::cin >> Esub_credits ;
            if (cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                std::cout << "     -> Enter a Number ! \n";
                continue;
            }
        sub.setsubcredits(Esub_credits);
        break;
        }while(true);

        // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // .

        return sub;
    }

    // TEMPLSTE INDEX

    // TEMPLATE INDEX SHOW 

    int show_template_index(){
        int size ;
        templates::templateindex data;
        ifstream file("templates/00_templateindex", ios::binary);
        if (!file.is_open()){
            return 0;
        }
        file.seekg(0,ios::end);
        size = file.tellg();
        file.seekg(0,ios::beg);
        if (size == 0){
            return 0;
        }
        cout << "┌──────────────────────┬────────────────┐" << endl;
        cout << "│ Template Name        │ No of Subjects │" << endl;
        cout << "├──────────────────────┼────────────────┤" << endl;
        while(file.read(reinterpret_cast<char *>(& data), sizeof(data))){
            
            if (data.template_name_in_index[0] == '\0' && data.template_N_in_index == 0){
                continue;
            }
            
            else {
                cout << "│ " << std::left << std::setw(20) << data.template_name_in_index
                << " │ " << std::right << std::setw(14) << data.template_N_in_index << " │" << endl;
            }
            
        }
        
        cout << "└──────────────────────┴────────────────┘" << endl;
        return 1;
    }

    
    // TEMPLATE INDEX MODIFING 

    void add_template_index(const std::string & template_name , int number_of_subjects){

        templates::templateindex data;
        strcpy(data.template_name_in_index,template_name.c_str());
        data.template_N_in_index = number_of_subjects;

        ofstream file("templates/00_templateindex" , ios::binary | ios::app );
        if (do_template_exist(template_name) == -1){
            file.write(reinterpret_cast<char *>(&data),sizeof(data));
        }
        file.close();

    }

    int do_template_exist(const std::string & template_name){

        ifstream file("templates/00_templateindex", ios::binary);
        templates::templateindex T ;
        int index=0;

        while(file.read(reinterpret_cast<char*>(&T), sizeof(T))){

            if (std::string(T.template_name_in_index) == template_name){
                return (int)file.tellg() - 24;
            }
        }

        return -1;
    }


    void replace_template_index(const std::string & template_name , int number_of_subjects , int index){

        templates::templateindex data;
        strcpy(data.template_name_in_index , template_name.c_str());
        data.template_N_in_index = number_of_subjects;

        fstream file("templates/00_templateindex" , ios::binary | ios::in | ios::out );
        file.seekp(index , ios::beg);
        file.write(reinterpret_cast<char *>(&data), sizeof(data));
        file.close();

    }

    void delete_template_index(int index){

        templates::templateindex delete_index{};

        fstream file("templates/00_templateindex" , ios::binary | ios::in | ios::out );
        if (index == -1){
            return;
        }
        file.seekp(index , ios::beg);
        file.write(reinterpret_cast<char *>(&delete_index) , sizeof(delete_index));


    }

    templateindex give_template_data_at_index(int index){
        ifstream file("templates/00_templateindex" , ios::binary);
        templateindex data;
        file.seekg(index , ios::beg);
        file.read(reinterpret_cast<char *>(&data), sizeof(data));
        return data;
    }

    int give_number_of_subjects(const std::string & template_name){
        return give_template_data_at_index(do_template_exist(template_name)).template_N_in_index;
    }

};

// int main(){
// // //     templates::create_template("BCA2ndSem" ,5);
// // //     // templates::add_template_index("fdd",34);
// // //     templates::add_template_index("HHhfdd",834);
// // //     templates::add_template_index("AAAfdd",345);
// // //     templates::add_template_index("AAAfdd",345);
// // //     templates::show_template_index();
// // //     templates::replace_template_index("OOO", 89, 48);
// // //     templates::show_template_index();
// // //     // templates::delete_template_index(24);
// //     templates::show_template_index();
// // //     // cout<<templates::do_template_exist("HHhfdd");
// // //     // Subject * str = templates::return_template_data("fdddf");  
// // //     // for (int i = 0 ; i< templates::give_number_of_subjects("fdddf"); i++ ) {
// // //     //     cout<<str[i].getsubcode()<<endl;
// // //     //     cout<<str[i].getsubcredits()<<endl;
// // //     //     cout<<str[i].getsubname()<<endl;
// // //     //     cout<<str[i].getsubobtainedmarks()<<endl;
// // //     //     cout<<str[i].getsubtotalmarks()<<endl;
// // //     // }  // templates::delete_template("fdddf");

// // templates::create_template("aaa",2);
// //     templates::show_template("aaa");
// // templates::create_template("paa",2);
// //     templates::show_template("paa");

// // //     templates::delete_template("fdd" );
    
// }

