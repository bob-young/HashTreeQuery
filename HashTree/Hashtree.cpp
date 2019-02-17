//
// Created by bob on 19-1-15.
//

#include "Hashtree.h"

void Hashtree::build(HashNode* now ,int target){
    //std::cout<<"cap:"<<now->get_capacity()<<std::endl;
    node_count++;
    if(now->get_level()==target){
        leaves.push_back(now);
        return;
    }else{
        //std::cout<<"[HashTree]:"<<now->get_level()<<std::endl;
        for(int i=0;i<prime[now->get_level()];i++){
            //std::cout<<"__"<<now->get_level()<<std::endl;
            HashNode* tmp=new HashNode(now->get_level()+1,"");
            //std::cout<<"[HashTree]:"<<tmp<<std::endl;
            now->add_son(tmp);
            build(tmp,target);
        }
        return;
    };
}

Hashtree::Hashtree(int depth):Hashtree(){
    if(depth>10){
        throw "too much nodes;";
    }
    this->depth=depth;
    leaves.clear();
    leaves.reserve(Prime::get_cap(depth-1));
    std::cout<<"building...\n";
    build(&root,depth-1);
    std::cout<<"build hash tree at level "<< depth-1;
    std::cout<<" with capacity of "<<Prime::get_cap_total(depth-1)<<std::endl;
}

Hashtree::Hashtree() {
    root.setroot();
    leaves.push_back(&root);

}

HashtreeState Hashtree::add_level() {
    return HashtreeState::SUCCESS;
}

int Hashtree::get_capacity() {
    return Prime::get_cap_total(this->depth-1);
}

int Hashtree::get_depth() {
    return this->depth;
}

HashNode *Hashtree::get_root() {
    return &(this->root);
}
