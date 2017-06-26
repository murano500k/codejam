#include<bits/stdc++.h>

using namespace std;
# define INF INT_MAX

// iPair ==>  Integer Pair
typedef pair<long long, long long> iPair;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
private:
    list< iPair > *adj;
    vector<iPair> predefined;

public:
    long long N;
    long long sizeX;
    long long sizeY;
    long long D;
    long long root;

    Graph(long long X,long long Y, long long D);  // Constructor
    Graph();  // Constructor
    ~Graph();  // Constructor

    // function to add an edge to graph
    void addEdge(long long u, long long v, long long w);

    void parseEdge(long long row, long long column, long long diff);

    // prlong longs shortest path from s
    long long shortestPath(long long s, long long iter_t);

    void initEdges();

    void initEdgesVertical();

    void initEdgesHorizontal();


    void checkEdgesHorizontal();

    void checkEdgesVertical();

    void checkEdgesHorizontal(long long int *result);
};

