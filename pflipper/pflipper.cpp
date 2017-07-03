//https://code.google.com/codejam/contest/6254486/dashboard#s=p1
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

int getFlipsCount();

void getData(string basic_string);


int tryFlip(vector<vector<int> > indexes);

bool checkAndPrint(vector<bool>* testItems, bool willPrint);

    void printFlips(vector<vector<int> > *testItems);

    vector<bool> items;
    int main() {
        string buf;

        ifstream fin("../pflipper/A-small-practice.in");
        ofstream fout("../pflipper/A-small.out");
        getline(fin, buf);
        tMax = std::stoi(buf);
        cout << "testcases count = " << tMax << endl;
        iter_t = 1;
        long long i = 0;
        while (getline(fin, buf)) {
            getData(buf);
            int result = getFlipsCount();
            if (result == INF) {
                cout << "Case #" << iter_t << ": IMPOSSIBLE" << endl;
                fout << "Case #" << iter_t << ": IMPOSSIBLE" << endl;
            } else {
                cout << "Case #" << iter_t << ": " << result << endl;
                fout << "Case #" << iter_t << ": " << result << endl;
            }
            iter_t++;
            //if (iter_t == 16) return 0;
        }
        fout.close();
    }

    void getData(string buf) {
        istringstream iss(buf);
        string data;
        iss>>data;
        iss>>K;
        //cout << "getData K=" << K << endl;
        items.clear();
        for (int i = 0; i < data.length(); ++i) {
            if (data.at(i) == '+' || data.at(i) == '-') items.insert(items.end(), data.at(i) == '+');
        }
        //cout << "inserted " << items.size() << " items" << endl;
    }

    int getFlipsCount() {
        //cout<<"Case "<<iter_t<<" K="<<K<<endl;
        vector<vector<int>> allFlips;
        vector<int> flip;
        for (int i = 0; i <= items.size() - K; ++i) {
            int j = i;
            flip.clear();
            while (j < i + K) {
                //cout<<j;
                flip.push_back(j++);
            }
            allFlips.push_back(flip);
        }

        int bestResult = INF;
        do {
            int result = tryFlip(allFlips);
            if (result < bestResult) {
                bestResult = result;
                //cout << "\nres= " << result << endl;
            }
        } while (std::next_permutation(allFlips.begin(), allFlips.end()));
        return bestResult;
    }


    int tryFlip(vector<vector<int> > indexes) {
        vector<bool> testItems;
        testItems.clear();
        testItems.insert(testItems.begin(), items.begin(), items.end());
        vector<vector<int> >::iterator iter_f = indexes.begin();
        int timesFlipped = 0;
        //cout<<"test items size="<<testItems.size()<<endl;
        if (checkAndPrint(&testItems, false)) return timesFlipped;

        timesFlipped = 0;
        while (iter_f < indexes.end()) {
            vector<int>::iterator iter_i = iter_f->begin();
            while (iter_i < iter_f->end()) {
                testItems.at(*iter_i) = !testItems.at(*iter_i);
                iter_i++;
            }
            timesFlipped++;
            //check all pcakes are face up after current flip
            if (checkAndPrint(&testItems, false)) {
                return timesFlipped;
            }
            iter_f++;
        }
        //check all pcakes are face up after all flips combo
        if (checkAndPrint(&testItems, false)) return timesFlipped;
        else return INF;
    }
    bool checkAndPrint(vector<bool> *testItems, bool willPrint) {
        bool result = true;
        vector<bool>::iterator iter_b = testItems->begin();
        if (willPrint)cout << "try ";
        while (iter_b < testItems->end()) {
            if (willPrint) cout << *iter_b;
            if (!*iter_b) result = false;
            iter_b++;
        }
        if (willPrint) cout << "\t" << result << endl;
        return result;
    }

    void printFlips(vector<vector<int> > *testItems) {
        bool result = true;
        vector<vector<int>>::iterator iter_b = testItems->begin();
        cout << "flips: \n";
        while (iter_b < testItems->end()) {
            vector<int>::iterator iter_i = iter_b->begin();
            while (iter_i < iter_b->end()) cout << *iter_i++;
            cout << endl;
            iter_b++;
        }
    }

