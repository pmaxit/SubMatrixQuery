#include "segment_tree.h"
#include <QDebug>

typedef Traits::Interval Interval;
typedef Traits::Pure_interval Pure_interval;
typedef Traits::Key Key;

Segment_Tree::Segment_Tree()
{
    m_segment_tree = NULL;
}

Segment_Tree::~Segment_Tree(){
    if(m_segment_tree)
        delete m_segment_tree;
}

void Segment_Tree::build_segment_tree(QVector<QRect> &rects){


    std::list<Interval> InputList;

    for(int i=0; i< rects.size(); i++){
        QRect rect = rects[i];
        int x1 = rect.left();
        int x2 = rect.right();

        int y1 = rect.top();
        int y2 = rect.bottom();

        int area = rect.width()* rect.height();
        if(x1 < x2 && y1 < y2){
            InputList.push_back(Interval(Pure_interval(Key(x1,y1), Key(x2,y2)),area));
        }
        else{
            InputList.push_back(Interval(Pure_interval(Key(x1,y2), Key(x2,y1)),-1*area));
        }

    }

    if(m_segment_tree)
        delete m_segment_tree;

    m_segment_tree = new Segment_tree_2_type(InputList.begin(), InputList.end());

    qDebug()<<"\n\nSegment Tree Prepared"<<endl;
}

QVector<QRect> Segment_Tree::maxAreaRectangle(QPoint &p){
    double epsilon = 0.005;
    std::list<Interval> OutputList;
    QVector<QRect> rects;

    Interval q1 = Interval(Pure_interval(Key(p.x(), p.y()), Key(p.x() + epsilon, p.y() + epsilon)), 0);

    m_segment_tree->window_query(q1, std::back_inserter(OutputList));
    std::list<Interval>::iterator j = OutputList.begin();

    qDebug()<<" Window Query... "<<p<<endl;
    QRect maxRect;
    int area = -1;
    while(j != OutputList.end()){
        std::cout << (*j).first.first.x() << "-" << (*j).first.second.x() << " "
                      << (*j).first.first.y() << "-" << (*j).first.second.y()<<std::endl;

            QRect rect = QRect(QPoint((*j).first.first.x(), (*j).first.first.y()),
                               QPoint((*j).first.second.x(), (*j).first.second.y()));


            if( area < rect.width()* rect.height()){

                area = rect.width()*rect.height();
                maxRect = rect;
            }

            rects.push_back(rect);
            j++;
    }

    rects.push_back(maxRect);
    return rects;
}
