#include "maxrectangle.h"

#include <QDebug>

maxRectangle::maxRectangle(QObject *parent): QObject(parent)
{
    m_dp = new dominantPoints(parent);
    m_bp = new BoundedRectangle(parent);
    QObject::connect(this, SIGNAL(displayRectangle(QMap<int, QVector<QRect>> &)),
            parent, SLOT(on_addRectangles(QMap<int, QVector<QRect>> &)));
}

void maxRectangle::setBoundaryRectangle(int width, int height){
    m_dp->setBoundaryRectangle(width, height);
    m_bp->setBoundaryRectangle(width, height);
}

void maxRectangle::addPoints(std::vector<QPoint> &points){
    std::copy(points.begin(), points.end(), back_inserter(m_points));
}

void maxRectangle::process(){

    QMap<int, QVector<QRect> > rectMaps;
    vector<QRect> dominants;

    // sharing only one point with boundary
    dominants = m_dp->type3(m_points);
    rectMaps.insert(1, QVector<QRect>::fromStdVector(dominants));

    // find rectangle sharing opposite boundary
    dominants = m_dp->type2(m_points);
    rectMaps.insert(3, QVector<QRect>::fromStdVector(dominants));

    // find rectangle sharing adjancent boundary
    dominants = m_dp->type1(m_points);
    rectMaps.insert(2, QVector<QRect>::fromStdVector(dominants));

    // find Rectangle sharing 3 boundaries
    dominants = m_dp->type4(m_points);
    rectMaps.insert(4, QVector<QRect>::fromStdVector(dominants));

    // find inner rectangle with 3 points in one quadrant
    dominants = m_bp->buildRectangles(m_points, QRect(QPoint(0,0),QPoint(800, 600)), 1);
    rectMaps.insert(5, QVector<QRect>::fromStdVector(dominants));

    // find inner rectangle with 1 point in each quadrant
    dominants = m_bp->buildRectangles(m_points, QRect(QPoint(0,0),QPoint(800, 600)), 2);
    rectMaps.insert(6, QVector<QRect>::fromStdVector(dominants));

    dominants = m_bp->buildRectangles(m_points, QRect(QPoint(0,0),QPoint(800, 600)), 3);
    rectMaps.insert(7, QVector<QRect>::fromStdVector(dominants));

    //QVector<QRect> temp = QVector<QRect>::fromStdVector(dominants);
    //rectMaps.insert(5, temp);

    emit(displayRectangle(rectMaps));
}
