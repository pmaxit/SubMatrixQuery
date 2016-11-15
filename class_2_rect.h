#ifndef CLASS_2_RECT_H
#define CLASS_2_RECT_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <iostream>
#include <vector>
#include <limits>

#include "range_tree_node.h"

using namespace std;

class Class_2_Rect
{
protected:
    typedef Range_tree_node *link_type;
public:
    Class_2_Rect();
    static bool cmp_x(const QPoint &p, const QPoint &q){ return p.x() < q.x() ; }
    static bool cmp_y(const QPoint &p, const QPoint &q){ return p.y() < q.y() ; }

    void find_type(link_type node, std::vector<QRect> &rects);

    std::vector<QPoint> getPoints(const std::vector<QPoint> &points, const QPoint& c, const QPoint& d);
};

#endif // CLASS_2_RECT_H
