#include "graph.h"
#include "vector"
#include <limits>

typedef unsigned int uint;
typedef Graph::Iterator Adjacencies;

using namespace std;

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

void dijkstra(Graph& g, uint v){
	/*
	 * Declaring initial variables, set S will check the nodes in "secure zone" of Dijkstra's
	 * algorithm, S will represents the "Secure zone".
	 * By default, node v is in the "secure zone" from the begin of the algorithm.
	 * Pi vector constantly constains the short path from v to all nodes in the secure zone
	 * (invariant of Dijkstra's algorithm).
	 * In the beginning of the algorithm, all shorts ways are considered infinity.
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
};


int main(){
	//Set configuration of the graph
	uint nodesCount = 6;
	bool isOriented = true;
	IMPL implementation = ADJACENCIES_LIST;

	/*
	 * HERE: Charge all edges you want, using the graph API.
	 */

	//Set the origin node to calculate the shortest paths from it to all of the rest nodes, with Dijkstra.
	uint originNodeForDijkstra = 1;

	Graph g(nodesCount, isOriented, implementation);
	dijkstra(g, originNodeForDijkstra);

	return 0;
}
