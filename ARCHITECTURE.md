 
# Fields 

- Student ID `AUTO`
- Roll Number `AUTO`
- Name 
- Date of Birth 
- Gender 
- Course 
- Section 
- No of Subjects
- Enrollement Year 
- Pending Fee

- Subject : 
	- SubName
	- SubCode
	- Total Marks 
	- Obtained Marks 
	- Credits

- contact
	- email
	- phone no 


- Address 
	- house
	- street
	- cuty
	- state
	- country
	- pincode


# Global or static variables 

- `int student_id_A = 1;   `
- `int rollno_assigner_initial = 1000;`

# Functions 



## Constructos

- Create Student Record `CUSTOM `
- Create Student Record `TEMPLATE` 

## Setters 

- set name 
- set DOB 
- set gender 
- set/change course  
- set section 
- set no of subject `CUSTOM ONLY `
- set enrollement Year 
- set pending fee
- set email 
- set phone no 
- set address 


## Getters 

- get student ID 
- get Roll no 
- get name
- get DOB
- get Gender
- get Course 
- get Section 
- get No of Subjects `BOTH`
- get Enrollement Year 
- get Pending Fee
- get Email
- get Phone No 
- get Address 



## -> Template Management `templates` : `namespace` ✓ ✕

- Struct `templateindex` : Name , N 

- `show template index` : cout the template index in table form , no return

- `void show_template(const std::string & template_name)` : prints the template data in table form and empties the heap

- `int create_template(const std::string & template_name , int number_of_subjects = 10)` : create template if not created return -1
	- `ofstream file_exists_check(const std::string & file_name, int number_of_subjects = -1)` : return file , empty file ptr
		- if number_of_subjects passed then : 	`add_template_index()`
		- if not then not called : `add_template_index()`
	- `Subject enter_and_return_sub()` : return Subject object , use `verifynmae(string name)` from subjects to check the string length < 20 entererd

- `delete_templatevoid delete_template(const std::string & template_name)` : deltetr templare  binary file & call `delte_template_index()` , use `<filesystem>` , if not exist then not deleted

- `Subject * return_template_data(const std::string & template_name)` : returns nullptr or pointer to heap data of the template name entered

- `templateindex give_template_data_at_index(int index)` : returns the struct at index from the temlape file, index must be vaild 

- `int give_number_of_subjects(const std::string & template_name)` : give number of subjects in index by template name index must be vaild


### Template Index 
	- Modifing
		- `void add_template_index(const std::string & template_name , int number_of_subjects)` : add tempalte index , if already exist do nohing 
		- `int do_template_exist(const std::string & template_name)` : if exists return the index and if not then -1
		- `void replace_template_index(const std::string & template_name , int number_of_subjects , int index)` :  if replaces the index nmae the index must be valid
		- `void delete_template_index(int index)` : deltes the template index from the index  if index is -1 returned by `do_template_exist()` it does nothing it returns
	- `void show_template_index()` : prints the templates available in table form 



## Records Management `recorddata` : `namespace`

### namespaces 

- `record`
- `show`
- `session`
- `fetch`

### variables 

- `std::string session_file_path` : path to session file `"../files/session_data"`
- `std::string record_file_path` : path to record file `"../files/record"`
- `int rollno_assigner = 1000` : the step value added to previous roll no assigner to assign to new courses

### Functions

- `int init_files()` : checks if session and record files exist by trying to open them `session::inti_session()` and `record::init_record()` ; returns 1 if it created the session and record file , if cant create record file gives -1 , if it only creates record file then returns 0, if cant create retrurns -1 , if nothing is created then 2; 
- `int connect(datafields::fields & data)` : to eneter the data in record and regsiter in session file ; 
	- do course exst will give -1 if not index if exists in session
	- for session if new course it will add if not exist , if exist it will increase the roll by 1 
	- then after these session , the new id and rolll no is init to data
	- now adding or updating data to record_file if recotd_file cant be opened it returns -1 , then checking the record file if exist then updates data if -1 then adds data

### record

- `int add_data(datafields::fields & data)` : appends the student data using   struct to the record_file with append mode — return 1 on success, -1 if file could not be opened

- `int update_data(datafields::fields & data)` : finds the index by do_exist and it will always be there as it is made for connect() updates the data and return 1 if file not open then 0 

- `int delete_data(datafields::fields & data)` : it will check if it exist by do_exist and if not return -1 if exists it will fil that struct in binary file with zero struct and return 1

- `int do_exists(datafields::fields & data)` : checks if exists or not by student_id if not exists  retrn -1 if size = 0 returns -1 , if file not opened returns -1 , if finede then return the index where the struct is located

- `int get_length()` : if file not opend then return 0 , find the size of size == 0 then returns 0; else length = size / sizeof(datafields::fields)

- `int init_record()` : creates a new or overwrite the binary dfiel of records return 1 if sucess , else 0

- `int check_duplicate(datafields::fields & data)` : checks the all records and compare fields values name , email , phone no , dob if all same then returns 1 as it is duplicate else -1

### fetch 

- `datafields::fields record_by_key(int key, bool flag = true)` : get a record by a key if key if true get by id else by roll no 

- `datafields::fields record_by_id(int student_id)` : returns the data searched by rollno , if not found or file not opneed empty data

- `datafields::fields record_by_rollno(int rollno)` :returns the data searched by student id  , if not found or file not opneed empty data

- `datafields::fields * all_record()` : gives the pointer to heap array struct of all the records return s null ptr if length is 0 , or file not opneded

- `datafields::fields * records_by_course(const std::string & course)` : check if the record exist in session 

- `int no_of_records_by_course(const std::string & course)` : scans entire record file and counts how many records, if zero records return 0

- `int export_csv_by_course(const std::string & course)` : exports two csv files stdents, subjects 
	- student contains all the fieldds except the sujects and each subject details 
	- the subjects one contained all details of subject identified by stuednt id 
	- return -1 if data not found,else create files in export folder with coourse name `<course>_students.csv` and `<course>_subjects.csv` 
	- if these cant be opened return 0 ,on sucess rerunr 1

- `int export_csv_all()` : same but exports all data in two files

### Session

- `int add_data(const std::string & course, int index)` : createes a new space in session data create course and assign it a new roll no batch range and add it in session for further return 0 if not fount , 

- `int update_data(const std::string & course, int index)` : read the current struct data and increases the roll number by 1 and appends it return 1 if ok , 0 if file not opened

- `int get_course_rollno(const std::string & course)` : rerun -1 if not exist if exists then give the roll no adjacent to course in the struct 

- `int do_course_exists(const std::string & course)` : move 8 byte from start to ignore student id and rollno assigner and searches the course by course if fount then give the index else -1

- `datafields::sub_rollno * get_data()` :move 8 byte from start to ignore student id and rollno assigner and rerurn heap allocated if no data then nullptr

- `int get_length()` : move 8 byte from start to ignore student id and rollno assigner and count the number of courses regestered in session

- `int get_student_id_A()` 

- `int init_rollno_for_new_course()` : reads current roll number base from byte `4` of session file rertun old value as init roll no and assign a new roll noo by `init_roll + rollno_assigner`

- `void inti_session()` : creates or overwrite a new session file in path , and from global variables add student_id_A and roll no base


### show 

> To prints the data


- `int all_records(int flag = 0)` : fetches all records via `fetch::all_record()` and displays them if nullptr return 0 , `flag = 0` shows student data table skip whrer id = 0 no subject record display,`flag = 1` prints subject  table with a student id , 1 on success

- `int records_by_course(const std::string & course, int flag = 0)` : same but course specific 

- `int session_data()` : reads the data from session file and display the sessioon student_id_A the rollnoinit , the struct of course and current roll no 




## -> Additional Functions `additionalfunctions` : `namespace`

- `float get_percentage(Subject * sub , int number_of_subjects )` : enters a `Subject` objects array if no of subject = 0 rturns -1 , if sum of obtained marks = 0 , else return float percentage
- `float get_percentage_each(Subject sub)` : takes a single `Subject` object and return percentage , total marks can never be zero as default = 100 until explicitly set if 0 then -1 , returns float percentage 
- `char get_cgpa(Subject * sub , int number_of_subjects)` : return cgpa value in float if number of subject is zero then cretit points -1 and returns  -1 
- `bool get_passstatus(Subject * sub , int number_of_subjects)` : returns `flase` if no of subject is zero , and `true` or `false` if percentage >= 40.0f 
- `int get_gradepoint_each(Subject sub)` : use each subject percentag and give grade point if `get_percantage_each()` = -1 then return -1
- `int get_creditpoint(Subject * sub , int number_of_subjects) ` : if numebr of subject = 0 return -1 else creditpoints
- `float get_averagemarks(Subject * sub , int number_of_subjects )` : returns float average marks if no of subjects is zero returns -1

## -> Subjects `Subject` : `class`

- get sub 
	- sub.get name 
	- sub.get code
	- sub.get total marks 
	- sub.get obtained marks 
	- sub.get credits 

- change sub 
	- sub.change name 
	- sub.change code
	- sub.change total marks 
	- sub.change obtained marks 
	- sub.change credits 

- `static bool verifyname(const string & name)`: returns true if size < 20 else false

## Validations 

