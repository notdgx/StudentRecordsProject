#include <iostream>
#include <string>
// #include "main.cpp"
#include "fields.cpp"
#include <fstream>
#include <iomanip>

int student_id_A = 1;   
int rollno_assigner_initial = 1000;

namespace recorddata{

    std::string session_file_path = "../files/session_data";
    std::string record_file_path = "../files/record";
    int rollno_assigner = 1000;

    namespace session{
        int add_data(const std::string & course);
        int update_data(const std::string & course, int index);
        int get_course_rollno(const std::string & course);
        int do_course_exists(const std::string & course);
        datafields::sub_rollno * get_data();
        int get_length();
        int get_student_id_A();
        int init_rollno_for_new_course();
        void init_session();
    }
    
    namespace record{
        int add_data(datafields::fields & data);
        int update_data(datafields::fields & data);
        int delete_data(datafields::fields & data);
        int do_exists(datafields::fields & data);
        int get_length();
        int check_duplicate(datafields::fields & data);
        int init_record();
    }

    namespace fetch{
        datafields::fields record_by_key(int key, bool flag);
        datafields::fields record_by_rollno(int rollno);
        datafields::fields record_by_id(int student_id);
        datafields::fields * all_record();
        datafields::fields * records_by_course(const std::string & course);
        int no_of_records_by_course(const std::string & course);
        int export_csv_by_course(const std::string & course);
        int export_csv_all();
    }

    namespace show{
        int all_records(int flag);
        int records_by_course(const std::string & course,int flag);
        int single_by_rollno(int rollno,int flag);
        int session_data();
    }

    // INITAILIZER IF FILE DOESNT EXISTs
    
    int init_files(){
        ifstream record_file(record_file_path,ios::in | ios::binary);
        ifstream session_file(session_file_path,ios::in | ios::binary);
        int a;

        if (!session_file.is_open()){
            session::init_session();
            a = record::init_record();
            if (a == 1)
            return 1;

            else 
            return -1;
        }

        if (!record_file.is_open()){
            a = record::init_record();
            if (a == 1)
            return 0;

            else 
            return -1;
        }
        return 2;
    }

    // RECORD DATA FILE

    int connect(datafields::fields & data){ // add or updare automatically

        // Update to session file

        int index = session::do_course_exists(data.student_course);
        if (index == -1){
            session::add_data(std::string(data.student_course));
        }

        else{
            session::update_data(std::string(data.student_course),index);
        }

        // assign the rollno as per course and student id also 
        data.student_id = session::get_student_id_A();
        data.student_rollno =  session::get_course_rollno(data.student_course);

        // update to record file

        fstream recordfile(record_file_path,ios::in | ios::out | ios::binary );
        if (!recordfile.is_open()){
            return -1;
        }

        int recordindex = record::do_exists(data);

        if (recordindex == -1 ){
        record::add_data(data);
        return 1;
        }

        record::update_data(data);
        return 1;

    }

    namespace record{

    int add_data(datafields::fields & data){
        ofstream file(record_file_path , ios::binary | ios::app);
        if (!file.is_open()){
            return -1;
        }
        file.write(reinterpret_cast<char *>(&data),sizeof(data));
        file.close();
        return 1;

    }

    int update_data(datafields::fields & data){
        int index = do_exists(data);
        fstream file(record_file_path,ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }

        file.seekp(index * sizeof(data),ios::beg);
        file.write(reinterpret_cast<char*>(&data),sizeof(data));
        file.close();
        return 1;
    }

    int delete_data(datafields::fields & data){
        int index = do_exists(data);
        if (index == -1){
            return -1;
        }
        fstream file(record_file_path,ios::in | ios::out | ios::binary);
        datafields::fields deleted{};
        if (!file.is_open()){
            return 0;
        }

        file.seekp(index * sizeof(data),ios::beg);
        file.write(reinterpret_cast<char *>(&deleted), sizeof(deleted));
        file.close();
        return 1;
        

    }



    int do_exists(datafields::fields & data){
        ifstream file(record_file_path,ios::in | ios::binary);
        if (!file.is_open()){
            return -2;
        }
        int student_id, i,size;
        file.seekg(0,ios::end);
        size = file.tellg();
        if (size == 0 ){
            return -1;
        }
        int length = get_length();
        for (i = 0; i < length ; i++){
            file.seekg(i * sizeof(data), ios::beg);
            file.read(reinterpret_cast<char*>(&student_id),sizeof(student_id));
            if (student_id == data.student_id){
                return i;
            }
        }
        return -1;
    }

    int get_length(){
        ifstream file(record_file_path,ios::in | ios::binary);
        int length,size;
        if (!file.is_open()) 
        return 0;
        file.seekg(0,ios::end);
        size = file.tellg();
        file.close();
        if (size <= 0){ 
            return 0;
        }
        length = size / sizeof(datafields::fields);
        return length;
    }


    int init_record(){
        ofstream file(recorddata::record_file_path,ios::out|ios::binary);
        if (!file.is_open()){
            return 1;
        }
        return 0;
    }

    int check_duplicate(datafields::fields & data){
        int count = 0 , size;
        ifstream file(record_file_path,ios::in | ios::binary);
        if (!file.is_open()){
            return -2;
        }
        file.seekg(0,ios::end);
        size = file.tellg();
        if (size == 0 ){
            return -1;
        }

        datafields::fields temp;
        while (file.read(reinterpret_cast<char *>(&temp),sizeof(temp))){

            if (temp.student_id == 0){continue;}

            count = 0;
            
            if (std::string(temp.student_name) == std::string(data.student_name)) {count++;}
            if (std::string(temp.student_contacts.email) == std::string(data.student_contacts.email)) {count++;}
            if (std::string(temp.student_contacts.phone_no) == std::string(data.student_contacts.phone_no)) {count++;}
            if ((temp.student_dob.day == data.student_dob.day) && (temp.student_dob.month == data.student_dob.month) && (temp.student_dob.year == data.student_dob.year)) {count++;}
            
            if (count>=4){
                return 1;
            }
        }
        return -1;
    }
}

    /// GET RECORD DATA


    namespace fetch{


    datafields::fields record_by_key(int key, bool flag = true){
        if (flag){
            return fetch::record_by_id(key);
        }
        else {
            return fetch::record_by_rollno(key);
        }
    }
    
    datafields::fields record_by_rollno(int rollno){
        datafields::fields data{};
        ifstream file(record_file_path , ios::binary);
        if (!file.is_open()){
            return data;
        }
        while (file.read(reinterpret_cast<char*>(&data), sizeof(data))){
            if (data.student_rollno == rollno){
                return data;
            }
        }
        return data;
    }

    datafields::fields record_by_id(int student_id){
        ifstream file(record_file_path ,ios::in | ios::binary);
        datafields::fields data{};
        if (!file.is_open()){
            return data;
        }
        while (file.read(reinterpret_cast<char*>(&data),sizeof(data)))
        {
            if (data.student_id == student_id){
                return data;
            }
        }
        return data;
    }

    // GET ALL RECORD DATA 

    
    datafields::fields * all_record(){
        int length = record::get_length();
        if (length == 0){
            return nullptr;
        }
        datafields::fields * data = new datafields::fields[length];
        ifstream file(record_file_path,ios::in | ios::binary);
        if (!file.is_open()){
            delete[] data;
            return nullptr;
        }

        file.read(reinterpret_cast<char *>(data),length * sizeof(datafields::fields)); //not data because data is a ptr
        return data;
    }

    // GET RECORD DATA BY COUERSE

    datafields::fields * records_by_course(const std::string & course){
        int flag1 = session::do_course_exists(course);
        int count = fetch::no_of_records_by_course(course);
        if (flag1 == -1 || count == 0){
            return nullptr;
        }
        // int * index_array = get_array_of_index(course);

        datafields::fields* data = new datafields::fields[count];
        datafields::fields temp;
        int index = 0;

        ifstream file(record_file_path , ios::in | ios::binary);
        if (!file.is_open()){
            delete[] data;
            return nullptr;
            }
        
        while (file.read(reinterpret_cast<char *>(&temp),sizeof(temp)))
        {
            if (std::string(temp.student_course) == course){
                data[index] = temp;
                index ++;
            }
        }
        
        return data;

    }

    /*int * get_array_of_index(const std::string & course){
        int count = get_no_of_records_by_course(course);
        int * array = new int[count];
        int length = get_record_length();
        int index = 0;
        datafields::fields temp;
        ifstream file(record_file_path , ios::in | ios::binary);
        for (int i = 0 ; i < length ; i++ ){
            file.read(reinterpret_cast<char *>(&temp),sizeof(temp));
            if (temp.student_course == course){
                array[index] = i;
                index++;
            }
        }
        return array;
    }*/


    int no_of_records_by_course(const std::string & course){
        int count=0;
        datafields::fields temp;
        ifstream file(record_file_path , ios::in | ios::binary);
        while (file.read(reinterpret_cast<char *>(&temp),sizeof(temp)))
        {
            if (std::string(temp.student_course) == course){
                count++;
            }
        }
        return count;
    }


    int export_csv_by_course(const std::string & course){
        std::string studentpath =  "../export/" + course + "_students.csv";
        std::string subjectpath =  "../export/" + course + "_subjects.csv";
        std::string studentscolumn ,subjectscolumn ;
        datafields::fields * data = records_by_course(course);
        if (data == nullptr){
            return -1;
        } 
        
        int count = no_of_records_by_course(course);
        
        fstream studentexportfile(studentpath , ios::out );
        fstream subjectexportfile(subjectpath , ios::out );
        if (!studentexportfile.is_open()|| !subjectexportfile.is_open()){
            return 0;
        }

        studentscolumn = "Student ID,Rollno,Name,DOB,Gender,Course,Section,No of Sub,Enrollement Year,Pending Fee,Email,Phone No,Address\n";
        studentexportfile << studentscolumn;

        subjectscolumn = "Student ID,Roll No,Name,Code,Total Marks,Obtained Marks,Credits\n";
        subjectexportfile << subjectscolumn;

        for (int i = 0 ; i < count ; i++){

            if (data[i].student_id == 0) { continue; }
            studentscolumn = std::to_string(data[i].student_id) + ',' + std::to_string(data[i].student_rollno)  
                    + ',' + data[i].student_name + ',' + std::to_string(data[i].student_dob.day) + '-' + std::to_string(data[i].student_dob.month) + '-' + std::to_string(data[i].student_dob.year) 
                    + ',' + data[i].student_gender + ',' + data[i].student_course + ',' + data[i].student_section + ',' + std::to_string(data[i].student_number_of_subjects) + ',' + std::to_string(data[i].student_enrollement_year) 
                    + ',' + std::to_string(data[i].student_pending_fee) + ',' + data[i].student_contacts.email + ',' + data[i].student_contacts.phone_no
                    + ',' + '\"' + data[i].student_address.house + ',' + data[i].student_address.street + ',' +  data[i].student_address.city + ',' +  data[i].student_address.state + ',' 
                    +  data[i].student_address.country + ',' +  data[i].student_address.pincode  + "\"\n";

            studentexportfile << studentscolumn ;

            for (int j = 0 ; j < data[i].student_number_of_subjects ; j++){
                subjectscolumn = std::to_string(data[i].student_id) + ',' + std::to_string(data[i].student_rollno) + ',' + data[i].student_subjects[j].getsubname() + ',' + std::to_string(data[i].student_subjects[j].getsubcode()) + ',' 
                + std::to_string(data[i].student_subjects[j].getsubtotalmarks()) + ',' + std::to_string(data[i].student_subjects[j].getsubobtainedmarks()) + ',' 
                + std::to_string(data[i].student_subjects[j].getsubcredits()) + "\n" ;  

                subjectexportfile << subjectscolumn; 
            }
            // subjectexportfile << '\n'; 

        }
        studentexportfile.close();
        subjectexportfile.close();
        return 1;
    }


    int export_csv_all(){
        std::string studentscolumn ,subjectscolumn ;
        datafields::fields * data = all_record();
        if (data == nullptr){
            return -1;
        } 
        
        int count = record::get_length();
        
        fstream studentexportfile("../export/all_students.csv", ios::out );
        fstream subjectexportfile("../export/all_subjects.csv", ios::out );
        if (!studentexportfile.is_open()|| !subjectexportfile.is_open()){
            return 0;
        }

        studentscolumn = "Student ID,Rollno,Name,DOB,Gender,Course,Section,No of Sub,Enrollement Year,Pending Fee,Email,Phone No,Address\n";
        studentexportfile << studentscolumn;

        subjectscolumn = "Student ID,Roll No,Name,Code,Total Marks,Obtained Marks,Credits\n";
        subjectexportfile << subjectscolumn;

        for (int i = 0 ; i < count ; i++){

            if (data[i].student_id == 0) { continue; }
            studentscolumn = std::to_string(data[i].student_id) + ',' + std::to_string(data[i].student_rollno)  
                    + ',' + data[i].student_name + ',' + std::to_string(data[i].student_dob.day) + '-' + std::to_string(data[i].student_dob.month) + '-' + std::to_string(data[i].student_dob.year) 
                    + ',' + data[i].student_gender + ',' + data[i].student_course + ',' + data[i].student_section + ',' + std::to_string(data[i].student_number_of_subjects) + ',' + std::to_string(data[i].student_enrollement_year) 
                    + ',' + std::to_string(data[i].student_pending_fee) + ',' + data[i].student_contacts.email + ',' + data[i].student_contacts.phone_no
                    + ',' + '\"' + data[i].student_address.house + ',' + data[i].student_address.street + ',' +  data[i].student_address.city + ',' +  data[i].student_address.state + ',' 
                    +  data[i].student_address.country + ',' +  data[i].student_address.pincode  + "\"\n";

            studentexportfile << studentscolumn ;

            for (int j = 0 ; j < data[i].student_number_of_subjects ; j++){
                subjectscolumn = std::to_string(data[i].student_id) + ',' + std::to_string(data[i].student_rollno) + ',' + data[i].student_subjects[j].getsubname() + ',' + std::to_string(data[i].student_subjects[j].getsubcode()) + ',' 
                + std::to_string(data[i].student_subjects[j].getsubtotalmarks()) + ',' + std::to_string(data[i].student_subjects[j].getsubobtainedmarks()) + ',' 
                + std::to_string(data[i].student_subjects[j].getsubcredits()) + "\n" ;  

                subjectexportfile << subjectscolumn; 
            }
            // subjectexportfile << '\n'; 

        }
        studentexportfile.close();
        subjectexportfile.close();
        return 1;
    }
}


    // ___________________________________________________________________

    // FOR SESSION DATA FILE

    namespace session{

    int add_data(const std::string & course ){
        fstream file(session_file_path , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }

        datafields::sub_rollno sessiondata{};
        strcpy(sessiondata.student_course,course.c_str());
        sessiondata.student_rollno_A = init_rollno_for_new_course();


            file.seekg(0,ios::end);
            file.write(reinterpret_cast<char *>(& sessiondata),sizeof(sessiondata));
            file.close();
            return 1;

        return -1;

    }

    int update_data(const std::string & course, int index){
        // int rollno = get_course_rollno(course);
        fstream file(session_file_path , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }
        datafields::sub_rollno data;
        file.seekg(8 + (index * sizeof(data)), ios::beg);
        file.read(reinterpret_cast<char *>(&data), sizeof(data));

        data.student_rollno_A++;

        file.seekp(8 + (index * sizeof(data)), ios::beg);
        file.write(reinterpret_cast<char *>(&data), sizeof(data));
    
        file.close();
        return 1;
    }



    int get_course_rollno(const std::string & course){

        int index = do_course_exists(course);
        if (index == -1){
            return -1;
        }
        ifstream file(session_file_path , ios::in | ios::binary);
        datafields::sub_rollno data{};
        file.seekg((8+(index*sizeof(data))),ios::beg);
        file.read(reinterpret_cast<char *>(& data),sizeof(data));
        return data.student_rollno_A;

    }

    int do_course_exists(const std::string & course){
        ifstream file(session_file_path , ios::in | ios::binary);
        datafields::sub_rollno data{};
        int length = get_length();
        file.seekg(8,ios::beg);

        for (int i = 0 ; i < length ; i++){
            file.read(reinterpret_cast<char *>(& data),sizeof(data));
            if (std::string(data.student_course) == course){
                return i;
            }
        }

        return -1;
    }


    // get struct array of regestered course in session

    datafields::sub_rollno * get_data(){

        ifstream file(session_file_path , ios::in | ios::binary);
        int length = get_length();
        
        if (length == 0){
            return nullptr;
        }

        file.seekg(8,ios::beg);
        datafields::sub_rollno * data = new datafields::sub_rollno[length];
        file.read(reinterpret_cast<char *> (data), length * sizeof(datafields::sub_rollno) );
        return data;

    }

    // get how many course are registered in session

    int get_length(){

        ifstream file(session_file_path , ios::in | ios::binary | ios::ate);
        int size,length;
        // file.seekg(0,ios::end);
        if(!file.is_open()){
            return 0;
        }
        size = file.tellg();
        file.close();
        
        if (size == 8){
            return 0;
        }
        
        length = (size-8) / sizeof(datafields::sub_rollno);
        return length;
    }

    // student id

    int get_student_id_A(){
        fstream file(session_file_path , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }
        int student_id_A,new_id;
        file.read(reinterpret_cast<char*>(&student_id_A),sizeof(student_id_A));
        new_id = student_id_A + 1;
        file.seekp(0,ios::beg);
        file.write(reinterpret_cast<char *>(&new_id),sizeof(new_id));
        file.close();
        return student_id_A;
    }




    // student roll no initizer

    int init_rollno_for_new_course(){
        int init_roll,new_init_roll;
        fstream file(session_file_path , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }

        file.seekg(4,ios::beg);
        file.read(reinterpret_cast<char *>(&init_roll),sizeof(init_roll));
        new_init_roll=init_roll+recorddata::rollno_assigner;
        file.seekp(4,ios::beg);
        file.write(reinterpret_cast<char *>(&new_init_roll),sizeof(new_init_roll));
        file.close();
        return init_roll;

    }

    void init_session(){
        ofstream file(recorddata::session_file_path, ios::out | ios::binary);
        file.write(reinterpret_cast<char*>(&student_id_A), sizeof(int));
        file.write(reinterpret_cast<char*>(&rollno_assigner_initial), sizeof(int));
        file.close();
}

}
namespace show{

    int single_by_rollno(int rollno,int flag = 0){
        datafields::fields data = fetch::record_by_rollno(rollno);
        if (data.student_id == 0){
            cout << "Record Doesnt Exist \n";
            return 0;
        }

        if(flag == 0){
            std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";
            std::cout << "| "
            << std::left << std::setw(4)  << "ID"      << " | "
            << std::left << std::setw(8)  << "Roll"    << " | "
            << std::left << std::setw(22) << "Name"    << " | "
            << std::left << std::setw(12) << "DOB"     << " | "
            << std::left << std::setw(2)  << "G"       << " | "
            << std::left << std::setw(8)  << "Course"  << " | "
            << std::left << std::setw(3)  << "Sec"     << " | "
            << std::left << std::setw(5)  << "Subj"    << " | "
            << std::left << std::setw(4)  << "Year"    << " | "
            << std::left << std::setw(10) << "Fee"     << " | "
            << std::left << std::setw(24) << "Email"   << " | "
            << std::left << std::setw(11) << "Phone"   << " | "
            << std::left << std::setw(16) << "City"
            << " |\n";
            std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";std::string dob = std::to_string(data.student_dob.day)   + "-"
            + std::to_string(data.student_dob.month) + "-"
            + std::to_string(data.student_dob.year);
            std::cout << "| "
            << std::left << std::setw(4)  << data.student_id                      << " | "
            << std::left << std::setw(8)  << data.student_rollno                  << " | "
            << std::left << std::setw(22) << data.student_name                    << " | "
            << std::left << std::setw(12) << dob                                     << " | "
            << std::left << std::setw(2)  << data.student_gender                  << " | "
            << std::left << std::setw(8)  << data.student_course                  << " | "
            << std::left << std::setw(3)  << data.student_section                 << " | "
            << std::left << std::setw(5)  << data.student_number_of_subjects      << " | "
            << std::left << std::setw(4)  << data.student_enrollement_year        << " | "
            << std::left << std::setw(10) << data.student_pending_fee             << " | "
            << std::left << std::setw(24) << data.student_contacts.email          << " | "
            << std::left << std::setw(11) << data.student_contacts.phone_no       << " | "
            << std::left << std::setw(16) << data.student_address.city
            << " |\n";
            std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";
            return 1;
        }

        if (flag == 1){
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        std::cout << "| "
        << std::left << std::setw(4)  << "ID"       << " | "
        << std::left << std::setw(8)  << "Roll"     << " | "
        << std::left << std::setw(22) << "Subject"  << " | "
        << std::left << std::setw(8)  << "Code"     << " | "
        << std::left << std::setw(10) << "Total"    << " | "
        << std::left << std::setw(12) << "Obtained" << " | "
        << std::left << std::setw(7)  << "Credits"
        << " |\n";
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        for (int j = 0; j < data.student_number_of_subjects; j++){
            std::cout << "| "
            << std::left << std::setw(4)  << data.student_id                                << " | "
            << std::left << std::setw(8)  << data.student_rollno                            << " | "
            << std::left << std::setw(22) << data.student_subjects[j].getsubname()          << " | "
            << std::left << std::setw(8)  << data.student_subjects[j].getsubcode()          << " | "
            << std::left << std::setw(10) << data.student_subjects[j].getsubtotalmarks()    << " | "
            << std::left << std::setw(12) << data.student_subjects[j].getsubobtainedmarks() << " | "
            << std::left << std::setw(7)  << data.student_subjects[j].getsubcredits()
            << " |\n";
            std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        }
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        return 1;
        }
    }


    int all_records(int flag = 0){
        datafields::fields * data = recorddata::fetch::all_record();
        int length = recorddata::record::get_length(); 

        if (data == nullptr){
            return 0;
        }

        if (flag == 0){
            std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";
            std::cout << "| "
            << std::left << std::setw(4)  << "ID"      << " | "
            << std::left << std::setw(8)  << "Roll"    << " | "
            << std::left << std::setw(22) << "Name"    << " | "
            << std::left << std::setw(12) << "DOB"     << " | "
            << std::left << std::setw(2)  << "G"       << " | "
            << std::left << std::setw(8)  << "Course"  << " | "
            << std::left << std::setw(3)  << "Sec"     << " | "
            << std::left << std::setw(5)  << "Subj"    << " | "
            << std::left << std::setw(4)  << "Year"    << " | "
            << std::left << std::setw(10) << "Fee"     << " | "
            << std::left << std::setw(24) << "Email"   << " | "
            << std::left << std::setw(11) << "Phone"   << " | "
            << std::left << std::setw(16) << "City"
            << " |\n";
            std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";

        for (int i = 0; i < length; i++){
            if (data[i].student_id == 0){continue;}
            std::string dob = std::to_string(data[i].student_dob.day)   + "-"
            + std::to_string(data[i].student_dob.month) + "-"
            + std::to_string(data[i].student_dob.year);
            std::cout << "| "
            << std::left << std::setw(4)  << data[i].student_id                      << " | "
            << std::left << std::setw(8)  << data[i].student_rollno                  << " | "
            << std::left << std::setw(22) << data[i].student_name                    << " | "
            << std::left << std::setw(12) << dob                                     << " | "
            << std::left << std::setw(2)  << data[i].student_gender                  << " | "
            << std::left << std::setw(8)  << data[i].student_course                  << " | "
            << std::left << std::setw(3)  << data[i].student_section                 << " | "
            << std::left << std::setw(5)  << data[i].student_number_of_subjects      << " | "
            << std::left << std::setw(4)  << data[i].student_enrollement_year        << " | "
            << std::left << std::setw(10) << data[i].student_pending_fee             << " | "
            << std::left << std::setw(24) << data[i].student_contacts.email          << " | "
            << std::left << std::setw(11) << data[i].student_contacts.phone_no       << " | "
            << std::left << std::setw(16) << data[i].student_address.city
            << " |\n";
        }
        std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";
        
    }
    
    
    else if (flag == 1){
        
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        std::cout << "| "
        << std::left << std::setw(4)  << "ID"       << " | "
        << std::left << std::setw(8)  << "Roll"     << " | "
        << std::left << std::setw(22) << "Subject"  << " | "
        << std::left << std::setw(8)  << "Code"     << " | "
        << std::left << std::setw(10) << "Total"    << " | "
        << std::left << std::setw(12) << "Obtained" << " | "
        << std::left << std::setw(7)  << "Credits"
        << " |\n";
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        
        for (int i = 0; i < length; i++){
            if (data[i].student_id == 0){continue;}
            for (int j = 0; j < data[i].student_number_of_subjects; j++){
                
                std::cout << "| "
                << std::left << std::setw(4)  << data[i].student_id                                << " | "
                << std::left << std::setw(8)  << data[i].student_rollno                            << " | "
                << std::left << std::setw(22) << data[i].student_subjects[j].getsubname()          << " | "
                << std::left << std::setw(8)  << data[i].student_subjects[j].getsubcode()          << " | "
                << std::left << std::setw(10) << data[i].student_subjects[j].getsubtotalmarks()    << " | "
                << std::left << std::setw(12) << data[i].student_subjects[j].getsubobtainedmarks() << " | "
                << std::left << std::setw(7)  << data[i].student_subjects[j].getsubcredits()
                << " |\n";
            }
            if (i < length - 1)
            std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        }
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        }
        return 1;
    }
    
    
    
    int records_by_course(const std::string & course, int flag = 0){
        datafields::fields * data = recorddata::fetch::records_by_course(course);
        int length = recorddata::fetch::no_of_records_by_course(course); 
    
        if (data == nullptr){
            return 0;
        }
    
        if (flag == 0){
            std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";
            std::cout << "| "
            << std::left << std::setw(4)  << "ID"      << " | "
            << std::left << std::setw(8)  << "Roll"    << " | "
            << std::left << std::setw(22) << "Name"    << " | "
            << std::left << std::setw(12) << "DOB"     << " | "
            << std::left << std::setw(2)  << "G"       << " | "
            << std::left << std::setw(8)  << "Course"  << " | "
            << std::left << std::setw(3)  << "Sec"     << " | "
            << std::left << std::setw(5)  << "Subj"    << " | "
            << std::left << std::setw(4)  << "Year"    << " | "
            << std::left << std::setw(10) << "Fee"     << " | "
            << std::left << std::setw(24) << "Email"   << " | "
            << std::left << std::setw(11) << "Phone"   << " | "
            << std::left << std::setw(16) << "City"
            << " |\n";
            std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";
    
        for (int i = 0; i < length; i++){
            if (data[i].student_id == 0){continue;}
            std::string dob = std::to_string(data[i].student_dob.day)   + "-"
            + std::to_string(data[i].student_dob.month) + "-"
            + std::to_string(data[i].student_dob.year);
            std::cout << "| "
            << std::left << std::setw(4)  << data[i].student_id                      << " | "
            << std::left << std::setw(8)  << data[i].student_rollno                  << " | "
            << std::left << std::setw(22) << data[i].student_name                    << " | "
            << std::left << std::setw(12) << dob                                     << " | "
            << std::left << std::setw(2)  << data[i].student_gender                  << " | "
            << std::left << std::setw(8)  << data[i].student_course                  << " | "
            << std::left << std::setw(3)  << data[i].student_section                 << " | "
            << std::left << std::setw(5)  << data[i].student_number_of_subjects      << " | "
            << std::left << std::setw(4)  << data[i].student_enrollement_year        << " | "
            << std::left << std::setw(10) << data[i].student_pending_fee             << " | "
            << std::left << std::setw(24) << data[i].student_contacts.email          << " | "
            << std::left << std::setw(11) << data[i].student_contacts.phone_no       << " | "
            << std::left << std::setw(16) << data[i].student_address.city
            << " |\n";
        }
        std::cout << "+------+----------+------------------------+--------------+----+----------+-----+-------+------+------------+--------------------------+-------------+------------------+\n";
        
    }
    
    
    else if (flag == 1){
        
        std::cout << "+----------+----------+\n";
        std::cout << "| "<< std::left << std::setw(8) << "Course" <<" | " << std::setw(8) << course <<" |\n";
        std::cout << "+----------+----------+\n";
        
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        std::cout << "| "
        << std::left << std::setw(4)  << "ID"       << " | "
        << std::left << std::setw(8)  << "Roll"     << " | "
        << std::left << std::setw(22) << "Subject"  << " | "
        << std::left << std::setw(8)  << "Code"     << " | "
        << std::left << std::setw(10) << "Total"    << " | "
        << std::left << std::setw(12) << "Obtained" << " | "
        << std::left << std::setw(7)  << "Credits"
        << " |\n";
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        
        for (int i = 0; i < length; i++){
            if (data[i].student_id == 0){continue;}
            for (int j = 0; j < data[i].student_number_of_subjects; j++){
                
                std::cout << "| "
                << std::left << std::setw(4)  << data[i].student_id                                << " | "
                << std::left << std::setw(8)  << data[i].student_rollno                            << " | "
                << std::left << std::setw(22) << data[i].student_subjects[j].getsubname()          << " | "
                << std::left << std::setw(8)  << data[i].student_subjects[j].getsubcode()          << " | "
                << std::left << std::setw(10) << data[i].student_subjects[j].getsubtotalmarks()    << " | "
                << std::left << std::setw(12) << data[i].student_subjects[j].getsubobtainedmarks() << " | "
                << std::left << std::setw(7)  << data[i].student_subjects[j].getsubcredits()
                << " |\n";
            }
            if (i < length - 1)
            std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        }
        std::cout << "+------+----------+------------------------+----------+------------+--------------+---------+\n";
        }
        return 1;
    }



    int session_data(){
        int length = session::get_length();
        ifstream file(session_file_path,ios::in | ios::binary);
        datafields::sub_rollno data;
        int value , value2;
        if (!file.is_open()){
            return 0;
        }
        
        file.read(reinterpret_cast<char *>(&value),sizeof(value)) ;
        file.read(reinterpret_cast<char *>(&value2),sizeof(value2));
        std::cout << "┌──────────────────────┬──────────┐\n";
        std::cout << "│ "<< std::left << std::setw(20)  << "Student ID"<< " │ " << std::setw(8)  << "Assigner" <<" │\n";
        std::cout << "├──────────────────────┼──────────┤\n";
        std::cout << "│ "<< std::left << std::setw(20)  << value << " │ " << std::setw(8)  << value2 <<" │\n";
        std::cout <<"└──────────────────────┴──────────┘\n";
        
        if (length == 0) { return -1;}
        
        std::cout << "┌──────────────────────┬──────────┐\n";
        std::cout << "│ "<< std::left << std::setw(20)  << "Course "<< " │ " << std::setw(8)  << "Roll No" <<" │\n";
        std::cout << "├──────────────────────┼──────────┤\n";
        while(file.read(reinterpret_cast<char *>(&data),sizeof(data))){
            std::cout << "│ "<< std::left << std::setw(20)  << data.student_course << " │ " << std::setw(8)  << data.student_rollno_A <<" │\n";
        }
        std::cout << "└──────────────────────┴──────────┘\n";

        return 1;


    }


}

}




int main(){



// recorddata::record::init_record();
// recorddata::session::inti_session();

datafields::fields data[5];

// --- data[0] --- BCA
strcpy(data[0].student_name, "Arjun Sharma");
data[0].student_dob = {15, 6, 2001};
data[0].student_gender = 'M';
strcpy(data[0].student_course, "BCA");
data[0].student_section = 'A';
data[0].student_number_of_subjects = 5;
data[0].student_enrollement_year = 2021;
data[0].student_pending_fee = 5000;
strcpy(data[0].student_contacts.email, "arjun@mail.com");
strcpy(data[0].student_contacts.phone_no, "9876543210");
strcpy(data[0].student_address.house, "12B");
strcpy(data[0].student_address.street, "MG Road");
strcpy(data[0].student_address.city, "Delhi");
strcpy(data[0].student_address.state, "Delhi");
strcpy(data[0].student_address.country, "India");
strcpy(data[0].student_address.pincode, "110001");
data[0].student_subjects[0].setsubname(std::string("Mathematics"));
data[0].student_subjects[0].setsubcode(101); data[0].student_subjects[0].setsubcredits(4);
data[0].student_subjects[0].setsubtotalmarks(100); data[0].student_subjects[0].setsubobtainedmarks(78);
data[0].student_subjects[1].setsubname(std::string("C++"));
data[0].student_subjects[1].setsubcode(102); data[0].student_subjects[1].setsubcredits(3);
data[0].student_subjects[1].setsubtotalmarks(100); data[0].student_subjects[1].setsubobtainedmarks(85);
data[0].student_subjects[2].setsubname(std::string("English"));
data[0].student_subjects[2].setsubcode(103); data[0].student_subjects[2].setsubcredits(2);
data[0].student_subjects[2].setsubtotalmarks(100); data[0].student_subjects[2].setsubobtainedmarks(72);
data[0].student_subjects[3].setsubname(std::string("Data Structures"));
data[0].student_subjects[3].setsubcode(104); data[0].student_subjects[3].setsubcredits(4);
data[0].student_subjects[3].setsubtotalmarks(100); data[0].student_subjects[3].setsubobtainedmarks(91);
data[0].student_subjects[4].setsubname(std::string("Networking"));
data[0].student_subjects[4].setsubcode(105); data[0].student_subjects[4].setsubcredits(3);
data[0].student_subjects[4].setsubtotalmarks(100); data[0].student_subjects[4].setsubobtainedmarks(66);

// --- data[1] --- BCA
strcpy(data[1].student_name, "Priya Verma");
data[1].student_dob = {22, 3, 2002};
data[1].student_gender = 'F';
strcpy(data[1].student_course, "BCA");
data[1].student_section = 'B';
data[1].student_number_of_subjects = 5;
data[1].student_enrollement_year = 2021;
data[1].student_pending_fee = 0;
strcpy(data[1].student_contacts.email, "priya@mail.com");
strcpy(data[1].student_contacts.phone_no, "9123456780");
strcpy(data[1].student_address.house, "45A");
strcpy(data[1].student_address.street, "Park Street");
strcpy(data[1].student_address.city, "Mumbai");
strcpy(data[1].student_address.state, "Maharashtra");
strcpy(data[1].student_address.country, "India");
strcpy(data[1].student_address.pincode, "400001");
data[1].student_subjects[0].setsubname(std::string("Mathematics"));
data[1].student_subjects[0].setsubcode(101); data[1].student_subjects[0].setsubcredits(4);
data[1].student_subjects[0].setsubtotalmarks(100); data[1].student_subjects[0].setsubobtainedmarks(95);
data[1].student_subjects[1].setsubname(std::string("C++"));
data[1].student_subjects[1].setsubcode(102); data[1].student_subjects[1].setsubcredits(3);
data[1].student_subjects[1].setsubtotalmarks(100); data[1].student_subjects[1].setsubobtainedmarks(92);
data[1].student_subjects[2].setsubname(std::string("English"));
data[1].student_subjects[2].setsubcode(103); data[1].student_subjects[2].setsubcredits(2);
data[1].student_subjects[2].setsubtotalmarks(100); data[1].student_subjects[2].setsubobtainedmarks(85);
data[1].student_subjects[3].setsubname(std::string("Data Structures"));
data[1].student_subjects[3].setsubcode(104); data[1].student_subjects[3].setsubcredits(4);
data[1].student_subjects[3].setsubtotalmarks(100); data[1].student_subjects[3].setsubobtainedmarks(79);
data[1].student_subjects[4].setsubname(std::string("Networking"));
data[1].student_subjects[4].setsubcode(105); data[1].student_subjects[4].setsubcredits(3);
data[1].student_subjects[4].setsubtotalmarks(100); data[1].student_subjects[4].setsubobtainedmarks(88);

// --- data[2] --- MCA
strcpy(data[2].student_name, "Rohit Mehta");
data[2].student_dob = {8, 11, 2000};
data[2].student_gender = 'M';
strcpy(data[2].student_course, "MCA");
data[2].student_section = 'A';
data[2].student_number_of_subjects = 5;
data[2].student_enrollement_year = 2022;
data[2].student_pending_fee = 12000;
strcpy(data[2].student_contacts.email, "rohit@mail.com");
strcpy(data[2].student_contacts.phone_no, "9988776655");
strcpy(data[2].student_address.house, "7C");
strcpy(data[2].student_address.street, "Lake View");
strcpy(data[2].student_address.city, "Pune");
strcpy(data[2].student_address.state, "Maharashtra");
strcpy(data[2].student_address.country, "India");
strcpy(data[2].student_address.pincode, "411001");
data[2].student_subjects[0].setsubname(std::string("Algorithms"));
data[2].student_subjects[0].setsubcode(201); data[2].student_subjects[0].setsubcredits(4);
data[2].student_subjects[0].setsubtotalmarks(100); data[2].student_subjects[0].setsubobtainedmarks(55);
data[2].student_subjects[1].setsubname(std::string("DBMS"));
data[2].student_subjects[1].setsubcode(202); data[2].student_subjects[1].setsubcredits(4);
data[2].student_subjects[1].setsubtotalmarks(100); data[2].student_subjects[1].setsubobtainedmarks(60);
data[2].student_subjects[2].setsubname(std::string("OS"));
data[2].student_subjects[2].setsubcode(203); data[2].student_subjects[2].setsubcredits(3);
data[2].student_subjects[2].setsubtotalmarks(100); data[2].student_subjects[2].setsubobtainedmarks(48);
data[2].student_subjects[3].setsubname(std::string("Networks"));
data[2].student_subjects[3].setsubcode(204); data[2].student_subjects[3].setsubcredits(3);
data[2].student_subjects[3].setsubtotalmarks(100); data[2].student_subjects[3].setsubobtainedmarks(71);
data[2].student_subjects[4].setsubname(std::string("Python"));
data[2].student_subjects[4].setsubcode(205); data[2].student_subjects[4].setsubcredits(3);
data[2].student_subjects[4].setsubtotalmarks(100); data[2].student_subjects[4].setsubobtainedmarks(83);

// --- data[3] --- BSC
strcpy(data[3].student_name, "Sneha Patel");
data[3].student_dob = {30, 7, 2003};
data[3].student_gender = 'F';
strcpy(data[3].student_course, "BSC");
data[3].student_section = 'A';
data[3].student_number_of_subjects = 5;
data[3].student_enrollement_year = 2022;
data[3].student_pending_fee = 3000;
strcpy(data[3].student_contacts.email, "sneha@mail.com");
strcpy(data[3].student_contacts.phone_no, "9012345678");
strcpy(data[3].student_address.house, "3F");
strcpy(data[3].student_address.street, "Rose Garden");
strcpy(data[3].student_address.city, "Ahmedabad");
strcpy(data[3].student_address.state, "Gujarat");
strcpy(data[3].student_address.country, "India");
strcpy(data[3].student_address.pincode, "380001");
data[3].student_subjects[0].setsubname(std::string("Physics"));
data[3].student_subjects[0].setsubcode(301); data[3].student_subjects[0].setsubcredits(4);
data[3].student_subjects[0].setsubtotalmarks(100); data[3].student_subjects[0].setsubobtainedmarks(62);
data[3].student_subjects[1].setsubname(std::string("Chemistry"));
data[3].student_subjects[1].setsubcode(302); data[3].student_subjects[1].setsubcredits(4);
data[3].student_subjects[1].setsubtotalmarks(100); data[3].student_subjects[1].setsubobtainedmarks(58);
data[3].student_subjects[2].setsubname(std::string("Biology"));
data[3].student_subjects[2].setsubcode(303); data[3].student_subjects[2].setsubcredits(3);
data[3].student_subjects[2].setsubtotalmarks(100); data[3].student_subjects[2].setsubobtainedmarks(74);
data[3].student_subjects[3].setsubname(std::string("Mathematics"));
data[3].student_subjects[3].setsubcode(304); data[3].student_subjects[3].setsubcredits(3);
data[3].student_subjects[3].setsubtotalmarks(100); data[3].student_subjects[3].setsubobtainedmarks(80);
data[3].student_subjects[4].setsubname(std::string("English"));
data[3].student_subjects[4].setsubcode(305); data[3].student_subjects[4].setsubcredits(2);
data[3].student_subjects[4].setsubtotalmarks(100); data[3].student_subjects[4].setsubobtainedmarks(67);

// --- data[4] --- BSC
strcpy(data[4].student_name, "Karan Singh");
data[4].student_dob = {5, 1, 2001};
data[4].student_gender = 'M';
strcpy(data[4].student_course, "BSC");
data[4].student_section = 'B';
data[4].student_number_of_subjects = 5;
data[4].student_enrollement_year = 2022;
data[4].student_pending_fee = 8000;
strcpy(data[4].student_contacts.email, "karan@mail.com");
strcpy(data[4].student_contacts.phone_no, "9871234560");
strcpy(data[4].student_address.house, "22D");
strcpy(data[4].student_address.street, "Civil Lines");
strcpy(data[4].student_address.city, "Jaipur");
strcpy(data[4].student_address.state, "Rajasthan");
strcpy(data[4].student_address.country, "India");
strcpy(data[4].student_address.pincode, "302001");
data[4].student_subjects[0].setsubname(std::string("Physics"));
data[4].student_subjects[0].setsubcode(301); data[4].student_subjects[0].setsubcredits(4);
data[4].student_subjects[0].setsubtotalmarks(100); data[4].student_subjects[0].setsubobtainedmarks(70);
data[4].student_subjects[1].setsubname(std::string("Chemistry"));
data[4].student_subjects[1].setsubcode(302); data[4].student_subjects[1].setsubcredits(4);
data[4].student_subjects[1].setsubtotalmarks(100); data[4].student_subjects[1].setsubobtainedmarks(75);
data[4].student_subjects[2].setsubname(std::string("Biology"));
data[4].student_subjects[2].setsubcode(303); data[4].student_subjects[2].setsubcredits(3);
data[4].student_subjects[2].setsubtotalmarks(100); data[4].student_subjects[2].setsubobtainedmarks(68);
data[4].student_subjects[3].setsubname(std::string("Mathematics"));
data[4].student_subjects[3].setsubcode(304); data[4].student_subjects[3].setsubcredits(3);
data[4].student_subjects[3].setsubtotalmarks(100); data[4].student_subjects[3].setsubobtainedmarks(82);
data[4].student_subjects[4].setsubname(std::string("English"));
data[4].student_subjects[4].setsubcode(305); data[4].student_subjects[4].setsubcredits(2);
data[4].student_subjects[4].setsubtotalmarks(100); data[4].student_subjects[4].setsubobtainedmarks(90);

datafields::fields dataupdate;

strcpy(dataupdate.student_name, "Priya Verma");
dataupdate.student_dob = {22, 3, 2002};
dataupdate.student_gender = 'F';
strcpy(dataupdate.student_course, "BCA");
dataupdate.student_section = 'B';
dataupdate.student_number_of_subjects = 5;
dataupdate.student_enrollement_year = 2021;
dataupdate.student_pending_fee = 500;
strcpy(dataupdate.student_contacts.email, "priya@mail.com");
strcpy(dataupdate.student_contacts.phone_no, "9123456780");
strcpy(dataupdate.student_address.house, "45A");
strcpy(dataupdate.student_address.street, "Park Street");
strcpy(dataupdate.student_address.city, "Mumbai");
strcpy(dataupdate.student_address.state, "Maharashtra");
strcpy(dataupdate.student_address.country, "India");
strcpy(dataupdate.student_address.pincode, "400001");
dataupdate.student_subjects[0].setsubname(std::string("Mathematics"));
dataupdate.student_subjects[0].setsubcode(101); dataupdate.student_subjects[0].setsubcredits(4);
dataupdate.student_subjects[0].setsubtotalmarks(100); dataupdate.student_subjects[0].setsubobtainedmarks(99);
dataupdate.student_subjects[1].setsubname(std::string("C++"));
dataupdate.student_subjects[1].setsubcode(102); dataupdate.student_subjects[1].setsubcredits(3);
dataupdate.student_subjects[1].setsubtotalmarks(100); dataupdate.student_subjects[1].setsubobtainedmarks(99);
dataupdate.student_subjects[2].setsubname(std::string("English"));
dataupdate.student_subjects[2].setsubcode(103); dataupdate.student_subjects[2].setsubcredits(2);
dataupdate.student_subjects[2].setsubtotalmarks(100); dataupdate.student_subjects[2].setsubobtainedmarks(99);
dataupdate.student_subjects[3].setsubname(std::string("Data Structures"));
dataupdate.student_subjects[3].setsubcode(104); dataupdate.student_subjects[3].setsubcredits(4);
dataupdate.student_subjects[3].setsubtotalmarks(100); dataupdate.student_subjects[3].setsubobtainedmarks(99);
dataupdate.student_subjects[4].setsubname(std::string("Networking"));
dataupdate.student_subjects[4].setsubcode(105); dataupdate.student_subjects[4].setsubcredits(3);
dataupdate.student_subjects[4].setsubtotalmarks(100); dataupdate.student_subjects[4].setsubobtainedmarks(99);

recorddata::connect(data[0]);
recorddata::connect(data[1]);
recorddata::connect(data[2]);
recorddata::connect(data[3]);
recorddata::connect(data[4]);

cout << "Do course exists : (it gives where it exist index ) : "<<recorddata::session::do_course_exists("BSC")<<endl;
cout << "Get course roll no bca: " << recorddata::session::get_course_rollno("BCA")<<endl;
cout << "ID bca: " << data[0].student_id<<endl;
cout << "ID bca: " << data[1].student_id<<endl;
cout << "ID mcs: " << data[2].student_id<<endl;
cout << "ID bsc: " << data[3].student_id<<endl;
cout << "ID bsc: " << data[4].student_id<<endl;
cout << "Get course roll no bsc: " << recorddata::session::get_course_rollno("BSC")<<endl;
cout << "Get course roll no mca: " << recorddata::session::get_course_rollno("MCA")<<endl;
cout << "Session length no of corses :" << recorddata::session::get_length()<<endl;
cout << "get std id A :" << recorddata::session::get_student_id_A()<<endl;
// cout << "get init roll no :" << recorddata::session::init_rollno_for_new_course()<<endl;

int a = recorddata::session::get_length();
datafields::sub_rollno * sessiondata = recorddata::session::get_data();

for (int i = 0 ; i < a ; i++){
    std::cout<<"course : "<<sessiondata[i].student_course<<endl;
    std::cout<<"Roll no : "<<sessiondata[i].student_rollno_A<<endl;
}



cout<<"Length : "<<recorddata::record::get_length()<<endl;
cout<<"DO Exists: "<<recorddata::record::do_exists(data[3])<<endl; // didnt added validation to check the duplicate data it checks though the student id but it will always be assigned new
// cout<<"DElete : "<<recorddata::record::delete_data(data[3])<<endl; // 1 sucess 0 file not opened -1 not found
cout<<"DO Exists: "<<recorddata::record::do_exists(data[3])<<endl; // -1 not found
cout<<"BSC NO OF RECORDs : "<<recorddata::fetch::no_of_records_by_course("BSC")<<endl; // 20 beacause data also delted one
cout<<"BCA NO OF RECORDs : "<<recorddata::fetch::no_of_records_by_course("BCA")<<endl; // 40 
cout<<"MCA NO OF RECORDs : "<<recorddata::fetch::no_of_records_by_course("MCA")<<endl; // 20 
int b = recorddata::record::get_length(); 

datafields::fields recorddata1 = recorddata::fetch::record_by_key(4);
cout<<"_________"<<endl;
cout << "NAME : " <<recorddata1.student_name<<endl;
cout << "NO OF SUB : "<<recorddata1.student_number_of_subjects<<endl;
cout << "COURSE: "<<recorddata1.student_course<<endl;
cout << "EMAIL : "<<recorddata1.student_contacts.email<<endl;
cout << "DOB : "<<recorddata1.student_dob.day<<" "<<recorddata1.student_dob.month<<" "<<recorddata1.student_dob.year<<endl;

datafields::fields * f = recorddata::fetch::all_record();

for (int j = 0 ; j < b ; j++ ){
    cout << "______________"<< endl;
    cout << "COURSE :: "<< f[j].student_course<<endl;
    cout << "NO OF SUB :: "<<f[j].student_number_of_subjects<<endl;
    cout <<"NAME :<<"<< f[j].student_name<<endl;
    cout << "______________"<< endl;
}

cout<< recorddata::fetch::export_csv_by_course("BCA");
cout<< recorddata::fetch::export_csv_by_course("BSC");
cout<< recorddata::fetch::export_csv_by_course("MCA");
cout<< recorddata::fetch::export_csv_all()<<endl;
recorddata::show::all_records(0);
recorddata::show::all_records(1);
recorddata::show::session_data();
recorddata::show::records_by_course("BCA");
recorddata::show::records_by_course("BSC");
recorddata::show::records_by_course("MCA");
recorddata::show::records_by_course("BCA",1);
recorddata::show::records_by_course("BSC",1);
recorddata::show::records_by_course("MCA",1);
}
