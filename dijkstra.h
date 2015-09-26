#include "graph.h"
#include "fibonacci-heap/fib-heap.h"
#include "vector"
#include <limits>

typedef Graph::Iterator Adjacencies;

typedef unsigned int uint;
typedef unsigned int Predecessor;
typedef float Distance;

using namespace std;

vector<pair<Distance, Predecessor> > dijkstra(Graph& g, uint source);
