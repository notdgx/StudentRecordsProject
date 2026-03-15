#pragma once

#include <iostream>
#include <string>
#include "subjects.hpp"

namespace additionalfunctions{

    float get_percentage(Subject * sub , int number_of_subjects );
    float get_percentage_each(Subject sub);
    float get_averagemarks(Subject * sub , int number_of_subjects );
    bool get_passstatus(Subject * sub , int number_of_subjects);
    int get_gradepoint_each(Subject sub);
    int get_creditpoint(Subject * sub , int number_of_subjects);
    float get_cgpa(Subject * sub , int number_of_subjects);

}
