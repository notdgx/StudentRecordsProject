#include <iostream>
#include <string>
#include "subjects.cpp"

namespace additionalfunctions{

float get_percentage(Subject * sub , int number_of_subjects ){ 

    float percentage;
    int sum_totalmarks=0;
    int sum_obtainedmarks=0;

    if (number_of_subjects == 0 ){
        return -1 ; 
    }
    
    for (int i = 0 ; i < number_of_subjects ; i++ ){
        sum_obtainedmarks += sub[i].getsubobtainedmarks();     
        sum_totalmarks += sub[i].getsubtotalmarks(); // it cannot be zerso  o as default is set to 100 until explictly set to zeroo
    }

    if (sum_obtainedmarks == 0){
        return 0.00f;
    }

    percentage = (static_cast<float> (sum_obtainedmarks) / sum_totalmarks) * 100;
    return percentage ;
    
}

float get_percentage_each(Subject sub){
    float percentage;
    if (sub.getsubtotalmarks() == 0 ){ return -1;}
    percentage = (static_cast<float>(sub.getsubobtainedmarks()) / sub.getsubtotalmarks()) * 100;
    return percentage;

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


int get_gradepoint_each(Subject sub){
    float percentage = get_percentage_each(sub);

    if (percentage == -1 ){ return -1;}

    if (percentage >= 90) return 10;
    else if (percentage >= 80) return 9;
    else if (percentage >= 70) return 8;
    else if (percentage >= 60) return 7;
    else if (percentage >= 50) return 6;
    else if (percentage >= 40) return 5;

    return 0;  // below 40
}


int get_creditpoint(Subject * sub , int number_of_subjects) {
    int creditpoint = 0;

    if (number_of_subjects == 0) {return -1;}
    for (int i=0 ; i< number_of_subjects ; i++){
        creditpoint += sub[i].getsubcredits() *  get_gradepoint_each(sub[i]);
    }
    return creditpoint;
}

float get_cgpa(Subject * sub , int number_of_subjects){
    float cgpa;
    int totalcreditpoints = get_creditpoint(sub,number_of_subjects);
    int totalcredits = 0 ; 
    if (totalcreditpoints == -1 ){ return -1;}
    for (int i = 0 ; i < number_of_subjects ; i++){
        totalcredits += sub[i].getsubcredits();
    }

    cgpa = (static_cast<float>(totalcreditpoints) / totalcredits);
    return cgpa; 
}

}