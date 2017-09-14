#include <iostream>
#include "menu.h"
#include "manager.h"

using namespace std;

int main() {
	//Manager
	Manager manager(cin,cout,cout);
	//Menu with function pointers to Manager
	Menu menu(&manager);
	//Load Menu system
	menu.load(cin);
}