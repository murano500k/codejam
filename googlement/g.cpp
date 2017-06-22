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
    GENERAL,
    ITEM,
    RESULT
};
int parse_testcases(string s);
int parse_max_pancakes(string s);
long double parse_cake(string s, int l);



int parse_items_num(string s);

void ld_sort( long double list[], int length ) ;


int get_num(int pInt[10], int num);


int get_result(const char *line, int l) {
    cout<<"line="<< line<<endl;
    int num[9], i=0;
    while(i<l){
        num[i]= *line + '0';
        cout<<i<<") "<<num[i]<<endl;
        i++;
        line++;
    }
}


int unique(int *pnum){
    int num=*pnum;
    int digits[10],i=0;
    //cout<<"unicue num="<<num<<endl;
    while (num) { // loop till there's nothing left
        digits[i] = num % 10; // assign the last digit
        num /= 10; // "right shift" the number
        i++;
    }

    int digits_num=i;
    //std::cout << "dn="<<digits_num<< std::endl;
    std::list<int> la(digits, digits+digits_num-1);
    la.sort();
    la.unique();
    int unique= (int) la.size();
    return (int) unique;
}
int factorial(int n){
    if(n!=1){
        return(n * factorial(n-1));
    }
    else return 1;
}

int parent_number(int *num,int digits_count) {

    int digits[digits_count];
    int iter_d=0;
    int digit_iterator=0;
    int num_iterator=0;
    while(digit_iterator<digits_count){
        if(num[num_iterator]!=0){
            int num_to_add=num[num_iterator];
            iter_d++;

            for (int i = 0; i < num_to_add; ++i) {
                digits[digit_iterator++]=iter_d;
            }
        }
        num_iterator++;
    }

    return get_num(digits,digits_count);
}
int process(int *pnum){
    int num=*pnum;
    cout<<"\nprocess: "<<num<<endl;
    int digits[10],i=0;
    while (num) { // loop till there's nothing left
        digits[i++] = num % 10; // assign the last digit
        num /= 10; // "right shift" the number
    }
    int digits_num=i;
    int sum=0;
    for(i=0;i<digits_num;i++){
        sum+=digits[i];
        //cout<<"digits["<<i<<"]="<<digits[i]<<endl;
    }
    int unique_digits = unique(pnum);
    if(unique_digits<0)
    cout<<"s="<<sum<<" u="<<unique_digits<<endl;
    if(sum<digits_num){
        return factorial(digits_num)/(unique_digits*factorial(digits_num-unique_digits));
    } else{
        int parent_num=parent_number(pnum, digits_num);//get_num(digits, unique_digits);
        cout<<"parent="<<parent_num<<endl;
        return process(&parent_num)*unique_digits*digits_num;
    }
}


int get_num(int *pInt, int num) {
    int res=0;
    for (int i = 0; i < num; ++i) {
        res+=pow(10,i)*(*pInt++);
    }
    return res;
}

int main() {
    string buf;
    ifstream fin ("../googlement/A-small-practice.in");
    ofstream fout("../googlement/G-small.out");
    cout<<"test"<<endl;
    int next_action=TESTCASES;
    int horses_num, iter_h;
    int t_num;
    int l;
    long double * horses;
    char c;
    getline(fin,buf);
    int iter_t=0;
    while(getline(fin,buf)){
        int number=std::stoi(buf);
        cout<<"number="<<number<<endl;
        int result=process(&number);
        cout<<" res="<<result<<endl;
        cout<<"Case #"<<iter_t<<": "<<"n="<<number<<" "<<process(&number)<<endl;
        break;
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

int parse_max_pancakes(string s){
    std::istringstream iss(s);
    int l;
    iss >> l;
    return l;
}
int parse_items_num(string s){
    std::istringstream iss(s);
    int horses_num;
    iss >> horses_num;
    iss >> horses_num;
    return horses_num;
}
long double parse_cake(string s, int l){
    std::istringstream iss(s);
    int pos, speed;
    iss >> pos;
    iss >> speed;
    return ((long double)l-pos)/speed;
}
