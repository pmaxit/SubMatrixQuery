#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <QVector>
#include <QRect>
#include <CGAL/Cartesian.h>
#include <CGAL/Segment_tree_k.h>
#include <CGAL/Range_segment_tree_traits.h>
#include <iostream>

typedef CGAL::Cartesian<double> K;
typedef CGAL::Segment_tree_map_traits_2<K, char> Traits;
typedef CGAL::Segment_tree_2<Traits > Segment_tree_2_type;

class Segment_Tree
{
public:

    void build_segment_tree(QVector<QRect> &rects);
    QVector<QRect> maxAreaRectangle(QPoint &p);

    Segment_Tree();
    ~Segment_Tree();

protected:
    Segment_tree_2_type* m_segment_tree;

};

#endif // SEGMENT_TREE_H
