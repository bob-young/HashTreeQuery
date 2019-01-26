#include <iostream>
#include "HashNode.h"
#include "Hashtree.h"
#include "HashtreeFile.h"

#define EMPTY_8 {50,50,50,50,50,50,50,50};

int main() {
    std::cout << "Hello, World!" << std::endl;
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

    Hashtree ht=Hashtree(3);
    std::cout<<ht.leaves.size()<<std::endl;

    char a[]="abc10\0";
    std::string b;
    b.resize(100);
    int c=999;
    sscanf(a,"abc%d",&c);
    std::cout<<c;
    //HashtreeFile hf;
    std::string s="./a.txt";
    HashtreeFile hf=HashtreeFile();
    hf.File_to_Hashtree(s,ht);
    return 0;
}