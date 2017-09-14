#include "menu.h"

using namespace std;

//Add a menu item to menu list
void menu_list::add_item(string text, menu_list* menu_pointer, func func_pointer) {
	menu_item item;
	item._text = text;
	item._menu_pointer = menu_pointer;
	item._func_pointer = func_pointer;
	_list.push_back(item);
}

//Print the menu list
void menu_list::print() {
	//Print the menu title
	cout << _title << endl;
	string divider(_title);
	cout << divider.replace(0,divider.length(),divider.length(),'-') << endl;
	cout << endl;
	//Print the menu items
	vector<menu_item>::iterator it;
	int count = 1;
	for (it=_list.begin(); it!=_list.end(); ++it, ++count) {
		cout << count << ". ";
		cout << it->_text;
		cout << endl;
	}
	//Print input reminder
	cout << endl;
	cout << "Enter your choice (1-" << size() << "): ";

}

//Print to remind that user specified a non-exist menu item
void menu_list::print_invalid() {
	cout << "Invalid input, re-enter again (1-" << size() << "): ";
}

//Get the menu_item's menu_list pointer
menu_list* menu_list::get_menu_pointer(int id) {
	if (id<0||id>=size()) return NULL;
	return _list[id]._menu_pointer;
}

//Get the menu_item's function pointer
func menu_list::get_func_pointer(int id) {
	if (id<0||id>=size()) return NULL;
	return _list[id]._func_pointer;
}

//Constructor of Menu
Menu::Menu(Manager* m):manager(m) {
	//Add menu item to each menu list
	//With specified menu list or function pointers
	_main.set_title("HKUST Course Registration System");
	_main.add_item("Student Management",&_student);
	_main.add_item("Course Management",&_course);
	_main.add_item("Course Registration",&_registration);
	_main.add_item("Report Management",&_report);
	_main.add_item("File Management",&_file);
	_main.add_item("Exit",NULL,&Manager::_exit);

	_student.set_title("HKUST Course Registration System  (Student Menu)");
	_student.add_item("Insert Student Record",&_main,&Manager::_student_insert);
	_student.add_item("Modify Student Record",&_main,&Manager::_student_modify);
	_student.add_item("Delete Student Record",&_main,&Manager::_student_delete);
	_student.add_item("Query Student Record",&_main,&Manager::_student_query);
	_student.add_item("Go back to main menu",&_main);

	_course.set_title("HKUST Course Registration System  (Course Menu)");
	_course.add_item("Insert Course Record",&_main,&Manager::_course_insert);
	_course.add_item("Modify Course Record",&_main,&Manager::_course_modify);	
	_course.add_item("Delete Course Record",&_main,&Manager::_course_delete);
	_course.add_item("Query Course Record",&_main,&Manager::_course_query);
	_course.add_item("Go back to main menu",&_main);

	_registration.set_title("HKUST Course Registration System  (Registration Menu)");
	_registration.add_item("Add Course",&_main,&Manager::_registration_add);
	_registration.add_item("Drop Course",&_main,&Manager::_registration_drop);
	_registration.add_item("Modify Exam Mark",&_main,&Manager::_registration_modify);
	_registration.add_item("Query Registration",&_main,&Manager::_registration_query);
	_registration.add_item("Go back to main menu",&_main);

	_report.set_title("HKUST Course Registration System  (Report Generation Menu)");
	_report.add_item("List all student information",&_main,&Manager::_report_student);
	_report.add_item("List all course information",&_main,&Manager::_report_course);
	_report.add_item("List all courses of a student",&_main,&Manager::_report_courses_of);
	_report.add_item("List all students of a course",&_main,&Manager::_report_students_of);
	_report.add_item("Go back to main menu",&_main);

	_file.set_title("HKUST Course Registration System  (File Menu)");
	_file.add_item("Save Database",&_main,&Manager::_file_save);
	_file.add_item("Load Database",&_main,&Manager::_file_load);
	_file.add_item("Go back to main menu",&_main);
}

//Load the Menu system
void Menu::load(istream& in) {
	//Set current menu list as the main menu list
	menu_list* cur_list = &_main;
	//Buffer
	char input[256];
	//Flag for menu list control
	bool cur_unchanged = true;
	//Flag for function calling
	bool func_called = false;
	//While-1 loop to navigate the Menu system
	while (cur_list) {
		//Clear screen first
        clear();
        //Print current menu list
		cur_list->print();
		cur_unchanged = true;
		//While the current list isn't changed
		while (cur_unchanged) {
			//Get input choice
			in.getline(input,256);
			int choice = (int)input[0] - 48;
			//Check validity
			if (!(choice>0&&choice<=cur_list->size()&&input[1]==0)) cur_list->print_invalid();
			else {
				//First run the function (if exist)
				if (cur_list->get_func_pointer(choice-1)) {
					func call_function = cur_list->get_func_pointer(choice-1);
					(manager->*call_function)();
					//Set flag
					func_called = true;
				}
				//Then navigate the menu list
				if (cur_list->get_menu_pointer(choice-1)) {
					//If function is called
					//Can be navigated back
					if (func_called) {
						cout << endl << "Hit ENTER to continue..." << endl;
						in.get();
						func_called = false;
					}
					//Update current menu list
					cur_list = cur_list->get_menu_pointer(choice-1);
					cur_unchanged = false;
				}
			}
		}
	}
}

//Clear screen
void Menu::clear() {
	//Windows
	#ifdef _WIN32
	system("cls");
	#endif
	//Linux
	#ifdef linux
	system("clear");
	#endif
}