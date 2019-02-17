//
// Created by bob on 19-2-16.
//

#ifndef HASHTREE_TEST_H
#define HASHTREE_TEST_H
#include <random>
#include "HashTreeQuery.h"

class test {
    std::default_random_engine re;
    HashTreeQuery* htq= nullptr;
public:
    int test_num;
    std::vector<std::string> test_key;
    std::vector<int> test_seq;
    test(int scale);
    void start();

};


#endif //HASHTREE_TEST_H
