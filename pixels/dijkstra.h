#include<bits/stdc++.h>

using namespace std;
# define INF LONG_LONG_MAX

typedef pair<long long, long long> iPair;

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

    Graph(long long X,long long Y, long long D);  // Constructor
    Graph();  // Constructor
    ~Graph();  // Constructor

    void addEdge(long long u, long long v, long long w);

    void parseEdge(long long row, long long column, long long diff);

    long long shortestPath(long long s);

    void initEdgesVertical();

    void initEdgesHorizontal();

};

