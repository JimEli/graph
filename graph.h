// Directed unweighted graph.
// Calculates BFS shortest path between 2 vertices.
#include <iostream>
#include <vector>
#include <limits>

#include "queue.h"
#include "range_for_reverse_iterator.h"

// Number of vertices.
const int NUM_VERTICES = 8;

class Graph
{
private:
	// Graph adjaceny list.
	std::vector<int> adjList[NUM_VERTICES];
	// Predecessor of i.
	int pred[NUM_VERTICES];
	// Distance of i from src.
	int dist[NUM_VERTICES];

public:
	// Form edge between adjacency list vertices source and dest.
	void addEdge(int src, int dest)
	{
		adjList[src].push_back(dest);
		adjList[dest].push_back(src);
	}

	// Modified BFS stores predecessor of each vertex in array p and its distance from source in array d.
	bool BFS(int src, int dest)
	{
		// Queue of vertices whose adjacency list is scanned per normal DFS algorithm.
		Queue<int> queue;
		// Stores information whether ith vertex is reached at least once in BFS.
		bool visited[NUM_VERTICES];

		// Initially all vertices are unvisited so v[i] for all is false.
		// And as no path yet constructed dist[i] for all set to infinity.
		for (int i = 0; i < NUM_VERTICES; i++) 
		{
			visited[i] = false;
			dist[i] = std::numeric_limits<int>::max();
			pred[i] = -1;
		}

		// Now source is 1st to be visited & distance from source to itself should be 0.
		visited[src] = true;
		dist[src] = 0;
		queue.push_back(src);

		// Standard BFS algorithm.
		while (!queue.empty())
		{
			int u = queue.front();
			queue.pop_front();

			for (unsigned i = 0; i < adjList[u].size(); i++)
			{
				if (visited[adjList[u][i]] == false)
				{
					visited[adjList[u][i]] = true;
					dist[adjList[u][i]] = dist[u] + 1;
					pred[adjList[u][i]] = u;
					queue.enqueue(adjList[u][i]);

					// Stop BFS when destination is found.
					if (adjList[u][i] == dest)
						return true;
				}
			}
		}

		return false;
	}

	// Print shortest distance between source and destination vertex.
	void printShortestDistance(int src, int dest)
	{
		if (BFS(src, dest) == false)
		{
			std::cout << "Given source and destination are not connected";
			return;
		}

		// Shortest path.
		std::vector<int> path;
		// Walk the path.
		int step = dest;

		path.push_back(dest);
		while (pred[step] != -1)
		{
			path.push_back(pred[step]);
			step = pred[step];
		}

		// Distance from source is in distance array.
		std::cout << "Shortest path length is : " << dist[dest] << std::endl;

		// Print path from source to destination.
		std::cout << "Path is: ";
		for (int i : reverse(path))
			std::cout << i << " ";
	}
};
