#include "dijkstra.h"

/**
   paths vector constantly constains the DISTANCE and PREDECESSOR for the path from source
   to de ith node in the secure zone (invariant of Dijkstra's algorithm).

   In the beginning of the algorithm, the paths from source to all nodes are considered as infinity.
   Since, at the beginning the secure zone is just the source node, source to all nodes are just the
   same source node (obviously).

   Q is the priority queue (based on a Fibonacci Heap implementatión of mine) that we
   use to select the node which minimizes the distance to the secure zone.
   Using a Fibonacci heap implementation for the priority queue we get the
   best asymptotical running time of Dijkstra! :)
   O( |E| +  |V| log|V| ) 
 */


vector<pair<Distance, Predecessor> > dijkstra(Graph& g, uint source){
	/*
	  S will mark the nodes in the secure zone.
	  paths and Q are described above.
	*/
	vector<bool> S(g.getN(), false);
	FibonacciHeap Q = FibonacciHeap();
	vector<pair<Distance, Predecessor> > paths(g.getN(), make_pair(FLOAT_INFINITY, source));

	/*
	  Setting distance of source node to 0.
	  Marked source as a node of the secure zone (Dijkstra assumes that the source node is already in the secure zone).
	 */
	S[source-1] = true;
	paths[source-1].first = 0;

	/*
	  The heap priority for one node 'X' is the distance between X and the secure zone.
	  Since the secure zone is just the source node, only the source node has priority 0.
	 */
	for (int i = 0; i < g.getN(); ++i)
		if(i+1 == source)
			Q.insert(0, i+1);
		else
			Q.insert(FLOAT_INFINITY, i+1);

	/*
	  Once generated initial variables and charge the correct weight to 
	  the all nodes in the priority queue, lets begin to expand the 
	  "secure zone" until cover the entire graph.
	 */
	while(!Q.empty()){
			/*
			   Select the node out of the "secure zone" wich minimize the distance to the secure zone.
			   O( log n ) (amortized) with a Priority queue implementation based on a Fibonacci heap :D 
			 */
			auto u = Q.extract_min();

			/*
			   Set u as added to the secure zone (S).
			 */
			S[u-1] = true;

			/*
			   Relax edges for neighbor nodes i to u, where i is still in G\S
			   (where i is not in the secure zone).
			 */
			for (Adjacencies vAdjs = g.adjacentsOf(u); vAdjs.thereIsMore(); vAdjs.advance()) {;
					auto i = vAdjs.next().first;

					if(!S[i-1] && paths[i-1].first > paths[u-1].first + g.getEdgeWeight(u,i)) {
						paths[i-1].first = paths[u-1].first + g.getEdgeWeight(u,i);
						paths[i-1].second = u;

						/*
						   Up the prority of the nodes
						 */
						Q.node_up(i-1, paths[u-1].first + g.getEdgeWeight(u,i));
					}

			}

	}

	/*
       Algorithm end.
       * paths vector contains the minimum distance between the source node and the ith node
             in the index i-1  (paths[i-1].first).
       * Also, in the same index, it contains the predecessor of the ith node to get the
	     shortest path from the source in the second member (paths[i-1].second).
	*/

	 return paths;
};
