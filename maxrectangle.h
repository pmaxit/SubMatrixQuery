#ifndef MAXRECTANGLE_H
#define MAXRECTANGLE_H

#include<iostream>
#include<vector>
#include<QPoint>
#include <numeric>
#include <stdlib.h>
#include <algorithm>
#include <Qrect>
#include <QObject>
#include <QVector>
#include <QMap>

#include "dominantpoints.h"
#include "boundedrectangle.h"

using namespace std;

class maxRectangle : public QObject
{
public:
    maxRectangle(QObject *parent=0);
    void addPoints(std::vector<QPoint> &points);
    void setBoundaryRectangle(int width, int height);

    void process();
private:
    Q_OBJECT
    std::vector<QPoint> m_points;
    dominantPoints* m_dp;
    BoundedRectangle *m_bp;

    int m_width;
    int m_height;

signals:
    void displayRectangle(QMap<int, QVector<QRect> >& rects);
};

#endif // MAXRECTANGLE_H
