#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QPainter>
#include <QVector>
#include <QMap>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                    Chord, Pie, Path, Text, Pixmap };

    RenderArea(QWidget *parent=0);

    QSize minimumSizeHint()const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void addPoints(const QVector<QPoint> &points);


public slots:
    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialiased(bool antialiased);
    void setTransformed(bool transformed);
    void clear();
    void addRectangles(QMap<int, QVector<QRect> > &rects);
    void appendRectangles(int key, QVector<QRect> &rects);
    void updateRectangles(int type);
    void setQueryPoint(QPoint &p);
    void toggleShowGrid();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    //void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    bool m_clear;
    int m_type;
    bool m_showGrid;

    QPoint m_query;
    QObject *m_parent;


    // store points
    QVector<QPoint> m_points;
    QMap<int, QVector<QRect>> m_rects;

    void drawBackground(QPainter *p, const QRect &rect);
};

#endif // RENDERAREA_H
