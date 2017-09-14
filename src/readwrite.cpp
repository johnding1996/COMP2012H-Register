#include "readwrite.h"

using namespace std;

//Read Record
void ReadWrite::read(Record* r, bool readKey) const {
	//Buffer for reading each Attribute c-string
	char buffer[ATTRIBUTE_LENGTH];
	//Flag to show whether an Attribute is recorded
	bool isRecorded = false;
	//Read each Attribute of that Record
	for (int i=0; i<r->size; ++i) {
		//Only read the ones that specified by readKey
		if ((readKey&&(!r->tuple[i]->isKey))||((!readKey)&&r->tuple[i]->isKey)) continue;
		//Remind for input
		remind << "Enter the " << r->tuple[i]->tag() << ": ";
		//Input
		in.getline(buffer,ATTRIBUTE_LENGTH);
		//Try assign
		isRecorded = r->tuple[i]->assign(buffer);
		//Clear the buffer
		std::memset(buffer,0,ATTRIBUTE_LENGTH);
		//While failed
		//Try input and assign again until success
		while (!isRecorded) {
			//Remind for valid input
			remind << "Invalid input, re-enter again " << r->tuple[i]->hint << ": ";
			//Input
			in.getline(buffer,ATTRIBUTE_LENGTH);
			//Try assign
			isRecorded = r->tuple[i]->assign(buffer);
			//Clear the buffer
			std::memset(buffer,0,ATTRIBUTE_LENGTH);
		}
		//Reset flag
		isRecorded = true;
	}
}

//Write Record
void ReadWrite::write(const Record* r) const {
	//If remind to console, output end line for nicer format
	remind << endl;
	string name;
	//Output each Attribute
	for (int i=0; i<r->size; ++i) {
		name = r->tuple[i]->name + ":";
		name.resize(14,' ');
		//Remind the name of each Attribute
		remind << name;
		//Output Attribute by ostream
		out << *(r->tuple[i]) << endl;
	}
}

//Write Record to file
//No remind needed
void ReadWrite::writefile(const Record* r) const {
	//Write the tag of Record
	out << r->tag() << endl;
	for (int i=0; i<r->size; ++i) {
		out << *(r->tuple[i]) << endl;
	}
}

//Write html head, specified for a Student
void ReadWrite::write_html_head(const Student* s, bool isSpecified, bool isEmpty) const {
	out << "<HTML>" << endl;
	out << "<HEAD>" << endl;
	out << "<HEAD>" << endl;
	if (!isSpecified) out << "<TITLE>All Students List</TITLE>" << endl;
	else out << "<TITLE>" << "Course Records for Student " << *(s->tuple[0]) << "</TITLE>" << endl;
	out << "</HEAD>" << endl;
	out << "<BODY bgColor=#ffffcc>" << endl;
	out << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>" << endl;
	if (!isSpecified) out << "<H2>All Students List</H2>" << endl;
    else out << "<H2>" << "Course Records for Student: " << *(s->tuple[1]) << " (" << *(s->tuple[0]) << ")" << "</H2>" << endl;
   	out << "<P>" << endl;
   	if (!isEmpty) out << "<TABLE cellSpacing=1 cellPadding=1 border=1>" << endl;
   	//Specified format for empty table
   	else {
   		if (!isSpecified) out << "No student found" << endl;
   		else out << "No course taken" << endl;
   		out << "</P>" << endl;
   		out << "</BODY>" << endl;
   		out << "</HTML>" << endl; 
   	}
}

//Write html head, specified for a Course
void ReadWrite::write_html_head(const Course* c, bool isSpecified, bool isEmpty) const {
	out << "<HTML>" << endl;
	out << "<HEAD>" << endl;
	out << "<HEAD>" << endl;
	if (!isSpecified) out << "<TITLE>All Course List</TITLE>" << endl;
	else out << "<TITLE>" << "Student Records for Course " << *(c->tuple[0]) << "</TITLE>" << endl;
	out << "</HEAD>" << endl;
	out << "<BODY bgColor=#ffffcc>" << endl;
	out << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>" << endl;
	if (!isSpecified) out << "<H2>All Course List</H2>" << endl;
    else out << "<H2>" << "Student Records for Course: " << *(c->tuple[1]) << " (" << *(c->tuple[0]) << ")" << "</H2>" << endl;
   	out << "<P>" << endl;
   	if (!isEmpty) out << "<TABLE cellSpacing=1 cellPadding=1 border=1>" << endl;
   	//Specified format for empty table
   	else {
   		if (!isSpecified) out << "No course found" << endl;
   		else out << "No student takes this course" << endl;
   		out << "</P>" << endl;
   		out << "</BODY>" << endl;
   		out << "</HTML>" << endl; 
   	}
}

//Write html table name
void ReadWrite::write_html_name(const Record* r) const {
	out << endl;
	out << "<TR>" << endl;
	//Write the name of each Attribute
	for (int i=0; i<r->size; ++i) {
		out << "<TD>" << r->tuple[i]->name << "</TD>" << endl;
	}
	out << "</TR>" << endl;
}

//Write Record to html file
void ReadWrite::write_html_record(const Record* r) const {
	out << endl;
	out << "<TR>" << endl;
	//Write each Attribute
	for (int i=0; i<r->size; ++i) {
		out << "<TD>" << *(r->tuple[i]) << "</TD>" << endl;
	}
	out << "</TR>" << endl;
}

//Write html end
void ReadWrite::write_html_end() const {
	out << endl;
	out << "</TABLE>" << endl;
	out << "</P>" << endl;
	out << "</BODY>" << endl;
	out << "</HTML>" << endl;
}