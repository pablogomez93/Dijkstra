#include "graph.h"

Graph::Graph(uint n, bool isOrientedGraph, IMPL impl){
	this->n = n;
	this->m = 0;
	this->isOriented = isOrientedGraph;
	this->type = impl;
	if(this->type == ADJACENCIES_MATRIX)
		this->matrix = vector<vector<float> > (n, vector<float>(n, DEFAULT_WEIGHT));
	else
		this->adjList = vector<list<pair<uint,float> > >(n, list<pair<uint,float> >());
}

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
	if(this->type == ADJACENCIES_MATRIX)
		return this->matrix[v1-1][v2-1];
	else 
		for (list<pair<uint,float> >::const_iterator it = adjList[v1-1].begin(); it != adjList[v1-1].end(); it++)
			if((*it).first == v2)
				return (*it).second;
}

bool Graph::areAdjacent(uint v1, uint v2) const{
	if(this->type == ADJACENCIES_MATRIX)
		return this->matrix[v1-1][v2-1] != DEFAULT_WEIGHT;
	else{
		for (list<pair<uint,float> >::const_iterator it = adjList[v1-1].begin(); it != adjList[v1-1].end(); it++)
			if((*it).first == v2)
				return true;

		return false;
	}
}

void Graph::applyEdge(uint v1, uint v2){
	if(this->type == ADJACENCIES_MATRIX){
		if(this->matrix[v1-1][v2-1] == DEFAULT_WEIGHT)
			this->m++;
		
		this->matrix[v1-1][v2-1] = 1;

		if(!this->isOriented)
			this->matrix[v2-1][v1-1] = 1;
	}else{
		adjList[v1-1].push_back(make_pair(v2,1));
	
		if(!this->isOriented)
			adjList[v2-1].push_back(make_pair(v1,1));

		this->m++;
	}
}

void Graph::applyEdge(uint v1, uint v2, float weight){
	if(this->type == ADJACENCIES_MATRIX){
		if(this->matrix[v1-1][v2-1] == DEFAULT_WEIGHT)
			this->m++;
		
		this->matrix[v1-1][v2-1] = weight;

		if(!this->isOriented)
			this->matrix[v2-1][v1-1] = weight;
	}else{
		adjList[v1-1].push_back(make_pair(v2, weight));
	
		if(!this->isOriented)
			adjList[v2-1].push_back(make_pair(v1, weight));		

		this->m++;
	}

}

void Graph::addVertex(){
	if(this->type == ADJACENCIES_MATRIX){
		for (int i = 0; i < this->n; ++i)
			this->matrix[i].push_back(DEFAULT_WEIGHT);

		this->matrix.push_back(vector<float>(this->n + 1, DEFAULT_WEIGHT));
	
	}else{
		this->adjList.push_back(list<pair<uint,float> >());
	}

	this->n++;
}

const typename Graph::Iterator Graph::adjacentsOf(uint v) const{
	if(this->type == ADJACENCIES_MATRIX)
		return Iterator(this->matrix[v-1], this->n, this->type);
	else
		return Iterator(this->adjList[v-1], this->n, this->type);
}





/*
 * Adjacents iterator implementation.
 */

Graph::Iterator::Iterator(const vector<float>& conections, uint n, IMPL type){
 	_values = conections;
	_it = _values.begin();
	_current = -1;

	for (int current = 0; current < _vSpace; ++current)
		if(_values[current] != DEFAULT_WEIGHT){
			_current = current;
			break;
		}
	
	_vSpace = n;
	_type = type;
}

Graph::Iterator::Iterator(const list<pair<uint,float> >& adjacents, uint n, IMPL type){
 	_adjacents = adjacents;
	_iter = _adjacents.begin();
	
	_vSpace = n;
	_type = type;
}

void Graph::Iterator::advance(){
	if(_type == ADJACENCIES_MATRIX){
		_current++;
		while(_current < _vSpace){
			if(_values[_current] != DEFAULT_WEIGHT)
				break;

			_current++;
		}

	}else
		_iter++;

	return;
}

int Graph::Iterator::next() const{
	if(_type == ADJACENCIES_MATRIX)
		return _current + 1;
	else
		return (*_iter).first;
}

bool Graph::Iterator::thereIsMore() const{
	if(_type == ADJACENCIES_MATRIX)
		return -1 < _current && _current < _vSpace;	
	else
		return _iter != _adjacents.end();
}
