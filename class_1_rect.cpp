#include "class_1_rect.h"
#include "utility.h"
void printMat(int **mat, int r, int c);
using namespace std;
Class_1_Rect::Class_1_Rect()
{

}

struct cmp_px2{
    bool operator()(const std::pair<QPoint,QPoint> &p, const QPoint &q){
        return p.first.x() < q.x();
    }
};

struct cmp_py2{
    bool operator()(const std::pair<QPoint,QPoint> &p, const QPoint &q){
        return p.first.y() < q.y();
    }
};

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


std::vector<QPoint> Class_1_Rect::getPoints(const std::vector<QPoint> &points, const QPoint& c, const QPoint& d){
    std::vector<QPoint> results;

    for(auto it = points.begin(); it != points.end(); it++){

        if(it->x() <= c.x() && it->y() <= d.y())
            results.push_back(*it);
    }

    // return the r reference of results.
    return std::move(results);
}

void Class_1_Rect::find_type(link_type node, std::vector<QRect> &rects){
    int x = node->object.x() + 1;
    auto midy = node->points.begin() + (node->points.end() - node->points.begin())/2;
    int y = midy->y() + 1;

    // sorted in x
    std::vector<QPoint> secondvx;
    std::vector<QPoint> fourthvx;
    std::vector<std::pair<QPoint, QPoint>> thirdvx;
    std::vector<std::pair<QPoint, QPoint>> firstvy;

    int h = INT_MIN;
    for(auto i=node->end-1; i>= node->start; i--){
        if(x >= i->x() && y >= i->y()){
            // second quadrant
            if(i->y() > h){
                h = i->y();

                // insert the point in vector
                secondvx.insert(secondvx.begin(), *i);
            }
        }
    }

    int w = INT_MAX;
    for(auto i = node->start; i != node->end; i++){
        if(x <= i->x() && y<= i->y()){
            // fourth quadrant
            QPoint ref = *i;
            if(i->y() < w){
                w = i->y();
                fourthvx.push_back(*i);
            }
        }
    }

    // get c the lowest point in third quadrant
    // thirdvx & firstvy

    for(auto i = node->end -1; i >= node->start; i--){
        if(x >= i->x() && y <= i->y()){
            // third quadrant
            QPoint ref = *i;
            if(thirdvx.size() > 0){
                auto it = thirdvx.begin();
                // ref will be minimum y
                if(it->second.y() < ref.y())
                    ref = it->second;
            }
            thirdvx.insert(thirdvx.begin(), make_pair(*i, ref));
        }
    }

    for(auto i=node->points.end() -1; i >= node->points.begin(); i--){
        if(x <= i->x() && y >= i->y()){
            // first quadrant
            QPoint ref = *i;
            if(firstvy.size() > 0){
                auto it = firstvy.begin();
                // ref will be minimum x.
                if(it->second.x() < ref.x())
                    ref = it->second;
            }
            firstvy.insert(firstvy.begin(), make_pair(*i, ref));
        }
    }

    // create matrix
    int **mat = new int*[secondvx.size()];
    for(int i=0; i< secondvx.size(); i++){
        mat[i] = new int[fourthvx.size()];
        for(int j=0; j < fourthvx.size(); j++)
            mat[i][j] = 0;
    }

    int rindex = 0;

    if(secondvx.size() <= 1 || fourthvx.size() <= 1)
        return;

    //std::cout<<thirdvx<<std::endl;
    for(auto i= secondvx.begin(); i < secondvx.end() -1; i++, rindex++ ){
        auto a = i;
        auto b = i+1;

        QPoint c = {INT_MAX, INT_MAX};
        QPoint d = {INT_MAX, INT_MAX};
        //cout<<"point a "<<*a<<endl;
        //cout<<"point b "<<*b<<endl;
        // get the point c in first quadrant
        auto r = std::lower_bound(firstvy.begin(), firstvy.end(), *b, cmp_py2());
        if(r != firstvy.end()){
            c = r->second;
        }
        //cout<<"point c "<<c<<endl;
        r = std::lower_bound(thirdvx.begin(), thirdvx.end(), *a, cmp_px2());
        if(r != thirdvx.end())
            d = r->second;

        //cout<<"point d "<<d<<endl;
        auto points = getPoints(fourthvx, c, d);
        //cout<<points<<endl;
        int elems = points.size();
        for(int i=0; i< elems - 1; i++){
            QPoint p1 = points[i];
            QPoint p2 = points[i+1];

            auto p = std::find(fourthvx.begin(), fourthvx.end(), p1);
            size_t index = std::distance(fourthvx.begin(), p);
            mat[rindex][index] = (p1.y() - b->y())*(p2.x() - a->x());
        }

    }
    printMat(mat, secondvx.size(), fourthvx.size());
}
