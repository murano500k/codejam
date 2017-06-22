#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <list>
using namespace std;

enum ACTION{
    TESTCASES,
    ITEM
};

int nextAction=TESTCASES;
int iteratorT;
int tMax;
int digitsNum;

vector<int> digits;
int main()
{
    string buf;
    ifstream fin ("../googlement/A-small-practice.in");
    ofstream fout("../googlement/G-small.out");
    getline(fin,buf);
    tMax=std::stoi(buf);
    cout<<"testcases count = "<<tMax<<endl;
    while(getline(fin,buf)){
        digitsNum= (int) buf.size();

        int number=std::stoi(buf);
        cout<<"number="<<number<<endl;
        int result=process(&number);
        cout<<" res="<<result<<endl;
        cout<<"Case #"<<iter_t<<": "<<"n="<<number<<" "<<process(&number)<<endl;
        break;
    }
}
