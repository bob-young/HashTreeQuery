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
test::test(int scale) {
    htq=new HashTreeQuery();
    test_num=scale;
    if(scale>htq->hashTree->get_capacity()){
        cout<<"[test]: max capacity is "<<htq->hashTree->get_capacity()<<",but input is "<<scale<<endl;
        exit(0);
    }
    for(int i=0;i<scale;i++){
        test_key.push_back(to_string(re()%scale));
        htq->put(test_key[test_key.size()-1]);
    }
    cout<<"[test]: max capacity is "<<htq->hashTree->get_capacity()<<",input finish "<<scale<<endl;
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
    for(int i=0;i<test_num;i++){
        test_seq.push_back(re()%test_num);
    }
    timer.start();
    for(int i=0;i<test_num;i++){
        HashMem a;
        htq->get(test_key[test_seq[i]],&a);
    }
    timer.stop();
    cout<<"[test]:"<< test_num<<" tables ,use "<< timer.time_usage()<<"s"<<endl;
}
