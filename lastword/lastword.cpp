https://code.google.com/codejam/contest/4304486/dashboard
#include <fstream>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
#define INF INT_MAX
int tMax=0;
int K=-1;
int iter_t=1;

string solveTestCase(string s);



string process (string current, string s);

int main() {
    string buf;
    ifstream fin("../lastword/A-large-practice.in");
    ofstream fout("../lastword/A-large.out");
    getline(fin, buf);
    while (getline(fin, buf)) {
        string res= solveTestCase(buf);
        cout << "Case #" << iter_t << ": " << res << endl;
        fout << "Case #" << iter_t << ": " << res << endl;
        iter_t++;
    }
    fout.close();
}

string solveTestCase(string s) {
    string testS="";
    testS+=s.at(0);
    if(testS.size()==s.size())
        return testS;
    return process(testS, s);
}
string process (string current, string s){
    string next=max(current+s.at(current.size()),s.at(current.size())+current);
    if(next.size()==s.size()) return next;
    return process(next,s);
}