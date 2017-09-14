#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>

//Symbolic constant for the length of c-string of each Attribute
#ifndef ATTRIBUTE_LENGTH
#define ATTRIBUTE_LENGTH 64
#endif

//Abstract base class Attribute
//And classes that inherit Attirbute: StudentID, CourseCOde, StudentName, Year, Gender, CourseName, Credit, ExamMark

#ifndef ATTRIBUTE
#define ATTRIBUTE

//Sturct Attribute
struct Attribute {
	//Default Constructor
	Attribute():str(new char[ATTRIBUTE_LENGTH]),isKey(false) {clear();}
	//Constructor for derived classes
	Attribute(std::string hint_copy, std::string name_copy, bool k = false)
		:str(new char[ATTRIBUTE_LENGTH]),hint(hint_copy),name(name_copy),isKey(k) {clear();}
	//Copy Constructor
	Attribute(Attribute& at):str(new char[ATTRIBUTE_LENGTH]),isKey(false) {copy(at.str);}
	//Virtual Destructor
	virtual ~Attribute() {
		delete[] str;
		str = NULL;
	}
	//Clear the char array
	void clear() {std::memset(str,0,ATTRIBUTE_LENGTH);}
	//Copy the char array
	void copy(const char* strcp);
	//Pure virtual function assign()
	//In derived classes, check validity of the input string and assign to itself
	virtual bool assign(const char* strcp) = 0;
	//Pure virtual function tag()
	//In derived classes, return the hint word for insertion and modification
	virtual std::string tag() const = 0;
	//Print the c-string to the ostream
	//Called by the overloaded operator<<
	virtual void print(std::ostream& os) const {os << std::string(str);}
	//Overloaded operator<< function
	//Print the attribute to the console and file
	friend std::ostream& operator<< (std::ostream& os, const Attribute& at) {at.print(os); return os;}
	//Overloaded operator=
	//Assign the c-string with checking validity
	void operator= (const Attribute& at);
	//Overloaded operator<
	//Compare the attribute by alphabetical order
	bool operator< (const Attribute& at) const {return (strcmp(str,at.str)<0);}
	//Overloaded operator==
	//Compare the attribute by alphabetical order
	bool operator== (const Attribute& at) const {return (strcmp(str,at.str)==0);}
	//Virtual function hash_func()
	//Only useful for key attirbute
	//For non-key attribute, return the length of table can cause overflow error. It is never used.
	virtual int hash_func(int tlength) const {return tlength;};
	//Strings
	std::string hint;
	std::string name;
	//Char array, storage
	char* str;
	//Bool
	//Show whether it is a key attribute
	bool isKey;
};

struct StudentID: public Attribute {
	//Constructor
	StudentID():Attribute("[student ID]","Student ID",true) {}
	//Destructor
	~StudentID() {}
	//Overloaded function assign()
	bool assign(const char* strcp);
	//Overloaded fucntion tag()
	std::string tag() const {return "student ID";}
	//Overloaded function hash_func(), since it is a key-attribute
	int hash_func(int tlength) const;
};

struct CourseCode: public Attribute {
	//Constructor
	CourseCode():Attribute("[course code]","Course Code",true) {}
	//Destructor
	~CourseCode() {}
	//Overloaded function assign()
	bool assign(const char* strcp);
	//Overloaded fucntion tag()
	std::string tag() const {return "course code";}
	//Overloaded function hash_func(), since it is a key-attribute
	int hash_func(int tlength) const;
};

struct StudentName: public Attribute {
	//Constructor
	StudentName():Attribute("[student name]","Student Name") {}
	//Destructor
	~StudentName() {}
	//Overloaded function assign()
	bool assign(const char* strcp);
	//Overloaded fucntion tag()
	std::string tag() const;
};

struct Year: public Attribute {
	//Constructor
	Year():Attribute("[1-3]","Year") {}
	//Destructor
	~Year() {}
	//Overloaded function assign()
	bool assign(const char* strcp);
	//Overloaded fucntion tag()
	std::string tag() const;
};

struct Gender: public Attribute {
	//Constructor
	Gender():Attribute("[M,F]","Gender") {}
	//Destructor
	~Gender() {}
	//Overloaded function assign()
	bool assign(const char* strcp);
	//Attribute Gender also has specialized print()
	//Since we print "Male" and "Female" instead of "M" and "F"
	void print(std::ostream& os) const;
	//Overloaded fucntion tag()
	std::string tag() const;
};

struct CourseName: public Attribute {
	//Constructor
	CourseName():Attribute("[course name]","Course Name") {}
	//Destructor
	~CourseName() {}
	//Overloaded function assign()
	bool assign(const char* strcp);
	//Overloaded fucntion tag()
	std::string tag() const;
};

struct Credit: public Attribute {
	//Constructor
	Credit():Attribute("[course credit]","Credit") {}
	//Destructor
	~Credit() {}
	//Overloaded function assign()
	bool assign(const char* strcp);
	//Overloaded fucntion tag()
	std::string tag() const;
};

struct ExamMark: public Attribute {
	//Constructor
	//We use "~" to represent uninitialized ExamMark
	ExamMark():Attribute("[exam mark]","Exam Mark") {str[0] = '~';}
	//Destructor
	~ExamMark() {}
	//Overloaded function assign()
	bool assign(const char* strcp);
	//Attirbute ExamMark also has specialized print()
	//Since we print "N/A" instead of null string for uninitialized ExamMark
	void print(std::ostream& os) const;
	//Overloaded fucntion tag()
	std::string tag() const;
};

#endif