#include <iostream>
#include <string>
#include "subjects.cpp"
#include "courses.cpp"


using namespace std;


class Students
{

private:

    static int rollnoG;

    string student_name;
    int student_roll;
    int Nsubjects;
    string course;
    Subject sub[10];

    void genrollno()
    {
        student_roll = Students::rollnoG;
        Students::rollnoG++;
    }

public:

    // CONSTRUCTERSSSSSS

    // ___________________________________________________________

    Students(){}


    Students(string NAME, string CourseTemplate)
    {
        setname(NAME);
        genrollno();
        cout<<"StudentDetails Created with Name : "<<student_name<<"  Roll No : "<<student_roll << "  Course : "<<course << "  No of Subjects : "<<Nsubjects<< endl ; 
        if (setcourse(CourseTemplate)==1){
        cout<<"Student Data Created With default Subjects "<<endl;}
        else {
        cout<<"Student Data Created But Not Valid Course Found "<<endl;}
    }

    Students(string NAME, string COURSE , int NumberOfSubject)
    {
        setname(NAME);
        genrollno();
        addcourse(COURSE ,NumberOfSubject);
        cout<<"StudentDetails Created with Name : "<<student_name<<"  Roll No : "<<student_roll << "  Course : "<<course << "  No of Subjects : "<<Nsubjects<< endl ; 
        cout<<"Student Data Created With Custom Course Subjects "<<endl;

    }



    // ___________________________________________________________

    // setterrrr

    void setname(string name)
    {
        student_name = name;
    }

    int setcourse(string course)
    {

        if (course == "BCAsem2")
        {
            Nsubjects = 10;
            this->course = course;
            sub[0] = Subject("CPP__________________", 100, 100, 0);
            sub[1] = Subject("DTT_GIMPP____________", 101, 100, 0);
            sub[2] = Subject("AEC_English__________", 102, 100, 0);
            sub[3] = Subject("Computer_Organization", 103, 100, 0);
            sub[4] = Subject("CPP_Practical________", 104, 100, 0);
            sub[5] = Subject("Computer_Hardware____", 105, 100, 0);
            sub[6] = Subject("AI___________________", 106, 100, 0);
            sub[7] = Subject("MIS__________________", 107, 100, 0);
            sub[8] = Subject("Punjabi______________", 108, 100, 0);
            sub[9] = Subject("AI_Practical________", 109, 100, 0);
            return 1;
        }


        else if (course == "BAsem2"){

            Nsubjects = 7;
            this->course = course;

            sub[0] = Subject("English_Literature___", 201, 100, 0);
            sub[1] = Subject("History_of_India_____", 202, 100, 0);
            sub[2] = Subject("Political_Science____", 203, 100, 0);
            sub[3] = Subject("Economics____________", 204, 100, 0);
            sub[4] = Subject("Philosophy___________", 207, 100, 0);
            sub[5] = Subject("Punjabi______________", 209, 100, 0);
            sub[6] = Subject("Environmental_Studies", 210, 100, 0);
            return 1;

        }

        else
        {
            cout << "Not A Valid Course in LIST Add Custom Cource" << endl;
            return -1;
        }
    }



    void setobtainedmarks(int SubjectCode, int ObtainedMarks)
    {

        int Flag=0,i;
        
        for (i = 0; i < Nsubjects; i++)
        {
            if (SubjectCode == sub[i].getsubcode())
            {
                Flag=1;
                break;

            }
            
        }


        if (Flag!=1){

            cout << "Enter a Vaild Subject Code" << endl;

            
        }
        
        else if (Flag==1){
            
            if (ObtainedMarks <= sub[i].getsubtotalmarks() && ObtainedMarks >= 0)
            {
                cout << "Obtained Marks Updated for Subject : "<<sub[i].getsubname() << " And Subject Code : " << sub[i].getsubcode() << " | From : "<<sub[i].getsubobtainedmarks() <<" --> " << ObtainedMarks <<" |"<<endl;
                sub[i].setsubobtainedmarks(ObtainedMarks);
            }
    
            else
            {
                cout << "Enter a valid Marks " << endl;
            }
            
        }
    };




    void addcourse(string CourseName , int NumberOfSubjects){
        course=CourseName;
        Nsubjects=NumberOfSubjects;

        cout << "Custom Cource Created with Name : "<<course <<" No of Subjects : "<< Nsubjects;
    }

    void changecoursesubject(int Index , string SubjectName ,int SubjectCode , int TotalMarks=100 , int ObtainedMarks=0){

        if (Index>0 && Index<=Nsubjects){
            sub[Index-1].setsubame(SubjectName);
            sub[Index-1].setsubcode(SubjectCode);
            sub[Index-1].setsubobtainedmarks(ObtainedMarks);
            sub[Index-1].setsubtotalmarks(TotalMarks);
        }

        else {
            cout << "Invalid Index Number ";
        }

    }

    // ___________________________________________________________

    // FUNCTIONS

    void displayDetails()
    {
        cout << "__________________________________________" << endl << endl;
        cout << "NAME : " << student_name << endl;
        cout << "ROLL NO : " << student_roll << endl;
        cout << "COURSE NO : " << course << endl;
        cout << "NO of subjects : " << Nsubjects << endl;
        cout << "_________________________________________________________________________________________________________" << endl
             << endl;

        cout << "SUBINDEX      SUBJECT                      SUBCODE            OBTAINEDMARKS         TOTALMARKS" << endl;
        cout << "_________________________________________________________________________________________________________" << endl
             << endl;

        for (int i = 0; i < Nsubjects; i++)
        {
            cout << i+1 <<".        "<< sub[i].getsubname() << "              "<< sub[i].getsubcode() << "                    "<< sub[i].getsubobtainedmarks() << "                   "<< sub[i].getsubtotalmarks() << endl;
        }

        cout << "_________________________________________________________________________________________________________" << endl
             << endl;
    }



    // GETTERS 

    string getstudentname(){
        return student_name ;
    }

    int getstudentrollno(){
        return student_roll;
    }

    string getstudentcourse(){
        return course;
    }

    int getnumberofsubjects(){
        return Nsubjects;
    }

    int getaveragemarks(){
        int s=0;
        for (int i =0 ; i < Nsubjects ; i++ ){
            s+=sub[i].getsubobtainedmarks();
        }

        return s/Nsubjects;
    }

    int getpercentage(){

        int s=0;
        int t=0;
        for (int i =0 ; i < Nsubjects ; i++ ){
            s+=sub[i].getsubobtainedmarks();
            t+=sub[i].getsubtotalmarks();
        }

        return (s/t)*100;
        
    }

    Subject getsubject(int SubjectCode){

        int Flag=0,i;
        
        for (i = 0; i < Nsubjects; i++)
        {
            if (SubjectCode == sub[i].getsubcode())
            {
                Flag=1;
                break;

            }
        }


        if (Flag=1){

            return sub[i];

            }

        else {

            cout << "Enter a Vaild Subject Code" << endl;
        }
    }
};

int Students::rollnoG = 4001;

int main()
{
    
    // STUDENT BY TEMPLATE COURSE 
 
    Students s1("Ram","BCAsem2");
    s1.displayDetails();
    cout<<"Name : "<<s1.getstudentname()<<endl;
    cout<<"Roll NO : "<<s1.getstudentrollno()<<endl;
    cout<<"Course : "<<s1.getstudentcourse()<<endl;
    cout<<"No of Subjects : "<<s1.getnumberofsubjects()<<endl;
    cout<<"Average MArks : "<<s1.getaveragemarks()<<endl;
    cout<<"Percentage : "<<s1.getpercentage()<<endl;
    s1.getsubject(105);
    s1.setobtainedmarks(102,56);
    s1.setobtainedmarks(105,36);
    s1.setobtainedmarks(107,96);
    s1.setobtainedmarks(103,59);
    s1.displayDetails();
    s1.changecoursesubject(3,"YYYYYYYYYYYYYYYYYYYYY",124,100,50);
    s1.displayDetails();
    Subject tmp = s1.getsubject(105);
    cout<<tmp.getsubname()<<endl;
    cout<<tmp.getsubcode()<<endl;
    cout<<tmp.getsubobtainedmarks()<<endl;
    cout<<tmp.getsubtotalmarks()<<endl;
 


 
    // STUDENT BY TEMPLEATE with mistakes 
    
    // Students s2("Ram","BCAsem2d");
    Students s2("Shyam","BCAsem2");
    s2.displayDetails();
    s2.setobtainedmarks(199,99); // Enter a valid subject code
    s2.setobtainedmarks(105,999); // Enter a valid subject marks 
    s2.setobtainedmarks(105,99); // Marks added
    s2.changecoursesubject(99,"YYYYYYYYYYYYYYYYYYYYY",124,100,50); // INVALIDE INDEX


    // STUDENT DATA BY CUSTOM COURSE AND SUBJECTS 

    Students s3("Peter" ,"BTech" , 6); // with no subject deatails and garbage random data
    s3.displayDetails(); 
    s3.changecoursesubject(1,"YYYYYYYYYYYYYYYYYYYYY",124,100,50);
    s3.changecoursesubject(2,"YYYYYYYYYYYYYYYYYYYYY",125,100,50);
    s3.changecoursesubject(3,"YYYYYYYYYYYYYYYYYYYYY",126,100,50);
    s3.changecoursesubject(4,"YYYYYYYYYYYYYYYYYYYYY",127,100,50);
    s3.changecoursesubject(5,"YYYYYYYYYYYYYYYYYYYYY",128,100,50);
    s3.changecoursesubject(6,"YYYYYYYYYYYYYYYYYYYYY",129,100,50);
    s3.changecoursesubject(99,"YYYYYYYYYYYYYYYYYYYYY",124,100,50); // INVALID
    s3.displayDetails(); 
    cout<<"Name : "<<s3.getstudentname()<<endl;
    cout<<"Roll NO : "<<s3.getstudentrollno()<<endl;
    cout<<"Course : "<<s3.getstudentcourse()<<endl;
    cout<<"No of Subjects : "<<s3.getnumberofsubjects()<<endl;
    cout<<"Average MArks : "<<s3.getaveragemarks()<<endl;
    cout<<"Percentage : "<<s3.getpercentage()<<endl;
    Subject tmp2 = s1.getsubject(105);
    cout<<tmp2.getsubname()<<endl;
    cout<<tmp2.getsubcode()<<endl;
    cout<<tmp2.getsubobtainedmarks()<<endl;
    cout<<tmp2.getsubtotalmarks()<<endl;

    // suggested changes to make the course Template and course Custom a seperate calss and use it in the Students calss 
    // the member function will be then as per the choice 
    // difffernt fuctions wil not be cluttered



    

    return 0;
}  