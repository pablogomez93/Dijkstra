#include "graph.h"

Graph::Graph(uint n, bool isOrientedGraph){
	vector<vector<float> > newGraph(n, vector<float>(n, DEFAULT_WEIGHT));
	this->graph = newGraph;
	this->n = n;
	this->m = 0;
	this->isOriented = isOrientedGraph;
}

Graph::~Graph(){}

bool Graph::isOrientedGraph() const{
	return this->isOriented;
}

uint Graph::getN() const{
	return this->n;
}

uint Graph::getM() const{
	return this->m;
}

float Graph::getEdgeWeight(uint v1, uint v2) const{
	return this->graph[v1-1][v2-1];
}

bool Graph::areAdjacent(uint v1, uint v2) const{
	return this->graph[v1-1][v2-1] != DEFAULT_WEIGHT;
}

void Graph::applyEdge(uint v1, uint v2){
	if(this->graph[v1-1][v2-1] == DEFAULT_WEIGHT)
		this->m++;
	
	this->graph[v1-1][v2-1] = 1;

	if(!this->isOriented)
		this->graph[v2-1][v1-1] = 1;
}

void Graph::applyEdge(uint v1, uint v2, float weight){
	if(this->graph[v1-1][v2-1] == DEFAULT_WEIGHT)
		this->m++;
	
	this->graph[v1-1][v2-1] = weight;

	if(!this->isOriented)
		this->graph[v2-1][v1-1] = weight;
}

void Graph::addVertex(){
	for (int i = 0; i < this->n; ++i)
		this->graph[i].push_back(DEFAULT_WEIGHT);

	this->n++;
	this->graph.push_back(vector<float>(this->n, DEFAULT_WEIGHT));
}

const typename Graph::Iterator Graph::adjacentsOf(uint v) const{
	return Iterator(this->graph[v-1], this->n);
}



/*
 * Adjacents iterator implementation.
 */

Graph::Iterator::Iterator(const vector<float>& conections, uint n){
	_values = conections;
	_it = _values.begin();
	_current = 0;
	_vSpace = n;
}

void Graph::Iterator::advance(){
	vector<float>::const_iterator iter;

	for (iter = _it; iter != _values.end(); ++iter,_current++){
		if(*iter != DEFAULT_WEIGHT){
			_it = iter;
			_it++;
			_current++;
			break;
		}
	}

	if(_current > _vSpace)
		_current = -1;

	return;
}

int Graph::Iterator::next() const{
	return _current;
}

bool Graph::Iterator::thereIsMore() const{
	vector<float>::const_iterator iter;
	for (iter = _it; iter != _values.end(); ++iter)
		if(*iter != DEFAULT_WEIGHT)
			return true;

	return false;
}
