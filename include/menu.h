#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "manager.h"

//Class Menu
//An indepentend extendable menu system
#ifndef MENU
#define MENU

//typedef the member function pointer to Class Manager
typedef void (Manager::*func) ();
//Declaration fo the menu_item and menu_list
struct menu_item;
struct menu_list;

//Struct menu_item
struct menu_item {
	//Text of that item
	std::string _text;
	//Pointer to menu_list if that item link to another menu list
	menu_list* _menu_pointer;
	//Function pointer if that item link to a function
	func _func_pointer;
};

//Struct menu_list
struct menu_list {
	//Consturctor
	menu_list() {}
	//Destructor
	~menu_list() {}
	//Set title of this menu list
	void set_title(std::string title) {_title.assign(title);};
	//Add a menu item to this menu list
	void add_item(std::string text, menu_list* menu_pointer = NULL, func func_pointer = NULL);
	//Print this menu list to screen
	void print();
	//Print to remind that user specified a non-exist menu item
	void print_invalid();
	//Get the menu_item's menu_list pointer
	menu_list* get_menu_pointer(int id);
	//Get the menu_item's function pointer
	func get_func_pointer(int id);
	//Get the size of this menu list
	int size() {return _list.size();};
	//Title
	std::string _title;
	//Vector of menu_item
	std::vector<menu_item> _list;
};

//Declaration of Class Manager
//Since it is use in definition of Class Menu
class Manager;

//Class Menu
class Menu {
public:
	//Consturctor
	//With a Manager to set the function pointer
	Menu(Manager* m);
	//Destructor
	~Menu() {};
	//Load the menu system
	void load(std::istream& in);
private:
	//Clear the screen
	void clear();
	//Menu lists for the menu system
	menu_list _main;
	menu_list _student;
	menu_list _course;
	menu_list _registration;
	menu_list _report;
	menu_list _file;
	//Pointer to Manager
	Manager* manager;
};

#endif
