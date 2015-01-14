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
	/* Declaring initial variables, set S will check the nodes in "secure zone" of Dijkstra's algorithm.
	 * By default, node v is in the "secure zone".
	 * Pi vector contains constantly the short path from v to all nodes in the secure zone (invariant of Dijkstra's algorithm).
	 * By default, all shorts ways are infinity.
	 */
	vector<bool> S(g.getN(),false);
	S[v-1] = true;
	vector<float> pi(g.getN(),numeric_limits<float>::max());
	
	/*
	 * Setting position of v in pi vector to 0, and replacing the position of each adjacent of v to the weight between it and v.
	 */
	for (Adjacencies vAdjs = g.adjacentsOf(v); vAdjs.thereIsMore(); vAdjs.advance())
		pi[vAdjs.next()-1] = g.getEdgeWeight(v,vAdjs.next());

	pi[v-1] = 0;
	
	/*
	 * Once generate initial variables and charge the correct weight to adjacents of v in pi vector, 
	 * begin to expand the "secure zone".
	 */
	uint count = 1;
	while(count < g.getN()){
		/*
		 * Select the node out of the "secure zone" wich minimize the distance to the secure zone.
		 */
		uint u = getMinimunOfPI(pi, S);

		/*
		 * Set u as added to the S set.
		 */
		S[u-1] = true;
	
		/*
		 * Relax edges for adjacents nodes to u.
		 */
		for (Adjacencies vAdjs = g.adjacentsOf(u); vAdjs.thereIsMore(); vAdjs.advance()){
			int i = vAdjs.next();

			if(pi[i-1] > pi[u-1] + g.getEdgeWeight(u,i))
				pi[i-1] = pi[u-1] + g.getEdgeWeight(u,i);
		}		

		count++;
	}
	
	/*
	 * Algorithm end.
	 * pi vector variable has all short paths, from original v to all nodes
	 */
};


int main(){
	Graph g(6, true, ADJACENCIES_LIST);

	g.applyEdge(1,2,4);
	g.applyEdge(1,3,7);
	g.applyEdge(1,6,3);
	g.applyEdge(2,3,3);
	g.applyEdge(2,5,1);
	g.applyEdge(3,4,1);
	g.applyEdge(3,5,1);
	g.applyEdge(5,4,4);
	g.applyEdge(6,5,3);

	dijkstra(g,1);

	return 0;
}