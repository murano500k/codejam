#include "dijkstra.h"
Graph::Graph(){}
Graph::~Graph(){}

Graph::Graph(long long X,long long Y, long long D)
{
    this->sizeX = X;
    this->sizeY = Y;
    this->D = D;
    this->N = X*Y;
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

long long Graph::shortestPath(long long src)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    vector<long long> dist(N+1, INF);
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty())
    {
        long long u = pq.top().second;
        pq.pop();

        list< pair<long long, long long> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            long long v = (*i).first;
            long long weight = (*i).second;
            if (dist[v] > dist[u] + weight)
            {
                vector<iPair>::iterator iter_p=predefined.begin();
                while(iter_p<predefined.end()){
                    if(iter_p->first==v &&  iter_p->second > dist[u]+weight){
                        return INF;
                    }
                    iter_p++;
                }
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    long long sum=0;
    for (long long i = 1; i <= N; ++i){
        sum+=dist[i];
    }
    return sum%1000000007;
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

