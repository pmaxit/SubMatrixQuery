#include "class_4_rect.h"
#include<set>

#define check(a, b) if(a == b.end()) continue;

struct pointcmp_y1{
    bool operator()(const QPoint &p, const QPoint &q){
        return p.y() < q.y();
    }
};

struct pointcmp_x1{
    bool operator()(const QPoint &p, const QPoint &q){
        return p.x() < q.x();
    }
};

Class_4_Rect::Class_4_Rect()
{

}

struct cmp_px{
    bool operator()(const std::pair<QPoint,QPoint> &p, const QPoint &q){
        return p.first.x() < q.x();
    }
};


struct cmp_py{
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
  if(lowerb == last-1)
      lowerb = last-1;

  // if lowerb is not lower
  if(comp(*lowerb, value))
      return lowerb;

  return last;

}


void Class_4_Rect::find_type2(link_type node, std::vector<QRect> &rects){

    std::set<QPoint,pointcmp_y1> first;
    std::set<QPoint,pointcmp_x1> second;
    std::set<QPoint, pointcmp_y1> third;
    std::set<QPoint, pointcmp_x1> fourth;

    // sorted in Y
    std::vector<pair<QPoint, QPoint>> firstv;

    // sorted in Y
    std::vector<pair<QPoint, QPoint>> thirdv;

    // sorted in X
    std::vector<pair<QPoint,QPoint>> secondv;

    // sorted in X
    std::vector<pair<QPoint,QPoint>> fourthv;


    // sorted in X
    std::vector<pair<QPoint, QPoint>> firstvx;

    // sorted in X
    std::vector<pair<QPoint, QPoint>> thirdvx;

    // sorted in Y
    std::vector<pair<QPoint,QPoint>> secondvy;

    // sorted in Y
    std::vector<pair<QPoint,QPoint>> fourthvy;


    // divide the points in quadrant
    int x = node->object.x(); // x axis
    auto midy = node->points.begin() + (node->points.end() - node->points.begin())/2;
    int y = midy->y();        // y axis


    // draw axis rectangle
    //rects.push_back(QRect(QPoint(x, node->region.top()), QPoint(x,node->region.bottom())));
    //rects.push_back(QRect(QPoint(node->region.left(),y), QPoint(node->region.right(), y)));

    // sorted in x
    for(auto i = node->start; i != node->end; i++){

        if(x <= i->x() && y <= i->y()){
            // fourth quadrant
           QPoint ref = *i;
           for(auto it = fourthv.begin(); it != fourthv.end(); it++){
               if(it->second.y() < ref.y()){
                   ref = it->second;
               }
           }
           fourthv.push_back(make_pair(*i, ref));
        }

        if(x >= i->x() && y >= i->y()){
            // second quadrant
            secondv.push_back(make_pair(*i, *i));
            for(auto it=secondv.begin(); it!= secondv.end(); it++){
                if(it->second.y() < i->y()){
                    it->second = *i;
                }
            }
        }

        if(x <= i->x() && y >= i->y() ){
            // first quadrant
            QPoint ref = *i;
            for(auto it = firstvx.begin(); it != firstvx.end(); it++){
                if(it->second.y() > ref.y()){
                    ref  = it->second;
                }
            }
            firstvx.push_back(make_pair(*i, ref));
        }

        if ( x >= i->x() && y <= i->y()){
            // third quadrant
            thirdvx.push_back(make_pair(*i, *i));
            for(auto it=thirdvx.begin(); it != thirdvx.end(); it++){
                if(it->second.y() > i->y()){
                    it->second = *i;
                }
            }
        }

    }

    // points sorted by y coordinate
    for(auto i = node->points.begin(); i < node->points.end(); i++){
        if(x <= i->x() && y >= i->y() ){
            // first qudrant
            first.insert(*i);
            firstv.push_back(make_pair(*i,*i));
            for(auto it = firstv.begin(); it!= firstv.end(); it++){
                if(it->second.x() > i->x()){
                    it->second = *i;

                }
            }
        }

        else if(x <= i->x() && y <= i->y()){
            // fourth quadrant
            QPoint ref = *i;
            for(auto it = fourthvy.begin(); it != fourthvy.end(); it++){
                if(it->second.x() < ref.x()){
                    ref = it->second;
                }
            }
            fourthvy.push_back(make_pair(*i, ref));
        }


        else if ( x >= i->x() && y <= i->y()){
            // third quadrant
            third.insert(*i);
            QPoint ref = *i;
            for(auto it = thirdv.begin(); it != thirdv.end(); it++){
                if(it->second.x() > ref.x()){
                    ref = it->second;
                }
            }
            thirdv.push_back(make_pair(*i,ref));
        }

        else if(x >= i->x() && y >= i->y()){
            // second quadrant
            secondvy.push_back(make_pair(*i, *i));
            for(auto it=secondvy.begin(); it != secondvy.end(); it++){
                if(it->second.x() < i->x()){
                    it->second = *i;
                }
            }
        }
    }

    // if any of the quadrant size is zero then no point in finding type 2 rectangles
    if(firstv.size() == 0 || secondv.size() == 0 || thirdv.size() == 0 || fourthv.size() ==0)
        return;

    /************************************ First quadrant as right ******************************/
    for(auto i = firstv.begin(); i!= firstv.end(); i++){

        //cout<<"FIRST QUADRANT "<<i->first<<endl;
        auto b = largest_less_than(fourthv.begin(), fourthv.end(), i->first, cmp_px());
        check(b, fourthv);
        //cout<<"FOURTH QUADRANT "<<b->second<<endl;

        auto l = largest_less_than(thirdv.begin(), thirdv.end(), b->second, cmp_py());
        check(l,thirdv);
        //cout<<"THIRD QUADRANT "<<l->second<<endl;

        auto t = std::lower_bound(secondv.begin(), secondv.end(), l->second, cmp_px());
        check(t, secondv);
        //cout<<"SECOND QUADRANT"<<t->second<<endl;

        auto r = std::lower_bound(firstv.begin(), firstv.end(), t->second, cmp_py());
        //cout<<"FIRST QUADRANT"<<r->second<<endl;

        // either r is empty or it contains the same point
        if(r == firstv.end() || r->second == i->first){

            if(r == firstv.end()){
                QRect rect = QRect(QPoint(l->second.x(),t->second.y()), QPoint(i->first.x(), b->second.y()));
                rects.push_back(rect);
            }else{
                QRect rect = QRect(QPoint(l->second.x(),t->second.y()), QPoint(r->second.x(), b->second.y()));
                rects.push_back(rect);
            }
        }

        //cout<<"********************************************"<<endl;
    }


    /************************************ First quadrant as top ******************************/

    if(firstvx.size() == 0 || thirdvx.size() == 0 || secondvy.size() == 0 || fourthvy.size() == 0)
        return;

    for(auto i = firstvx.begin(); i!= firstvx.end(); i++){
        //cout<<"FIRST QUADRANT "<<i->first<<endl;

        auto l = std::lower_bound(secondvy.begin(), secondvy.end(), i->first, cmp_py());

        check(l, secondvy);
        //cout<<"SECOND QUADRANT "<<l->second<<endl;

        auto r = std::lower_bound(thirdvx.begin(), thirdvx.end(), l->second, cmp_px());
        check(r, thirdvx);
        //cout<<"THIRD QUADRANT "<<r->second<<endl;

        auto b = largest_less_than(fourthvy.begin(), fourthvy.end(), r->second, cmp_py());
        check(r, fourthvy);
        //cout<<"FOURTH QUADRANT "<<b->second<<endl;

        auto t = largest_less_than(firstvx.begin(), firstvx.end(), b->second, cmp_px() );
        //cout<<"FIRST QUADRANT "<<t->first<<endl;

        if(t == firstvx.end() || t->second == i->first){
            //cout<<"RECTANGLE FOUND"<<endl;
            if(t == firstvx.end()){
                QRect rect = QRect(QPoint(l->second.x(),i->first.y()), QPoint(r->second.x(), b->second.y()));
                rects.push_back(rect);
            }else{
                QRect rect = QRect(QPoint(l->second.x(),t->second.y()), QPoint(r->second.x(), b->second.y()));
                rects.push_back(rect);
            }
        }
    }
}
