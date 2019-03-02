//
// Created by bob on 19-1-26.
//

#ifndef HASHTREE_HASHTREEQUERY_H
#define HASHTREE_HASHTREEQUERY_H

#include "Hashtree.h"

class HashTreeQuery {
private:

    std::string file_path=std::string("default.txt");
    std::string owner;
    std::vector<std::string > current_users;
public:
    Hashtree* hashTree;
    HashTreeQuery(const char* fp);//use an existed one
    HashTreeQuery();//create a new one
    HashtreeState get(std::string tablename,HashMem* key);//--
    HashtreeState put(std::string tablename);//--
    HashtreeState get0(std::string tablename,size_t * key);//get key
    HashtreeState put0(std::string tablename);//add a key
    HashtreeState update(std::string tabname);
    HashtreeState add_user(std::string tablename,std::string username); //share
    HashtreeState remove_user(std::string tablename,std::string username);//remove
    HashtreeState reset(std::string tablename);
    HashtreeState flush();
    ~HashTreeQuery();
};


#endif //HASHTREE_HASHTREEQUERY_H
