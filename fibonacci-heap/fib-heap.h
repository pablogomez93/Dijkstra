#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <limits>
#include <vector>
#include "circular_doubly_linked_list.h"

/**
 * This fibonacci heap implementation requires a std of c++11 to compile well.
 * If you use the Makefile attached, it will do it for you :).
 */

typedef unsigned int uint;

using namespace std;
 
struct Node {
	float key;
	bool marked;
	uint value;
	int degree;
	CircularLinkedList<Node*> children;
	Node* parent;
	uint oid;
};

class FibonacciHeap {
	
typedef CircularLinkedList<Node*> node_list;

public:
	//Operations for a mergeable heap:
	FibonacciHeap() {
		_min = _roots.end();
		_n     = 0;
		_roots = node_list();
		_next_oid = 0;
	}

	void insert_nodes(Graph& g, uint v) {
		_references.resize(g.getN(), _roots.end());

		for (uint i = 0; i < g.getN(); i++) {
				if(i == v-1) continue; 
					
				else {
					
						Node* newGuest = new Node{numeric_limits<float>::max(), false, i+1, 0, node_list(), nullptr, i};

						/**
						 * Adding node to the roots list of the heap. 
						 */
						_roots.push_back(newGuest);

						/**
						 * Save a reference to the new node
						 */
						_references[i] = --(_roots.end());

						/**
						 * Update minimum of the entire heap.
						 */
						if(_min == _roots.end() || (*_min)->key > newGuest->key)
							_min = --(_roots.end());

						/**
						 * Increase the count of the elements current in the heap.
						 */
						_n++;
				}
		}
			
		return;
	}


	uint extract_min() {
		uint backup_min = (*_min)->value;

		/**
		 * Applying all children of the smallest node as roots of the heap
		 * cleaning its parent (it becomes null).
		 */
		for (typename node_list::iterator it = (*_min)->children.begin(); it != (*_min)->children.end(); ++it) {
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
	void node_up(uint node_id, float k) {
		Node* x = *(_references[node_id]);

		x->key = k;

		if(x->parent != nullptr && x->key < x->parent->key) {
			_cut(x, x->parent);
			_cascading_cut(x->parent);
		}

		if(x->key < (*_min)->key) 
			_min = _references[node_id];
	}	


	bool isEmpty() {
		return _n == 0;
	}

private:
	int _n, _next_oid;
	node_list _roots;
	vector<typename node_list::iterator> _references;
	typename node_list::iterator _min, _rightNode;

	void _swap(Node** x, Node** y) {
		typename node_list::iterator temp_iterator = _references[(*x)->oid];
		_references[(*x)->oid] = _references[(*y)->oid];
		_references[(*y)->oid] = temp_iterator;

		Node* temp = *x;
		*x = *y;
		*y = temp;
	}

	void _consolidate() {
		vector<Node*> roots_sort_by_degree;
		roots_sort_by_degree.reserve(_n);

		for (int i = 0; i < _n-1; i++)
			roots_sort_by_degree.push_back(nullptr);

	    for (int i = _roots.size(); i > 0; i--) {
	    	Node* x  = (*_rightNode);
	    	_rightNode = _roots.right(_rightNode);

			int d = x->degree;
			while(roots_sort_by_degree[d] != nullptr) {
				Node* y = roots_sort_by_degree[d];

				if(x->key > y->key)
					_swap(&x, &y);

				_link(y, x);
				roots_sort_by_degree[d] = nullptr;
				d++;
			}

			roots_sort_by_degree[d] = x;
	    }

	    _min = _roots.end();

	    for (int i = 0; i < roots_sort_by_degree.size(); i++)
	    	if(roots_sort_by_degree[i] != nullptr) {
	    		if(_min == _roots.end())	
	    			_roots.clear();

	    		_roots.push_back(roots_sort_by_degree[i]);

	    		if(_min == _roots.end() || roots_sort_by_degree[i]->key < (*_min)->key)
	    			_min = --(_roots.end());

	    	}

	}

	void _link(Node* y, Node* x) {
		x->children.push_back(y);
		x->degree++;
		y->marked = false;

		_roots.erase(_references[y->oid]);

		_references[y->oid] = --((x->children).end());
	}

	void _cut(Node* x, Node* y) {
		y->children.erase(_references[x->oid]);
		x->parent = nullptr;
		x->marked = false;

		_roots.push_back(x);

		_references[x->oid] = --(_roots.end());
	}

	void _cascading_cut(Node* y) {
		Node* z = y->parent;
		if(z != nullptr)
			if(!y->marked) {
				y->marked = true;
			} else {
				_cut(y, z);
				_cascading_cut(z);
			}
	}

};

#endif //FIBHEAP_H