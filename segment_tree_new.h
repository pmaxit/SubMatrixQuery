
#ifndef SEGMENT_TREE_NEW_H_
#define SEGMENT_TREE_NEW_H_
#include<iostream>
#include<vector>

#include "interval.h"
#include "utils.h"
#include "node.h"
//#include "utility.h"

template<class T>
class Segment_Tree_New{

    typedef Node<T> nodeType;
    typedef std::shared_ptr<nodeType> nodePtr;

    public:
        void build(const std::vector<T>& rects, int dimension =1 ){
          std::vector<Interval>&& intervals = getElementaryIntervals(rects, dimension);

          int n = intervals.size();
          //TODO: calculate size appropriately
          nodes.resize(10000);
          //cout<<"SIZE : "<<intervals.size()<<"  "<<intervals<<endl;
          if(n == 0){
            return; // no meaning to build segment tree without intervals.
          }

          nodes[0] = std::make_shared<nodeType>(nodeType(0, nodes.size() == 1, Interval::range(intervals[0], intervals[n-1])));
          nodeType root = *nodes[0];

          for(int i=0; i < n; i++){
            insertOnBuild(intervals[i], intervals, std::make_shared<nodeType>(root));
          }

          // storing the segments
          storeObjects(rects, dimension);

          // build secondary structure
          if(dimension == 1)
            associateTree(nodes[0]);
          return;
        }

        void associateTree(nodePtr root){

          if(!root)
            return;
          // create secondary structure of rectangles stored at root
          root->createAssocTree();
          //root->assoc->printTree();
          associateTree(leftChild(root));
          associateTree(rightChild(root));
        }

        void printTree(){
          for(int i=0; i< nodes.size(); i++){
            if(nodes[i]){
              std::cout<<i<<" -- "<<nodes[i]<<"  "<<nodes[i]->nodeList<<std::endl;

            }
          }
        }

        void storeObjects(const std::vector<T>& rects, int dimension){
          // get interval
          for(auto rect: rects){

            Interval i = getInterval(rect, dimension);
            insert(i, nodes[0], rect);
          }
        }

        // get all intersected rectangle in 1 dimension

        void doStabbingQuery(int point, nodePtr root, std::vector<T>& results){

          if(!root)
            return;

          copy(root->nodeList.begin(), root->nodeList.end(), back_inserter(results));

          if(leftChild(root) && leftChild(root)->interval.contains(point))
            doStabbingQuery(point, leftChild(root), results);

          if(rightChild(root) && rightChild(root)->interval.contains(point))
            doStabbingQuery(point, rightChild(root), results);
        }

        // get the maximum rectangle
        T stabbinQuery(int x, int y){
          nodePtr root = nodes[0];
          T result;
          doXStabbingQuery(x,y, root, result);
          return result;
        }

        // get the maximum rectangle in Y dimension
        void doYStabbingQuery(int point, nodePtr node, T& maxAreaRect){
          if(!node)
            return ;

          //cout<<"NODE IN Y "<<node<<"  "<<maxAreaRect.area()<<endl;
          maxAreaRect = maxAreaRect < *node->maxAreaRectangle? *node->maxAreaRectangle : maxAreaRect;

          if(leftChild(node) && leftChild(node)->interval.contains(point))
            doYStabbingQuery(point, leftChild(node), maxAreaRect);

          if(rightChild(node) && rightChild(node)->interval.contains(point))
            doYStabbingQuery(point, rightChild(node), maxAreaRect);
        }

        // get all the rectangles for X dimension
        void doXStabbingQuery(int x, int y, nodePtr root, T& maxRect){
          if(!root)
            return ;
          // query in y
          //std::cout<<"Search in "<<root->nodeList<<std::endl;
          T rect = root->assoc->stabbinQuery(y);
          maxRect = std::max(rect, maxRect);

          //std::cout<<"rect returned "<<rect<<std::endl;

          if(leftChild(root) && leftChild(root)->interval.contains(x))
            doXStabbingQuery(x, y,leftChild(root), maxRect);

          if(rightChild(root) && rightChild(root)->interval.contains(x))
            doXStabbingQuery(x,y, rightChild(root), maxRect);
        }

        T stabbinQuery(int point){
            T result;
            nodePtr root = nodes[0];

            doYStabbingQuery(point, root, result);
            return result;
        }

        /*      Insert the interval       */
        bool insert(Interval interval, nodePtr current, T& rect){

          if(interval.contains(current->interval)){
            // while inserting check with max value
            if(!current->maxAreaRectangle)
              current->maxAreaRectangle = std::make_shared<T>(rect);
            else{
              if(*current->maxAreaRectangle < rect)
                *current->maxAreaRectangle = rect;
            }

            current->nodeList.push_back(rect);
            return true;
          }

          if(leftChild(current) && leftChild(current)->interval.intersects(interval))
            insert(interval, leftChild(current), rect);

          if(rightChild(current) && rightChild(current)->interval.intersects(interval))
            insert(interval, rightChild(current), rect);

          return true;
        }

    protected:
        // insert on build
        void insertOnBuild(Interval interval, std::vector<Interval> &intervals, nodePtr node){
          int startIndex = 0;
          int endIndex = intervals.size()-1;

          while(startIndex != endIndex){
            //std::cout<<"Stage 0"<<std::endl;
            int middleIndex = ( startIndex + endIndex ) / 2;

            //std::cout<<nodes.capacity<<endl;
            nodePtr left = leftChild(node) == NULL ? createLeftChild(node, startIndex == middleIndex,
              Interval::range(intervals[startIndex], intervals[middleIndex])) : leftChild(node);

            if(left->interval.contains(interval)){
              node = left;
              endIndex = middleIndex;

            }else{
              // if leftsubtree does not contain the interval to insert, then interval must belong to the right subtree
              startIndex = middleIndex + 1;
              nodePtr right = rightChild(node) == NULL ? createRightChild(node, startIndex == endIndex,
                Interval::range(intervals[startIndex], intervals[endIndex])) : rightChild(node);

              node = right;
            }
          }
        }

        nodePtr leftChild(nodePtr node){
          int leftIndex = node->leftChildIndex();
          return nodes[leftIndex];
        }

        nodePtr rightChild(nodePtr node){
          int rightIndex = node->rightChildIndex();
          return nodes[rightIndex];
        }

        nodePtr createLeftChild(nodePtr node, bool isLeaf, Interval interval){

          int lci = node->leftChildIndex();
          nodes[lci] = std::make_shared<nodeType>(lci, isLeaf, interval);
          return nodes[lci];
        }

        nodePtr createRightChild(nodePtr node, bool isLeaf, Interval interval){
          int rci = node->rightChildIndex();
          nodes[rci] = std::make_shared<nodeType>(rci, isLeaf, interval);
          return nodes[rci];
        }

        std::vector<nodePtr> nodes;
        int originalLength;
};
#endif
