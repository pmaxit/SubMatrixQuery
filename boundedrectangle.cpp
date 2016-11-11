#include "boundedrectangle.h"

#include <CGAL/Cartesian.h>
#include <CGAL/Range_segment_tree_traits.h>
#include <CGAL/Range_tree_k.h>

typedef CGAL::Cartesian<double> K;
typedef CGAL::Range_segment_tree_set_traits_2<K> Traits;
typedef CGAL::Range_tree_2<Traits> Range_tree_2_type;

using namespace std;

BoundedRectangle::BoundedRectangle(QObject *parent):QObject(parent)
{
    rt = new Range_tree(1, parent);
}

struct pointcmp_x{
    bool operator()(const QPoint &p, const QPoint &q){
        return p.x() < q.x();
    }
};

void BoundedRectangle::setBoundaryRectangle(int width, int height){
    m_width=width;
    m_height=height;
}

vector<QRect> BoundedRectangle::buildRectangles(std::vector<QPoint> & points, QRect boundary, int type){

    // sort on x first
    std::sort(points.begin(), points.end(), cmp_x);

    rt->make_tree(points.begin(), points.end(), QRect(QPoint(0,0), QPoint(m_width, m_height)));

    //rects.push_back(boundary);
    return rt->traverse(type);
}
