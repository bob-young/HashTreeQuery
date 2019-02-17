//
// Created by bob on 19-1-15.
//

#ifndef HASHTREE_HASHTREE_H
#define HASHTREE_HASHTREE_H


#include "HashNode.h"
#include "HashtreeState.h"

class Hashtree {
private:
    HashNode root=HashNode(0,"root");
    int id=0;
    std::string name="default";
    int depth;
    //std::vector<HashNode*> leaves;
    friend class HashtreeFile;
    void build(HashNode *now,int target_level);
public:
    int node_count=0;
    Hashtree(int depth);
    Hashtree();
    HashtreeState add_level();
    int get_capacity();
    int get_depth();
    HashNode* get_root();
    std::vector<HashNode*> leaves;
    void show(HashNode* hn){
        std::cout<<"[Hashtree]{"<<hn<<std::endl;
        std::cout<<"\t level:"<<hn->get_level()<<std::endl;
        std::cout<<"\t cap:"<<hn->get_capacity()<<std::endl;
        std::cout<<"\t name:"<<hn->data<<std::endl;
        std::cout<<"\t users:"<<hn->get_users().size()<<std::endl;
        std::cout<<"\t occu:"<<hn->occupied<<std::endl;
        std::cout<<"\t sons:"<<hn->sons.size()<<std::endl;
        std::cout<<"}\n";
        if(hn->sons.size()>0){
            for(int i=0;i<hn->sons.size();i++)
                show((HashNode*)hn->sons[i]);
        }
    }
};


#endif //HASHTREE_HASHTREE_H
