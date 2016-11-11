#include "renderarea.h"
#include <QDebug>
#include <QMouseEvent>

RenderArea::RenderArea(QWidget *parent): QWidget(parent)
{
    m_parent = parent;
    shape = Polygon;
    antialiased = true;
    transformed = false;
    m_clear = false;
    m_showGrid = true;

    // default brush
    this->brush = QBrush(Qt::blue, Qt::DiagCrossPattern);

    // default pen
    this->pen = QPen(Qt::red);
    this->pen.setWidth(4);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    m_type=0;
    m_query=QPoint(-1,-1);
}

QSize RenderArea::sizeHint() const{
    return QSize(400, 200);
}

QSize RenderArea::minimumSizeHint()const{
    return QSize(100, 100);
}

void RenderArea::setShape(Shape shape){
    this->shape = shape;
    update();
}

void RenderArea::setPen(const QPen &pen){
    this->pen = pen;
    update();
}

void RenderArea::setBrush(const QBrush &brush){
    this->brush = brush;
    update();
}

void RenderArea::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

void RenderArea::setTransformed(bool transformed)
{
    this->transformed = transformed;
    update();
}

void RenderArea::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    if(m_showGrid)
        drawBackground(&painter, QRect(0, 0, width(), height()));

    painter.setPen(pen);
    painter.setBrush(brush);
    if(antialiased){
        painter.setRenderHint(QPainter::Antialiasing, true);
    }
    if(m_clear){
        m_clear = false;
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setPen(palette().dark().color());
        painter.setBrush(QBrush(Qt::NoBrush));
        painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
        return;
    }
    painter.drawPoints(m_points);

    QVector<QRect> rects;

    if(m_type != 0)
        rects = m_rects[m_type];
    else{
        foreach(int i, m_rects.keys())
            rects += m_rects[i];
    }

    for(int i=0; i< rects.size(); i++){

        // filter type of rectangles
        QRect rect = rects[i];

        painter.setPen(QPen(Qt::black,1));
        painter.setBrush(QBrush(Qt::NoBrush));
        painter.drawRect(rect);

        painter.fillRect(rect, QColor(128, 128, 255, 128));
    }
    //painter.drawRects(m_rects);

    for(int i=0; i< m_points.size(); i++){
        char s[100];
        QPoint p = m_points[i];
        sprintf(s,"(%d, %d)",p.x(), p.y());
            painter.drawText(p,QString(s));
    }


    /** DRAW QUERY POINT **/
    if(m_query.x() != -1 && m_query.y()!= -1){
        // draw the point
        // Set the pen
        painter.setPen(QPen(Qt::red,5));
        painter.setBrush(QBrush(Qt::NoBrush));

        painter.drawPoint(m_query);
    }
    //painter.setRenderHint(QPainter::Antialiasing, false);
    //painter.setPen(palette().dark().color());
    //painter.setBrush(QBrush(Qt::NoBrush, Qt::CrossPattern));
    //painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RenderArea::drawBackground(QPainter *p, const QRect &crect){
    const QRectF rect = crect.normalized();
      p->save();
      p->setPen(QPen(Qt::lightGray,4));
      int l = int(rect.left());
      l -= (l % 10);

      int r = int(rect.right());
      r -= (r % 10);
      if(r < int(rect.right()))
         r += 10;

      int t = int(rect.top());
      t -= (t % 10);

      int b = int(rect.bottom());
      b -= (b % 10);
      if(b < int(rect.bottom()))
         b += 10;

      for( int x = l; x <= r; x+=10)
         for( int y = t; y <= b; y+=10)
            p->drawPoint(x,y);

      p->restore();
}

void RenderArea::addPoints(const QVector<QPoint> &points){
    // add points
    m_points += points;
    update();
}

void RenderArea::addRectangles(QMap<int, QVector<QRect>> &rects){
    m_rects = rects;
    update();
}

void RenderArea::appendRectangles(int key, QVector<QRect> &rects){
    m_rects[key] = rects;
    update();
}

void RenderArea::updateRectangles(int type){
    m_type = type;
    update();
}

void RenderArea::clear(){
    m_points.clear();
    m_clear=  true;
    update();
}

void RenderArea::toggleShowGrid(){
    m_showGrid = !m_showGrid;
    update();
}

void RenderArea::setQueryPoint(QPoint &p){
    m_query = p;
    update();
}
