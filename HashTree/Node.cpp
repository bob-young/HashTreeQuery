//
// Created by bob on 19-1-14.
//
#ifndef HASHTREE_NODE_CPP
#define HASHTREE_NODE_CPP
#include "Node.h"

template <typename T>
Node<T>::Node(T data) {
    this->data=data;
}


template <typename T>
Node<T>::Node(int cap, T data):Node<T>(data) {
    this->capacity=cap;
}


template <typename T>
NodeState Node<T>::add_son(Node *son) {
    if(sons.size()+1>=this->capacity){
        return NodeState::OUT_OF_CAP;
    }

    sons.push_back(son);
    return NodeState ::SUCCESS;
}

template <typename T>
NodeState Node<T>::add_son(T son_data) {
    if(sons.size()+1>=this->capacity){
        return NodeState::OUT_OF_CAP;
    }

    Node *tmp=new Node(son_data);
    sons.push_back(tmp);
    return NodeState::SUCCESS;
}

template <typename T>
void Node<T>::set_capacity(int x) {
    this->capacity=x;
}

template <typename T>
NodeState Node<T>::remove_son(int index) {
    sons.erase(sons.begin()+index);
    return NodeState ::SUCCESS;
}

template <typename T>
NodeState Node<T>::clear_son() {
    while (sons.size()){
        delete sons.end();
        sons.pop_back();
    }
    return NodeState ::SUCCESS;
}

template <typename T>
int Node<T>::count_son() {
    return (int)sons.size();
}


template <typename T>
Node<T>::~Node() {
    if(sons.size()>0){
        for(int i=0;i<sons.size();i++){
            delete(sons[i]);
        }
    }

}

template <typename T>
int Node<T>::get_capacity() {
    return capacity;
}

#endif


