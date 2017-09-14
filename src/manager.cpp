#include "manager.h"

using namespace std;

//Insert Student
void Manager::_student_insert() {
	Student s;
	//Read the key attributes from console
	readwrite.read(&s);
	//Try insert
	Student* sp = database->student_insert(s);
	//If failed then print
	if (!sp) cout << "Student already exist" << endl;
	//Else read the non-key attributes
	else readwrite.read(sp,false);
}

//Modify Student
void Manager::_student_modify() {
	Student s;
	//Read the key attributes from console
	readwrite.read(&s);
	//Try modify
	Student* sp = database->student_modify(s);
	//If failed then print
	if (!sp) cout << "Student not exist" << endl;
	//Else modify the non-key attributes
	else readwrite.read(sp,false);
}

//Delete Student
void Manager::_student_delete() {
	Student s;
	//Read the key attributes from console
	readwrite.read(&s);
	//Try delete
	if (!database->student_delete(s)) {
		cout << "Student not exist" << endl;
		return;
	}
	//Delete all the relevant CourseSelections
	const CourseSelection* csp;
	while (csp=database->list_courses_of(s)) database->selection_drop(*csp);
	//Print
	cout << "Deletion of student record successful" << endl;
}

//Query Student
void Manager::_student_query() {
	Student s;
	//Read the key attributes from console
	readwrite.read(&s);
	//Try qurey
	const Student* sp = database->student_query(s);
	//If failed then print
	if (!sp) cout << "Student not exist" << endl;
	//Else write the Student Record to console
	else readwrite.write(sp);
}

//Insert Course
void Manager::_course_insert() {
	Course c;
	//Read the key attributes from console
	readwrite.read(&c);
	//Try insert
	Course* cp = database->course_insert(c);
	//If failed then print
	if (!cp) cout << "Course already exist" << endl;
	//Else read the non-key attributes
	else readwrite.read(cp,false);
}

//Modify Course
void Manager::_course_modify() {
	Course c;
	//Read the key attributes from console
	readwrite.read(&c);
	//Try modify
	Course* cp = database->course_modify(c);
	//If failed then print
	if (!cp) cout << "Course not exist" << endl;
	//Else modify the non-key attributes
	else readwrite.read(cp,false);
}

//Delete Course
void Manager::_course_delete() {
	Course c;
	//Read the key attributes from console
	readwrite.read(&c);
	//Try delete
	if (!database->course_delete(c)) {
		cout << "Course not exist" << endl;
		return;
	}
	//Delete all the relevant CourseSelections
	const CourseSelection* csp;
	while (csp=database->list_students_of(c)) database->selection_drop(*csp);
	//Print
	cout << "Deletion of course record successful" << endl;
}

//Query Course
void Manager::_course_query() {
	Course c;
	//Read the key attributes from console
	readwrite.read(&c);
	//Try query
	const Course* cp = database->course_query(c);
	//If failed then print
	if (!cp) cout << "Course not exist" << endl;
	//Else read the non-key attributes
	else readwrite.write(cp);
}

//Add CourseSelection
void Manager::_registration_add() {
	//Read the key attribute of Student from console
	Student s;
	readwrite.read(&s);
	//Check exist
	if (!database->student_query(s)) {
		cout << "Student not exist" << endl;
		return;
	}
	//Read the key attribute of Course from console
	Course c;
	readwrite.read(&c);
	//Check exist
	if (!database->course_query(c)) {
		cout << "Course not exist" << endl;
		return;
	}
	//Construct CourseSelection from Student and Course
	CourseSelection cs(s,c);
	//Try add
	CourseSelection* csp = database->selection_add(cs);
	//Print result
	if(!csp) cout << "The studet already registered the course" << endl;
	else cout << "Add course successful" << endl;
}

//Drop CourseSelection
void Manager::_registration_drop() {
	//Read the key attribute of Student from console
	Student s;
	readwrite.read(&s);
	//Check exist
	if (!database->student_query(s)) {
		cout << "Student not exist" << endl;
		return;
	}
	//Read the key attribute of Course from console
	Course c;
	readwrite.read(&c);
	//Check exist
	if (!database->course_query(c)) {
		cout << "Course not exist" << endl;
		return;
	}
	//Construct CourseSelection from Student and Course
	CourseSelection cs(s,c);
	//Try delete
	//Print result
	if(database->selection_drop(cs)) cout << "Drop course successful" << endl;
	else cout << "The registration record not exist" << endl;
}

//Modify CourseSelection
void Manager::_registration_modify() {
	//Read the key attribute of Student from console
	Student s;
	readwrite.read(&s);
	//Check exist
	if (!database->student_query(s)) {
		cout << "Student not exist" << endl;
		return;
	}
	//Read the key attribute of Course from console
	Course c;
	readwrite.read(&c);
	//Check exist
	if (!database->course_query(c)) {
		cout << "Course not exist" << endl;
		return;
	}
	//Construct CourseSelection from Student and Course
	CourseSelection cs(s,c);
	//Try modify
	CourseSelection* csp = database->selection_modify(cs);
	//If failed then print
	if(!csp) cout << "The registration record not exist" << endl;
	//Else read the non-key attributes from the console
	else readwrite.read(csp,false);
}

//Query CourseSeleection
void Manager::_registration_query() {
	//Read the key attribute of Student from console
	Student s;
	readwrite.read(&s);
	//Check exist
	if (!database->student_query(s)) {
		cout << "Student not exist" << endl;
		return;
	}
	//Read the key attribute of Course from console
	Course c;
	readwrite.read(&c);
	//Check exist
	if (!database->course_query(c)) {
		cout << "Course not exist" << endl;
		return;
	}
	//Construct CourseSelection from Student and Course
	CourseSelection cs(s,c);
	//Try query
	const CourseSelection* csp = database->selection_query(cs);
	//If failed then print
	if(!csp) cout << "The registration record not exist" << endl;
	//Else write the CourseSelection to the console
	else readwrite.write(csp);
}

//List all Students
void Manager::_report_student() {
	//Set file
	ofstream fileout;
	fileout.open("Students.html",std::ofstream::out | std::ofstream::trunc);
	//Set a wasted ostream to accept the remind from ReadWrite
	ofstream wastedout;
	//Construct a new ReadWrite for file output
	ReadWrite rwfile(cin,fileout,wastedout);
	Student s;
	//If no Student
	if (database->student_size()==0) {
		//Specialized for the case of no Student
		rwfile.write_html_head(&s,false,true);
		//Close file and print result
		fileout.close();
		cout << "Output Successful" << endl;
		return;
	}
	//Write head and name of the table in html file
	rwfile.write_html_head(&s);
	rwfile.write_html_name(&s);
	//List all students
	const Student* sp;
	//Write each to file
	while (sp=database->list_student()) rwfile.write_html_record(sp);
	//Write the end of html file
	rwfile.write_html_end();
	//Close file and print result
	fileout.close();
	cout << "Output Successful" << endl;
}

//List all Course
void Manager::_report_course() {
	//Set file
	ofstream fileout;
	fileout.open("Courses.html",std::ofstream::out | std::ofstream::trunc);
	//Set a wasted ostream to accept the remind from ReadWrite
	ofstream wastedout;
	ReadWrite rwfile(cin,fileout,wastedout);
	Course c;
	//If no Course
	if (database->course_size()==0) {
		//Specialized for the case of no Course
		rwfile.write_html_head(&c,false,true);
		//Close file and print result
		fileout.close();
		cout << "Output Successful" << endl;
		return;
	}
	//Write head and name of the table in html file
	rwfile.write_html_head(&c);
	rwfile.write_html_name(&c);
	//List all courses
	const Course* cp;
	//Write each to file
	while (cp=database->list_course()) rwfile.write_html_record(cp);
	//Write the end of html file
	rwfile.write_html_end();
	//Close file and print result
	fileout.close();
	cout << "Output Successful" << endl;
}

//List all Courses of a Student
void Manager::_report_courses_of() {
	Student s;
	//Read a Stundent from console
	readwrite.read(&s);
	//Check exist
	const Student* sp = database->student_query(s);
	if (!sp) {
		cout << "Student not exist" << endl;
		return;
	}
	//Set file
	ofstream fileout;
	//Set filename by Student Record
	ostringstream filenamess;
	filenamess << *(s.tuple[0]);
	string filename = filenamess.str() + ".html";
	fileout.open(filename.c_str(),std::ofstream::out | std::ofstream::trunc);
	//Set a wasted ostream to accept the remind from ReadWrite
	ofstream wastedout;
	ReadWrite rwfile(cin,fileout,wastedout);
	//If no registered Course
	if (!database->list_courses_of(s)) {
		//Specialized for the case of no registered Course
		rwfile.write_html_head(sp,true,true);
		//Close file and print result
		fileout.close();
		cout << "Output Successful" << endl;
		return;
	} 
	//Finish that listing process by traversal
	else while(database->list_courses_of(s));
	//Write head and name of the table in html file
	rwfile.write_html_head(sp,true);
	Course c;
	CourseSelection cs;
	ExtendedCourse ec(c,cs);
	//Note that the table in html file is of ExtendedCourse type
	rwfile.write_html_name(&ec);
	const CourseSelection* csp;
	//List all courses of a Student
	while (csp=database->list_courses_of(s)) {
		//Find the corresponding Course
		Course c(*csp);
		const Course* cp = database->course_query(c);
		if(cp) {
			//Construct the corresponding ExtendedCourse by Course and CourseSelection
			ExtendedCourse ec(*cp,*csp);
			//Write each to file
			rwfile.write_html_record(&ec);
		}
	}
	//Write the end of html file
	rwfile.write_html_end();
	//Close file and print result
	fileout.close();
	cout << "Output Successful" << endl;
}

//List all Students of a Course
void Manager::_report_students_of() {
	Course c;
	//Read a Course from console
	readwrite.read(&c);
	//Check exist
	const Course* cp = database->course_query(c);
	if (!cp) {
		cout << "Course not exist" << endl;
		return;
	}
	//Set file
	ofstream fileout;
	//Set filename by Course Record
	ostringstream filenamess;
	filenamess << *(c.tuple[0]);
	string filename = filenamess.str() + ".html";
	fileout.open(filename.c_str(),std::ofstream::out | std::ofstream::trunc);
	//Set a wasted ostream to accept the remind from ReadWrite
	ofstream wastedout;
	ReadWrite rwfile(cin,fileout,wastedout);
	//If no registered Student
	if (!database->list_students_of(c)) {
		//Specialized for the case of no registered Student
		rwfile.write_html_head(cp,true,true);
		//Close file and print result
		fileout.close();
		cout << "Output Successful" << endl;
		return;
	}
	//Finish that listing process by traversal
	else while(database->list_students_of(c));
	//Write head and name of the table in html file
	rwfile.write_html_head(cp,true);
	Student s;
	CourseSelection cs;
	ExtendedStudent es(s,cs);
	//Note that the table in html file is of ExtendedStudent type
	rwfile.write_html_name(&es);
	const CourseSelection* csp;
	//List all Students of a Course
	while (csp=database->list_students_of(c)) {
		//Find the corresponding Student
		Student s(*csp);
		const Student* sp = database->student_query(s);
		if (sp) {
			//Construct the corresponding ExtendedStudent by Course and CourseSelection
			ExtendedStudent es(*sp,*csp);
			//Write each to file
			rwfile.write_html_record(&es);
		}
	}
	//Write the end of html file
	rwfile.write_html_end();
	//Close file and print result
	fileout.close();
	cout << "Output Successful" << endl;
}

//Save to file
void Manager::_file_save() {
	//Buffer
	char input[32];
	//Print reminder for input
	cout << "Enter the filename: ";
	//Get filename from console
	cin.getline(input,32);
	//Set file
	ofstream fileout;
	//Overwrite the file
	fileout.open(input,std::ofstream::out | std::ofstream::trunc);
	//Set a wasted ostream to accept the remind from ReadWrite
	ofstream wastedout;
	//ReadWrite for file saving
	ReadWrite rwfile(cin,fileout,wastedout);
	//Format for the file
	//List all Student, Course, CourseSelection
	//With a total number of each type to check validity when loading
	//With a tag for each record to check validity when loading
	//Write all Student
	const Student* sp;
	fileout << database->student_size() << endl;
	while (sp=database->list_student()) rwfile.writefile(sp);
	//Write all Course
	const Course* cp;
	fileout << database->course_size() << endl;
	while (cp=database->list_course()) rwfile.writefile(cp);
	//Write all CourseSelection
	const CourseSelection* csp;
	fileout << database->selection_size() << endl;
	while (csp=database->list_selection()) rwfile.writefile(csp);
	//Close file and print result
	fileout.close();
	cout << "Saving successful" << endl;
}

//Load from file
void Manager::_file_load() {
	//Buffer
	char input[32];
	//Print reminder for input
	cout << "Enter the filename: ";
	//Get filename from console
	cin.getline(input,32);
	//Set file
	ifstream filein;
	filein.open(input);
	//Check file exist
	if(!filein.is_open()) {
		cout << "Error: Load File Error (File not exist / File Corrupted / Incorrect Format)" << endl;
		return;
	}
	//Set a wasted ostream to accept the remind from ReadWrite
	ofstream wastedout;
	//ReadWrite for file loading
	ReadWrite rwfile(filein,cout,wastedout);
	//Allocate a new DataBase
	DataBase* newdatabase = new DataBase;
	//Count number to check file validity
	int total;
	int count;
	//Read Student Table
	//Read total number of Student Record
	if(!filein.getline(input,32)) {
		cout << "Loading failed" << endl;
		delete newdatabase;
		return;
	}
	//Set counter
	total = atoi(input);
	count = 0;
	//Read Student Record
	//With tag 's'
	while (filein.getline(input,32)&&input[0]=='s'&&count<total) {
		Student s;
		rwfile.read(&s);
		Student* sp = newdatabase->student_insert(s);
		if (!sp) {
			cout << "Loading failed" << endl;
			delete newdatabase;
			return;
		}
		rwfile.read(sp,false);
		++count;
	}
	//Check we read all
	if(count!=total) {
		cout << "Loading failed" << endl;
		delete newdatabase;
		return;
	}
	//Read Course Table
	//The number of Courses is already in the buffer
	total = atoi(input);
	count = 0;
	//Read Course Record
	//With tag 'c'
	while (filein.getline(input,32)&&input[0]=='c'&&count<total) {
		Course c;
		rwfile.read(&c);
		Course* cp = newdatabase->course_insert(c);
		if (!cp) {
			cout << "Loading failed" << endl;
			delete newdatabase;
			return;
		}
		rwfile.read(cp,false);
		++count;
	}
	//Check we read all
	if(count!=total) {
		cout << "Loading failed" << endl;
		delete newdatabase;
		return;
	}
	//Read CourseSelection Table
	//The number of Courses is already in the buffer
	total = atoi(input);
	count = 0;
	//Flag for good state
	bool isgood = true;
	//Read CourseSelection Record
	//With tag 'r'
	while (filein.getline(input,32)&&input[0]=='r'&&count<total) {
		//Simialar process as reading from console
		Student s;
		rwfile.read(&s);
		if(!newdatabase->student_query(s)) isgood = false;
		Course c;
		rwfile.read(&c);
		if(!newdatabase->course_query(c)) isgood = false;
		CourseSelection cs(s,c);
		CourseSelection* csp = newdatabase->selection_add(cs);
		if(!csp) isgood = false;
		rwfile.read(csp,false);
		//If not in good state then abort
		if(!isgood) {
			cout << "Loading failed" << endl;
			delete newdatabase;
			return;
		}
		++count;
	}
	//Check we read all
	if(count!=total) {
		cout << "Loading failed" << endl;
		delete newdatabase;
		return;
	}
	//Close file and print result
	filein.close();
	//Swap the DataBase when loading successfully
	delete database;
	database = newdatabase;
	cout << "Loading successful" << endl;
}