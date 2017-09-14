# Register
Project 5 for COMP2012H, 2016 Fall, HKUST

A symplified course registration system


## How-to-compile-and-run
```
$ make
$ bin/Register
```


## Technical Details
Source file tree:
```
    |
    |--include
    |  |--attribute.h
    |  |--database.h
    |  |--doublylinkedlist.h
    |  |--hashtable.h
    |  |--manager.h
    |  |--menu.h
    |  |--readwrite.h
    |  |--record.h
    |
    |--src
    |  |--attribute.cpp
    |  |--database.cpp
    |  |--manager.cpp
    |  |--menu.cpp
    |  |--readwrite.cpp
    |  |--record.cpp
    |  |--register.cpp
    |
    |--Makefile
    |--Register.pro
```
Note that I did not use QT library, but only generate the Makefile by qmake.


## Deviation from sample program
Some texts in the menu system may be different. The file for saving and loading is in self-designed format.


## Design ideas
As a large project, I tried to make my work slight by reducing duplicated codes as much as possible, taking advantage of the power of OOP. I define each attribute type as a class which inherits from an abstract base class Attribute, similarly for each record, which is a collection of several attributes with one (or more) key attributes. I implemented the doubly linked list and the hash table as template classes, each with its own iterator. There are both equipped with many operations so that are enough for our use. I use a DataBase class to store all the data and manage all the relevant data operations. And the Manager class is to directly response and tackle users' operations. The menu system is independenely implemented and is extendable. It gets function pointers from other classes to be functionalized, in this project, the function pointers are pointed to meneber functions of Manager class. The main function is very simple, just instantize a Manager and a Menu class, then load the menu.
