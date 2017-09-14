#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "record.h"

//Class ReadWrite
//Manage all the input/output functionalities
#ifndef READWRITE
#define READWRITE

//Class ReadWrite
class ReadWrite {
public:
	//Constructor
	//Need one istream and two ostream, for input, output, and remind
	ReadWrite(std::istream& i, std::ostream& o, std::ostream& r):in(i),out(o),remind(r) {}
	//Destructor
	~ReadWrite() {}
	//Write Record
	void write(const Record* r) const;
	//Write Record when saving file
	void writefile(const Record* r) const;
	//Read Record
	//readKey shows whether we read the key or non-key attributes 
	void read(Record* r, bool readKey = true) const;
	//Write html head
	//These two are overloaded
	//isSpecified shows whether we show information of that Record in the htnl head
	//isEmpty shows whether the html table is empty
	void write_html_head(const Student* s, bool isSpecified = false, bool isEmpty = false) const;
	void write_html_head(const Course* c, bool isSpecified = false, bool isEmpty = false) const;
	//Write html table name
	void write_html_name(const Record* r) const;
	//Write Record to html file
	void write_html_record(const Record* r) const;
	//Write html end
	void write_html_end() const;
private:
	//Reference to the streams
	std::istream& in;
	std::ostream& out;
	std::ostream& remind;
};

#endif