#ifndef SEGMENT_NODE_H
#define SEGMENT_NODE_H

#include "interval.h"
#include <iostream>
#include <vector>

template<class T>
class Segment_Tree_New;

template<class T>
class Node{
public:

    int index;
    bool isLeaf;
    Interval interval;
    std::shared_ptr<T> maxAreaRectangle;
    std::vector<T> nodeList;
    std::shared_ptr<Segment_Tree_New<T>> assoc;

    friend std::ostream& operator<<(std::ostream& out, const Node<T>& node){
      out<<"[ "<< node.index <<","<<node.isLeaf<<"," <<node.interval<<"] NODELIST: "<<node.nodeList;
      return out;
    }

    friend std::ostream& operator<<(std::ostream& out, const std::shared_ptr<Node<T>>& node){
      out<<*node;
      return out;
    }

    Node<T>(int index, bool isLeaf, Interval interval):index(index),isLeaf(isLeaf), interval(interval){
      maxAreaRectangle = std::make_shared<T>(T()); // initialize default;
    }

    int leftChildIndex(){ return 2*index + 1; }

    int rightChildIndex(){ return 2*(index + 1);}

    void createAssocTree(){
      assoc = std::make_shared<Segment_Tree_New<T>>(Segment_Tree_New<T>());
      assoc->build(nodeList, 2);
    }
};
#endif
