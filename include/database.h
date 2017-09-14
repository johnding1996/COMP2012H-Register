#include <iostream>
#include "attribute.h"
#include "record.h"
#include "doublylinkedlist.h"
#include "hashtable.h"

//Symbolic constant of the number of buckets of Student HashTable, so as StudentIndex HashTable
#ifndef STUDENT_HASHTABLE_LENGTH
#define STUDENT_HASHTABLE_LENGTH 29
#endif

//Symbolic constant of the number of buckets of Course HashTable, so as CourseIndex HashTable
#ifndef COURSE_HASHTABLE_LENGTH
#define COURSE_HASHTABLE_LENGTH 29
#endif

//Class DataBase
//Manage all storage and data operations
//All functions directly used by Manager
#ifndef DATABASE
#define DATABASE

using namespace std;

//Class DataBase
class DataBase {
public:
	//Consturctor
	//Initialize every HashTable, DoublyLinkedList, and their Iterators
	//Initialize isListing to false
	DataBase():student(),course(),selection(),student_id(),course_id(),
		it_student(student.begin()),it_course(course.begin()),it_selection(selection.begin()),
		it_sid(student_id.begin()),it_cid(course_id.begin()),isListing(false),
		ddl_student(new DoublyLinkedList<Student>), it_ddl_student(ddl_student->begin()),
		ddl_course(new DoublyLinkedList<Course>), it_ddl_course(ddl_course->begin()),
		ddl_selection(new DoublyLinkedList<CourseSelection>), it_ddl_selection(ddl_selection->begin()) {}
	//Destructor
	//Delete all pointers to DoublyLinkedList
	~DataBase() {
		delete ddl_student;
		delete ddl_course;
		delete ddl_selection;
	}
public:
	//Insert Student
	Student* student_insert(const Student& s) {return student.insert(s);}
	//Modify Student
	Student* student_modify(const Student& s) {return student.find(s);}
	//Delete Student
    bool student_delete(const Student& s) {return student.remove(s);}
	//Query Student
    const Student* student_query(const Student& s) {return student.find(s);}
	//Insert Course
	Course* course_insert(const Course& c) {return course.insert(c);}
	//Modify Course
	Course* course_modify(const Course& c) {return course.find(c);}
	//Delete Course
    bool course_delete(const Course& c) {return course.remove(c);}
   	//Query Course
    const Course* course_query(const Course& c) {return course.find(c);}
    //Add CourseSelection
    CourseSelection* selection_add(const CourseSelection& cs);
    //Drop CourseSelection
    bool selection_drop(const CourseSelection& cs);
    //Modify CourseSelection (ExamMark)
    CourseSelection* selection_modify(const CourseSelection& cs) {return selection.find(cs);}
    //Query CourseSelection
    const CourseSelection* selection_query(const CourseSelection& cs) {return selection.find(cs);}
    //List all Students
    const Student* list_student();
    //List all Courses
    const Course* list_course();
    //List all CourseSelections
    const CourseSelection* list_selection();
    //List all Courses of a Student
    const CourseSelection* list_courses_of(const Student& s);
    //List all Students of a Course
    const CourseSelection* list_students_of(const Course& c);
    //Return Student HashTable Size
	int student_size() {return student.size();}
    //Return Course HashTable Size
	int course_size() {return course.size();}
    //Return CourseSelection DoublyLinkedList Size
	int selection_size() {return selection.size();}
private:
	//HashTables and DoublyLikedLists
	HashTable<Student,STUDENT_HASHTABLE_LENGTH> student;
	HashTable<Course,COURSE_HASHTABLE_LENGTH> course;
	DoublyLinkedList<CourseSelection> selection;
	HashTable<StudentIndex,STUDENT_HASHTABLE_LENGTH> student_id;
	HashTable<CourseIndex,COURSE_HASHTABLE_LENGTH> course_id;
	//Their Iterators
	HashTable<Student,STUDENT_HASHTABLE_LENGTH>::Iterator it_student;
	HashTable<Course,COURSE_HASHTABLE_LENGTH>::Iterator it_course;
	DoublyLinkedList<CourseSelection>::Iterator it_selection;
    HashTable<StudentIndex,STUDENT_HASHTABLE_LENGTH>::Iterator it_sid;
	HashTable<CourseIndex,COURSE_HASHTABLE_LENGTH>::Iterator it_cid;
	//State flag of listing operations
	bool isListing;
	//Temporary DoublyLinkedLists and their Iterators
	DoublyLinkedList<Student>* ddl_student;
	DoublyLinkedList<Student>::Iterator it_ddl_student;
	DoublyLinkedList<Course>* ddl_course;
	DoublyLinkedList<Course>::Iterator it_ddl_course;
	DoublyLinkedList<CourseSelection>* ddl_selection;
	DoublyLinkedList<CourseSelection>::Iterator it_ddl_selection;
};

#endif