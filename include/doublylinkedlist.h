//Template Class DoublyLinkedList
//And auxilary template classes Node, DoublyLinkedList<T>::Interator

#ifndef DOUBLYLINKEDLIST
#define DOUBLYLINKEDLIST

//Template Sturct Node
template <typename T>
struct Node {
	//Constructor
	Node():val(),enable(true),prev(NULL),next(NULL) {}
	//Destructor
	~Node() {}
	//Value
	T val;
	//Previous Node Pointer
	Node* prev;
	//Next Node Pointer
	Node* next;
	//Bool to show whhether it is a valid node
	bool enable;
};

//Template Class DoublyLinkedList
template <typename T>
class DoublyLinkedList {
public:
	//Definition of Class Iterator
	class Iterator;
	//Constructor
	DoublyLinkedList();
	//Destructor
	~DoublyLinkedList();
	//Insert
	//allowRepetition set whether the values can be repeated
	T* insert(const T& v, bool allowRepetition = false);
	//Remove
	bool remove(const T& v);
	//Remove the previous value in the sorted doubly linked list
	//Used together with find(const T&, Iterator&)
	bool remove_prev(const Iterator& it);
	//Find
	//Find the value and also modify the iterator to the next position of that value
	T* find(const T& v, Iterator& it);
	//Find
	//Find in a no-repitition doubly linked list, no need to modify the iterator
	T* find(const T& v);
	//Return size
	int size() const {return _size;}
	//Reaturn an Iterator at the begining pisition
	Iterator begin() const {return Iterator(_head->next);}
	//Return an Iterator at the ending position, pass the end
	Iterator end() const {return Iterator(_tail);}
private:
	//Head Node Pointer
	Node<T>* _head;
	//Tail Node Pointer
	Node<T>* _tail;
	//Size
	int _size;
};

//Template Class Iterator
template <typename T>
class DoublyLinkedList<T>::Iterator {
public:
	//Copy Constructor
	Iterator(const Iterator& it):cur(it.cur) {}
	//Conversion Constructor
	Iterator(Node<T>* nd):cur(nd) {}
	//Destructor
	~Iterator() {}
	//Overloaded operator*
	T& operator* () {return cur->val;}
	//Overloaded operator++
	Iterator& operator++ () {
		cur = cur->next;
		return (*this);
	}
	//Overloaded operator--
	Iterator& operator-- () {
		cur = cur->prev;
		return (*this);
	}
	//Overloaded operator=
	void operator= (Iterator it) {cur = it.cur;}
	//Overloaded operator==
	//Compare the pointer address
	bool operator== (Iterator it) {return cur==it.cur;}
	//Overloaded operator!=
	//Compare the pointer address
	bool operator!= (Iterator it) {return cur!=it.cur;}
	//Return the node pointer
	//Used by remove_prev(const Iterator&) 
	Node<T>* _node_pointer() const {return cur;}
private:
	//Node Pointer
	Node<T>* cur;
};

//Counstructor of DoublyLinkedList
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	//Initialize the head and tail node
	_head = new Node<T>;
	_tail = new Node<T>;
	//Not enable them
	_head->enable = false;
	_tail->enable = false;
	//Link them
	_head->next = _tail;
	_tail->prev = _head;
	//Set size
	_size = 0;
}

//Destructor of DoublyLinkedList
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	//Delete all the enabled node
	Node<T>* cur = _head->next;
	while (cur->enable) {
		cur = cur->next;
		delete cur->prev;
	}
	//Delete head and tail
	delete _head;
	delete _tail;
	//Set to null
	_head = NULL;
	_tail = NULL;
	_size = 0;
}

//find(const T&, Iterator&) of DoublyLinkedList
template <typename T>
T* DoublyLinkedList<T>::find(const T& v, Iterator& it) {
	//If starts at the end position, return null
	if(it==end()) return NULL;
	//Use iterator to scan
	for (;it!=end();++it) {
		//If find
		if (*it==v) {
			T* tmp = &(*it);
			//Set the iterator to the next position
			++it;
			return tmp;
		}
		//If overlooked, set iterator to the end position and return null
		if (v<*it) {
			it = end();
			return NULL;
		}
	}
	return NULL;
}

//find(const T&) of DoublyLinkedList
template <typename T>
T* DoublyLinkedList<T>::find(const T& v) {
	//Call find(const T&, Iterator&) with iterator at the begining position
	Iterator it = begin();
	return find(v, it);
}

//insert(const T&, bool allowRepetition) of DoublyLinkedList
template <typename T>
T* DoublyLinkedList<T>::insert(const T& v, bool allowRepetition) {
	Node<T>* cur = _head->next;
	//Find the insertion position
	while (cur->enable&&(cur->val<v)) {
		cur = cur->next;
	}
	//If find repitition and doesn't allow, return null
	if ((!allowRepetition)&&cur->enable&&(cur->val==v)) return NULL;
	//Insert the new Node
	Node<T>* nd = new Node<T>;
	nd->val = v;
	nd->prev = cur->prev;
	nd->next = cur;
	cur->prev->next = nd;
	cur->prev = nd;
	//Modify size
	++_size;
	//Return the pointer to value
	return &(nd->val);
}

//remove(const T&) of DoublyLinkedList
template <typename T>
bool DoublyLinkedList<T>::remove(const T& v) {
	Node<T>* cur = _head->next;
	//Find the value, first appearence
	while (cur->enable) {
		if (cur->val==v) break;
		//If overlook, return false
		if (v<cur->val) return false;
		cur = cur->next;
	}
	//If cannot find, return false
	if (!cur->enable) return false;
	//Delete that node
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	delete cur;
	//Modify size
	--_size;
	//Return true
	return true;
}

//remove_prev(const Iterator&) 
template <typename T>
bool DoublyLinkedList<T>::remove_prev(const Iterator& it) {
	//Get the Node pointer from the iterator
	Node<T>* cur = it._node_pointer();
	cur = cur->prev;
	//Check validity
	if (!cur->enable) return false;
	//Remove Node
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	delete cur;
	//Modify size
	--_size;
	//Return true
	return true;
}

#endif