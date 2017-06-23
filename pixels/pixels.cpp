#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <list>
#include <iterator>
#include <set>

using namespace std;
class Cell {
public:
    pair<int, int> xy;
    int b;
    Cell(){}
    ~Cell(){}
};

Cell* cells[201][201];

vector<Cell> vCells;

int getResult();

void parseInfo(string buf);

void initCells();

void printCells();

void getData(string buf) ;

void processCell(int x, int y);

int tMax=0;
int N=-1;
int sizeX;
int sizeY;
int D;
int iter_t;

int main(){
    string buf;

    ifstream fin ("../pixels/D-small-practice.in");
    ofstream fout("../pixels/D-small.out");
    getline(fin,buf);
    tMax=std::stoi(buf);
    cout<<"testcases count = "<<tMax<<endl;
    iter_t=1;
    int i=0;
    while(getline(fin,buf)) {
        //cout<<"buf "<<buf<<endl;
        if(N==-1) {
            parseInfo(buf);
            cout<<"Start Case #"<<iter_t<<" X="<<sizeX<<" Y="<<sizeY<<" N="<<N<<" D="<<D<<endl;
            i=1;
            continue;
        } else {
            getData(buf);
            if(i>=N) {
                int result=getResult();
                cout<<"Case #"<<iter_t<<": "<<result<<endl;
                fout<<"Case #"<<iter_t<<": "<<result<<endl;
                iter_t++;
                N=-1;
            }
            i++;
        }
        if(iter_t==2)break;
    }
    fout.close();
}

void parseInfo(string buf) {
    std::istringstream iss(buf);
    string numberS;
    iss>>numberS;
    sizeY=stoi(numberS);
    iss>>numberS;
    sizeX=stoi(numberS);
    iss>>numberS;
    N=stoi(numberS);
    iss>>numberS;
    D=stoi(numberS);
}


void getData(string buf) {
    Cell cell;
    std::istringstream iss(buf);
    string numberS;
    iss>>numberS;
    cell.xy.second=stoi(numberS);
    iss>>numberS;
    cell.xy.first=stoi(numberS);
    iss>>numberS;
    cell.b=stoi(numberS);
    vCells.insert(vCells.end(),cell);
}

int getResult(){
    initCells();
    printCells();
    vector<Cell>::iterator viCell=vCells.begin();
    while(viCell<vCells.end()){
        processCell(viCell->xy.first, viCell->xy.second);
        viCell++;
    }
    return 0;
}

void processCell(int x, int y) {
    Cell * cell = cells[x][y];


}

void initCells() {
    for(int x=1;x<201;x++){
        for(int y=1;y<201;y++) {
            cells[x][y]= nullptr;
        }
    }
    vector<Cell>::iterator iv=vCells.begin();
    while(iv<vCells.end()){
        cells[iv->xy.first][iv->xy.second] = iv.base();
        iv++;
    }
}
void printCells() {
    for(int x=1;x<=sizeX;x++){
        cout<<x<<"\t";
        for(int y=1;y<=sizeY;y++) {
            if(cells[x][y]!= nullptr) {
                //<<"("<<cells[x][y]->xy.first<<","<<cells[x][y]->xy.second<<")"<<cells[x][y]->b<<" ";
                cout<<cells[x][y]->b<<" ";

            }
            else cout<<"x ";
        }
        cout<<"\n";
    }
    for (int i = 0; i <vCells.size(); ++i)
        cells[vCells.at(i).xy.first][vCells.at(i).xy.second] = &vCells.at(i);
}
Cell * left(Cell * c){
    if(c->xy.first==1) {
        return nullptr;
    }

    return cells[c->xy.first-1][c->xy.second];
}
Cell * right(Cell * c,int xMax){
    if(c->xy.first==xMax) {
        return nullptr;
    }
    return cells[c->xy.first+1][c->xy.second];
}
Cell * top(Cell * c,int xMax){
    if(c->xy.second==1) {
        return nullptr;
    }
    return cells[c->xy.first][c->xy.second-1];
}
Cell * bottom(Cell * c,int yMax){
    if(c->xy.second==yMax) {
        return nullptr;
    }
    return cells[c->xy.first][c->xy.second+1];
}