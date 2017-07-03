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

unsigned long long solveTestCaseLarge(string basic_string);

bool checkNum(string prefix);

void addPossibleSolutions(string s, string prefix, vector<string> * solutions);

void add9s(string* toAdd, unsigned long long max);

int main() {
    string buf;

    ifstream fin("../tidynum/B-large-practice.in");
    ofstream fout("../tidynum/B-large.out");
    getline(fin, buf);
    tMax = std::stoi(buf);
    cout << "testcases count = " << tMax << endl;
    iter_t = 1;
    while (getline(fin, buf)) {
        if(iter_t==71) {
            cout<<"\t"<<iter_t<<"\t  "<<buf<<endl;
        //    cout<<"MAX_LL=   "<<LONG_LONG_MAX<<endl;
            //iter_t++;
            //continue;
        }
        unsigned long long result = solveTestCaseLarge(buf);
        cout << "Case #" << iter_t << ": " << result << endl;
        fout << "Case #" << iter_t << ": " << result << endl;
        iter_t++;

        //if (iter_t == 5) return 0;
    }
    fout.close();
}

unsigned long long int solveTestCaseLarge(string s) {
    if(iter_t==12)cout<<s<<" checkNum="<<checkNum(s)<<endl;
    if(s.size()==1 || checkNum(s))
        return stoull(s);
    string prefix;
    vector<string> solutions;

    for (int i = 0; i < s.size(); ++i) {
        prefix=s.substr(0,i);
        if(prefix.size()>1 && !checkNum(prefix))break;
        addPossibleSolutions(s,prefix,&solutions);
    }
    unique(solutions.begin(),solutions.end());
    unsigned long long r=0;
    unsigned long long testInt=stoull(s);
    for (int j = 0; j < solutions.size(); ++j) {
        //cout<<solutions[j]<<endl;
        unsigned long long sol = stoull(solutions[j]);
        if(sol<=testInt && r<sol) r=sol;
    }
    return r;
}
bool checkNum(string num){
    //cout<<"check "<<num<<endl;
    //const char*p=num.c_str();
    for (int i = 0; i < num.size(); ++i) {
        if(i!=num.size()-1) {
            if(num[i]>num[i+1])return false;
        }
    }
    //while(++p!='\0') if(*p<*(p-1))return false;
    return true;
}
void addPossibleSolutions(string s, string prefix, vector<string> * solutions){
    unsigned long long in=stoull(s);
    if(prefix.size()==0){
        //int iMax=(int)*(s.begin())-48;
        //cout<<"prefix="<<prefix<<" iMax="<<iMax<<" in="<<in<<endl;
        for (int i = 1; i < 10; ++i) {
            string toAdd;
            toAdd.append(to_string(i));
            add9s(&toAdd, in);
           // cout<<"toAdd: "<<toAdd<<endl;
            solutions->push_back(toAdd);
        }
    } else if(s.size()>2){
        int iMin=(int)*(prefix.end()-1)-48;
        //cout<<"prefix="<<prefix<<" iMin="<<iMin<<" in="<<in<<endl;
        for (int i = iMin; i < 10; ++i) {
            string toAdd;
            toAdd.append(prefix);
            toAdd.append(to_string(i));
            add9s(&toAdd, in);
           // cout<<"toAdd: "<<toAdd<<endl;
            solutions->push_back(toAdd);
        }
    }
}
void add9s(string* toAdd, unsigned long long max){
    do{
        toAdd->append("9");
    }while(stoull(*toAdd)<max);
    toAdd->resize(toAdd->size()-1);
}


