#include <stdio.h>
#include <limits>
#include "vector"
#include "dijkstra.h"
#include "graph.h"

using namespace std;

void print_results(uint originNode, vector<pair<Distance, Predecessor> > paths) {
	vector<uint> path;
	path.reserve(paths.size());

	for (uint i = 0; i < paths.size(); ++i) {		
		printf("\n%u->%u: ", originNode, i+1);

		if(paths[i].first != numeric_limits<float>::max()) {
				path.clear();
				path.push_back(i+1);


				if(i+1 != originNode){
					uint predecessor = paths[i].second;
					while(predecessor != originNode) {
						path.push_back(predecessor);
						predecessor = paths[predecessor-1].second;
					}

					path.push_back(originNode);
				}

				printf("\n   Shortest path: ");

				for (int i = path.size()-1; i >= 0; --i)
					printf("%u ", path[i]);

				printf("   with a distance: %f\n", paths[i].first);

		} else {
				printf("\n   Unreacheable\n");
		}
	}
}



int main(){
	//Set configuration of the graph
	uint nodesCount = 4;
	bool isOriented = true;
	IMPL implementation = ADJACENCIES_LIST;
	Graph g(nodesCount, isOriented, implementation);

	/*
	 * HERE: Charge all edges you want, using the graph API.
	 */
	 g.applyEdge(0, 1, 3338);
	 g.applyEdge(0, 2, 522);
	 
	 g.applyEdge(1, 0, 11555);
	 g.applyEdge(1, 2, 3354);
	 
	 g.applyEdge(2, 0, 1654);
	 g.applyEdge(2, 1, 6565);
	 
	 g.applyEdge(3, 0, 5422);
	 g.applyEdge(3, 1, 66);
	 g.applyEdge(3, 2, 242);

	//Set the origin node to calculate the shortest paths from it to all of the rest nodes, with Dijkstra.
	uint sourceNode = 3;
	
	/**
	 * Executing Dijkstra's algorithm
	 */
	auto paths = dijkstra(g, sourceNode);

	print_results(sourceNode, paths);

	return 0;
}

