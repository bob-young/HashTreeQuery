//
// Created by bob on 19-1-14.
//

#include <cstring>
#include <iostream>

#include "HashNode.h"


//HashNode::HashNode(int level, int a) : Node<int>(Prime::get_prime(level),a) {
//
//}

bool HashNode::isroot() {
    if(root){
        return true;
    } else {
        return false;
    }
}

bool HashNode::isHash() {
    if(isroot()){
        memset(&hashcode,'\0',KEYBYTE);
        return true;
    }else{
#if(KEYSIZE==8)
        if((long)hashcode==0)
            return false;
        else
            return true;
#elif (KEYSIZE==16)
        loong l[2];
        memcpy(l,&hashcode,8);
        memcpy(l+1,(char*)&hashcode-8,8)
#endif
    }

}


bool HashNode::get_hash(HashMem *hashcode_8_or_16) {
    if(isHash()){
        memcpy(hashcode_8_or_16,&hashcode,KEYBYTE);
//        for (int i = 0; i < 8 ; ++i) {
//            printf("%02x ",*((char*)&hashcode+i));
//        }
        return true;
    }
    return false;
}

int HashNode::count_users() {
    return (int)users.size();
}

std::vector<std::string> HashNode::get_users() {
    return users;
}

std::string HashNode::get_owner() {
    return users[0];
}

std::vector<std::string> HashNode::get_gusts() {
    std::vector<std::string> ret=users;
    ret.erase(ret.begin());
    return ret;
}

std::string HashNode::get_colname() {
    return data;
}

bool HashNode::remove_user(int index) {
    if (index <= 0 && index >= users.size()) {
        return false;
    }else{
        users.erase(users.begin()+index);
        return true;
    }

}

bool HashNode::reomve_user(std::string username) {
    int remove=-1;
    for(int i=0 ;i<users.size();i++){
        if(users[i].compare(username)){
            remove=i;
        }
    }
    return remove_user(remove);
}

void HashNode::setroot() {
    if(isroot()){
        return;
    } else{
        root=true;
        memset(&hashcode,'\0',KEYBYTE);
        return;
    }

}

bool HashNode::set_hash(HashNode &father, int index) {

    int offset = KEYBYTE*8 - Prime::get_bit_total(this->level);
    char x=(char)(index+1);
    HashMem m;
    father.get_hash(&m);
    HashMem add;
    memset(&add,'\0',KEYBYTE);
    memcpy((char*)&add,&x,sizeof(char));//little ended
    //std::cout<<"offset="<<offset<<std::endl;
    //std::cout<<"add=\t"<<(std::bitset<KEYSIZE*8>)add<<std::endl;
    //std::cout<<"m  =\t"<<(std::bitset<KEYSIZE*8>)m<<std::endl;
    m = (add << offset) | m;
    //std::cout<<(std::bitset<KEYSIZE*8>)m<<std::endl;
    memcpy(&hashcode,&m,KEYBYTE);

    return true;
}

int HashNode::get_level() {
    return level;
}

NodeState HashNode::add_son(HashNode *ptr_son) {
    if(sons.size()+1>this->capacity){
        std::cout<<"[hashnode]:out of cap "<<this->capacity<<std::endl;
        exit(0);
        return NodeState::OUT_OF_CAP;
    }
    //std::cout<<ptr_son->level<<" ppp:" <<ptr_son->capacity<<std::endl;
    ptr_son->set_hash(*this,(int)sons.size());
    sons.push_back(ptr_son);
    return NodeState ::SUCCESS;
}

bool HashNode::add_user(std::string user) {
    users.push_back(user);
    return true;
}
