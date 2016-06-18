#include "graph.h"
#include "vector"

typedef Graph::AdjacentsIterator Adjacencies;

typedef unsigned int uint;
typedef unsigned int Predecessor;
typedef float Distance;

std::vector<std::pair<Distance, Predecessor> > dijkstra(Graph& g, uint source);
