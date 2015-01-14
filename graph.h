#ifndef __GRAPH__H__
#define __GRAPH__H__
#define DEFAULT_WEIGHT numeric_limits<float>::max()

#include "vector"
#include "list"
#include <utility>
#include <limits>

using namespace std;

typedef unsigned int uint;

struct Edge{
	uint from;
	uint to;
	float weight;

	Edge(uint f, uint t, float w){
		this->from = f;
		this->to = t;
		this->weight = w;
	}
};



enum IMPL {ADJACENCIES_MATRIX, ADJACENCIES_LIST};

class Graph{

public:
	class Iterator;

	/*
	 * Construct a simple graph, with n nodes. Is necesary to define if the graph is oriented or not and if 
	 * it is implemented over adjacencies matrix (ADJACENCIES_MATRIX) or adjacencies lists (ADJACENCIES_LIST), enum IMPL indicates this.
	 * Each makes graph operations more performantes in diferent cases.
	 * Nodes are represented by numbers between 1 and n inclusive.
	 */
	Graph(uint n, bool isOrientedGraph, IMPL impl);

	/*
	 * Applies an edge between two diferent nodes v1 and v2(nodes must be already applied to the graph).
	 * This method is util when the graph edges hasn't weight.
	 */
	void applyEdge(uint v1, uint v2);

	/*
	 * Applies an edge with a weight, between two diferent nodes v1 and v2 (nodes must be already applied to the graph).
	 * This method is util when the graph has weight in each edge.
	 */
	void applyEdge(uint v1, uint v2, float weight);

	/*
	 * In non-oriented graph, returns if nodes v1 and v2, are adjacents, that means if exist an edge between both.
	 * If graph is oriented, returns if exist an edge from node v1 to node v2. 
	 */
	bool areAdjacent(uint v1, uint v2) const;
	
	/*
	 * Return if the graph is oriented or not, true if it is.
	 */
	bool isOrientedGraph() const;
	
	/*
	 * Get the cuantity of direfent nodes are now in the graph.
	 */
	uint getN() const;

	/*
	 * Get the cuantity of direfent edges are now inserted in the graph.
	 */
	uint getM() const;

	/*
	 * Return all edges of the graph, in a set.
	 */
	vector<Edge>& getEdges();

	/*
	 * Add a new vertex, with out adjacents.
	 * Increases n by one.
	 */
	void addVertex();

	/*
	 * Return the weight of the edge between nodes v1 and v2. If the graph is non-oriented, the orden of the parameters 
	 * doesn't matter, but it's important in a oriented graph, v1 indicates the origin of the edge, and v2 indicates the end.
	 */
	float getEdgeWeight(uint v1, uint v2) const;

	/*
	 * Return an iterator of the adjacents nodes for a single node in the graph.
	 */
	const Iterator adjacentsOf(uint v) const;

	class Iterator{
			
		public:	
			Iterator(const vector<float>& conections, uint n, IMPL type);
			Iterator(const list<pair<uint,float> >& adjacents, uint n, IMPL type);
			
			/*
			 * Get actual adjacent of the iterator. This not modify the iterator status.
			 */
			int next() const;

			/*
			 * Indicates if exist an adjacent node for review 
			 */
			bool thereIsMore() const;

			/*
			 * Moves the iterator to the next adjacent. This change the output of next() method in the next call to it.
			 */
			void advance();
		
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
	vector<Edge> edges;

};

#endif