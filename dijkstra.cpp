#include "graph.h"
#include "vector"
#include <stdio.h>
#include <limits>

typedef unsigned int uint;
typedef Graph::Iterator Adjacencies;

using namespace std;

void print_final_minimum_distances(int originNode, vector<float> paths) {
	for (int i = 0; i < paths.size(); ++i)
		printf("Desde %d hasta %d: %f \n", originNode, i+1, paths[i]);
}

uint getMinimunOfPI(vector<float>& pi, vector<bool>& S){
	uint minimum = 0;
	float minimal = numeric_limits<float>::max();

	for (uint i = 0; i < pi.size(); ++i)
		if(!S[i] && pi[i] < minimal){
			minimum = i;
			minimal = pi[i];
		}

	return minimum+1;
}

vector<float> dijkstra(Graph& g, uint v){
	/*
	 * Declaring initial variables, set S will check the nodes in "secure zone" of Dijkstra's
	 * algorithm, S will represents the "Secure zone".
	 * By default, node v is in the "secure zone" from the begin of the algorithm.
	 * Pi vector constantly constains the short path from v to all nodes in the secure zone
	 * (invariant of Dijkstra's algorithm).
	 * In the beginning of the algorithm, the paths from v to all nodes are considered as infinity.
	 */
	vector<bool> S(g.getN(), false);
	S[v-1] = true;
	vector<float> pi(g.getN(), numeric_limits<float>::max());

	/*
	 * Setting distance of v in pi vector to 0, and replacing the distance of each node adjacent of
	 * v to the weight between it and v.
	 */
	for (Adjacencies vAdjs = g.adjacentsOf(v); vAdjs.thereIsMore(); vAdjs.advance())
		pi[vAdjs.next()-1] = g.getEdgeWeight(v, vAdjs.next());

	pi[v-1] = 0;

	/*
	 * Once generate initial variables and charge the correct weight to adjacents of v in pi vector,
	 * lets begin to expand the "secure zone" until cover the entire graph.
	 */
	uint count = 1;
	while(count < g.getN()){
		/*
		 * Select the node out of the "secure zone" wich minimize the distance to the secure zone.
		 */
		uint u = getMinimunOfPI(pi, S);

		/*
		 * Set u as added to the secure zone (S).
		 */
		S[u-1] = true;

		/*
		 * Relax edges for neighbor nodes i to u, where i is still in G\S
		 * (where i is not in the secure zone).
		 */
		for (Adjacencies vAdjs = g.adjacentsOf(u); vAdjs.thereIsMore(); vAdjs.advance()){
			int i = vAdjs.next();

			if(!S[i-1] && pi[i-1] > pi[u-1] + g.getEdgeWeight(u,i))
				pi[i-1] = pi[u-1] + g.getEdgeWeight(u,i);
		}

		count++;
	}

	/*
	 * Algorithm end.
	 * pi vector variable has all shortest paths, from original v to all nodes
	 */

	 return pi;
};


int main(){
	//Set configuration of the graph
	uint nodesCount = 4;
	bool isOriented = true;
	IMPL implementation = ADJACENCIES_LIST;
	Graph g(nodesCount, isOriented, implementation);

	/*
	 * HERE: Charge all edges you want, using the graph API.
	 */
	 g.applyEdge(1,2,6);
	 g.applyEdge(1,3,3);
	 g.applyEdge(1,4,5);
	 
	 g.applyEdge(2,1,5);
	 g.applyEdge(2,3,15);
	 g.applyEdge(2,4,9);
	 
	 g.applyEdge(3,1,5);
	 g.applyEdge(3,2,1);
	 g.applyEdge(3,4,15);
	 
	 g.applyEdge(4,1,5);
	 g.applyEdge(4,2,1);
	 g.applyEdge(4,3,15);

	//Set the origin node to calculate the shortest paths from it to all of the rest nodes, with Dijkstra.
	uint originNodeForDijkstra = 1;
	
	/**
	 * Executing Dijkstra's algorithm :)
	 */
	vector<float> paths = dijkstra(g, originNodeForDijkstra);

	print_final_minimum_distances(originNodeForDijkstra, paths);

	return 0;
}

