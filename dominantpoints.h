#ifndef DOMINANTPOINTS_H
#define DOMINANTPOINTS_H

#include<iostream>
#include<QPoint>
#include <vector>
#include <QRect>
#include <QObject>
#include <set>

using namespace std;

class dominantPoints : public QObject
{
    Q_OBJECT
public:
    dominantPoints(QObject * parent);

    void setBoundaryRectangle(int width, int height);
    vector<QRect> type1(const vector<QPoint> &points);
    vector<QRect> type2(const vector<QPoint> &points);
    vector<QRect> type3(const vector<QPoint> &points);
    vector<QRect> type4(const vector<QPoint> &points);

private:


    static bool cmp_x(const QPoint &p, const QPoint &q){ return p.x() < q.x() ; }
    static bool cmp_y(const QPoint &p, const QPoint &q){ return p.y() < q.y() ; }

    void add_firstQDomPoints(vector<QRect> &points);
    void add_secondQDomPoints(vector<QRect> &points);
    void add_thirdQDomPoints(vector<QRect> &points);
    void add_fourthQDomPoints(vector<QRect> &points);

    vector<QPoint> m_points;
    int m_width;
    int m_height;
};

#endif // DOMINANTPOINTS_H
