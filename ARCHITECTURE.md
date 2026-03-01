 
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

- email
- phone no 
- Address 


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


## Show Details 

- show all details 
- show student details 
- show subjects details 

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


- Template Index 
	- Modifing
		- `void add_template_index(const std::string & template_name , int number_of_subjects)` : add tempalte index , if already exist do nohing 
		- `int do_template_exist(const std::string & template_name)` : if exists return the index and if not then -1
		- `void replace_template_index(const std::string & template_name , int number_of_subjects , int index)` :  if replaces the index nmae the index must be valid
		- `void delete_template_index(int index)` : deltes the template index from the index  if index is -1 returned by `do_template_exist()` it does nothing it returns
	- `void show_template_index()` : prints the templates available in table form 



## Records Management 

- show records from `record.csv
- add student data object record to `record.csv
- fetch student record data and set to temp running object to `record.csv

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

