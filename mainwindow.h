#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maxrectangle.h"
#include "segment_tree.h"
#include "segment_tree_new.h"
#include <QSettings>
#include <QPoint>
#include <QVector>
#include <QRect>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static QSettings settings;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setQueryPoint(QPoint &p);
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:

    void on_actionClear_triggered();

    void on_actionGenerate_triggered();

    void on_actionRandom_Query_triggered();

    void on_addRectangles(QMap<int, QVector<QRect>>&);

    void on_selectTypeRectangles(int type);

    void on_comboBox_currentIndexChanged(int index);

    void on_actionShow_Rectangles_triggered();

    void on_actionShow_Grid_triggered();

    void on_actionQuery_Point_triggered();

signals:
    void drawRectangles(QMap<int, QVector<QRect>> &);

private:
    Ui::MainWindow *ui;
    maxRectangle* mr;
    Segment_Tree segmentTree;
    Segment_Tree_New<QRect> segmentTreeNew;

    QPoint m_query;
    QVector<QRect> m_rects;
    QRect rect;
};

#endif // MAINWINDOW_H
