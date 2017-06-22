#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;
enum ACTION{
    TESTCASES,
    GENERAL,
    ITEM,
    RESULT
};

struct Cake{
    int r,h;
    double s_side;
    double s_top;
    double s;
};

int parse_max_pancakes(string s);

int parse_items_num(string s);

int parse_testcases(string s);

double parse_cake2(string s) ;

Cake parse_cake(string s) ;

Cake* cakes;


void cake_sort_r( Cake list[], int length ) {
    int i = 1;
    while ( i < length ) {
        for (int j = i; list[j - 1].r > list[j].r; j-- ) {
            Cake temp = list[j];
            list[j] = list[j - 1];
            list[j - 1] = temp;
        }
        i++;
    }
}
void cake_sort_s( Cake list[], int length ) {
    int i = 1;
    while ( i < length ) {
        for (int j = i; list[j - 1].r > list[j].r; j-- ) {
            Cake temp = list[j];
            list[j] = list[j - 1];
            list[j - 1] = temp;
        }
        i++;
    }
}
void cake_reverse( Cake list[], int length ) {
    int i = 0;
    int j=length-1;
    while ( i < j) {
        Cake temp=list[i];
        list[i]=list[j];
        list[j]=temp;
        i++;
        j--;
    }
}
int parse_testcases(string s){
    std::istringstream iss(s);
    int count;
    iss >> count;
    return count;
}

int parse_max_pancakes(string s){
    std::istringstream iss(s);
    int l;
    iss >> l;
    iss >> l;
    return l;
}

int parse_items_num(string s) {
    std::istringstream iss(s);
    int items_num;
    iss >> items_num;
    return items_num;
}
Cake parse_cake(string s) {
    Cake cake;
    std::istringstream iss(s);
    iss >> cake.r;
    iss >> cake.h;
    cake.s_side=(double)2*M_PI*cake.h*cake.r;
    cake.s_top=(double)M_PI*cake.r*cake.r;
    //cout<<"parse cake: r="<<cake.r<<" h="<<cake.h<<" s="<<cake.s_side<<endl;
    return cake;
}

int main() {
    string buf;
    ifstream fin ("../pancake/A-small-practice.in");
    ofstream fout("../pancake/pancake-small.out");
    cout << fixed << setprecision(9);
    fout << fixed << setprecision(6);
    int next_action=TESTCASES;
    int items_num, iter_c;
    int t_num, iter_t;
    int max_cakes;
    double * cs_side;
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
                items_num= parse_items_num(buf);
                max_cakes=  parse_max_pancakes(buf);
                //cout<<"testcase"<<iter_t+1<<" max_cakes="<<max_cakes<<" allitems="<<items_num<<endl;
                iter_c=0;
                cakes=new Cake[items_num];
                cs_side=new double[items_num];
                next_action=ITEM;
                break;
            case ITEM:
                //Get time left for horse
                cakes[iter_c]=parse_cake(buf);
                iter_c++;
                if(iter_c==items_num){
                    next_action=GENERAL;
                    cake_sort_r(cakes, items_num);
                    cake_reverse(cakes,items_num);
                    double s_max=0;
                    for (int i = 0; i < items_num; ++i) {
                        cakes[i].s=cakes[i].s_side+cakes[i].s_top+cakes[i+1].s_top;
                        //cout<<"cake"<<i<<": r="<<cakes[i].r<<" h="<<cakes[i].h<<" s="<<cakes[i].s<<endl;
                    }
                    int i=0, j=0;
                    bool skip=true;
                    while(i<iter_c){
                        if(skip && cakes[j].s<cakes[j+1].s) continue;
                        else {
                            skip=false;
                            s_max+=cakes[j].s;
                            i++;
                        }
                        j++;
                    }

                    //Get result
                    iter_t++;
                    cout<<"Case #"<<iter_t<<": "<<s_max<<endl;

                    //fout<<"Case #"<<iter_t<<": "<<sum<<endl;
                    // if(iter_t==19)return 0;
                }
                break;
        }
    }
}