#include "graph.h"

Graph::Graph(uint nodesSpaceSize, bool isOrientedGraph, IMPL impl) {
	n = nodesSpaceSize;
	m = 0;
	isOriented = isOrientedGraph;
	type = impl;
	edges = vector<Edge>();
	if(type == ADJACENCIES_MATRIX)
		matrix = vector<vector<float> > (n, vector<float>(n, DEFAULT_WEIGHT));
	else
		adjList = vector<list<pair<uint,float> > >(n, list<pair<uint,float> >());
}

bool Graph::isOrientedGraph() const {
	return isOriented;
}

uint Graph::getN() const {
	return n;
}

uint Graph::getM() const {
	return m;
}

vector<Edge>& Graph::getEdges() {
	return edges;
}

float Graph::getEdgeWeight(uint v1, uint v2) const {
	if(type == ADJACENCIES_MATRIX)
		return matrix[v1-1][v2-1];
	else
		for (list<pair<uint,float> >::const_iterator it = adjList[v1-1].begin(); it != adjList[v1-1].end(); it++)
			if(it->first == v2)
				return it->second;
}

bool Graph::areAdjacent(uint v1, uint v2) const {
	if(type == ADJACENCIES_MATRIX)
		return matrix[v1-1][v2-1] != DEFAULT_WEIGHT;
	else {
		for (list<pair<uint,float> >::const_iterator it = adjList[v1-1].begin(); it != adjList[v1-1].end(); it++)
			if(it->first == v2)
				return true;

		return false;
	}
}

void Graph::applyEdge(uint v1, uint v2) {
	if(type == ADJACENCIES_MATRIX) {
		if(matrix[v1-1][v2-1] == DEFAULT_WEIGHT) {
			m++;
			edges.push_back(Edge(v1, v2, 1));
		}

		matrix[v1-1][v2-1] = 1;

		if(!isOriented)
			matrix[v2-1][v1-1] = 1;
	} else {
		adjList[v1-1].push_back(make_pair(v2, 1));

		if(!isOriented)
			adjList[v2-1].push_back(make_pair(v1, 1));

		m++;
		edges.push_back(Edge(v1, v2, 1));
	}
}

void Graph::applyEdge(uint v1, uint v2, float weight) {
	if(type == ADJACENCIES_MATRIX) {
		if(matrix[v1-1][v2-1] == DEFAULT_WEIGHT) {
			m++;
			edges.push_back(Edge(v1,v2,weight));
		}

		matrix[v1-1][v2-1] = weight;

		if(!isOriented)
			matrix[v2-1][v1-1] = weight;
	} else {
		adjList[v1-1].push_back(make_pair(v2, weight));

		if(!isOriented)
			adjList[v2-1].push_back(make_pair(v1, weight));

		m++;
		edges.push_back(Edge(v1,v2,weight));
	}

}

void Graph::addVertex() {
	if(type == ADJACENCIES_MATRIX) {
		for (int i = 0; i < n; ++i)
			matrix[i].push_back(DEFAULT_WEIGHT);

		matrix.push_back(vector<float>(n+1, DEFAULT_WEIGHT));

	} else {
		adjList.push_back(list<pair<uint,float> >());
	}

	n++;
}

const typename Graph::Iterator Graph::adjacentsOf(uint v) const {
	if(type == ADJACENCIES_MATRIX)
		return Iterator(matrix[v-1], n, type);
	else
		return Iterator(adjList[v-1], n, type);
}





/*
 * Adjacents iterator implementation.
 */

Graph::Iterator::Iterator(const vector<float>& conections, uint n, IMPL type) {
 	_values = conections;
	_it = _values.begin();
	_current = -1;

	for (int current = 0; current < _vSpace; ++current)
		if(_values[current] != DEFAULT_WEIGHT) {
			_current = current;
			break;
		}

	_vSpace = n;
	_type = type;
}

Graph::Iterator::Iterator(const list<pair<uint,float> >& adjacents, uint n, IMPL type) {
 	_adjacents = adjacents;
	_iter = _adjacents.begin();

	_vSpace = n;
	_type = type;
}

void Graph::Iterator::advance() {
	if(_type == ADJACENCIES_MATRIX) {
		_current++;
		while(_current < _vSpace) {
			if(_values[_current] != DEFAULT_WEIGHT)
				break;

			_current++;
		}

	} else
		_iter++;

	return;
}

pair<uint,float> Graph::Iterator::next() const {
	if(_type == ADJACENCIES_MATRIX)
		return make_pair(_current + 1, _values[_current]);
	else
		return (*_iter);
}

bool Graph::Iterator::thereIsMore() const {
	if(_type == ADJACENCIES_MATRIX)
		return -1 < _current && _current < _vSpace;
	else
		return _iter != _adjacents.end();
}
