#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <list>
#include <iterator>
#include <set>

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


int bestTimeToFinish(set<Tour> completedTours, int currentCamp, int timePassed);

int tMax=0;
int C=-1;
vector<Tour> tours;
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
            tours.clear();
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
    tours.insert(tours.end(),tour);
}


int getResult(){
    sort( tours.begin( ), tours.end( ), [ ]( const Tour& lhs, const Tour& rhs )
    {
        return lhs.campInterval.first < rhs.campInterval.first;
    });
    int bestTime=-1;
    for (int i = 0; i < C; ++i) {
        Tour startTour=tours.at(i);
        set<Tour> completedTours;
        completedTours.insert(completedTours.end(), startTour);
        int timeToFinish=bestTimeToFinish(completedTours, startTour.campInterval.second, startTour.duration);
        cout<<"\tbestTime="<<timeToFinish<<endl;
        if(bestTime==-1) bestTime=timeToFinish;
        else if(timeToFinish!=-1){
            if(bestTime>timeToFinish) bestTime=timeToFinish;
        }
    }
    return bestTime;
}


int bestTimeToFinish(set<Tour> completedTours, int currentCamp, int timePassed){
    if(completedTours.size()==tours.size())
        return timePassed;

    int currentDayTime=timePassed%24;
    int timeToFinish=-1;
    for (int i = 0; i < tours.size(); ++i) {
        const Tour nextTour=tours.at(i);
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

