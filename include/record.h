#include "attribute.h"

//Symbolic Constant for the number of attributes in each record
//Note some attributes are not used
#ifndef RECORD_SIZE
#define RECORD_SIZE 5
#endif

//Abstract base class Record
//And classes that inherit Record: Student, Course, CourseSelection, StudentIndex, CourseIndex, ExentedStudent, ExtendedCourse

#ifndef RECORD
#define RECORD

//Struct Record
struct Record {
	//Default Constructor
	Record():size(RECORD_SIZE),tuple(new Attribute*[RECORD_SIZE]()) {
		//Assign NULL to the array pointer
		for (int i=0; i<RECORD_SIZE; ++i) 
			tuple[i]=NULL;
	}
	//Virtual Destructor
	virtual ~Record();
	//Overloaded operator<
	//Compare the record by the comparison of their key attributes
	virtual bool operator< (const Record& r) const;
	//Overloaded operator==
	//Compare the record by the comparison of their key attributes
	virtual bool operator== (const Record& r) const;
	//Virtual function hash_func()
	//Calculate the hash function by the hash functions of their key attribute
	virtual int hash_func(int tlength) const;
	//Overloaded operator=
	//Assign by copy each attribute
	virtual Record& operator= (const Record& r);
	//Pure virtual function tag()
	//Return the tag char for file storage
	virtual char tag() const = 0;
	//The number of attributed actually used
	int size;
	//Array of pointers to attributes
	Attribute** tuple;
};

//Declare Struct CourseSelection since it is used in the definition of Struct Student and Course
struct CourseSelection;

//Struct Student
struct Student: public Record {
	//Constructor
	Student();
	//Coversion Constructor from CourseSelection
	Student(const CourseSelection& cs);
	//Destructor
	~Student() {}
	//Overloaded tag() return 's'
	char tag() const {return 's';}
};

//Struct Course
struct Course: public Record {
	//Constructor
	Course();
	//Coversion Constructor from CourseSelection
	Course(const CourseSelection& cs);
	//Destructor
	~Course() {}
	//Overloaded tag() return 'c'
	char tag() const {return 'c';}
};

//Struct CourseSelection
struct CourseSelection: public Record {
	//Constructor
	CourseSelection();
	//Constructor from Student and Course
	CourseSelection(const Student& s, const Course& c);
	//Destructor
	~CourseSelection() {};
	//Overloaded operator<
	//Since the comparison of CourseSelection Record compares two key attributes
	bool operator< (const Record& r) const;
	//Overloaded operator==
	//Since the comparison of CourseSelection Record compares two key attributes
	bool operator== (const Record& r) const;
	//Overloaded tag() return 'r'
	char tag() const {return 'r';}
};

//Sturnct StudentIndex
struct StudentIndex: public Record {
	//Constructor
	StudentIndex();
	//Conversion Constructor form Student
	StudentIndex(const Student& s);
	//Conversion Constructor form CourseSelection
	StudentIndex(const CourseSelection* cs);
	//Destructor
	~StudentIndex() {}
	//Pointer to the CourseSelection Record
	const CourseSelection* pointer;
	//Overloaded tag() return null, it will never be used
	char tag() const {return '\0';}
};

//Sturnct CourseIndex
struct CourseIndex: public Record {
	//Constructor
	CourseIndex();
	//Conversion Constructor form Course
	CourseIndex(const Course& c);
	//Conversion Constructor form CourseSelection
	CourseIndex(const CourseSelection* cs);
	//Destructor
	~CourseIndex() {}
	//Pointer to the CourseSelection Record
	const CourseSelection* pointer;
	//Overloaded tag() return null, it will never be used
	char tag() const {return '\0';}
};

//Sturnct ExtendedStudent
//Only for reporting students of a course
struct ExtendedStudent: public Record {
	//Conversion Constructor from Student and CourseSelection
	ExtendedStudent(const Student& s, const CourseSelection& cs);
	//Destructor
	~ExtendedStudent() {}
	//Overloaded tag() return null, it will never be used
	char tag() const {return '\0';}
};

//Sturnct ExtendedCourse
//Only for reporting courses of a student
struct ExtendedCourse: public Record {
	//Conversion Constructor from Course and CourseSelection
	ExtendedCourse(const Course& c, const CourseSelection& cs);
	//Destructor
	~ExtendedCourse() {}
	//Overloaded tag() return null, it will never be used
	char tag() const {return '\0';}
};

#endif