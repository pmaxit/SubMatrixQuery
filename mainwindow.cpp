#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QVector>
#include <QPoint>
#include <QDebug>
#include <QMap>
#include <QMouseEvent>

//QSettings MainWindow::settings(("submatrix","utdallas"));
QSettings MainWindow::settings("/Users/puneet/iosettings.ini", QSettings::IniFormat);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Maximum Empty Rectangle Query");
    mr = new maxRectangle(this);

    setMySize();

    statusBar()->showMessage(tr("Ready"));
    qsrand(QDateTime::currentMSecsSinceEpoch());

    //ui->widget->setParent(this);
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_actionGenerate_triggered()));
    connect(this, SIGNAL(drawRectangles(QMap<int, QVector<QRect>> &)), this,SLOT(on_addRectangles(QMap<int, QVector<QRect>> &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMySize(){
    setMinimumSize(800, 600);

    int width = 2400;
    int height = 2400;

    ui->widget->setMinimumHeight(height);
    ui->widget->setMinimumWidth(width);

    QString str;
    str.setNum(ui->widget->width());
    ui->label_width->setText(str);

    str.setNum(ui->widget->height());
    ui->label_height->setText(str);

    mr->setBoundaryRectangle(width, height);
}

void MainWindow::on_addRectangles(QMap<int, QVector<QRect> > &rects){
    qDebug()<<" on adding rectangles"<<endl;

    m_rects.clear();

    foreach(int i, rects.keys())
        m_rects += rects[i];
    //m_rects = rects; // copy the rectangles
    ui->widget->addRectangles(rects);

    //segmentTree.build_segment_tree(m_rects);
    segmentTreeNew.build(m_rects.toStdVector());
}

void MainWindow::on_actionGenerate_triggered()
{
    // generate randome points based on the # points.
    int points_cnt = ui->lineEdit->text().toInt();

    ui->lineEdit->setText("");
    QVector<QPoint> points;

    while(points.size() < points_cnt){

        int w = ui->widget->width();
        int h = ui->widget->height();

        QPoint point(qrand() %(w)+20, qrand() %(h)+20);


        point = mapToGlobal(point);
        point = ui->widget->mapFromGlobal(point);

        if(!points.contains(point))
            points.append(point);

    }

    ui->widget->addPoints(points);
    // add it to maxRectangle dataset too.
    std::vector<QPoint> vec_points = points.toStdVector();
    mr->addPoints(vec_points);

    qDebug()<<" Savings settings "<<endl;
    // add to persistent storage
    settings.beginWriteArray("points");
    for(int i = 0; i < points.size(); i++){
        settings.setArrayIndex(i);
        settings.setValue("QPoint",points[i]);
    }
    settings.endArray();
}

void MainWindow::on_actionClear_triggered()
{
    ui->widget->clear();
}

void MainWindow::on_selectTypeRectangles(int type){
    qDebug()<<"Select Query "<<type<< endl;
    ui->widget->updateRectangles(type);
}

void MainWindow::on_actionRandom_Query_triggered()
{
    QVector<QPoint> points;
    // get the points
    int size = settings.beginReadArray("points");

    for(int i=0; i< size; i++){
        settings.setArrayIndex(i);
        QPoint point = settings.value("QPoint").toPoint();
        points.append(point);
    }
    settings.endArray();

    ui->widget->addPoints(points);
    // add it to maxRectangle dataset too.
    std::vector<QPoint> vec_points = points.toStdVector();
    mr->addPoints(vec_points);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    qDebug()<<" CURRENT INDEX "<<index<<endl;
    ui->widget->updateRectangles(index);
}

void MainWindow::on_actionShow_Rectangles_triggered()
{
    mr->process();
    qDebug()<<"action query "<<endl;
}

void MainWindow::setQueryPoint(QPoint &p){
    ui->xlabel->setText(QString(p.x()));
    ui->ylabel->setText(QString(p.y()));
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton){
        m_query = event->pos();
        qDebug()<<m_query<<endl;
    }
    //m_query = mapTo(ui->widget, m_query);
    m_query = mapToGlobal(m_query);
    m_query = ui->widget->mapFromGlobal(m_query);

    ui->widget->setQueryPoint(m_query);

    ui->xlabel->setText(QString::number(m_query.x()));
    ui->ylabel->setText(QString::number(m_query.y()));
}

void MainWindow::on_actionShow_Grid_triggered()
{
    ui->widget->toggleShowGrid();
}

void MainWindow::on_actionQuery_Point_triggered()
{
    // get only maxArearectangle
    QRect rect = segmentTreeNew.stabbinQuery(m_query.x(), m_query.y());
    QVector<QRect> maxRect{rect};
    ui->widget->appendRectangles(8, maxRect);

    /*
    QVector<QRect>&& rects = segmentTree.maxAreaRectangle(m_query);
    QVector<QRect> maxRect{rects.back()};

    rects.pop_back();
    ui->widget->appendRectangles(7,rects);
    ui->widget->appendRectangles(8, maxRect);
    */
}
