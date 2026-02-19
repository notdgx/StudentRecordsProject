#include <iostream>
#include <string>

using namespace std;

class Subject
{

private: 
    string sub_name;
    int sub_code;
    int sub_total_marks;
    int sub_obtained_mark;

public:

    Subject(){}

    Subject(string NAME, int CODE, int TotalMARKS, int ObtainedMARKS)
    {
        setsubame(NAME);
        setsubcode(CODE);
        setsubtotalmarks(TotalMARKS);
        setsubobtainedmarks(ObtainedMARKS);
    }

    // GETTERRRRR

    string getsubname()
    {
        return sub_name;
    }

    int getsubcode()
    {
        return sub_code;
    }

    int getsubtotalmarks()
    {
        return sub_total_marks;
    }

    int getsubobtainedmarks()
    {
        return sub_obtained_mark;
    }

    // SETTERRRRR

    void setsubame(const string name)
    {
        sub_name = name;
    }

    void setsubcode(int code)
    {
        sub_code = code;
    }

    void setsubtotalmarks(int totalmarks)
    {
        sub_total_marks = totalmarks;
    }

    void setsubobtainedmarks(int obtainedmarks)
    {
        sub_obtained_mark = obtainedmarks;
    }
};