//
// Created by bob on 19-1-14.
//

#ifndef HASHTREE_PRIME_NUMBER_H
#define HASHTREE_PRIME_NUMBER_H

#include "HConfig.h"

static const int prime[] PRIMELIST;
static const int binary_len[] BITLENLIST;
static const int prime_cap[] CAPLIST;

class Prime{
private:
    static const int max=PRIMENUM;

public:
    static const int get_prime(int index) {
        if(index >= max){
            throw "too much hash node";
            //return 0;
        }
        return prime[index];
    }

    static const int get_cap(int level) {
        if(level >= max){
            throw "too much hash node";
            //return 0;
        }
        return prime_cap[level];
    }
    static const int get_bit(int level) {
        if(level >= max){
            throw "too much hash node";
            //return 0;
        }
        return binary_len[level];
    }
    static const int get_bit_total(int level) {
        if(level >= max){
            throw "too much hash node";
            //return 0;
        }
        int ret=0;
        for (int i = 0; i <level ; ++i) {
            ret+=binary_len[i];
        }
        return ret;
    }

    static const int get_cap_total(int level) {
        if(level >= max){
            throw "too much hash node";
            //return 0;
        }
        int ret=0;
        for (int i = 0; i <level ; ++i) {
            ret+=prime_cap[i];
        }
        return ret;
    }

};

#endif //HASHTREE_PRIME_NUMBER_H
