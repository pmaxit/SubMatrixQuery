#include "class_3_rect.h"
#include<set>

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

Class_3_Rect::Class_3_Rect()
{

}

void Class_3_Rect::findMiddleRectangle(link_type node, vector<QRect> &rects){
// get the boundary

    // x side
    QRect boundary = node->region;
    // points
    //cout<<node->points<<endl;

    // find point in m_points;
    auto it = std::lower_bound(node->start, node->end, node->object, cmp_x);
    auto mid = it;
    //cout<<*it<<endl;
    std::set<QPoint, pointcmp_y1> ptree_y;

    // traverse from bigger to smaller number
    while(it != node->start){
        it--;
        int y = it->y();
        auto p1 = std::upper_bound(ptree_y.begin(), ptree_y.end(), *it, cmp_y);
        auto p2 = std::lower_bound(ptree_y.begin(), ptree_y.end(), *it, cmp_y);

        if(p2 != ptree_y.begin() && p1 != ptree_y.end()){
            --p2;

            for(auto i = mid; i < node->end; i++){

                if(p2->y() < i->y() && p1->y() > i->y()){
                    // i can be a right boundary .
                    rects.push_back(QRect(QPoint(it->x(), p2->y()), QPoint(i->x(), p1->y())));
                    break;
                }
            }

        }

        ptree_y.insert(*it);
    }

    /******************************** 3 points on right side of x axis ***************************/
    it = mid; // reinitialize it

    //
    ptree_y.clear();
    while(it != node->end){
        it++;
        int y = it->y();
        auto p1 = std::upper_bound(ptree_y.begin(), ptree_y.end(), *it, cmp_y);
        auto p2 = std::lower_bound(ptree_y.begin(), ptree_y.end(), *it, cmp_y);

        if(p2 != ptree_y.begin() && p1 != ptree_y.end()){
            --p2;
            //cout<<"TOP BOUNDARY "<<p2->y()<<endl;
            //cout<<"BOTTOM BOUNDARY "<<p1->y()<<endl;
            //rects.push_back(QRect(QPoint(node->object.x(), p2->y()), QPoint(it->x(), p1->y())));
            for(auto i = mid; i >= node->start; i--){
                //cout<<" CHECKING "<<*i<<endl;
                if(p2->y() < i->y() && p1->y() > i->y()){
                    // i can be left boundary
                    //cout<<"MID POINT "<<i->y()<<endl;
                    rects.push_back(QRect(QPoint(i->x(), p2->y()), QPoint(it->x(), p1->y())));
                    break;
                }
            }
        }
        ptree_y.insert(*it);
    }


    /********************************* 3 points below the y axis ***************************/

    auto midy = node->points.begin() + (node->points.end() - node->points.begin())/2;

    std::set<QPoint, pointcmp_x1> ptree_x;
    it = midy;

    while(it != node->points.end()){
        it++;


        auto p1 = std::upper_bound(ptree_x.begin(), ptree_x.end(), *it, cmp_x);
        auto p2 = std::lower_bound(ptree_x.begin(), ptree_x.end(), *it, cmp_x);

        if(p2 != ptree_x.begin() && p1 != ptree_x.end() ){
            p2--;
            //rects.push_back(QRect(QPoint(node->object.x(), )))
            for(auto i = midy; i >= node->points.begin(); i--){
                if(p2->x() < i->x() && p1->x() > i->x()){
                    rects.push_back(QRect(QPoint(p2->x(),i->y()), QPoint(p1->x(), it->y())));
                    break;
                }
            }
        }
        ptree_x.insert(*it);
    }

    /************************** 3 points above the y yaxis *****************************/
    ptree_x.clear();
    it= midy;

    while(it != node->points.begin()){
        it--;


        auto p1 = std::upper_bound(ptree_x.begin(), ptree_x.end(), *it, cmp_x);
        auto p2 = std::lower_bound(ptree_x.begin(), ptree_x.end(), *it, cmp_x);

        if(p2 != ptree_x.begin() && p1 != ptree_x.end() ){
            p2--;
            //rects.push_back(QRect(QPoint(node->object.x(), )))
            for(auto i = midy; i < node->points.end(); i++){
                if(p2->x() < i->x() && p1->x() > i->x()){
                    rects.push_back(QRect(QPoint(p2->x(),it->y()), QPoint(p1->x(), i->y())));
                    break;
                }
            }
        }
        ptree_x.insert(*it);
    }

}
