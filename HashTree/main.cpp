#include <iostream>
#include "HashNode.h"
#include "Hashtree.h"
#include "HashtreeFile.h"
#include "HashTreeQuery.h"
#include "test.h"

#define EMPTY_8 {50,50,50,50,50,50,50,50};
void test_HashTreeQuery1(){
    HashTreeQuery htq("default.txt");
    htq.hashTree->show(htq.hashTree->get_root());
    std::string t=std::string("aaacab");
    HashMem mem;
    htq.get(t,&mem);
    std::cout<<(std::bitset<KEYSIZE*8>)mem<<std::endl;
    std::cout<<htq.hashTree->node_count;
}
void test_HashTreeQuery(){
    HashTreeQuery htq;
    htq.put("aaa");
    htq.put("aaaa");
    htq.put("aaaaa");
    htq.put("aaab");
    htq.put("aaaab");
    htq.put("aaaaab");
    htq.hashTree->show(htq.hashTree->get_root());
    htq.flush();
}

void test_HashFile(){
    Hashtree ht=Hashtree(FIX_DEPTH);
    std::cout<<ht.leaves.size()<<std::endl;

//    char a[]="abc10\0";
//    std::string b;
//    b.resize(100);
//    int c=999;
//    sscanf(a,"abc%d",&c);
//    std::cout<<c;
    //HashtreeFile hf;
    std::string s="./aa.txt";
    HashtreeFile hf=HashtreeFile();
    ht.show(ht.get_root());
    hf.Hashtree_to_File(s,ht);
}

int main() {

//    HashNode *r=new HashNode(0,"root");
//    HashNode *s0=new HashNode(1,"son10");
//    HashNode *s1=new HashNode(1,"son11");
//    r->setroot();
//
//    s0->set_hash(*r,0);
//    s1->set_hash(*r,1);
//    r->showHashcode();
//    s0->showHashcode();
//    s1->showHashcode();

    //test_HashFile();
    std::cout << "Hello!" << std::endl;
#define T_T 100000
    test t(500,T_T);
    t.start();
    //test_HashTreeQuery1();
    return 0;
}

