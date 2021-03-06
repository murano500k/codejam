//https://code.google.com/codejam/contest/3264486/dashboard#s=p1
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <list>
#include <iterator>
#include <set>
#include <climits>

using namespace std;
#define INF INT_MAX
int tMax=0;
int K=-1;
int iter_t;


string solveTestCase(string s);


vector<bool> items;
int main() {
    string buf;

    ifstream fin("../tidynum/B-small-practice.in");
    ofstream fout("../tidynum/B-small.out");
    getline(fin, buf);
    tMax = std::stoi(buf);
    cout << "testcases count = " << tMax << endl;
    iter_t = 1;
    long long i = 0;
    while (getline(fin, buf)) {
        string result = solveTestCase(buf);
        if (result == "IMPOSSIBLE") {
            cout << "Case #" << iter_t << ": IMPOSSIBLE" << endl;
            fout << "Case #" << iter_t << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << iter_t << ": " << result << endl;
            fout << "Case #" << iter_t << ": " << result << endl;
        }
        iter_t++;
        //if (iter_t == 5) return 0;
    }
    fout.close();
}

string solveTestCase(string s) {
        if (s.size() == 1) return s;
        bool isTidy = true;
        int i = 1;
        while (i < s.size()) {
            isTidy = s.at(i) >= s.at(i - 1);
            if (!isTidy) break;
            i++;
        }
        if (isTidy) return s;
        int number = stoi(s);
        return solveTestCase(to_string(--number));
}
