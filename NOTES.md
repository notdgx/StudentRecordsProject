# Errors : {Solved}

```
dx Students ▸ g++ source/*.cpp -I headers/ -o run 
source/datafile.cpp: In function ‘int recorddata::show::single_by_rollno(int, int)’:
source/datafile.cpp:717:5: warning: control reaches end of non-void function [-Wreturn-type]
  717 |     }
      |     ^
source/templates.cpp: In function ‘std::ofstream templates::file_exists_check(const string&, int)’:
source/templates.cpp:163:5: warning: control reaches end of non-void function [-Wreturn-type]
  163 |     }
      |     ^
source/templates.cpp: In function ‘Subject* templates::return_template_data(const string&)’:
source/templates.cpp:190:5: warning: control reaches end of non-void function [-Wreturn-type]
  190 |     }
      |     ^
/usr/bin/ld: /tmp/ccXGjNLh.o: warning: relocation against `student_id_A' in read-only section `.text'
/usr/bin/ld: /tmp/ccPSVtUK.o: in function `recorddata::session::init_rollno_for_new_course()':
datafile.cpp:(.text+0x5b5a): undefined reference to `recorddata::rollno_assigner'
/usr/bin/ld: /tmp/ccPSVtUK.o: in function `recorddata::session::init_session()':
datafile.cpp:(.text+0x5c60): undefined reference to `student_id_A'
/usr/bin/ld: datafile.cpp:(.text+0x5c7e): undefined reference to `rollno_assigner_initial'
/usr/bin/ld: /tmp/ccXGjNLh.o: in function `main':
main.cpp:(.text+0x1e): undefined reference to `student_id_A'
/usr/bin/ld: main.cpp:(.text+0x28): undefined reference to `rollno_assigner_initial'
/usr/bin/ld: main.cpp:(.text+0x32): undefined reference to `recorddata::rollno_assigner'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
```

# Problems : 

- total number of records is giving including the deleted one 🟢
- in recent records it is giving 5 but if deleted then not showin them 🛑
- in show by roll no if not a valid roll no giving the recent record details 🟢
- if roll no is entered as char continous loop 
- space is exclude every where ther is cin string 🟢
- in every tempalte no fistst subject name 🟢
- if in delete record put the char it just loop 🟢
- the export by course doesnt show any message on success 🟢
- add full address on opening a record and showing it 🟢
- on modifing record the details not saved 
- and show record is showing the previous 
- and if new course updated then the subject details not showing any message if n = 0
- can t change n when custom sourse added
- make the subject details modifiable if not in template
- and if then only obtained marks only
- we can change n even if template is used
- if the record is already a custom course the one can modify it 
- whilw switching to template subjcets can be changed
- 


# Features 
- if template name is already exist and added in create tempalte then overwrite 
- 