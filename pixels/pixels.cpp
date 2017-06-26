#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <list>
#include <iterator>
#include <set>
#include "dijkstra.h"

using namespace std;

long long tMax=0;
long long N=-1;
long long iter_t;
static Graph *g;

int main(){
    string buf;

    ifstream fin ("../pixels/D-small-practice.in");
    ofstream fout("../pixels/D-small.out");
    getline(fin,buf);
    tMax=std::stoi(buf);
    cout<<"testcases count = "<<tMax<<endl;
    iter_t=1;
    long long i=0;
    while(getline(fin,buf)) {
        //cout<<"buf "<<buf<<endl;
        if(N==-1) {
            std::istringstream iss(buf);
            long long sizeX,sizeY,D;
            iss>>sizeY;
            iss>>sizeX;
            iss>>N;
            iss>>D;
            g=new Graph(sizeX, sizeY, D);
            //cout<<"Start Case #"<<iter_t<<" sizeX="<<g->sizeX<<" sizeY="<<g->sizeY<<" N="<<N<<" D="<<g->D<<endl;
            i=1;
            continue;
        } else {
            std::istringstream iss(buf);
            long long row,column,diff;
            iss>>row;
            iss>>column;
            iss>>diff;
            g->parseEdge(row,column,diff);
            if(i==N) {
                g->initEdgesHorizontal();
                g->initEdgesVertical();
                long long result=g->shortestPath(0);
                if(result==INF){
                    cout<<"Case #"<<iter_t<<": IMPOSSIBLE"<<endl;
                    fout<<"Case #"<<iter_t<<": IMPOSSIBLE"<<endl;
                } else {
                    cout<<"Case #"<<iter_t<<": "<<result<<endl;
                    fout<<"Case #"<<iter_t<<": "<<result<<endl;
                }
                iter_t++;
                N=-1;
                continue;
            }
            i++;
        }
        //if(iter_t==5)break;
        //break;
    }
    fout.close();
}
