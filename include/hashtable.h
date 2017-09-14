#include "doublylinkedlist.h"

//Template Class HashTable
//And auxilary template class HashTable<T, int>::Interator
#ifndef HASHTABLE
#define HASHTABLE

//Template Class HashTable
template <typename T, int _length>
class HashTable {
public:
	//Definition of Class Iterator
	class Iterator;
	//Default Constructor
	HashTable():_size(0),_table(new DoublyLinkedList<T>[_length]){}
	//Destructor
	~HashTable() {
		delete[] _table;
		_table = NULL;
	}
	//Insert
	//allowRepetition set whether the values can be repeated
	T* insert(const T& v, bool allowRepetition = false);
	//Remove
	bool remove(const T& v);
	//Remove the previous value in the HashTable
	//Used together with find(const T&, Iterator&)
	bool remove_prev(const Iterator& it);
	//Find
	//Find the value and also modify the iterator to the next position of that value
	T* find(const T& v, Iterator& it);
	//Find
	//Find in a no-repitition HashTable, no need to modify the iterator
	T* find(const T& v);
	//Return size
	int size() const {return _size;}
	//Return size of the doubly linked list in that slot
	int list_size(const T& v) const;
	//Reaturn an Iterator at the begining pisition
	Iterator begin();
	//Return an Iterator at the ending position, pass the end
	Iterator end() {return Iterator(_table,_length-1,_table[_length-1].end());}
	//Reaturn an Iterator at the begining pisition of that slot
	Iterator begin(const T& v) {return Iterator(_table,hash_func(v),_table[hash_func(v)].begin());}
	//Return an Iterator at the ending position, pass the end, of that slot
	Iterator end(const T& v) {return Iterator(_table,hash_func(v),_table[hash_func(v)].end());}
private:
	//Array of doubly linked list
	DoublyLinkedList<T>* _table;
	//Size
	int _size;
	//Hash function that calls the hash_func() in each record
	int hash_func(const T& v);
};

//Template Class Iterator
template <typename T, int _length>
class HashTable<T,_length>::Iterator {
public:
	//Copy Constructor
	Iterator(const Iterator& it):_table(it._table),index(it.index),cur(it.cur) {}
	//Constructor
	//Used by HashTable
	Iterator(DoublyLinkedList<T>* tb, int id, typename DoublyLinkedList<T>::Iterator it)
		:_table(tb),index(id),cur(it) {}
	//Desturctor
	~Iterator() {}
	//Overloaded operator*
	T& operator* () {return *cur;}
	//Overloaded operator++
	Iterator& operator++ ();
	//Overloaded operator=
	void operator= (Iterator it) {
		_table = it._table;
		index = it.index;
		cur = it.cur;
	}
	//Overloaded operator!=
	//Compare the DoublyLinkedList Iterator
	bool operator!= (Iterator it) {return cur!=it.cur;}
	//Overloaded operator==
	//Compare the DoublyLinkedList Iterator
	bool operator== (Iterator it) {return cur==it.cur;}
	//Return the DoublyLinkedList Iterator
	//Used by remove_prev(const Iterator&)
	typename DoublyLinkedList<T>::Iterator& _list_iterator() {return cur;}
	const typename DoublyLinkedList<T>::Iterator& _list_iterator_const() const {return cur;}
	//Return index
	//Used by remove_prev(const Iterator&)
	int _index() const {return index;}
public:
	//Copy of the DoublyLinkedList array pointer
	DoublyLinkedList<T>* _table;
	//Index, the current no of slot
	int index;
	//The current DoublyLinkedList Iterator
	typename DoublyLinkedList<T>::Iterator cur;
};

//operator++() of Iterator
template <typename T, int _length>
typename HashTable<T,_length>::Iterator& HashTable<T,_length>::Iterator::operator++ () {
	//Increment
	++cur;
	//If meet the end of that DoublyLinkedList
	if(cur==_table[index].end()) {
		//Find the next non-empty DoublyLinkedList
		++index;
		while(index<_length&&_table[index].begin()==_table[index].end()) ++index;
		//If reach the end, set to the end position
		//Else set to the begining position of that DoublyLinkedList
		if (index == _length) {
			index = _length-1;
			cur = _table[_length-1].end();
		}
		else cur = _table[index].begin();
	}
	//Return the Iterator
	return (*this);
}

//begin() of HashTable
template <typename T, int _length>
typename HashTable<T,_length>::Iterator HashTable<T,_length>::begin() {
	//Find the first non-empty DoublyLinkedList
	int id = 0;
	while(id<_length&&_table[id].begin()==_table[id].end()) ++id;
	//If reach the end, set to the end position
	if (id == _length) return end();
	//Else set to the begining position of that DoublyLinkedList
	return Iterator(_table,id,_table[id].begin());
}

//hash_func(const T&) of HashTable
template <typename T, int _length>
int HashTable<T,_length>::hash_func(const T& v) {
	//Directly call the hash_func() of the Record
	return v.hash_func(_length);
}

//insert(const T&, bool allowRepetition) of HashTable
template <typename T, int _length> 
T* HashTable<T,_length>::insert(const T& v, bool allowRepetition) {
	//Insert to that DoublyLinkedList
	T* tmp = _table[hash_func(v)].insert(v,allowRepetition);
	//If success, modify the size
	if(tmp) ++_size;
	return tmp;
}

//remove(const T&) of HashTable
template <typename T, int _length>
bool HashTable<T,_length>::remove(const T& v) {
	//Remove from that DoublyLinkedList
	bool tmp = _table[hash_func(v)].remove(v);
	//If success, modify the size
	if(tmp) --_size;
	return tmp;
}

//remove_prev(const Iterator&) of HashTable
template <typename T, int _length>
bool HashTable<T,_length>::remove_prev(const Iterator& it){
	//Call remove_prev of that DoublyLinkedList with the DoublyLinkedList Iterator
	bool tmp = _table[it._index()].remove_prev(it._list_iterator_const());
	//If success, modify the size
	if(tmp) --_size;
	return tmp;
}

//find(const T&, Iterator&) of HashTable
template <typename T, int _length>
T* HashTable<T,_length>::find(const T& v, Iterator& it) {
	//Call find of that DoublyLinkedList with the DoublyLinkedList Iterator
	return _table[hash_func(v)].find(v,it._list_iterator());
}

//find(const T&) of HashTable
template <typename T, int _length>
T* HashTable<T,_length>::find(const T& v) {
	//Call find of that DoublyLinkedList
	return _table[hash_func(v)].find(v);
}

//list_size(const T&) of HashTable
template <typename T, int _length>
int HashTable<T,_length>::list_size(const T& v) const {
	//Call size of that DoublyLinkedList
	return _table[hash_func(v)].size();
}

#endif