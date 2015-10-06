#ifndef FIBHEAP_H
#define FIBHEAP_H

/*
   Cola de prioridad basada en un Fibonacci Heap simple
   para el algoritmo de Dijkstra.
   Usando una cola de prioridad como esta se consiguen
   las mejores complejidades para este algoritmo.
   O( |E| +  |V| log|V| ) 
 */

#include <limits>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "circular_doubly_linked_list/circular_doubly_linked_list.h"

/**
   Esta implementation de cola de prioridad basada en un Fibonacci heap requiere
   la std de c++11 para compilar correctamente.
   Si se utiliza el Makefile adjunto, este lo hará por vos :).
 */

using namespace std;
 
struct Node {
	float key;
	bool marked;
	uint value;
	int degree;
	CircularLinkedList<Node*> children;
	Node* parent;
	int oid;
};

class FibonacciHeap {
	
typedef CircularLinkedList<Node*> node_list;

public:
FibonacciHeap() {
	_min = _roots.end();
	_n     = 0;
	_roots = node_list();
	_next_oid = 0;
}

int insert(float key, uint val) {
	Node* newGuest = new Node{key, false, val, 0, node_list(), nullptr, _next_oid++};

	/**
	 * Adding node to the roots list of the heap. 
	 */
	_roots.push_back(newGuest);

	/**
	 * Save a reference to the new node
	 */
	_references.push_back(--(_roots.end()));

	/**
	 * Update minimum of the entire heap.
	 */
	if(_min == _roots.end() || (*_min)->key > newGuest->key)
		_min = --(_roots.end());

	/**
	 * Increase the count of the elements current in the heap.
	 */
	_n++;

	return newGuest->oid;
}

uint extract_min() {
	if(_n < 1)	throw runtime_error("Heap empty. There is no minimum to extract!");

	uint backup_min = (*_min)->value;

	/**
	 * Applying all children of the smallest node as roots of the heap
	 * cleaning its parent (it becomes null).
	 */
	for (auto it = (*_min)->children.begin(); it != (*_min)->children.end(); ++it) {
		(*it)->parent = nullptr;
		_roots.push_back(*it);

		_references[(*it)->oid] = --(_roots.end());
	}

	/**
	 * Removing the minimum node of the root_list.
	 */
	_rightNode = _roots.right(_min);
	_roots.erase(_min);
	_references[(*_min)->oid] = _roots.end();
	_min = _roots.end();

	if(_roots.size() > 0)
		_consolidate();

	_n--;
	
	return backup_min;
}

void node_up(int node_id, float key) {
	auto x = *(_references[node_id]);

	x->key = key;
	auto p = x->parent;

	if(p != nullptr && x->key < p->key) {
		_cut(x, p);
		_cascading_cut(p);
	}

	if(x->key < (*_min)->key) 
		_min = _references[node_id];
}	

bool empty() const {return !_n;}

private:
void _swap(Node** x, Node** y) {
	auto temp = *x;
	*x = *y;
	*y = temp;
}

void _consolidate() {
	vector<Node*> roots_sort_by_degree;
	roots_sort_by_degree.reserve(log2(_n));

	for (int i = 0; i <= log2(_n); i++)
			roots_sort_by_degree.push_back(nullptr);

    for (int i = _roots.size(); i > 0; i--) {
	    	auto x  = (*_rightNode);
			_rightNode = _roots.right(_rightNode);

			int d = x->degree;
			while(roots_sort_by_degree[d] != nullptr) {
					auto y = roots_sort_by_degree[d];

					if(x->key > y->key)
						_swap(&x, &y);

					_link(y, x);
					roots_sort_by_degree[d] = nullptr;
					d++;
			}

			roots_sort_by_degree[d] = x;
    }

    for (int i = 0; i < roots_sort_by_degree.size(); i++)
	    	if(roots_sort_by_degree[i] != nullptr) {
	    		if(_min == _roots.end())	
	    			_roots.clear();

	    		_roots.push_back(roots_sort_by_degree[i]);
	    		_references[roots_sort_by_degree[i]->oid] = (--(_roots.end()));

	    		if(_min == _roots.end() || roots_sort_by_degree[i]->key < (*_min)->key)
	    			_min = --(_roots.end());
	    	}
}

void _link(Node* y, Node* x) {
	x->children.push_back(y);
	x->degree++;
	y->marked = false;
	y->parent = *(_references[x->oid]);
	
	_roots.erase(_references[y->oid]);
	_references[y->oid] = --((x->children).end());
}

void _cut(Node* x, Node* y) {
	y->children.erase(_references[x->oid]);
	y->degree--;
	x->parent = nullptr;
	x->marked = false;

	_roots.push_back(x);
	_references[x->oid] = --(_roots.end());
}

void _cascading_cut(Node* y) {
	auto z = y->parent;
	if(z != nullptr)
		if(!y->marked) {
			y->marked = true;
		} else {
			_cut(y, z);
			_cascading_cut(z);
		}
}

int _n, _next_oid;
node_list _roots;
vector<typename node_list::iterator> _references;
typename node_list::iterator _min, _rightNode;

};

#endif //FIBHEAP_H