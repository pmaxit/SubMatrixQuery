#include "class_4_rect.h"
#include<set>
#include "utility.h"

#define check(a, b) if(a == b.end()) continue;
std::ostream &operator<<(std::ostream &out, const QPoint &p){
    return out<<"Point("<<p.x()<<","<<p.y()<<")";
}

std::ostream &operator<<(std::ostream &out, const QRect &r){
    return out<<"Rect[ "<<r.topLeft()<< r.bottomRight()<< " ] ";
}


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

// find rectangles having one point in each quadrant
void Class_4_Rect::find_type_new2(link_type node, std::vector<QRect> &rects){

    int x = node->object.x(); // x axis
    auto midy = node->points.begin() + (node->points.end() - node->points.begin())/2;
    int y = midy->y();        // y axis

    // sorted in X
    std::vector<pair<QPoint,QPoint>> fourthvx;
    std::vector<pair<QPoint,QPoint>> firstvx;
    std::vector<pair<QPoint,QPoint>> secondvx;
    std::vector<pair<QPoint,QPoint>> thirdvx;


    // sorted in Y
    std::vector<pair<QPoint,QPoint>> fourthvy;
    std::vector<pair<QPoint,QPoint>> firstvy;
    std::vector<pair<QPoint,QPoint>> secondvy;
    std::vector<pair<QPoint,QPoint>> thirdvy;

    // sorted in x
    for(auto i = node->start; i != node->end; i++){
        if(x <= i->x() && y <= i->y()){
            // fourth quadrant
            QPoint ref = *i;
            if(fourthvx.size() >0){
                auto it = fourthvx.end() -1;
                if(it->second.y() < ref.y())
                    ref = it->second;
            }
            fourthvx.push_back(make_pair(*i, ref));
        }
        else
        if(x <= i->x() && y >= i->y() ){
            // first quadrant
            QPoint ref = *i;
            if(firstvx.size() > 0){
                auto it = firstvx.end() - 1;
                if(it->second.y() > ref.y())
                    ref = it->second;
            }
            firstvx.push_back(make_pair(*i, ref));
        }

    }

    // reverse iteration on x sorted points
    for(auto i = node->end-1; i >= node->start; i--){
        if(x >= i->x() && y >= i->y()){
            // second quadrant
            QPoint ref = *i;
            //std::cout<<*i<<std::endl;
            if(secondvx.size() > 0){
                auto it = secondvx.begin();
                if(it->second.y() > ref.y())
                    ref = it->second;
            }
            secondvx.insert(secondvx.begin(),make_pair(*i, ref));
        }
        else
        if ( x >= i->x() && y <= i->y()){
            // third quadrant
            QPoint ref = *i;

            if(thirdvx.size() > 0){
                auto it = thirdvx.begin();
                if(it->second.y() < ref.y())
                    ref = it->second;
            }
            thirdvx.insert(thirdvx.begin(), make_pair(*i, ref));
        }
    }

    for(auto i = node->points.end() -1; i >= node->points.begin(); i--){
        if(x <= i->x() && y >= i->y() ){
            // first qudrant
            QPoint ref = *i;

            if(firstvy.size() > 0){
                auto it = firstvy.begin();
                if(it->second.x() < ref.x())
                    ref = it->second;
            }
            firstvy.insert(firstvy.begin(), make_pair(*i, ref));
        }
        else
        if(x >= i->x() && y >= i->y()){
            // second quadrant
            QPoint ref = *i;

            if(secondvy.size() > 0 ){
                auto it = secondvy.begin();
                if(it->second.x() > ref.x())
                    ref = it->second;
            }
            secondvy.insert(secondvy.begin(), make_pair(*i, ref));
        }

    }

    for(auto i = node->points.begin(); i < node->points.end(); i++){
        if(x <= i->x() && y <= i->y()){
            // fourth quadrant
            QPoint ref = *i;

            if(fourthvy.size() > 0){
                auto it = fourthvy.end() - 1;
                if(it->second.x() < ref.x()){
                    ref = it->second;
                }
            }
            fourthvy.push_back(make_pair(*i, ref));
        }
        else
        if ( x >= i->x() && y <= i->y()){
            // third quadrant
            //std::cout<<*i<<std::endl;
            QPoint ref = *i;
            if(thirdvy.size() > 0){
                auto it = thirdvy.end() - 1;
                if(it->second.x() > ref.x()){
                    ref = it->second;
                }
            }
            thirdvy.push_back(make_pair(*i,ref));
        }
    }

    if(firstvy.size() == 0 || secondvx.size() == 0 || thirdvy.size() == 0 || fourthvx.size() ==0)
        return;

    /************************************ First quadrant as right ******************************/
    for(auto i = firstvy.begin(); i!= firstvy.end(); i++){

        //cout<<"FIRST QUADRANT "<<i->first<<endl;
        auto b = largest_less_than(fourthvx.begin(), fourthvx.end(), i->first, cmp_px());
        check(b, fourthvx);
        //cout<<"FOURTH QUADRANT "<<b->second<<endl;

        auto l = largest_less_than(thirdvy.begin(), thirdvy.end(), b->second, cmp_py());
        check(l,thirdvy);
        //cout<<"THIRD QUADRANT "<<l->second<<endl;

        auto t = std::lower_bound(secondvx.begin(), secondvx.end(), l->second, cmp_px());
        check(t, secondvx);
        //cout<<"SECOND QUADRANT"<<t->second<<endl;

        auto r = std::lower_bound(firstvy.begin(), firstvy.end(), t->second, cmp_py());
        //cout<<"FIRST QUADRANT"<<r->second<<endl;

        // either r is empty or it contains the same point
        if(r == firstvy.end() || r->second == i->first){

            if(r == firstvy.end()){
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

void Class_4_Rect::find_type2(link_type node, std::vector<QRect> &rects){

    // get staircase points

    // sorted in Y
    std::vector<pair<QPoint, QPoint>> firstvy;

    // sorted in Y
    std::vector<pair<QPoint, QPoint>> thirdvy;

    // sorted in X
    std::vector<pair<QPoint,QPoint>> secondvx;

    // sorted in X
    std::vector<pair<QPoint,QPoint>> fourthvx;


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
           for(auto it = fourthvx.begin(); it != fourthvx.end(); it++){
               if(it->second.y() < ref.y()){
                   ref = it->second;
               }
           }
           fourthvx.push_back(make_pair(*i, ref));
        }
        if(x >= i->x() && y >= i->y()){

            // second quadrant
            secondvx.push_back(make_pair(*i, *i));
            for(auto it=secondvx.begin(); it!= secondvx.end(); it++){
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
            //std::cout<<*i<<std::endl;
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

            firstvy.push_back(make_pair(*i,*i));
            for(auto it = firstvy.begin(); it!= firstvy.end(); it++){
                if(it->second.x() > i->x()){
                    it->second = *i;

                }
            }
        }

         if(x <= i->x() && y <= i->y()){
            // fourth quadrant
            QPoint ref = *i;

            for(auto it = fourthvy.begin(); it != fourthvy.end(); it++){
                if(it->second.x() < ref.x()){
                    ref = it->second;
                }
            }
            fourthvy.push_back(make_pair(*i, ref));
        }


         if ( x >= i->x() && y <= i->y()){
            // third quadrant
            //std::cout<<*i<<std::endl;
            QPoint ref = *i;
            for(auto it = thirdvy.begin(); it != thirdvy.end(); it++){
                if(it->second.x() > ref.x()){
                    ref = it->second;
                }
            }
            thirdvy.push_back(make_pair(*i,ref));
        }

         if(x >= i->x() && y >= i->y()){
            // second quadrant
            secondvy.push_back(make_pair(*i, *i));
            for(auto it=secondvy.begin(); it != secondvy.end(); it++){
                if(it->second.x() < i->x()){
                    it->second = *i;
                }
            }
        }
    }

    std::cout<<".... CHECKING START......."<<std::endl;
    std::cout<<firstvy<<std::endl;
    std::cout<<secondvy<<std::endl;
    std::cout<<thirdvy<<std::endl;
    std::cout<<fourthvy<<std::endl;
    std::cout<<"...........CHECKING MID.............. "<<std::endl;
    find_type_new2(node, rects);
    std::cout<<".... CHECKING END......."<<std::endl;
    // if any of the quadrant size is zero then no point in finding type 2 rectangles
    if(firstvy.size() == 0 || secondvx.size() == 0 || thirdvy.size() == 0 || fourthvx.size() ==0)
        return;

    /************************************ First quadrant as right ******************************/
    for(auto i = firstvy.begin(); i!= firstvy.end(); i++){

        //cout<<"FIRST QUADRANT "<<i->first<<endl;
        auto b = largest_less_than(fourthvx.begin(), fourthvx.end(), i->first, cmp_px());
        check(b, fourthvx);
        //cout<<"FOURTH QUADRANT "<<b->second<<endl;

        auto l = largest_less_than(thirdvy.begin(), thirdvy.end(), b->second, cmp_py());
        check(l,thirdvy);
        //cout<<"THIRD QUADRANT "<<l->second<<endl;

        auto t = std::lower_bound(secondvx.begin(), secondvx.end(), l->second, cmp_px());
        check(t, secondvx);
        //cout<<"SECOND QUADRANT"<<t->second<<endl;

        auto r = std::lower_bound(firstvy.begin(), firstvy.end(), t->second, cmp_py());
        //cout<<"FIRST QUADRANT"<<r->second<<endl;

        // either r is empty or it contains the same point
        if(r == firstvy.end() || r->second == i->first){

            if(r == firstvy.end()){
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
