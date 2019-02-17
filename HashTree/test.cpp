//
// Created by bob on 19-2-16.
//

#include "test.h"
#include "HashTreeQuery.h"
using namespace std;

#include<time.h>

class Timer{
public:
    Timer(){};
    clock_t start_time,stop_time;
    void start(){
        start_time=clock();
    }
    void stop(){
        stop_time=clock();
    }
    double time_usage(){
        return (double)(stop_time-start_time)/CLOCKS_PER_SEC;
    }

};
test::test(int x,int y) {
    htq=new HashTreeQuery();
    scale=x;
    test_times=y;
    if(scale>htq->hashTree->get_capacity()){
        cout<<"[test]: max capacity is "<<htq->hashTree->get_capacity()<<",but input is "<<scale<<endl;
        exit(0);
    }
    //generate X keys
    for(int i=0;i<scale;i++){
        //test_key.push_back(to_string(re()%scale));
        htq->put(to_string(i));
    }
    cout<<"[test]: max capacity is "<<htq->hashTree->get_capacity()<<",input keys "<<scale<<endl;
//    htq.put("aaa");
//    htq.put("aaaa");
//    htq.put("aaaaa");
//    htq.put("aaab");
//    htq.put("aaaab");
//    htq.put("aaaaab");
//    htq.hashTree->show(htq.hashTree->get_root());
//    htq.flush();

}

void test::start() {
    Timer timer;
    cout<<"generate test sequence\n";
//    for(int i=0;i<test_num;i++){
//        test_seq.push_back(re()%test_num);
//    }
    timer.start();
    for(int i=0;i<test_times;i++){
        HashMem a;
        htq->get(to_string(re()%scale),&a);
    }
    timer.stop();
    cout<<"[test]:"<< scale <<" tables for "<< test_times<<" times,use "<< timer.time_usage()<<" s"<<endl;
}
