#ifndef RANGE_TREE_NODE_H
#define RANGE_TREE_NODE_H

#include<algorithm>
#include<iostream>
#include<vector>
#include<QPoint>
#include<QRect>
class Range_tree;

struct Range_tree_node{
    Range_tree_node *parent_link;
    Range_tree_node *left_link;
    Range_tree_node *right_link;

    QPoint object;
    QRect region;
    Range_tree *sublayer;
    std::vector<QPoint> points;
    std::vector<QPoint>::iterator start;
    std::vector<QPoint>::iterator end;

    Range_tree_node():parent_link(0), left_link(0), right_link(0)
    {}

    Range_tree_node(Range_tree_node *ll, Range_tree_node *rl, QPoint &obj, QRect &region,
                    std::vector<QPoint> & intPoints, Range_tree *slayer,
                    std::vector<QPoint>::iterator istart,
                    std::vector<QPoint>::iterator iend
                    ):
        parent_link(0),left_link(ll), right_link(rl), object(obj), region(region), sublayer(slayer), start(istart), end(iend){
        std::copy(intPoints.begin(), intPoints.end(), back_inserter(points));
    }

    virtual ~Range_tree_node(){
        if(sublayer != 0)
            delete sublayer;
    }
};



#endif // RANGE_TREE_NODE_H
