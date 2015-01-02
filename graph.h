#ifndef __GRAPH__H__
#define __GRAPH__H__
#define DEFAULT_WEIGHT numeric_limits<float>::max()

#include "vector"
#include <limits>

using namespace std;

typedef unsigned int uint;


class Graph{

public:
	class Iterator;
	Graph(uint n, bool isOrientedGraph);
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
			Iterator(const vector<float>& conections, uint vertexSize);
			bool thereIsMore() const;
			void advance();
			int next() const;
		
		private:
			vector<float> _values;
			vector<float>::const_iterator _it;
			int _current;
			uint _vSpace;
	};

private:
	vector<vector<float> > graph;
	uint n;
	uint m;
	bool isOriented;
};

#endif