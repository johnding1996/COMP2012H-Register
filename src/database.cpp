#include "database.h"

using namespace std;

//Add CourseSelection
CourseSelection* DataBase::selection_add(const CourseSelection& cs) {
	//Insert CourseSelection to DoublyLinkedList
	CourseSelection* csp = selection.insert(cs);
	//If fail since repeated, return null
	if (!csp) return NULL;
	//Else construct StudentIndex and CourseIndex Records by this CourseSelection
	StudentIndex sid(csp);
	CourseIndex cid(csp);
	//Insert them to correspoing HashTable
	//Since allow repitition, always succeed
	student_id.insert(sid,true);
	course_id.insert(cid,true);
	//Return the allocated pointer
	return csp;
}

//Drop CourseSelection
bool DataBase::selection_drop(const CourseSelection& cs) {
	//Find that CourseSelection
	CourseSelection* csp = selection.find(cs);
	if(!csp) return false;
	//Construct StudentIndex and CourseIndex by this CourseSelection
	StudentIndex sid(csp);
	CourseIndex cid(csp);
	//Try Remove this CourseSelection
	if(!selection.remove(cs)) return false;
	//Use Iterator to find corresponding StudentIndex
	HashTable<StudentIndex,STUDENT_HASHTABLE_LENGTH>::Iterator sid_it = student_id.begin(sid);
	StudentIndex* sid_p;
	while (sid_it != student_id.end(sid))
		//Find next, if not null
		if(sid_p = student_id.find(sid,sid_it))
			//If it points to this CourseSelection, then delete it
			if(sid_p->pointer==csp) student_id.remove_prev(sid_it);
	//Use Iterator to find corresponding CourseIndex
	HashTable<CourseIndex,COURSE_HASHTABLE_LENGTH>::Iterator cid_it = course_id.begin(cid);
	CourseIndex* cid_p;
	while (cid_it != course_id.end(cid))
		//Find next, if not null
		if(cid_p = course_id.find(cid,cid_it))
			//If it points to this CourseSelection, then delete it
			if(cid_p->pointer==csp) course_id.remove_prev(cid_it);
	//Return true at the end
	return true;
}

//List all the Students
const Student* DataBase::list_student() {
	//If not Listing, Initialize a listing process
	if(!isListing) {
		isListing = true;
		//Replace the Student DoublyLinkedList by a new one
		delete ddl_student;
		ddl_student = new DoublyLinkedList<Student>;
		//Insert all Students in to that DoublyLinkedList
		//They are thereby sorted
		for (it_student = student.begin();it_student!=student.end();++it_student) {
			ddl_student->insert(*it_student);
		}
		//Set the Iterator
		it_ddl_student = ddl_student->begin();
	}
	//If reach the end
	if(it_ddl_student == ddl_student->end()) {
		//Reset the state and return null to show the end of listing
		isListing = false;
		return NULL;
	}
	//Get the pointer by dereference
	Student* tmp = &(*it_ddl_student);
	//Increment the Iterator
	++it_ddl_student;
	//Return that pointer
	return tmp;
}

//List all the Courses
const Course* DataBase::list_course() {
	//If not Listing, Initialize a listing process
	if(!isListing) {
		isListing = true;
		//Replace the Course DoublyLinkedList by a new one
		delete ddl_course;
		ddl_course = new DoublyLinkedList<Course>;
		//Insert all Courses in to that DoublyLinkedList
		//They are thereby sorted
		for (it_course = course.begin();it_course!=course.end();++it_course) {
			ddl_course->insert(*it_course);
		}
		//Set the Iterator
		it_ddl_course = ddl_course->begin();
	}
	//If reach the end
	if(it_ddl_course == ddl_course->end()) {
		//Reset the state and return null to show the end of listing
		isListing = false;
		return NULL;
	}
	//Get the pointer by dereference
	Course* tmp = &(*it_ddl_course);
	//Increment the Iterator
	++it_ddl_course;
	//Return that pointer
	return tmp;
}

//List all Selections
//They are already sorted so that no need to use another DoublyLinkedList
const CourseSelection* DataBase::list_selection() {
	//If not Listing, Initialize a listing process
	if(!isListing) {
		it_selection = selection.begin();
		isListing = true;
	}
	//If reach the end, reset the state and return null to show the end of listing
	if(it_selection==selection.end()) {
		isListing = false;
		return NULL;
	}
	//Get the pointer by dereference
	CourseSelection* tmp = &(*it_selection);
	//Increment the Iterator
	++it_selection;
	//Return that pointer
	return tmp;
}

//List all Courses of a Student
const CourseSelection* DataBase::list_courses_of(const Student& s) {
	//Construct StudentIndex by Student
	StudentIndex sid(s);
	//If not Listing, Initialize a listing process
	if(!isListing) {
		isListing = true;
		//Replace the Course DoublyLinkedList by a new one
		delete ddl_selection;
		ddl_selection = new DoublyLinkedList<CourseSelection>;
		//Insert all relevant CourseSelections in to that DoublyLinkedList
		//They are thereby sorted
		StudentIndex* sid_p;
		it_sid = student_id.begin(sid);
		while (it_sid!=student_id.end(sid)) {
			//Use find of StudentIndex HashTable
			sid_p=student_id.find(sid,it_sid);
			//The last result of find can be null
			if(sid_p) ddl_selection->insert(*(sid_p->pointer));
		}
		//Set the Iterator
		it_ddl_selection = ddl_selection->begin();
	}
	//If reach the end
	if(it_ddl_selection == ddl_selection->end()) {
		//Reset the state and return null to show the end of listing
		isListing = false;
		return NULL;
	}
	//Get the pointer by dereference
	CourseSelection* tmp = &(*it_ddl_selection);
	//Increment the Iterator
	++it_ddl_selection;
	//Return that pointer
	return tmp;
}

//List all Students of a Course
const CourseSelection* DataBase::list_students_of(const Course& c) {
	//Construct CourseIndex by Course
	CourseIndex cid(c);
	//If not Listing, Initialize a listing process
	if(!isListing) {
		isListing = true;
		//Replace the Course DoublyLinkedList by a new one
		delete ddl_selection;
		ddl_selection = new DoublyLinkedList<CourseSelection>;
		//Insert all relevant CourseSelections in to that DoublyLinkedList
		//They are thereby sorted
		CourseIndex* cid_p;
		it_cid = course_id.begin(cid);
		while (it_cid!=course_id.end(cid)) {
			//Use find of StudentIndex HashTable
			cid_p=course_id.find(cid,it_cid);
			//The last result of find can be null
			if(cid_p) ddl_selection->insert(*(cid_p->pointer));
		}
		//Set the Iterator
		it_ddl_selection = ddl_selection->begin();
	}
	//If reach the end
	if(it_ddl_selection == ddl_selection->end()) {
		//Reset the state and return null to show the end of listing
		isListing = false;
		return NULL;
	}
	//Get the pointer by dereference
	CourseSelection* tmp = &(*it_ddl_selection);
	//Increment the Iterator
	++it_ddl_selection;
	//Return that pointer
	return tmp;
}