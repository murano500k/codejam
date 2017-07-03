//https://code.google.com/codejam/contest/8304486/dashboard#s=p2
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <list>
#include <iterator>
#include <set>
#include <zconf.h>

using namespace std;

typedef std::pair<int, int> Range;
const int MAX_TIME=1000000000;
class Tour{

public:
    Range campInterval;
    Range timeInterval;
    int duration;
    Tour(int C, string in) {
        std::istringstream iss(in);
        campInterval.first=C;
        iss>>campInterval.second;
        iss>>timeInterval.first;
        iss>>duration;
        timeInterval.second=timeInterval.first+duration;
    }
    ~Tour(){}

    void toString() {
        cout<<campInterval.first<<" -> "<<campInterval.second<<", "<<timeInterval.first<<" - "<<timeInterval.second<<endl;
    }
};


void getData(int i,string buf) ;

int getResult();

int findBestPath(int startingFrom, int startTime, bool * passed );

int getAllTime(int waitTime);

int getWaitTime(int index, int time, bool *pBoolean);

int getEnd(int index);

bool allPassed(bool *pBoolean);

int tMax=0;
int N=-1;
vector<Tour> paths;
int iter_t;
int main(){

    string buf;
    ifstream fin ("../everest/C-small-practice.in");
    ofstream fout("../everest/C-small.out");
    getline(fin,buf);
    tMax=std::stoi(buf);
    cout<<"testcases count = "<<tMax<<endl;
    iter_t=1;
    int i=0;
    while(getline(fin,buf)) {
        //cout<<"buf="<<buf<<endl;
        if(N==-1) {
            cout<<"Case #"<<iter_t<<endl;
            N=stoi(buf);
            i=1;
            paths.clear();
            continue;
        } else {
            getData(i++, buf);
            if(i>2*N) {
                int result=getResult();
                cout<<"Case #"<<iter_t<<": "<<result<<endl;
                fout<<"Case #"<<iter_t<<": "<<result<<endl;
                iter_t++;
                N=-1;
            }
        }


      // if(iter_t==7)break;
    }
    fout.close();
}



void getData(int i,string buf) {
    int startCamp= (int) floor((i + 1) / 2);
    Tour tour(startCamp, buf);
    //tour.toString();
    paths.insert(paths.end(),tour);
}

int hops=0;
int getResult(){
    for (int i = 0; i < paths.size(); ++i) {
        cout<<i<<". camps "<<paths[i].campInterval.first<<"->"<<paths[i].campInterval.second<<"\t";
        cout<<" time "<<paths[i].timeInterval.first<<"->"<<paths[i].timeInterval.second<<endl;
    }
    int  bestResults[paths.size()];
    bool passedCamps[paths.size()];
    for (int i = 0; i < 2; ++i) {
        for (int ip = 0; ip < paths.size(); ++ip) passedCamps[ip]=false;
        hops=0;
        Tour* tour=&paths[i];
        passedCamps[i]= true;
        int end=tour->campInterval.second;
        int endT=tour->timeInterval.second;
        cout<<"case: \n";
        tour->toString();
        bestResults[i]=findBestPath(end,endT,passedCamps);
        cout<<"\n\tresult"<<i<<" "<<bestResults[i]<<endl<<endl;
    }
    int best=bestResults[0];
    for (int j = 0; j < 2; ++j) {
        if(best>bestResults[j]) best=bestResults[j];
    }
    return best;
}
int findBestPath(int startingFrom, int startTime, bool * passed ){
    if(iter_t==99)sleep(1);
    if(allPassed(passed))
        return startTime;
    //hops++;
    if(iter_t==99)cout<<iter_t<<". findbestpath from c="<<startingFrom<<" startTime="<<startTime<<"\n";
    int startDayTime=startTime%24;

    int index=(startingFrom-1)*2;
    int wait1=getWaitTime(index, startDayTime, passed);
    int wait2=getWaitTime(index+1,startDayTime,passed);
    int end1=paths[index].campInterval.second;
    int end2=paths[index+1].campInterval.second;

    if(wait1==MAX_TIME && wait2==MAX_TIME){
        for (int i = 0; i < paths.size(); ++i) {

            if(!*(passed+i)){
                if(iter_t==99)cout<<"r="<<MAX_TIME<<endl;
                return MAX_TIME;
            }
        }
        if(iter_t==99)cout<<"r="<<startTime<<endl;
        return startTime;
    }
    int result1=MAX_TIME;
    int result2=MAX_TIME;
    if(wait1<MAX_TIME) {
        *(passed+index)=true;
        result1=findBestPath(end1, startTime+wait1+paths[index].duration,passed);
        *(passed+index)=false;
    }
    if(wait2<MAX_TIME) {
        *(passed+index+1)=true;
        result2=findBestPath(end2, startTime+wait2+paths[index+1].duration,passed);
        *(passed+index+1)=false;
    }
    if(iter_t==99)if(result1<MAX_TIME) cout<<"\tr1="<<result1;
    if(iter_t==99)if(result2<MAX_TIME) cout<<"\tr2="<<result2;
    if(iter_t==99)cout<<endl;
    if(result1<MAX_TIME && result1<result2)return result1;
    else if(result2<MAX_TIME)return result2;
    else return MAX_TIME;
}

bool allPassed(bool *passed) {
    for (int i = 0; i < paths.size(); ++i) {
        if(!*(passed+i)) return false;
    }
    return true;
}

int getEnd(int index) {
    return paths[index].campInterval.second;
}

int getWaitTime(int index, int startDayTime, bool *passed) {
    Tour * t1=&paths[index];
    bool campPassed=*(passed+index);
    if(campPassed) return MAX_TIME;
    int wait= (int) fabs(t1->timeInterval.first - startDayTime);
    if(startDayTime>t1->timeInterval.first) wait=24-wait;
    return wait;
}

/*

int bestTimeToFinish(set<Tour> completedTours, int currentCamp, int timePassed){
    if(completedTours.size()==paths.size())
        return timePassed;

    int currentDayTime=timePassed%24;
    int timeToFinish=-1;
    for (int i = 0; i < paths.size(); ++i) {
        const Tour nextTour=paths.at(i);
        set<Tour>::const_iterator it = completedTours.find(nextTour);
        set<Tour>::const_iterator it2 = completedTours.end();
        if (it != it2)continue;
        if(nextTour.campInterval.first!=currentCamp) continue;
        int nextWaitTime;
        if(nextTour.timeInterval.first<currentDayTime){
            nextWaitTime=24+nextTour.timeInterval.first-currentDayTime;
        } else nextWaitTime=nextTour.timeInterval.first-currentDayTime;
        int nextTimePassed=timePassed+nextTour.duration+nextWaitTime;
        set<Tour> updatedCompletedTours=completedTours;
        updatedCompletedTours.insert(completedTours.end(), nextTour);
        int currentResult=bestTimeToFinish(updatedCompletedTours,nextTour.campInterval.second,nextTimePassed);
        if(currentResult!=-1) {
            if(timeToFinish==-1 || currentResult<timeToFinish) timeToFinish=currentResult;
        }
    }
    return timeToFinish;
}
*/

