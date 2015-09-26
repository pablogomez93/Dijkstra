#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <list>

template<typename T> 
class CircularLinkedList : public std::list<T> {

	public:
		typename std::list<T>::iterator right(typename std::list<T>::iterator current) {
			if(current == --this->end()) {
				return this->begin();
			} else {
				return ++current;
			}
		};

		typename std::list<T>::iterator left(typename std::list<T>::iterator current) {
			if(current == this->begin())
				return --this->end();
			else
				return --current;
		};
};


#endif //CIRCULAR_DOUBLY_LINKED_LIST_H