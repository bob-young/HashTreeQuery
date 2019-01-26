//
// Created by bob on 19-1-14.
//

#ifndef HASHTREE_NODE_H
#define HASHTREE_NODE_H

#pragma once

#include <vector>

#include "NodeErrs.h"


template <typename T>
class Node {
protected:
    int capacity=0;

public:
    //args
    std::vector<Node*> sons;
    T data;

    //func

    Node(T data);
    Node(int cap,T data);
    virtual ~Node();
    void set_capacity(int);
    int get_capacity();
    NodeState add_son(T son_data);
    NodeState add_son(Node* son);
    NodeState remove_son(int index);
    NodeState clear_son();
    int count_son();
};


#endif //HASHTREE_NODE_H

#include "Node.cpp"