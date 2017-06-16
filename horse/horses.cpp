#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;
enum ACTION{
    TESTCASES,
    GENERAL,
    HORSE,
    RESULT
};
int parse_testcases(string s);
int parse_length(string s);
double parse_horse(string s,int l);



int parse_horses_num(string s);

void ld_sort( long double list[], int length ) ;

int main() {
    string buf;
    ifstream fin ("../horse/A-large-practice.in");
    ofstream fout("../horse/Horses-large.out");
    cout << fixed << setprecision(6);
    fout << fixed << setprecision(6);
    int next_action=TESTCASES;
    int horses_num, iter_h;
    int t_num, iter_t;
    int l;
    long double * horses;
    while(getline(fin,buf) ){
        switch (next_action){
            case TESTCASES:
                //get testcases num
                t_num=parse_testcases(buf);
                //cout<<"tnum="<<t_num<<endl;
                iter_t=0;
                next_action=GENERAL;
                break;
            case GENERAL:
                //get testcase info
                l=parse_length(buf);
                horses_num=parse_horses_num(buf);
                cout<<"testcase"<<iter_t+1<<" l="<<l<<" h="<<horses_num<<endl;
                iter_h=0;
                horses= new long  double[horses_num];
                next_action=HORSE;
                break;
            case HORSE:
                //Get time left for horse
                horses[iter_h]=parse_horse(buf,l);
                iter_h++;
                if(iter_h==horses_num){
                    next_action=GENERAL;
                    //Get result
                    ld_sort(horses,horses_num);
                    long double  tmax=horses[horses_num-1];
                    cout<<"tmax="<<tmax<<endl;
                    long double result=l/tmax;
                    iter_t++;
                    cout<<"Case #"<<iter_t<<": "<< setprecision(6)<<result<<endl;
                    cout<<endl;
                    fout<<"Case #"<<iter_t<<": "<< setprecision(6)<<result<<endl;
                }
                break;
        }
    }
}
void ld_sort( long double list[], int length ) {
    int i = 1;
    while ( i < length ) {
        for (int j = i; list[j - 1] > list[j]; j-- ) {
            long double  temp = list[j];
            list[j] = list[j - 1];
            list[j - 1] = temp;
        }
        i++;
    }
}
int parse_testcases(string s){
    std::istringstream iss(s);
    int count;
    iss >> count;
    return count;
}

int parse_length(string s){
    std::istringstream iss(s);
    int l;
    iss >> l;
    return l;
}
int parse_horses_num(string s){
    std::istringstream iss(s);
    int horses_num;
    iss >> horses_num;
    iss >> horses_num;
    return horses_num;
}
double parse_horse(string s, int l){
    std::istringstream iss(s);
    int pos, speed;
    iss >> pos;
    iss >> speed;
    return ((double)l-pos)/speed;
}
