#include <iostream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "database.h"
#include "readwrite.h"

//Class Manager
//Manage all the user operations
#ifndef MANAGER
#define MANAGER

using namespace std;

class Manager {
public:
	//Constructor
	//With one istream parameter, two ostream parameter to initialize a ReadWrite Instance
	//Practially will always be cin, cout, cout
	Manager(std::istream& i, std::ostream& o, std::ostream& r)
		:readwrite(i,o,r) {database = new DataBase;}
	//Destructor
	//Destroy the DataBase
	~Manager() {delete database;}
public:
	//All user operations
	//Their function pointers are used by Class Menu
	void _student_insert();
	void _student_modify();
	void _student_delete();
	void _student_query();
	void _course_insert();
	void _course_modify();
	void _course_delete();
	void _course_query();
	void _registration_add();
	void _registration_drop();
	void _registration_modify();
	void _registration_query();
	void _report_student();
	void _report_course();
	void _report_courses_of();
	void _report_students_of();
	void _file_save();
	void _file_load();
	void _exit() {exit(0);}
private:
	//DataBase Pointer
	//Dynamically allocated so that can be replased with loading from file
	DataBase* database;
	//ReadWrite
	ReadWrite readwrite;
};

#endif