#include <iostream>
#include <string>
#include "subjects.cpp"


float get_percentage(Subject * sub , int number_of_subjects ){

    float percentage;
    int sum_totalmarks=0;
    int sum_obtainedmarks=0;

    if (number_of_subjects == 0 ){
        return -1 ; 
    }
    
    for (int i = 0 ; i < number_of_subjects ; i++ ){
        sum_obtainedmarks += sub[i].getsubobtainedmarks(); 
        sum_totalmarks += sub[i].getsubtotalmarks(); // it cannot be zero as default is set to 100 until explictly set to zeroo
    }
    
    if (sum_obtainedmarks == 0){
        return 0.00f;
    }

    percentage = (static_cast<float> (sum_obtainedmarks) / sum_totalmarks) * 100;
    return percentage ;
    
}



float get_averagemarks(Subject * sub , int number_of_subjects ){
    
    float averagemarks; 
    int sum_obtainedmarks=0;
    
    for (int i = 0 ; i < number_of_subjects ; i++ ){
        sum_obtainedmarks += sub[i].getsubobtainedmarks();

    }

    if (number_of_subjects == 0){
        return -1;
    }

    averagemarks = (static_cast<float> (sum_obtainedmarks) /number_of_subjects ) ;
    return  averagemarks ;
    
}


bool get_passstatus(Subject * sub , int number_of_subjects){

    float percentage = get_percentage ( sub , number_of_subjects );

    if (percentage == -1 ){
        return false;
    }

    if (percentage >= 40.00f){
        return true;
    }

    return false;

}


char get_grade(Subject * sub , int number_of_subjects){

}


char get_cgpa(Subject * sub , int number_of_subjects){

}