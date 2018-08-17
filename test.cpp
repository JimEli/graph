// Shortest path between 2 vertices of unweighted graph.
#include <iostream>

#include "graph.h"

using namespace std;

// Driver program to test graph functions.
int main()
{
	Graph g;
	int source = 0, destination = 7;

	// add_edge(adjacency list, src vertex, dest vertex).
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

#if 0
// Shortest path between 2 vertices of unweighted graph.
#include <iostream>
#include <vector>
#include <limits>

#include "queue.h"
#include "range_for_reverse_iterator.h"

using namespace std;

// Number of vertices.
const int NUM_VERTICES = 8;

// Form edge between adjacency list vertices source and dest.
void addEdge(vector<int> *adjList, int src, int dest)
{
	adjList[src].push_back(dest);
	adjList[dest].push_back(src);
}

// Modified BFS stores predecessor of each vertex in array p and its distance from source in array d.
bool BFS(vector<int> *adjList, int src, int dest, int *pred, int *dist)
{
	// Queue of vertices whose adjacency list is scanned per normal DFS algorithm.
	Queue<int> queue;
	// Stores information whether ith vertex is reached at least once in BFS.
	bool visited[NUM_VERTICES];

	// Initially all vertices are unvisited so v[i] for all is false.
	// And as no path yet constructed dist[i] for all set to infinity.
	for (int i = 0; i < NUM_VERTICES; i++) {
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
void printShortestDistance(vector<int> *adjList, int src, int dest)
{
	// Stores predecessor of i and distance stores distance of i from src.
	int pred[NUM_VERTICES], dist[NUM_VERTICES];

	if (BFS(adjList, src, dest, pred, dist) == false)
	{
		cout << "Given source and destination are not connected";
		return;
	}

	// Shortest path.
	vector<int> path;
	// Walk the path.
	int step = dest;

	path.push_back(dest);
	while (pred[step] != -1)
	{
		path.push_back(pred[step]);
		step = pred[step];
	}

	// Distance from source is in distance array.
	cout << "Shortest path length is : " << dist[dest] << endl;

	// Print path from source to destination.
	cout << "Path is: ";
	for (int i : reverse(path))
		cout << i << " ";
}

// Driver program to test above functions.
int main()
{
	// Array of vectors stores graph in form of an adjacency list.
	vector<int> adj[NUM_VERTICES];
	int source = 0, dest = 7;

	// add_edge(adjacency list, src vertex, dest vertex) form edges between.
	addEdge(adj, 0, 1);
	addEdge(adj, 0, 3);
	addEdge(adj, 1, 2);
	addEdge(adj, 3, 4);
	addEdge(adj, 3, 7);
	addEdge(adj, 4, 5);
	addEdge(adj, 4, 6);
	addEdge(adj, 4, 7);
	addEdge(adj, 5, 6);
	addEdge(adj, 6, 7);

	printShortestDistance(adj, source, dest);
}

//
//
//
#pragma warning (disable: 4786)

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <list>

using namespace std;

const int INFINITY_ = std::numeric_limits<int>::max();

struct Vertex
{
	string name;          // Vertex name
	vector<Vertex *> adj; // Adjacent vertices
	int dist;             // Cost
	Vertex *path;         // Previous vertex on shortest path

	Vertex(const string & nm) : name(nm) { reset(); }

	void reset()
	{
		dist = INFINITY_;
		path = nullptr;
	}
};

typedef map<string, Vertex *> vMap;
typedef pair<string, Vertex *> vPair;

class Graph
{
public:
	Graph() { }
	~Graph();
	void addEdge(const string& sourceName, const string& destName);
	void printPath(const string& destName) const;
	void unweighted(const string& startName);

private:
	Vertex* getVertex(const string& vertexName);
	void printPath(const Vertex& dest) const;
	void clearAll();

	vMap vertexMap;
	vector<Vertex *> allVertices;
};

void Graph::addEdge(const string& sourceName, const string& destName)
{
	Vertex *v = getVertex(sourceName);
	Vertex *u = getVertex(destName);
	v->adj.push_back(u);

	cout << " Edge: " << v->name << ", " << u->name << endl;
}

void Graph::printPath(const string& destName) const
{
	vMap::const_iterator it = vertexMap.find(destName);

	if (it == vertexMap.end())
	{
		cout << "Destination vertex not found\n";
		return;
	}

	const Vertex& w = *(*it).second;

	if (w.dist == INFINITY_)
		cout << destName << " is unreachable";
	else
		printPath(w);

	cout << endl;
}

void Graph::printPath(const Vertex& dest) const
{
	if (dest.path != nullptr)
	{
		printPath(*dest.path);
		cout << " to ";
	}

	cout << dest.name;
}

// If vertexName not present, add to vertexMap, and return the Vertex.
Vertex* Graph::getVertex(const string& vertexName)
{
	vMap::iterator it = vertexMap.find(vertexName);

	if (it == vertexMap.end())
	{
		// Create new vertex.
		Vertex *newv = new Vertex(vertexName);

		allVertices.push_back(newv);
		vertexMap.insert(vPair(vertexName, newv));

		return newv;
	}

	return (*it).second;
}

void Graph::clearAll()
{
	for (unsigned i = 0; i < allVertices.size(); i++)
		allVertices[i]->reset();
}

Graph::~Graph()
{
	for (unsigned i = 0; i < allVertices.size(); i++)
		delete allVertices[i];
}

void Graph::unweighted(const string& startName)
{
	clearAll();

	vMap::iterator it = vertexMap.find(startName);

	if (it == vertexMap.end())
	{
		cout << startName << " is not a vertex in this graph\n";
		return;
	}

	Vertex *start = (*it).second;
	list<Vertex *> q;

	q.push_back(start);
	start->dist = 0;

	while (!q.empty())
	{
		Vertex *v = q.front();
		q.pop_front();

		for (unsigned i = 0; i < v->adj.size(); i++)
		{
			Vertex *w = v->adj[i];

			if (w->dist == INFINITY_)
			{
				w->dist = v->dist + 1;
				w->path = v;
				q.push_back(w);
			}
		}
	}
}

// Process a request; return false if end of file. 
bool processRequest(istream& in, Graph& g)
{
	string startName, destName;

	cout << "Enter start node: ";
	if (!(in >> startName))
		return false;

	cout << "Enter destination node: ";
	if (!(in >> destName))
		return false;

	g.unweighted(startName);
	g.printPath(destName);

	return true;
}

// Reads file given by argv[1], then calls processRequest to compute shortest path.
// Skimpy error checking.
int main(int argc, char *argv[])
{
	Graph g;

	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " graphfile\n";
		return 1;
	}

	ifstream inFile(argv[1]);
	if (!inFile)
	{
		cerr << "Cannot open " << argv[1] << endl;
		return 1;
	}

	string oneLine;
	// Read the words; add them to wordMap
	while (getline(inFile, oneLine))
	{
		string source, dest;

		istringstream st(oneLine);
		st >> source;
		st >> dest;
		g.addEdge(source, dest);
	}

	cout << "File read\n";

	while (processRequest(cin, g));
}
#endif
