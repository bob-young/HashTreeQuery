//
// Created by bob on 19-1-14.
//

#ifndef HASHTREE_HASHNODE_H
#define HASHTREE_HASHNODE_H

#include <string>
#include <string.h>
#include <bitset>
#include <iostream>

#include "HConfig.h"
#include "Node.h"
#include "prime_number.h"
#if (KEYSIZE == 8)
#define KEYBYTE 8
#define EMPTY {0,0,0,0,0,0,0,0};
#elif (KEYSIZE == 16)
#define KEYBIT 16
#define EMPTY {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#endif

class HashNode :public Node<std::string>{
private:
    int level;
    int max;
    bool occupied= false;
    bool root=false;
    //unsigned char hashcode[KEYBYTE] EMPTY;
    HashMem hashcode;
    HashMem prevHashcode;
    std::vector<std::string> users;
    //T data;//tablename

    friend class HashtreeFile;
public:
    HashNode(int level, std::string data):Node<std::string>(Prime::get_prime(level),data){
        this->level=level;
        memset(&prevHashcode,0,KEYBYTE);
    };
    void setroot();
    bool isroot();
    bool isHash();
    bool set_hash(HashNode& father_hash,int index);
    bool get_hash(HashMem *hashcode_8_or_16);
    NodeState add_son(HashNode* ptr_son);
    int count_users();
    std::vector<std::string> get_users();
    std::string get_owner();
    std::vector<std::string> get_gusts();
    std::string get_colname();
    bool reomve_user(std::string user);
    bool remove_user(int index);
    int get_level();
#ifdef DEBUG
    void showHashcode(){
        std::cout<<(std::bitset<KEYSIZE*8>)hashcode<<std::endl;
    }
    void showNode(){
        std::cout<<"name:"<<this->data<<std::endl;
        showHashcode();
        std::cout<<"users："<<std::endl;
        for(int i =0;i<users.size();i++){
            std::cout<<"[user "<<i<<"] : "<<this->users[i]<<"\t";
        }
        std::cout<<std::endl;
    }
#endif
};




#endif //HASHTREE_HASHNODE_H
