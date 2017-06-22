#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <list>
#include <iterator>

using namespace std;


int tMax=0;
int digitsNum;
string inG;

static vector<string> vec;

int process(string basic_string);

string getParent(string child);

int getSum(string number);

bool sumValid(string number);

int allDigitsValid(string number);

void swap_char(char* x, char* y)
;

void permute(const char *a, int l, int r)
;

void getAllPerms(string s);

int main()
{
    string buf;
    ifstream fin ("../googlement/A-small-practice.in");
    ofstream fout("../googlement/G-small.out");
    getline(fin,buf);
    tMax=std::stoi(buf);
    cout<<"testcases count = "<<tMax<<endl;
    int iter_t=0;
    while(getline(fin,buf)){
        digitsNum = (int) buf.size();
        inG=buf;
        //cout<<"number="<<buf<<endl;
        int result=process(buf);
        //cout<<" res="<<result-1<<endl;
        iter_t++;
        cout<<"Case #"<<iter_t<<": "<<"n="<<buf<<" r="<<result<<endl;
        fout<<"Case #"<<iter_t<<": "<<result<<endl;
        //if(iter_t==10)
        break;
    }
    fout.close();
}

int process(string googlement) {
    cout<<"process "<<googlement<<endl;
    int result=0;

    if(strcmp (inG.c_str(),googlement.c_str()) == 0) {
        cout<<"num is"<<googlement<<" result="<<result<<endl;
        result++;
    }
    if(!sumValid(googlement) || !allDigitsValid(googlement)) {
        return result;
    }
    string parent = getParent(googlement);
    /*if(strcmp (googlement.c_str(),parent.c_str()) == 0) {
        cout<<"num is"<<googlement<<" result="<<result<<endl;
        return result;
    }*/
    getAllPerms(parent);
    vector<string>::iterator iterator1=vec.begin();
    while(iterator1<vec.end()){
        string testStr=*iterator1;
        iterator1++;
        if(!sumValid(testStr) || !allDigitsValid(testStr)) {
            result++;
            continue;
        } else result+=process(testStr);
    }
    cout<<googlement<<" result="<<result<<endl;
    return result;
}
string getParent(string child){
    unsigned long i =0;
    string parent="";

    i=0;
    while(i<digitsNum){
        char c= child.at(i);
        int entries=(int)c-48;
       if(c!='0'){
           int digit=i+1;
           for (int j = 0; j < entries; ++j) {
               parent.append(to_string(digit)
               );
           }
       }
        i++;
    }
    while(parent.size()<digitsNum) parent+="0";
    return parent;
}
int getSum(string number){
    unsigned long i =0;
    int sum=0;
    while(i<number.size()){
        char c= number.at(i);
        int digit=(int)c-48;
        sum+=digit;
        i++;
    }

    return sum;
}
int allDigitsValid(string number){
    for (int i = digitsNum+1; i < number.size(); ++i) {
        int index=number.find_first_of((char)i,0);
        if(index
           >0) return false;
    }
    return true;
}
bool sumValid(string number){
    int sum = getSum(number);
    cout<<"sumValid n="<<number<<" s="<<getSum(number)<<" d("<<digitsNum<<")"<<" r="<<(sum<=digitsNum)<<endl;
    return sum<=digitsNum;
}
void getAllPerms(string s){
    //cout<<"perms in="<<s<<endl;
    vec.clear();
    permute(s.c_str(),0,digitsNum-1);
    for (int i = 0; i < vec.size(); ++i) {
       // cout<<"p="<<vec[i]<<endl;
    }
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(), vec.end() ), vec.end() );
    cout<<s<<" perms num = "<<vec.size()<<endl;
}
void permute(const char *constA, int l, int r)
{
    char *a= (char *) constA;
    int i;
    if (l == r){
        string str=a;
       // cout<<"permutation="<<str<<endl;
        vec.insert(vec.end(),str);
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swap_char((a+l), (a+i));
            permute(a, l+1, r);
            swap_char((a+l), (a+i)); //backtrack
        }
    }
}
void swap_char(char* x, char* y)
{
//  char *tmp=x; // this would create a new tmp pointer and assign "tmp" with x - and NOT "*tmp" with *x".
    char tmp = *x; // new code - store the VALUE pointed by x in tmp
    *x=*y; // store VALUE pointed by y to storage pointed by x
    *y=tmp; // modified to delete * from tmp - store VALUE of tmp to storage pointed by y
}

