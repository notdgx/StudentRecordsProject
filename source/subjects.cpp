#include <iostream>
#include <string>
#include <cstring>


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
        return string(sub_name);
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

    static bool verifyname(const string& name){
        if (name.size() >= sizeof(sub_name))
            return false;
        return true;

    }

    void setsubname(string& name)
    {   
        if (verifyname(name)){
        memset(sub_name, 0, sizeof(sub_name));
        strcpy(sub_name, name.c_str());}
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