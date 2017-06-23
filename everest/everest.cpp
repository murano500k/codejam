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

typedef std::pair<int, int> Range;

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


int findBestPath(int startingFrom, int startTime, Tour **vTemp);

int tMax=0;
int C=-1;
vector<Tour> paths;
int main(){

    string buf;
    ifstream fin ("../everest/C-small-practice.in");
    ofstream fout("../everest/C-small.out");
    getline(fin,buf);
    tMax=std::stoi(buf);
    cout<<"testcases count = "<<tMax<<endl;
    int iter_t=1;
    int i=0;
    while(getline(fin,buf)) {
        //cout<<"buf="<<buf<<endl;
        if(C==-1) {
            cout<<"Case #"<<iter_t<<endl;
            C=stoi(buf);
            i=1;
            paths.clear();
            continue;
        } else {
            getData(i++, buf);
            if(i>2*C) {
                int result=getResult();
                cout<<"Case #"<<iter_t<<": "<<result<<endl;
                fout<<"Case #"<<iter_t<<": "<<result<<endl;
                iter_t++;
                C=-1;
            }
        }


        if(iter_t==2)break;
    }
    fout.close();
}



void getData(int i,string buf) {
    int startCamp= (int) floor((i + 1) / 2);
    Tour tour(startCamp, buf);
    //tour.toString();
    paths.insert(paths.end(),tour);
}


int getResult(){
    int  bestResults[paths.size()];
    Tour* vTemp[paths.size()];
    for (int i = 0; i < paths.size(); ++i) {
        for (int j = 0; j < paths.size(); ++j) {
            vTemp[j]=&paths.at(j);
        }
        Tour* tour=vTemp[i];
        vTemp[i]=0;
        int end=tour->campInterval.second;
        int endT=tour->timeInterval.first;
        bestResults[i]=findBestPath(end,endT,vTemp, vTemp+paths.size());
    }
    int best=bestResults[0];
    for (int j = 0; j < paths.size(); ++j) {
        cout<<j<<". r="<<best<<endl;
        if(best>bestResults[j])best=bestResults[j];
    }
    cout<<"best="<<best<<endl;
}
int findBestPath(int startingFrom, int startTime, Tour *vTempStart, Tour *vTempEnd ){
    int startDayTime=startTime%24;
    int index1=startingFrom*2-2;
    int index2=index1+1;
    Tour*t1=vTempStart;
    Tour*t2=vTemp[index2];
    int wait1= INT8_MAX;
    int wait2= INT8_MAX;
    if(t1)wait1= (int) fabs(t1->timeInterval.first - startDayTime);
    if(t2)wait2= (int) fabs(t2->timeInterval.first - startDayTime);
    if(wait1==INT8_MAX && wait2==INT8_MAX) return startTime;
    if(wait1>wait2){
        vTemp[index2]=0;
        return findBestPath(index2, startTime+wait2,vTemp);
    } else {
        vTemp[index1]=0;
        return findBestPath(index1,startTime+wait1,vTemp);
    }
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

