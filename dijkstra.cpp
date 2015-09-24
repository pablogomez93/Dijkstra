#include "graph.h"
#include "vector"
#include <stdio.h>
#include <limits>

typedef unsigned int uint;
typedef Graph::Iterator Adjacencies;

using namespace std;

void print_final_shortest_distances(uint originNode, vector<float> paths) {
	for (int i = 0; i < paths.size(); ++i)
		printf("From node %u to node %d: %f \n", originNode, i+1, paths[i]);
}

void print_final_shortest_paths(uint originNode, vector<uint> paths) {
	vector<uint> path;
	path.reserve(paths.size());

	for (uint i = 0; i < paths.size(); ++i) {		
		printf("From node %u to node %u: ", originNode, i+1);

			path.clear();
			path.push_back(i+1);

			if(i+1 != originNode){
				uint predecessor = paths[i];
				while(predecessor != originNode) {
					path.push_back(predecessor);
					predecessor = paths[predecessor-1];
				}

				path.push_back(originNode);
			}


			for (int i = path.size()-1; i >= 0; --i)
				printf("%u ", path[i]);

			printf("\n");
	}
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

vector<uint> dijkstra(Graph& g, uint v){
	/*
	 * Declaring initial variables, set S will check the nodes in "secure zone" of Dijkstra's
	 * algorithm, S will represents the "Secure zone".
	 * By default, node v is in the "secure zone" from the begin of the algorithm.

	 */
	vector<bool> S(g.getN(), false);
	S[v-1] = true;

	/**
	 * pi vector constantly constains the DISTANCE of the shortest path from v to all nodes in the secure zone
	 * (invariant of Dijkstra's algorithm).
	 * In the beginning of the algorithm, the paths from v to all nodes are considered as infinity.

	 * predecessor vector constantly constains the SHORTEST PATH from v to all nodes in the secure zone.
	 * Since the secure zone is just v, at the beginning the paths from v to all nodes are just... v.
	 */
	vector<uint> predecessor(g.getN(), v);
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

			if(!S[i-1] && pi[i-1] > pi[u-1] + g.getEdgeWeight(u,i)) {
				pi[i-1] = pi[u-1] + g.getEdgeWeight(u,i);
				predecessor[i-1] = u;
			}
		}

		count++;
	}

	/*
	 * Algorithm end.
	 * - predecessor vector contains all shortest paths from v to all nodes;
	 * - pi vector contains all distances for shortest paths from original v to all nodes
	 */

	 return predecessor;
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
	 g.applyEdge(1,2,1);
	 g.applyEdge(1,3,1000);
	 g.applyEdge(1,4,1000);
	 
	 g.applyEdge(2,1,1000);
	 g.applyEdge(2,3,1);
	 g.applyEdge(2,4,1000);
	 
	 g.applyEdge(3,1,1000);
	 g.applyEdge(3,2,1000);
	 g.applyEdge(3,4,1000);
	 
	 g.applyEdge(4,1,1);
	 g.applyEdge(4,2,1000);
	 g.applyEdge(4,3,1000);

	//Set the origin node to calculate the shortest paths from it to all of the rest nodes, with Dijkstra.
	uint originNodeForDijkstra = 1;
	
	/**
	 * Executing Dijkstra's algorithm :)
	 */
	auto paths = dijkstra(g, originNodeForDijkstra);

	print_final_shortest_paths(originNodeForDijkstra, paths);

	return 0;
}

