// reading a text file
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;
static string leader_name;
static int num_max=0;
void update_max(string s);
bool is_number(const std::string& s);

int main () {
    string line;
    string out_line;
    ifstream myfile ("../leader/A-large-practice.in");
    ofstream fout;
    fout.open("../leader/A-large-practice.out");
    if (myfile.is_open())
    {
        getline (myfile,line);
        int i=1;
        while ( getline (myfile,line)){
            if(is_number(line) ){
                if(leader_name.length()>0) {
                    out_line+=leader_name;
                    fout<<out_line<<endl;
                    cout<<out_line<<endl;
                }
                num_max=0;
                string num = to_string(i++);
                out_line="Case #";
                out_line.append(num);
                out_line.append(": ");
            }else{
                update_max(line);
            }
        }
        out_line+=leader_name;
        fout<<out_line<<endl;
        cout<<out_line<<endl;
        myfile.close();
        fout.close();
    }

    else cout << "Unable to open file";

    return 0;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
void update_max(string str){
    int unique=0;
    int i = 0;

    while(str[i]!='\0'){

        char c = str.at(i);
        //cout<<"c="<<c<<endl;
        if(c!=' '){
            if(str.find(c, i+1)==string::npos){
                unique++;
            }
        }
        i++;
    }
    //cout<<"unique="<<unique<<endl;

    if(unique>num_max || (unique==num_max && leader_name.compare(str)>0) ){
        leader_name=str;
        num_max=unique;
    }
}
