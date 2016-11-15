#ifndef RANGE_TREE_H
#define RANGE_TREE_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <vector>

#include "range_tree_node.h"

#include "class_3_rect.h"
#include "class_4_rect.h"
#include "class_2_rect.h"
#include "class_1_rect.h"

class Range_tree: public QObject
{

protected:
    int is_built;
    int is_association;
    Class_4_Rect m_class4_rect;
    Class_3_Rect m_class3_rect;
    Class_2_Rect m_class2_rect;
    Class_1_Rect m_class1_rect;

    typedef Range_tree_node * link_type;
    friend struct Range_tree_node ;
    friend class Class_4_Rect;

    static link_type &left(link_type x){
        return x->left_link;
    }

    static link_type &right(link_type x){
        return x->right_link;
    }

    static link_type &parent(link_type x){
        return x->parent_link;
    }

    link_type header;
    link_type node;
    link_type root() const{
        if(header !=0)
            return header;
        else
            return 0;
    }

    Range_tree_node* build_range_tree(std::vector<QPoint>::iterator beg,
                                      std::vector<QPoint>::iterator end, QRect boundary);

public:
    Range_tree(int is_assoc=1, QObject *parent=NULL);
    static bool cmp_x(const QPoint &p, const QPoint &q){ return p.x() < q.x() ; }
    static bool cmp_y(const QPoint &p, const QPoint &q){ return p.y() < q.y() ; }

    bool make_tree( std::vector<QPoint>::iterator beg,
                    std::vector<QPoint>::iterator end, QRect boundary);

    std::vector<QRect> traverse(int type);
    void traverse(link_type root, std::vector<QRect> &rects, int type);
};

#endif // RANGE_TREE_H
