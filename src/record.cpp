#include "record.h"
#include <iostream>

//Destructor of Record
Record::~Record() {
	//Delete each pointer and set to null
	for (int i=0; i<RECORD_SIZE; ++i) {
		delete tuple[i];
		tuple[i] = NULL;
	}
	//Delete array and set to null
	delete[] tuple;
	tuple = NULL;
}

//Overloaded operator< of Record
bool Record::operator< (const Record& r) const {
	//Check validity of key attribute pointers
	if (!(tuple[0]&&r.tuple[0])) std::cerr << "Null Key Pointer.";
	//Compare the key attributes
	return (*(tuple[0])<*(r.tuple[0]));
}

//Overloaded operator== of Record
bool Record::operator== (const Record& r) const {
	//Check validity of key attribute pointers
	if (!(tuple[0]&&r.tuple[0])) std::cerr << "Null Key Pointer.";
	//Compare the key attributes
	return (*(tuple[0])==*(r.tuple[0]));
}

//Virtual hash_func() of Record
int Record::hash_func(int tlength) const {
	//Check validity of key attribute pointer
	if(!tuple[0]) std::cerr << "Null Key Pointer.";
	//Call the hash_func() of the key attribute
	return tuple[0]->hash_func(tlength);
}

//Overloaded operator= of Record
Record& Record::operator= (const Record& r) {
	//Copy each attribute if not null
	for (int i=0; i<RECORD_SIZE; ++i) {
		if (tuple[i]&&r.tuple[i]) *(tuple[i])=*(r.tuple[i]);
	}
	//Resize
	size = r.size;
	return (*this);
}

//Default Constructor of Student
//Specify the kinds of attributes
Student::Student():Record() {
	tuple[0] = new StudentID;
	tuple[1] = new StudentName;
	tuple[2] = new Year;
	tuple[3] = new Gender;
	size = 4;
}

//Conversion Constructor of Student
//Specify the kinds of attributes
//And copy the key attribute
Student::Student(const CourseSelection& cs) {
	tuple[0] = new StudentID;
	tuple[1] = new StudentName;
	tuple[2] = new Year;
	tuple[3] = new Gender;
	size = 4;
	*(tuple[0]) = *(cs.tuple[0]);
}

//Default Constructor of Course
//Specify the kinds of attributes
Course::Course():Record() {
	tuple[0] = new CourseCode;
	tuple[1] = new CourseName;
	tuple[2] = new Credit;
	size = 3;
}

//Conversion Constructor of Course
//Specify the kinds of attributes
//And copy the key attribute
Course::Course(const CourseSelection& cs) {
	tuple[0] = new CourseCode;
	tuple[1] = new CourseName;
	tuple[2] = new Credit;
	size = 3;
	*(tuple[0]) = *(cs.tuple[1]);
}

//Default Constructor of CourseSelection
//Specify the kinds of attributes
CourseSelection::CourseSelection():Record() {
	tuple[0] = new StudentID;
	tuple[1] = new CourseCode;
	tuple[2] = new ExamMark;
	size = 3;
}

//Constructor of CourseSelection
//Specify the kinds of attributes
//Copy the key and sub-key from Student and Course
CourseSelection::CourseSelection(const Student& s, const Course& c):Record() {
	tuple[0] = new StudentID;
	tuple[1] = new CourseCode;
	tuple[2] = new ExamMark;
	size = 3;
	*(tuple[0]) = *(s.tuple[0]);
	*(tuple[1]) = *(c.tuple[0]);
}

//Overloaded operator< of CourseSelection
bool CourseSelection::operator< (const Record& r) const {
	//Check Validity
	if (!(tuple[0]&&r.tuple[0])) std::cerr << "Null Key Pointer.";
	if (!(tuple[1]&&r.tuple[1])) std::cerr << "Null Key Pointer.";
	//Compare the key and the sub-key
	return (*(tuple[0])<*(r.tuple[0]))||((*(tuple[0])==*(r.tuple[0]))&&(*(tuple[1])<*(r.tuple[1])));
}

//Overloaded operator== of CourseSelection
bool CourseSelection::operator== (const Record& r) const {
	//Check Validity
	if (!(tuple[0]&&r.tuple[0])) std::cerr << "Null Key Pointer.";
	if (!(tuple[1]&&r.tuple[1])) std::cerr << "Null Key Pointer.";
	//Compare the key and the sub-key
	return (*(tuple[0])==*(r.tuple[0]))&&(*(tuple[1])==*(r.tuple[1]));
}

//Default Constructor of StudentIndex
//Specify the kinds of attributes
StudentIndex::StudentIndex():pointer(NULL),Record() {
	tuple[0] = new StudentID;
	size = 1;
}

//Conversion Constructor of StudentIndex
//Specify the kinds of attributes
//And copy the key attribute
StudentIndex::StudentIndex(const Student& s):pointer(NULL),Record() {
	tuple[0] = new StudentID;
	size = 1;
	*(tuple[0]) = *(s.tuple[0]);
}

//Conversion Constructor of StudentIndex
//Specify the kinds of attributes
//Copy the key attribute and the pointer
StudentIndex::StudentIndex(const CourseSelection* csp):Record() {
    tuple[0] = new StudentID;
    *(tuple[0]) = *(csp->tuple[0]);
	pointer = csp;
	size = 1;
}

//Default Constructor of CourseIndex
//Specify the kinds of attributes
CourseIndex::CourseIndex():pointer(NULL),Record() {
	tuple[0] = new CourseCode;
	size = 1;
}

//Conversion Constructor of CourseIndex
//Specify the kinds of attributes
//And copy the key attribute
CourseIndex::CourseIndex(const Course& c):pointer(NULL),Record() {
	tuple[0] = new CourseCode;
	size = 1;
	*(tuple[0]) = *(c.tuple[0]);
}

//Conversion Constructor of CourseIndex
//Specify the kinds of attributes
//Copy the key attribute and the pointer
CourseIndex::CourseIndex(const CourseSelection* csp):Record() {
    tuple[0] = new CourseCode;
    *(tuple[0]) = *(csp->tuple[1]);
	pointer = csp;
	size = 1;
}

//Conversion Constructor of ExtendedStudent
//Specify the kinds of attributes
//Copy all the relevant attributes
ExtendedStudent::ExtendedStudent(const Student& s, const CourseSelection& cs):Record() {
	tuple[0] = new StudentID;
	tuple[1] = new StudentName;
	tuple[2] = new Year;
	tuple[3] = new Gender;
	tuple[4] = new ExamMark;
	size = 5;
	*(tuple[0]) = *(s.tuple[0]);
	*(tuple[1]) = *(s.tuple[1]);
	*(tuple[2]) = *(s.tuple[2]);
	*(tuple[3]) = *(s.tuple[3]);
	*(tuple[4]) = *(cs.tuple[2]);
}

//Conversion Constructor of ExtendedCourse
//Specify the kinds of attributes
//Copy all the relevant attributes
ExtendedCourse::ExtendedCourse(const Course& c, const CourseSelection& cs):Record() {
	tuple[0] = new CourseCode;
	tuple[1] = new CourseName;
	tuple[2] = new Credit;
	tuple[3] = new ExamMark;
	size = 4;
	*(tuple[0]) = *(c.tuple[0]);
	*(tuple[1]) = *(c.tuple[1]);
	*(tuple[2]) = *(c.tuple[2]);
	*(tuple[3]) = *(cs.tuple[2]);
}