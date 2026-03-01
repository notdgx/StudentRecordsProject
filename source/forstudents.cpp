#include <string>


namespace forstudents{

extern int student_rollno_A;
extern int student_id_A;
struct date{
    int day;
    int month;
    int year;
};
struct contact{
    std::string email;
    char phone_no[11];
    std::string address;
    };

}

int forstudents::student_rollno_A = 4001 ;
int forstudents::student_id_A = 200;