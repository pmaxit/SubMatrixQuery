#ifndef CLASS_3_RECT_H
#define CLASS_3_RECT_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <iostream>
#include <vector>

#include "range_tree_node.h"

using namespace std;

class Class_3_Rect
{
protected:
    typedef Range_tree_node *link_type;
public:
    Class_3_Rect();
    static bool cmp_x(const QPoint &p, const QPoint &q){ return p.x() < q.x() ; }
    static bool cmp_y(const QPoint &p, const QPoint &q){ return p.y() < q.y() ; }

    void findMiddleRectangle(link_type node, std::vector<QRect> &rects);
};

#endif // CLASS_3_RECT_H
