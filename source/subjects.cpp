#include <iostream>
#include <string>

using namespace std;

class Subject
{

private: 
    char sub_name[20];
    int sub_code;
    int sub_totalmarks;
    int sub_obtainedmarks;
    int sub_credits;

public:

    Subject(){}

    Subject(string sub_name, int sub_code, int sub_totalmarks = 100, int sub_obtainedmarks = 0 , int sub_credits = 1 )
    {
        setsubname(sub_name);
        setsubcode(sub_code);
        setsubtotalmarks(sub_totalmarks);
        setsubobtainedmarks(sub_obtainedmarks);
        setsubcredits(sub_credits);
    }

    // GETTERS 

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
        return sub_totalmarks;
    }

    int getsubobtainedmarks()
    {
        return sub_obtainedmarks;
    }

    int getsubcredits(){
        return sub_credits;
    }

    // SETTERRSS

    void setsubname(const string name)
    {
        sub_name = name;
    }

    void setsubcode(int code)
    {
        sub_code = code;
    }

    void setsubtotalmarks(int totalmarks)
    {
        sub_totalmarks = totalmarks;
    }

    void setsubobtainedmarks(int obtainedmarks)
    {
        sub_obtainedmarks = obtainedmarks;
    }

    void setsubcredits(int credits){
        sub_credits = credits ;
    }
};