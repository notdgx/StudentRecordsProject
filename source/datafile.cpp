#include <iostream>
#include <string>
#include "main.cpp"
#include <fstream>

namespace recorddata{

    int get_session_length();

    int add_data(datafields::fields data){
        fstream file("../files/data" , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }

        int flag = do_course_in_session(data.student_course);

        file.close();
        return 1;

    }

    int add_session_data(datafields::sub_rollno data){
        fstream file("../files/data" , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }
        int index = do_course_in_session(data.student_course);
        if (index == -1){
            file.seekg(0,ios::end);
            file.write(reinterpret_cast<char *>(& data),sizeof(data));
            file.close();
            return 1;
        }
        return -1;

    }

    int update_session_data(datafields::sub_rollno data){
        fstream file("../files/data" , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }
        int index = do_course_in_session(data.student_course);
        int rollno = get_course_rollno_in_session(data.student_course);
        // if (index == -1 || rollno == -1 ){
        //     return -1;
        // }
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
        ifstream file("../files/data" , ios::in | ios::binary);
        datafields::sub_rollno data{};
        file.seekg((8+(index*sizeof(data))),ios::beg);
        file.read(reinterpret_cast<char *>(& data),sizeof(data));
        return data.student_rollno_A;

    }

    int do_course_in_session(const std::string & course){
        ifstream file("../files/data" , ios::in | ios::binary);
        datafields::sub_rollno data{};
        int length = get_session_length();
        file.seekg(8,ios::beg);

        for (int i = 0 ; i <= length ; i++){
            file.read(reinterpret_cast<char *>(& data),sizeof(data));
            if (data.student_course == course){
                return i;
            }
        }

        return -1;
    }


    // get struct array of regestered course in session

    datafields::sub_rollno * get_session_data(){

        ifstream file("../files/data" , ios::in | ios::binary);
        int length = get_session_length();
        
        if (length == 0){
            return nullptr;
        }

        file.seekg(8,ios::beg);
        datafields::sub_rollno * data = new datafields::sub_rollno[length];
        return data;

    }

    // get how many course are registered in session

    int get_session_length(){

        ifstream file("../files/data" , ios::in | ios::binary);
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
        ifstream file("../files/data" , ios::in| ios::binary);
        int student_id_A;
        file.read(reinterpret_cast<char*>(&student_id_A),sizeof(student_id_A));
        file.close();
        return student_id_A;
    }

    int update_student_id_A(){
        int old_id = get_student_id_A();
        old_id++;

        fstream file("../files/data" , ios::in | ios::out | ios::binary);
        if (!file.is_open()){
            return 0;
        }
        file.write(reinterpret_cast<char *>(&old_id),sizeof(old_id));
        return 1;

    }

}