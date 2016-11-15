#include "range_tree.h"
#include "binarysearchtree.h"
#include <vector>
#include <set>
#include <iostream>
using namespace std;

#define check(a, b) if(a == b.end()) continue;

struct pointcmp_y1{
    bool operator()(const QPoint &p, const QPoint &q){
        return p.y() < q.y();
    }
};

struct pointcmp_x1{
    bool operator()(const QPoint &p, const QPoint &q){
        return p.x() < q.x();
    }
};

Range_tree::Range_tree(int is_assoc, QObject *parent):is_association(is_assoc),
                                                            QObject(parent)
{
    is_built=false;
}


Range_tree_node* Range_tree::build_range_tree(std::vector<QPoint>::iterator beg,
                                              std::vector<QPoint>::iterator end, QRect boundary)
{

    int n = std::distance(beg, end);

    Range_tree*sublayer = 0;
    // create associated structure
    std::vector<QPoint> t_points;

    if(is_association){
        sublayer = new Range_tree(0, this);
        // create a copy of vector
        std::copy(beg, end, back_inserter(t_points));
        std::sort(t_points.begin(), t_points.end(), cmp_y);

        //sublayer->make_tree(t_points.begin(), t_points.end(),boundary);
    }
    if(n==0)
        return NULL;
    if(n==1){
        // contains only one point
        return new Range_tree_node(0, 0, *beg, boundary, t_points, sublayer, beg, end);
    }
    else{
        auto mid = beg + ( end - beg) / 2;


        QRect tmp = boundary;
        if(is_association)
            tmp.setRight(mid->x());
        else
            tmp.setBottom(mid->y());

        link_type vleft = build_range_tree(beg, mid, tmp);

        QRect tmp1 = boundary;
        if(is_association)
            tmp1.setLeft(mid->x());
        else
            tmp1.setTop(mid->y());

        link_type vright = build_range_tree(mid+1, end, tmp1);

        return new Range_tree_node(vleft, vright, *mid, boundary, t_points, sublayer, beg, end);

    }
}

bool Range_tree::make_tree( std::vector<QPoint>::iterator  beg,
                std::vector<QPoint>::iterator  end, QRect boundary){

    header =build_range_tree(beg, end, boundary );
    return true;
}



std::vector<QRect> Range_tree::traverse(int type){
    std::vector<QRect> rects;
    //if(type == 3)
    //    m_class1_rect.find_type(header, rects);
    //    m_class2_rect.find_type(header, rects);
    //findMiddleRectangle(header, rects);
    traverse(header, rects, type);
    //cout<<rects<<endl;
    //cout<< header->left_link->sublayer->header->region<<endl;
    return rects;
}

void Range_tree::traverse(link_type root, std::vector<QRect>& rects, int type){

    if(root != NULL){

        if(type == 1)
            m_class3_rect.findMiddleRectangle(root, rects);
        else if(type == 2){
            m_class4_rect.find_type_new2(root, rects);
        }else
            m_class1_rect.find_type(root, rects);

        traverse(root->left_link, rects, type);
        traverse(root->right_link, rects, type);
    }

}
