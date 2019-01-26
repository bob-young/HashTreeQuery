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
    Hashtree(int depth);
    Hashtree();
    HashtreeState add_level();
    int get_capacity();
    int get_depth();
    HashNode* get_root();
    std::vector<HashNode*> leaves;
};


#endif //HASHTREE_HASHTREE_H
