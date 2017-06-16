// reading a text file
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cmath>

bool srv_matches(int weight, int serv_weight, double test_servings_count);

using namespace std;


int main () {
    string line;
    string out_line;
    ifstream in ("/home/artem/projects/cpp/jam/Ratatouille/input/B-small-practice.in");
    ofstream fout;
    fout.open("/home/artem/projects/cpp/jam/Ratatouille/input/B-small-practice.out");
    if (in.is_open()){
        int num_ings, num_packages;
        string buffer;
        getline(in,buffer);
        std::istringstream iss_testcases(buffer);
        int num_testcases;
        iss_testcases >> num_testcases;
        int testcase=0;
        while(++testcase<=num_testcases) {
            //get num of ings and num of packs
            getline(in,buffer);
            std::istringstream iss(buffer);
            iss >> num_ings;
            iss >> num_packages;
            int have[num_ings][num_packages];
            int need[num_ings];
            //get weight of ings per serving
            getline(in,buffer);
            std::istringstream iss2(buffer);
            for (int i = 0; i < num_ings; ++i) {
                iss2>>need[i];
                //cout<<i<<" serv_weight="<<need[i]<<endl;
            }
            //get weight of each pack for each ing
            for (int i = 0; i < num_ings; ++i) {
                getline(in, buffer);
                std::istringstream iss3(buffer);
                for (int j = 0; j < num_packages; ++j) {
                    int pack_weight;
                    iss3 >> pack_weight;
                    have[i][j]=pack_weight;
                    //cout<<i<<","<<j<<" pack_weight="<<pack_weight<<endl;
                }
            }
            int result=0;
            for (int i = 0; i < num_packages; ++i) {
                int test_pack_weight=have[0][i];

                if(test_pack_weight<0) continue;
                double serv_test=(double)test_pack_weight/need[0];
                double exp_pack_weight=floor(serv_test+0.55555555555555555)*need[0];
                double delta;
                if(exp_pack_weight>test_pack_weight)delta=exp_pack_weight-test_pack_weight;
                else delta=test_pack_weight-exp_pack_weight;
                double percent_d=delta/exp_pack_weight;
                //cout<<"percent d="<<percent_d<<endl;
                if(percent_d>0.1)continue;
                double serv_test_min=floor((serv_test*0.9)+0.555555555555555);
                double serv_test_max=floor((serv_test*1.1)+0.555555555555555);
                bool allMatches=true;
                int matchIndexes[num_ings];
                matchIndexes[0]=i;
                for (int j = 1; j < num_ings; ++j) {
                    bool matches=false;
                    for (int k = 0; k < num_packages; ++k) {
                        int weigth=have[j][k];
                        //cout<<j<<","<<k<<" W="<<weigth<<endl;
                        if(weigth==-1) continue;
                        if(srv_matches(weigth,need[j],serv_test_min) || srv_matches(weigth,need[j],serv_test_max)){
                            matchIndexes[j]=k;
                            matches=true;
                            break;
                        };
                    }
                    if(!matches){
                        allMatches=false;
                        break;
                    }
                }
                if(allMatches){
                    result++;
                    for (int index = 0; index < num_ings; ++index) {
                        have[index][matchIndexes[index]]=-1;
                    }
                }
            }
            cout<<"Case #"<<testcase<<": "<<result<<endl;
            fout<<"Case #"<<testcase<<": "<<result<<endl;
        }
        in.close();
        fout.close();
    }

    else cout << "Unable to open file";

    return 0;
}
bool srv_matches(int weight, int serv_weight, double test_servings_count){
    //cout<<"\tsrv_matches w="<<weight<<" sw="<<serv_weight<<" servings="<<test_servings_count<<endl;
    double exp_w=serv_weight*test_servings_count;
    double delta;
    if(weight>exp_w) delta=weight-exp_w;
    else delta=exp_w-weight;
    double percent_delta=delta/exp_w;
    //cout<<" percent_delta="<<percent_delta;
    //if(percent_delta<=0.1)cout<<" matches"<<endl;
    return percent_delta<=0.1;
}

bool verify(int p_weight, int s_weight){
    double delta_weight=p_weight*0.1;
    int exp_num_serv=p_weight/s_weight;
    int exp_weight=exp_num_serv*s_weight;
    if(p_weight>=exp_weight){
        if(p_weight-delta_weight<=exp_weight) return true;
    } else{
        if(p_weight+delta_weight>exp_weight) return true;
    }
    return false;
}
bool verify(int p_weight, int s_weight, int exp_num_serv){
    int exp_weight= exp_num_serv*s_weight;
    return p_weight*0.9<=exp_weight || p_weight*1.1>=exp_weight;
}
