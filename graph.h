#ifndef __GRAPH__H__
#define __GRAPH__H__
#define DEFAULT_WEIGHT numeric_limits<float>::max()

#include "vector"
#include "list"
#include <utility>
#include <limits>

using namespace std;

typedef unsigned int uint;

enum IMPL {ADJACENCIES_MATRIX, ADJACENCIES_LIST};

class Graph{

public:
	class Iterator;
	Graph(uint n, bool isOrientedGraph, IMPL impl);
	~Graph();
	void applyEdge(uint v1, uint v2);
	void applyEdge(uint v1, uint v2, float weight);
	bool areAdjacent(uint v1, uint v2) const;
	bool isOrientedGraph() const;
	uint getN() const;
	uint getM() const;
	void addVertex();
	float getEdgeWeight(uint v1, uint v2) const;
	const Iterator adjacentsOf(uint v) const;

	class Iterator{
			
		public:	
			Iterator(const vector<float>& conections, uint n, IMPL type);
			Iterator(const list<pair<uint,float> >& adjacents, uint n, IMPL type);
			bool thereIsMore() const;
			void advance();
			int next() const;
		
		private:
			uint _vSpace;
			IMPL _type;
			vector<float> _values;
			list<pair<uint,float> > _adjacents;
			vector<float>::const_iterator _it;
			list<pair<uint,float> >::const_iterator _iter;
			int _current;
			bool firstCall;
	};

private:
	vector<vector<float> > matrix;
	vector<list<pair<uint,float> > > adjList;
	uint n;
	uint m;
	bool isOriented;
	IMPL type;

};

#endif