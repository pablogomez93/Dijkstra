#include "graph.h"
#include "vector"
#include "iostream"
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
	vector<bool> S(g.getN(),false);
	S[v-1] = true;
	vector<float> pi(g.getN(),numeric_limits<float>::max());
	
	for (Adjacencies vAdjs = g.adjacentsOf(v); vAdjs.thereIsMore(); vAdjs.advance()){
		pi[vAdjs.next()-1] = g.getEdgeWeight(v,vAdjs.next());
	}
	pi[v-1] = 0;
	
	uint count = 1;
	while(count < g.getN()){
		v = getMinimunOfPI(pi, S);
		S[v-1] = true;
	
		for (Adjacencies vAdjs = g.adjacentsOf(v); vAdjs.thereIsMore(); vAdjs.advance()){
			int i = vAdjs.next();

			if(pi[i-1] > pi[v-1] + g.getEdgeWeight(v,i))
				pi[i-1] = pi[v-1] + g.getEdgeWeight(v,i);
		}		

		count++;
	}
	
	/*
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