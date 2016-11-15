#include "class_2_rect.h"
#include "utility.h"

#define check(a, b) if(a == b.end()) continue;
using namespace std;

template <class ForwardIterator, class T, class cmp>
  ForwardIterator largest_less_than ( ForwardIterator first,
                                                  ForwardIterator last,
                                                  const T& value, cmp comp)
{
  ForwardIterator lowerb = std::lower_bound(first, last, value, comp);

  if(lowerb != first)
      lowerb--;

  // if lowerb is the end means every point was smaller than value
  if(lowerb == last)
      return last;

  // if lowerb is not lower
  if(comp(*lowerb, value))
      return lowerb;

  return last;
}

std::ostream &operator<<(std::ostream &out, const QPoint &r);

struct cmp_px1{
    bool operator()(const std::pair<QPoint,QPoint> &p, const QPoint &q){
        return p.first.x() < q.x();
    }
};

struct cmp_py1{
    bool operator()(const std::pair<QPoint,QPoint> &p, const QPoint &q){
        return p.first.y() < q.y();
    }
};

Class_2_Rect::Class_2_Rect()
{

}

std::vector<QPoint> Class_2_Rect::getPoints(const std::vector<QPoint> &points, const QPoint& c, const QPoint& d){
    std::vector<QPoint> results;

    for(auto it = points.begin(); it != points.end(); it++){

        if(it->y() >= c.y() && it->x() <= d.x())
            results.push_back(*it);
    }

    // return the r reference of results.
    return std::move(results);
}

void printMat(int **mat, int r, int c){
    std::cout<<"MATRIX A  "<<endl;
    for(int i =0; i< r-1; i++){
        for(int j=0; j< c-1; j++){
            std::cout<<mat[i][j]<<"   ";
        }
        std::cout<<endl;
    }
}

void Class_2_Rect::find_type(link_type node, std::vector<QRect> &rects){

    int x = node->object.x()+1;
    auto midy = node->points.begin() + (node->points.end() - node->points.begin())/2;
    int y = midy->y()+1;

    // sorted in X
    std::vector<QPoint> thirdvx;
    std::vector<QPoint> firstvx;
    std::vector<std::pair<QPoint, QPoint>> secondvx;
    std::vector<std::pair<QPoint, QPoint>> fourthvy;

    int h = INT_MAX;
    int w = INT_MIN;
    // get the lower & upper envelope
    for(auto i=node->end-1; i>= node->start; i--){
        if(x >= i->x() && y <= i->y()){
            // third quadrant

            if(i->y() < h){
                h = i->y();
                // insert the point in vector
                thirdvx.insert(thirdvx.begin(), *i);
            }
        }
    }

    for(auto i=node->start; i< node->end; i++){

        if(x <= i->x() && y >= i->y() ){
            // first quadrant
            if(i->y() > w){
                w = i->y();
                // insert the points in vector
                firstvx.push_back(*i);
            }
        }
    }

    // get c the lowest point in 2nd quadrant
    for(auto i=node->end-1; i >= node->start; i--){
        if(x >= i->x() && y >= i->y()){
            QPoint ref=*i;
            if(secondvx.size() > 0){
                auto it = secondvx.begin();
                if(it->second.y() > ref.y())
                    ref = it->second;
            }
            secondvx.insert(secondvx.begin(), std::make_pair(*i, ref));

        }

    }

    // get the d leftmost point
    for(auto i= node->points.begin(); i< node->points.end(); i++){
        if(x <= i->x() && y<= i->y()){
            QPoint ref = *i;
            if(fourthvy.size() >0){
                auto it = fourthvy.end() - 1;
                if(it->second.x() < ref.x())
                    ref = it->second;
            }
            fourthvy.push_back(std::make_pair(*i, ref));

        }
    }

    // create matrix
    //int mat[10][5];
    //int mat[thirdvx.size()-1][firstvx.size()-1];
    int **mat  = new int *[thirdvx.size()];
    for(int i=0; i< thirdvx.size(); i++){
        mat[i] = new int[firstvx.size()];
        for(int j = 0 ; j< firstvx.size(); j++)
            mat[i][j] = 0;
    }

    // for any consecutive pair a,b in third quadrant

    //std::cout<<firstvx<<std::endl;

    int rindex=0;

    if(thirdvx.size() <= 1)
        return;

    for(auto i = thirdvx.begin(); thirdvx.size() >=2 && i < thirdvx.end()-1; i++, rindex++){
        auto a = i;
        auto b = i+1;
        QPoint c={-INT_MIN, -INT_MIN};
        QPoint d ={INT_MAX, INT_MAX};

        // get the point c in 2nd quadrant
        auto t = std::lower_bound(secondvx.begin(), secondvx.end(), *a, cmp_px1());

        if(t != secondvx.end()){
            c = t->second;
        }

        // get the point d in 4th quadrant
        t = largest_less_than(fourthvy.begin(), fourthvy.end(), *b, cmp_py1());

        if(t != fourthvy.end()){
            d = t->second;
        }

        //std::cout<<" POINT A "<<*a<<" POINT B "<<*b<<std::endl;
        //std::cout<<" POINT C "<<c<<" POINT D "<<d<<std::endl;

        // get points from first quadrant between c & d
        auto points = getPoints(firstvx, c,d );
        //TODO: can be improved by simply searching in binary search tree.

        int elems = points.size();
        for(int i=0; i< elems - 1; i++){

           QPoint p1 = points[i];
           QPoint p2 = points[i+1];

           auto p = std::find(firstvx.begin(), firstvx.end(), p1);
           size_t index = std::distance(firstvx.begin(), p);
           mat[rindex][index] = (b->y() - p1.y())*(p2.x() - a->x());
        }

        //std::cout<<" Ip points "<< points<<std::endl;
    }
    printMat(mat, thirdvx.size(), firstvx.size());
}
