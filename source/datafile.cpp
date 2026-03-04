#include <iostream>
#include <string>
#include "main.cpp"
#include <fstream>

namespace recorddata{

    std::string session_file_path = "../files/session_data";
    std::string record_file_path = "../files/record";

    int get_session_length();

    // RECORD DATA FILE

    int connect_to_record_data(datafields::fields & data){ // add or updare automatically

        // Update to session file

        int index = do_course_in_session(data.student_course);
        if (index == -1){
            add_session_data(std::string(data.student_course),index);
        }

        else{
            update_session_data(std::string(data.student_course),index);
        }

        // assign the rollno as per course and student id also 
        data.student_id = get_student_id_A();
        data.student_rollno =  get_course_rollno_in_session(data.student_course);

        // update to record file

        fstream recordfile(record_file_path,ios::in | ios::out | ios::binary );
        if (!recordfile.is_open()){
            return -1;
        }

        int recordindex = do_record_exists(data);

        if (recordindex == -1 ){
        add_record_data(data);
        return 1;
        }

        update_record_data(data);
        return 1;

    }

    int add_record_data(datafields::fields & data){
        ofstream file(record_file_path , ios::binary | ios::app);
        if (!file.is_open()){
            return -1;
        }
        file.write(reinterpret_cast<char *>(&data),sizeof(data));
        file.close();
        return 1;

    }

    int update_record_data(datafields::fields & data){
        fstream file(record_file_path,ios::in | ios::out | ios::binary);
        int index = do_record_exists(data);
        if (!file.is_open()){
            return 0;
        }

        file.seekp(index * sizeof(data),ios::beg);
        file.write(reinterpret_cast<char*>(&data),sizeof(data));
        file.close();
        return 1;
    }

    int delete_record_data(datafields::fields & data){
        fstream file(record_file_path,ios::in | ios::out | ios::binary);
        datafields::fields deleted{};
        int index = do_record_exists(data);
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



    int do_record_exists(datafields::fields & data){
        ifstream file(record_file_path,ios::in | ios::binary);
        if (!file.is_open()){
            return -2;
        }
        int length = get_record_length();
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

    int get_record_length(){
        ifstream file(record_file_path,ios::in | ios::binary);
        int length,size;
        file.seekg(0,ios::end);
        size = file.tellg();
        file.close();
        length = size / sizeof(datafields::fields);
        return length;
    }

    /// GET RECORD DATA

    /*
    // datafields::fields get_record_data(int key , bool flag = true ){
    //     int a;
    //     int length = get_record_length();
    //     datafields::fields data{};
    //     if (flag){
    //         key = get_student_id_by_rollno(key);
    //     }
    //     else{
    //         a = do_student_id_exists_in_record(key);
    //         if (a == -1){
    //             return data;
    //         }
    //     }
    //     if (key == -1){
    //         return data;
    //     }

    //     ifstream file(record_file_path , ios::in | ios::binary);
    //     if (file.is_open()){
    //         for (int i = 0 ; i < length ; i++ ){
    //             file.seekg(i * sizeof(datafields::fields),ios::beg);
    //             file.read(reinterpret_cast<char *>(&))
    //         }
    //     }



    // }

    // int do_student_id_exists_in_record(int studentid){
    //     int length = get_record_length();
    //     ifstream file(record_file_path , ios::binary);
    //     int student_id_C;
    //     if (!file.is_open()){
    //         return 0;
    //     }

    //     for (int i = 0 ; i < length ; i++ ){
    //         file.seekg(i * sizeof(datafields::fields) , ios::beg);
    //         file.read(reinterpret_cast<char *>(&student_id_C),sizeof(student_id_C));
    //         if (student_id_C == studentid){
    //             return 1;
    //         }
    //     }
    //     return -1;
    // } */

    datafields::fields get_record_data(int key, bool flag = true){
        if (flag){
            return get_record_data_by_student_id(key);
        }
        else {
            return get_record_data_by_student_rollno(key);
        }
    }
    
    datafields::fields get_record_data_by_student_rollno(int rollno){
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

    datafields::fields get_record_data_by_student_id(int student_id){
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

    // ___________________________________________________________________

    // FOR SESSION DATA FILE

    int add_session_data(std::string & course , int index){
        fstream file(session_file_path , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }

        datafields::sub_rollno sessiondata{};
        strcpy(sessiondata.student_course,course.c_str());
        sessiondata.student_rollno_A = init_student_rollno_for_new_course();

        if (index == -1){
            file.seekg(0,ios::end);
            file.write(reinterpret_cast<char *>(& sessiondata),sizeof(sessiondata));
            file.close();
            return 1;
        }
        return -1;

    }

    int update_session_data(const std::string & course, int index){
        int rollno = get_course_rollno_in_session(course);
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



    int get_course_rollno_in_session(const std::string & course){

        int index = do_course_in_session(course);
        if (index == -1){
            return -1;
        }
        ifstream file(session_file_path , ios::in | ios::binary);
        datafields::sub_rollno data{};
        file.seekg((8+(index*sizeof(data))),ios::beg);
        file.read(reinterpret_cast<char *>(& data),sizeof(data));
        return data.student_rollno_A;

    }

    int do_course_in_session(const std::string & course){
        ifstream file(session_file_path , ios::in | ios::binary);
        datafields::sub_rollno data{};
        int length = get_session_length();
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

    datafields::sub_rollno * get_session_data(){

        ifstream file(session_file_path , ios::in | ios::binary);
        int length = get_session_length();
        
        if (length == 0){
            return nullptr;
        }

        file.seekg(8,ios::beg);
        datafields::sub_rollno * data = new datafields::sub_rollno[length];
        file.read(reinterpret_cast<char *> (&data), length * sizeof(datafields::sub_rollno) );
        return data;

    }

    // get how many course are registered in session

    int get_session_length(){

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

    int init_student_rollno_for_new_course(){
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