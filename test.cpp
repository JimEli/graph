// Shortest path between 2 vertices of unweighted graph.
#include <iostream>

#include "graph.h"

using namespace std;

// Driver program to test graph functions.
int main()
{
	Graph g;
	int start = 0, goal = 34;

	// Lets solve this simple 6x6 maze:
	// S #### - 012345
	// #  # # - 678901
	// ## # # - 234567
	// #    # - 890123
 	// # ## # - 456789
	// ####G# - 012345
	// # = wall, S = start and G = end.

	// add_edge(adjacency list, src vertex, dest vertex).
	g.addEdge(0, 1);
	g.addEdge(1, 7);
	g.addEdge(7, 8);
	g.addEdge(10, 16);
	g.addEdge(14, 8);
	g.addEdge(14, 20);
	g.addEdge(16, 22);
	g.addEdge(19, 20);
	g.addEdge(19, 25);
	g.addEdge(20, 13);
	g.addEdge(20, 21);
	g.addEdge(21, 22);
	g.addEdge(22, 28);
	g.addEdge(28, 34);

	g.printShortestDistance(start, goal);
}
