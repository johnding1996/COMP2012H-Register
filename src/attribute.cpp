#include "attribute.h"

//Symbolic constant for the valid length of StudentID
#ifndef STUDENTID_LENGTH
#define STUDENTID_LENGTH 8
#endif

//Symbolic constant for the valid lenth of CourseCode, lower bound
#ifndef COURSECODE_LENGTH_LOW
#define COURSECODE_LENGTH_LOW 7
#endif

//Symbolic constant for the valid lenth of CourseCode, upper bound
#ifndef COURSECODE_LENGTH_UP
#define COURSECODE_LENGTH_UP 8
#endif

using namespace std;

//Overloaded operator= of Attribute
void Attribute::operator= (const Attribute& at) {
	//CLear the inner c-string
	clear();
	//Copy
	copy(at.str);
}

//Copy of Attribute
void Attribute::copy(const char* strcp) {
	//Copy of c-string
	for (int i=0; i<ATTRIBUTE_LENGTH; ++i) {
		str[i] = strcp[i];
	}
}

//assign() of StudentID
bool StudentID::assign(const char* strcp) {
	//Check the length of input
	bool valid = (strlen(strcp)==STUDENTID_LENGTH);
	//Check each character is a decimal digit
	int i = 0;
	while (valid&&(i<STUDENTID_LENGTH)) {
		valid = valid && (strcp[i]>=48||strcp[i]<=57);
		++i;
	}
	//If valid then copy
	if (valid) {
		copy(strcp);
	}
	return valid;
}

//assign() of CourseCode
bool CourseCode::assign(const char* strcp) {
	//Check the length of input
	bool valid = (strlen(strcp)>=COURSECODE_LENGTH_LOW)&&(strlen(strcp)<=COURSECODE_LENGTH_UP);
	//Check the format
	int i = 0;
	while (valid&&(i<(int)strlen(strcp))) {
		//First four characters are capital letters
		//The rest are capital letters or decimal digits
		if (i<=3)
			valid = valid && (strcp[i]>=65&&strcp[i]<=90);
		else 
			valid = valid && ((strcp[i]>=48&&strcp[i]<=57)||(strcp[i]>=65&&strcp[i]<=90));
		++i;
	}
	//If valid then copy
	if (valid) {
		copy(strcp);
	}
	return valid;
}

//assign() of StudentName
bool StudentName::assign(const char* strcp) {
	//Check the length of input
	bool valid = (strlen(strcp)>=1&&strlen(strcp)<=32);
	//If valid then copy
	if (valid) {
		copy(strcp);
	}
	return valid;
}

//assign() of StudentName
bool Year::assign(const char* strcp) {
	//Check the length of input
	bool valid = (strlen(strcp)==1);
	//Can only be '1', '2' or '3'
	valid = valid && (strcp[0]=='1'||strcp[0]=='2'||strcp[0]=='3');
	//If valid then copy
	if (valid) {
		copy(strcp);
	}
	return valid;
}

//assign() of Gender
bool Gender::assign(const char* strcp) {
	//Check the length of input
	bool valid = (strlen(strcp)==1);
	//Can only be 'M' or 'F'
	valid = valid && (strcp[0]=='M'||strcp[0]=='F');
	//Backdoor for inner copy of Genders
	//Since the stored strings in files are in different format compared to the inputed strings
	valid = valid || (strlen(strcp)==4&&strcp[0]=='M'&&strcp[1]=='a'&&strcp[2]=='l'&&strcp[3]=='e');
	valid = valid || (strlen(strcp)==6&&strcp[0]=='F'&&strcp[1]=='e'&&strcp[2]=='m'&&strcp[3]=='a'&&strcp[4]=='l'&&strcp[5]=='e');
	//If valid then copy
	if (valid) {
		copy(strcp);
	}
	return valid;
}

//assign() of CourseName
bool CourseName::assign(const char* strcp) {
	//Check the length of input
	bool valid = (strlen(strcp)>=1&&strlen(strcp)<=50);
	//If valid then copy
	if (valid) {
		copy(strcp);
	}
	return valid;
}

//assign() of Credit
bool Credit::assign(const char* strcp) {
	//Check the length of input
	bool valid = (strlen(strcp)==1);
	//Can only be '0' ~ '5'
	valid = valid && (strcp[0]>=48&&strcp[0]<=53);
	//If valid then copy
	if (valid) {
		copy(strcp);
	}
	return valid;
}

//assign() of ExamMark
bool ExamMark::assign(const char* strcp) {
	//Backdoor for inner copy of ExamMarks
	//Since the stored strings in files are in different format compared to the inputed strings
	if(strlen(strcp)==3&&strcp[0]=='N'&&strcp[1]=='/'&&strcp[2]=='A') {
		clear();
		str[0]='~';
		return true;
	}
	//Check the length of input
	bool valid = (strlen(strcp)<=3&&strlen(strcp)>=1);
	//Can only be 0 ~ 100
	int score = atoi(strcp);
	valid = valid && (score>=0&&score<=100);
	//Check the format carefully
	int nodigit = 2;
	if(score<10) nodigit = 1;
	if(score==100) nodigit = 3;
	valid = valid && (strcp[nodigit]==0);
	//If valid then copy
	if (valid) {
		copy(strcp);
	}
	return valid;
}

//tag() of StudentName
string StudentName::tag() const{
	//If modifying, also show the stored string as hint
	string s(str);
	s = " [" + s + "]";
	//If inserting, only show the hint word
	if(str[0]==0) s = "";
	return ("student name" + s);
}

//tag() of Year
string Year::tag() const{
	//If modifying, also show the stored string as hint
	string s(str);
	//If inserting, only show the hint word
	if(str[0]==0) s = "1-3";
	s = " [" + s + "]";
	return ("student year" + s);
}

//tag() of Gender
string Gender::tag() const{
	//If modifying, also show the stored string as hint
	string s(str);
	//If inserting, only show the hint word
	if(str[0]==0) s = "M,F";
	s = " [" + s + "]";
	return ("student gender" + s);
}

//tag() of CourseName
string CourseName::tag() const{
	//If modifying, also show the stored string as hint
	string s(str);
	s = " [" + s + "]";
	//If inserting, only show the hint word
	if(str[0]==0) s = "";
	return ("course name" + s);
}

//tag() of Credit
string Credit::tag() const{
	//If modifying, also show the stored string as hint
	string s(str);
	//If inserting, only show the hint word
	if(str[0]==0) s = "0-5";
	s = " [" + s + "]";
	return ("course credit" + s);
}

//tag() of ExamMark
string ExamMark::tag() const{
	//If modifying, also show the stored string as hint
	string s(str);
	//If inserting, only show the hint word
	//Note the uninitialized string is different from the others
	if(str[0]=='~') s = "N/A";
	s = " [" + s + "]";
	return ("exam mark" + s);
}

//print() of Gender
void Gender::print(std::ostream& os) const {
	//Specified output to be more readable
	if(str[0]=='M') os << "Male";
	else os << "Female";
}

//print() of ExamMark
void ExamMark::print(std::ostream& os) const {
	//Specified output to show "N/A" if uninitialized
	if(str[0]=='~') os << "N/A";
	else Attribute::print(os);
}

//hash_func() of StudentID, since it is a key-attribute
int StudentID::hash_func(int tlength) const {
	//Check validity
	if (str[0]==0) cerr << "Uninitialized Attribute.";
	if (tlength<=0) cerr << "Invalid Hash Table Size.";
	//Calculate the hash function
	//With modular arithmatic to prevent overflow
	int base_mod = 1;
	int loc = 0;
	for (int i=0; i<STUDENTID_LENGTH; ++i) {
		loc += ((str[STUDENTID_LENGTH-1-i]-48)*base_mod)%tlength;
		base_mod = (base_mod*10)%tlength;
	}
	return (loc%tlength);
}

//hash_func() of CourseCode, since it is a key-attribute
int CourseCode::hash_func(int tlength) const {
	//Check validity
	if (str[0]==0) cerr << "Uninitialized Attribute.";
	if (tlength<=0) cerr << "Invalid Hash Table Size.";
	//Calculate the hash function
	//With modular arithmatic to prevent overflow
	int length = strlen(str);
	int base_mod = 1;
	int loc = 0;
	int digit = 0;
	for (int i=0; i<length; ++i) {
		if (str[length-1-i]<65) digit = str[length-1-i]-48;
		else digit = str[length-1-i]-55;
		loc += (digit*base_mod)%tlength;
		base_mod = (base_mod*36)%tlength;
	}
	return (loc%tlength);
}