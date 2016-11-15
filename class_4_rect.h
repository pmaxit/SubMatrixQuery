#ifndef CLASS_4_RECT_H
#define CLASS_4_RECT_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <iostream>
#include <vector>

#include "range_tree_node.h"

using namespace std;

class Class_4_Rect
{

protected:
    typedef Range_tree_node *link_type;

public:
    Class_4_Rect();
    void find_type_new2(link_type node, std::vector<QRect> &rects);
    void find_type2(link_type node, std::vector<QRect> &rects);
};

#endif // CLASS_4_RECT_H
