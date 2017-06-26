#include "dijkstra2.h"
Graph::Graph(){}
Graph::~Graph(){}
// Allocates memory for adjacency list
Graph::Graph(long long X,long long Y, long long D)
{
    this->sizeX = X;
    this->sizeY = Y;
    this->D = D;
    this->N = X*Y;
    this->root=N+1;
    adj = new list<iPair> [N+1];
}
void Graph::parseEdge(long long row, long long column, long long val){
    long long index=column+(row-1)*sizeX;
    //cout<<"parse: "<<" row="<<row<<" col="<<column<<" val="<<val<<"\nindex="<<index<<"\n";
    predefined.insert(predefined.end(),make_pair(index,val));
    addEdge(0,index,val);
}

void Graph::addEdge(long long u, long long v, long long w)
{
    //cout<<"add edge "<<u<<" - "<<v<<" ("<<w<<")"<<endl;
   // cout<<"add edge "<<v<<" - "<<u<<" ("<<w<<")"<<endl;


    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

long long Graph::shortestPath(long long src,long long iter_t)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    vector<long long> dist(N+1, INF);
    pq.push(make_pair(0, src));
    dist[src] = 0;

    /* Looping till priority queue becomes empty (or all
      distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        long long u = pq.top().second;
        pq.pop();

        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<long long, long long> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            long long v = (*i).first;
            long long weight = (*i).second;

            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                vector<iPair>::iterator iter_p=predefined.begin();
                while(iter_p<predefined.end()){
                    if(iter_p->first==v &&  iter_p->second > dist[u]+weight){
                        return INF;
                    }
                    iter_p++;
                }
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    long long sum=0;
    // Print shortest distances stored in dist[]
    cout<<"out:\n";
    for (long long i = 1; i <= N; ++i){
        cout<<dist[i]<<"\t";
        if(i%sizeX==0) cout<<"\n";
        //printf("%lli \t\t %lli\n", i, dist[i]);
        sum+=dist[i];
        vector< iPair >::iterator iter_p=predefined.begin();
        /*while(iter_p<predefined.end()){
            if(iter_p->first==i &&  iter_p->second != dist[i]){
                sum=INF;
                return sum;
            }
            iter_p++;
        }*/
    }
    long long sumByTen=sum%1000000007;
    //cout<<"Case #"<<iter_t<<": "<<sumByTen<<endl;
    return sumByTen;
}
void Graph::initEdges() {
    initEdgesHorizontal();
    initEdgesVertical();
}
void Graph::initEdgesHorizontal(){
    for(long long i = 2;i <= N; i++) {
        if (i % sizeX != 1) {
            addEdge(i, i - 1, D);
        }
    }
}
void Graph::initEdgesVertical(){

    for(long long y=2;y<=sizeY;y++){
        for(long long x=1;x<=sizeX;x++){
            long long u = (y - 2) * sizeX + x;
            long long v = (y - 1) * sizeX + x;
            addEdge(u,v,D);
        }
    }
}

