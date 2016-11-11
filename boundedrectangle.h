#ifndef BOUNDEDRECTANGLE_H
#define BOUNDEDRECTANGLE_H

#include <QRect>
#include <QPoint>
#include <vector>
#include <QObject>
#include "range_tree.h"

class BoundedRectangle : public QObject
{
    Q_OBJECT

protected:
    static bool cmp_x(const QPoint &p, const QPoint &q){ return p.x() < q.x() ; }
    static bool cmp_y(const QPoint &p, const QPoint &q){ return p.y() < q.y() ; }

public:
    BoundedRectangle(QObject *parent=0);
    void setBoundaryRectangle(int width, int height);

    std::vector<QRect> buildRectangles(std::vector<QPoint> & dominants, QRect boundary, int type);
    Range_tree *rt;
    int m_width;
    int m_height;
};

#endif // BOUNDEDRECTANGLE_H
