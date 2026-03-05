#include <iostream>
#include <string>
// #include "main.cpp"
#include "fields.cpp"
#include <fstream>

namespace recorddata{

    std::string session_file_path = "../files/session_data";
    std::string record_file_path = "../files/record";

    namespace session{
        int add_data(const std::string & course , int index);
        int update_data(const std::string & course, int index);
        int get_course_rollno(const std::string & course);
        int do_course_exists(const std::string & course);
        datafields::sub_rollno * get_data();
        int get_length();
        int get_student_id_A();
        int init_rollno_for_new_course();
    }

    namespace record{
        int add_data(datafields::fields & data);
        int update_data(datafields::fields & data);
        int delete_data(datafields::fields & data);
        int do_exists(datafields::fields & data);
        int get_length();
    }

    namespace fetch{
        datafields::fields record_by_key(int key, bool flag);
        datafields::fields record_by_rollno(int rollno);
        datafields::fields record_by_id(int student_id);
        datafields::fields * all_record();
        datafields::fields * records_by_course(const std::string & course);
        int no_of_records_by_course(const std::string & course);
    }

    // RECORD DATA FILE

    int connect(datafields::fields & data){ // add or updare automatically

        // Update to session file

        int index = session::do_course_exists(data.student_course);
        if (index == -1){
            session::add_data(std::string(data.student_course),index);
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
        fstream file(record_file_path,ios::in | ios::out | ios::binary);
        int index = do_exists(data);
        if (!file.is_open()){
            return 0;
        }

        file.seekp(index * sizeof(data),ios::beg);
        file.write(reinterpret_cast<char*>(&data),sizeof(data));
        file.close();
        return 1;
    }

    int delete_data(datafields::fields & data){
        fstream file(record_file_path,ios::in | ios::out | ios::binary);
        datafields::fields deleted{};
        int index = do_exists(data);
        if (!file.is_open()){
            return 0;
        }
        if (index == -1){
            return -1;
        }

        file.seekp(index * sizeof(data),ios::beg);
        file.write(reinterpret_cast<char *>(&deleted), sizeof(deleted));
        return 1;
        

    }



    int do_exists(datafields::fields & data){
        ifstream file(record_file_path,ios::in | ios::binary);
        if (!file.is_open()){
            return -2;
        }
        int length = get_length();
        int student_id, i,size;
        file.seekg(0,ios::end);
        size = file.tellg();
        if (size == 0 ){
            return -1;
        }
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
        file.seekg(0,ios::end);
        size = file.tellg();
        file.close();
        length = size / sizeof(datafields::fields);
        return length;
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

}


    // ___________________________________________________________________

    // FOR SESSION DATA FILE

    namespace session{

    int add_data(const std::string & course , int index){
        fstream file(session_file_path , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }

        datafields::sub_rollno sessiondata{};
        strcpy(sessiondata.student_course,course.c_str());
        sessiondata.student_rollno_A = init_rollno_for_new_course();

        if (index == -1){
            file.seekg(0,ios::end);
            file.write(reinterpret_cast<char *>(& sessiondata),sizeof(sessiondata));
            file.close();
            return 1;
        }
        return -1;

    }

    int update_data(const std::string & course, int index){
        int rollno = get_course_rollno(course);
        fstream file(session_file_path , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }
        // if (index == -1 || rollno == -1 ){
        //     return -1;
        // }
        datafields::sub_rollno data;
        strcpy(data.student_course,course.c_str());
        data.student_rollno_A = rollno;
        data.student_rollno_A++;
        file.seekg((8+(index*sizeof(data))),ios::beg);
        file.write(reinterpret_cast<char *>(&data),sizeof(data));
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

        ifstream file(session_file_path , ios::in | ios::binary);
        int size,length;
        file.seekg(0,ios::end);
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
        new_init_roll=init_roll+1000;
        file.seekp(4,ios::beg);
        file.write(reinterpret_cast<char *>(&new_init_roll),sizeof(new_init_roll));
        file.close();
        return init_roll;

    }

}

}