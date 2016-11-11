#include "dominantpoints.h"
#include <QDebug>


struct pointcmp_y{
    bool operator()(const QPoint &p, const QPoint &q){
        return p.y() < q.y();
    }
};

struct pointcmp_x{
    bool operator()(const QPoint &p, const QPoint &q){
        return p.x() < q.x();
    }
};

dominantPoints::dominantPoints(QObject *parent):QObject(parent){
    m_width = 0;
    m_height = 0;
}

// sharing with only 1 edge
vector<QRect> dominantPoints::type3(const vector<QPoint> &points){

    m_points = std::move(points);
    sort(m_points.begin(), m_points.end(), cmp_x);
    vector<QRect> rects;

    // create tree for the points

    std::set<QPoint, pointcmp_y> ptree_y;
    /****************************** First quadrant ****************************/
    for(auto it = m_points.rbegin(); it != m_points.rend(); ++it){
        // search predecessor / successor in y
        int y = it->y();
        auto p1 = std::upper_bound(ptree_y.begin(), ptree_y.end(), *it, cmp_y);
        auto p2 = std::lower_bound(ptree_y.begin(), ptree_y.end(), *it, cmp_y);

        if(p2 != ptree_y.begin() && p1 != ptree_y.end()){
            --p2;

       //  make a rectangle with *it, p1, p2 and right boundary
            rects.push_back( QRect(QPoint(it->x(), p2->y()),
                               QPoint(m_width,p1->y())));
        }
        ptree_y.insert(*it);
    }

    ptree_y.clear();
    /******************************* Second quadrant **************************/
    for(auto it = m_points.begin(); it != m_points.end(); it++){
        int y = it->y();
        auto p1 = std::upper_bound(ptree_y.begin(), ptree_y.end(), *it, cmp_y);
        auto p2 = std::lower_bound(ptree_y.begin(), ptree_y.end(), *it, cmp_y);

        if(p2 != ptree_y.begin() && p1 != ptree_y.end()){
            --p2;

       //  make a rectangle with *it, p1, p2 and left boundary
            rects.push_back( QRect(QPoint(0, p2->y()),
                               QPoint(it->x(),p1->y())));
        }
        ptree_y.insert(*it);
    }

    std::set<QPoint, pointcmp_x> ptree_x;
    sort(m_points.begin(), m_points.end(), cmp_y);
    /******************************* Third Quadrant ***************************/
    for(auto it = m_points.begin(); it != m_points.end(); it++){
        int y = it->x();
        auto p1 = std::upper_bound(ptree_x.begin(), ptree_x.end(), *it, cmp_x);
        auto p2 = std::lower_bound(ptree_x.begin(), ptree_x.end(), *it, cmp_x);

        // ptree.begin() is the first element
        // ptree.end() is the invalid element
        if(p2 != ptree_x.begin() && p1!= ptree_x.end()){
            --p2;

            // make a rectangle with *it, p1, p2 and top boundary
            rects.push_back(QRect(QPoint(p2->x(), 0), QPoint(p1->x(), it->y())));
        }
        ptree_x.insert(*it);

    }

    ptree_x.clear();
    /******************************** Fourth quadrant **************************/
    for(auto it = m_points.rbegin(); it != m_points.rend(); it++){
        int y = it->x();
        auto p1 = std::upper_bound(ptree_x.begin(), ptree_x.end(), *it, cmp_x);
        auto p2 = std::lower_bound(ptree_x.begin(), ptree_x.end(), *it, cmp_x);

        // ptree.begin() is the first element
        // ptree.end() is the invalid element
        if(p2 != ptree_x.begin() && p1!= ptree_x.end()){
            --p2;
            // make a rectangle with *it, p1, p2 and top boundary
            rects.push_back(QRect(QPoint(p2->x(), it->y()), QPoint(p1->x(), m_height)));
        }
        ptree_x.insert(*it);
    }

    return rects;

}

// sharing with atleast 2 opposite edges
// TODO: last rectangle is not included. Include that.
vector<QRect> dominantPoints::type2(const vector<QPoint> &points){
    m_points = std::move(points);

    vector<QRect> rects;
    sort(m_points.begin(), m_points.end(), cmp_y);

    int y0 = m_points[0].y();
    for(int i=1; i< m_points.size(); i++){
        int y1 = m_points[i].y();
        rects.push_back(QRect(QPoint(0, y0), QPoint(m_width, y1)));
        y0 = y1;
    }

    sort(m_points.begin(), m_points.end(), cmp_x);
    int x0 = m_points[0].x();
    for(int i=1; i< m_points.size(); i++){
        int x1 = m_points[i].x();
        rects.push_back(QRect(QPoint(x0, 0), QPoint(x1, m_height)));
        x0 = x1;
    }

    return rects;
}

vector<QRect> dominantPoints::type4(const vector<QPoint> &points){
    m_points = std::move(points);

    vector<QRect> rects;
    sort(m_points.begin(), m_points.end(), cmp_y);

    int y0=m_points[0].y();
    int y1 = m_points[m_points.size()-1].y();


    rects.push_back(QRect(QPoint(0,0), QPoint(m_width,y0)));
    rects.push_back(QRect(QPoint(0,y1), QPoint(m_width,m_height)));


    sort(m_points.begin(), m_points.end(), cmp_x);
    int x0 = m_points[0].x();
    int x1 = m_points[m_points.size()-1].x();

    rects.push_back(QRect(QPoint(0,0), QPoint(x0, m_height)));
    rects.push_back(QRect(QPoint(x1, 0), QPoint(m_width, m_height)));

    return rects;
}

// sharing with adjacent edges
vector<QRect> dominantPoints::type1(const vector<QPoint> &data){
    // sort the points in x order
    m_points = std::move(data);

    vector<QRect> rects;
    sort(m_points.begin(), m_points.end(), cmp_x);

    add_firstQDomPoints(rects);
    add_secondQDomPoints(rects);
    add_thirdQDomPoints(rects);
    add_fourthQDomPoints(rects);

    return rects;
}

void dominantPoints::add_firstQDomPoints(vector<QRect> &rects){

    // find the largest x
    int end = m_points.size()-1;
    int prev = end;

    QPoint anchor = m_points[end];
    for(int i=end-1; i>=0; i--){
        if(anchor.y() > m_points[i].y()){
            anchor = m_points[i];
            // convert to rectangle

            int left = min(m_points[i].x(), m_points[prev].x());
            int bottom = max(m_points[i].y(), m_points[prev].y());

            rects.push_back(QRect(QPoint(left, 0), QPoint(m_width, bottom)));
            prev = i;

        }
    }

}

void dominantPoints::setBoundaryRectangle(int width, int height){
    m_width = width;
    m_height = height;
}

void dominantPoints::add_secondQDomPoints(vector<QRect> &rects){

    // find the largest y
    int start = 0;
    QPoint anchor = m_points[start];
    int prev = start;
    for(int i=start+1; i< m_points.size(); i++){
        if(anchor.y() > m_points[i].y()){
            anchor = m_points[i];
            int right = max(m_points[i].x(), m_points[prev].x());
            int bottom = max(m_points[i].y(), m_points[prev].y());

            rects.push_back(QRect(QPoint(0, 0), QPoint(right, bottom)));
            prev = i;
        }
    }

    return;
}

void dominantPoints::add_thirdQDomPoints(vector<QRect> &rects){


    int start = 0;
    QPoint anchor = m_points[start];
    int prev = start;
    for(int i=start+1; i< m_points.size() ; i++){
        if(anchor.y() < m_points[i].y()){
            anchor = m_points[i];
            int right = max(m_points[i].x(), m_points[prev].x());
            int bottom = min(m_points[i].y(), m_points[prev].y());

            rects.push_back(QRect(QPoint(0, bottom ), QPoint(right, m_height)));
            prev = i;

        }
    }
}

void dominantPoints::add_fourthQDomPoints(vector<QRect> &rects){


    // find the largest x
    int end = m_points.size()-1;
    QPoint anchor = m_points[end];
    int prev = end;
    for(int i=end-1; i>=0; i--){
        if(anchor.y() < m_points[i].y()){
            anchor = m_points[i];

            int left = min(m_points[i].x(), m_points[prev].x());
            int bottom = min(m_points[i].y(), m_points[prev].y());

            rects.push_back(QRect(QPoint(left, bottom ), QPoint(m_width, m_height)));
            prev = i;
        }
    }
}
