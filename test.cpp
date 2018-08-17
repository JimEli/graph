// Shortest path between 2 vertices of unweighted graph.
#include <iostream>

#include "graph.h"

using namespace std;

// Driver program to test graph functions.
int main()
{
	Graph g;
	int source = 0, destination = 7;

	// add_edge(source vertex, destination vertex).
	g.addEdge(0, 1);
	g.addEdge(0, 3);
	g.addEdge(1, 2);
	g.addEdge(3, 4);
	g.addEdge(3, 7);
	g.addEdge(4, 5);
	g.addEdge(4, 6);
	g.addEdge(4, 7);
	g.addEdge(5, 6);
	g.addEdge(6, 7);

	g.printShortestDistance(source, destination);
}
