#include "mainwindow.h"
#include <QPushButton>
#include "point.h"
#include"circle.h"
#include"rect.h"
#include<QApplication>
#include <QPainter>
#include<color.h>
#include<colordialog.h>
#include<QBrush>
#include<QDebug>
#include<returnlast.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 默认绘制点
    m_shapeType = ShapePoint;
    //初始化成员变量
    colorDialog = new ColorDialog(this);
    returnlast=new ReturnLast(this);
    startPoint=new Point(0,0);
    endPoint=new Point(0,0);
    thirdPoint=new Point(0,0);
    x = new d_circle(0, 0, 0);
    rect =new n_Rect(startPoint,endPoint);
    triangle =new Triangle(startPoint,endPoint,thirdPoint);
    //caidanlan
    menubar =new QMenuBar(this);
    pmenu= new QMenu("工具(&t)",this);
    paction=new QAction("undo(&z)",this);
    paction2=new QAction("redo(&x)",this);
    pmenu->addAction(paction);
    pmenu->addAction(paction2);
    menubar->addMenu(pmenu);
    setMenuBar(menubar);


    // 设置绘图区域的大小
    m_image = QImage(QSize(1920, 1080), QImage::Format_RGB32);
    m_image.fill(Qt::white);
    setFixedSize(m_image.size());
    setWindowTitle(tr("Graph Generator"));
    returnlast->savePixmap(&m_image);

    // 创建控制按钮
    QPushButton *btnPoint = new QPushButton(tr("Generate Point"), this);
    QPushButton *btnCircle = new QPushButton(tr("Generate Circle"), this);
    QPushButton *btnRect = new QPushButton(tr("Generate Rect"), this);
    QPushButton *btnTriangle = new QPushButton(tr("Generate Triangle"), this);
    QPushButton *btnClear = new QPushButton(tr("Clear"), this);
    QPushButton *colorChooseButton = new QPushButton(tr("color choose"),this);
    QPushButton *undo=new QPushButton(tr("undo"),this);
    QPushButton *redo=new QPushButton(tr("redo"),this);

    // 设置按钮位置和大小
    btnPoint->setGeometry(20, 20, 150, 30);
    btnCircle->setGeometry(20, 60, 150, 30);
    btnRect->setGeometry(20, 100, 150, 30);
    btnTriangle->setGeometry(20,140,150,30);
    btnClear->setGeometry(20, 180, 150, 30);
    colorChooseButton->setGeometry(20,220,150,30);
    undo->setGeometry(1490,900,150,30);
    redo->setGeometry(1680,900,150,30);
    // 连接按钮的点击信号和槽函数
    connect(btnPoint, SIGNAL(clicked()), this, SLOT(pushButton_clicked_Point()));
    connect(btnCircle, SIGNAL(clicked()), this, SLOT(pushButton_clicked_Circle()));
    connect(btnRect, SIGNAL(clicked()), this, SLOT(pushButton_clicked_Rect()));
    connect(btnTriangle,SIGNAL(clicked()),this,SLOT(pushButton_clicked_Triangle()));
    connect(btnClear, SIGNAL(clicked()), this, SLOT(pushButton_clicked_clearImage()));
    connect(colorChooseButton, SIGNAL(clicked()), colorDialog, SLOT(exec()));
    connect(undo,SIGNAL(clicked()),returnlast,SLOT(undo()));
    connect(redo,SIGNAL(clicked()),returnlast,SLOT(redo()));
    connect(paction,SIGNAL(triggered()),returnlast,SLOT(undo()));
    connect(paction2,SIGNAL(triggered()),returnlast,SLOT(undo()));
    connect(returnlast,SIGNAL(imageChanged(QPixmap)),this,SLOT(updateimage(QPixmap)));

}

MainWindow::~MainWindow()
{
delete[]startPoint;
delete[]endPoint;
delete[]thirdPoint;
delete[]x;
delete[]rect;
delete[]triangle;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    // 绘制绘图区域
    QPainter painter(this);
    painter.drawImage(0, 0, m_image);
}

void MainWindow::clearImage()
{
    // 清空绘图区域
    m_image.fill(Qt::white);
    update();
}


void MainWindow::pushButton_clicked_Point(){
    m_shapeType = ShapePoint;
    installEventFilter(this);
}
void MainWindow::pushButton_clicked_Circle(){
    m_shapeType =ShapeCircle;
    installEventFilter(this);
}
void MainWindow::pushButton_clicked_Rect(){
    m_shapeType=ShapeRect;
    installEventFilter(this);
}
void MainWindow::pushButton_clicked_Triangle(){
    m_shapeType=ShapeTriangle;
    installEventFilter(this);
}
void MainWindow::pushButton_clicked_clearImage(){
    m_image.fill(Qt::white);
    update();
}
void MainWindow::updateimage(QPixmap a){
    qDebug() <<"sending completed!";
    QImage newimage=a.toImage();
    m_image=newimage.copy();
    update();
}
bool MainWindow::eventFilter(QObject* obj, QEvent *event)
{
    if (m_shapeType == ShapePoint) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event); // 获取鼠标事件
            if (mouseEvent->button() == Qt::LeftButton) { // 判断是否为左键单击事件
                //qDebug() << "valueChanged signal emitted";
                Point newpoint(mouseEvent->x(), mouseEvent->y());
                QPainter painter(&m_image);
                painter.setPen(QPen(colorDialog->color(), 5));
                painter.drawPoint(newpoint.getX(), newpoint.getY());
                painter.end();
                update();
                returnlast->savePixmap(&m_image);
                return true; // 事件已处理，返回true
            }



        }
    }
    else if (m_shapeType == ShapeCircle) {
        if (event->type() == QEvent::MouseButtonPress && x->isDrawing == false) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event); // 获取鼠标事件
            if (mouseEvent->button() == Qt::LeftButton) {
                x->isDrawing = true; // 标记正在画图
                startPoint->setX(mouseEvent->x()); // 记录起始点横坐标
                startPoint->sety(mouseEvent->y()); // 记录起始点纵坐标
                update();
                return true; // 事件已处理，返回true
            }
        }
        else if (event->type() == QEvent::MouseMove && x->isDrawing == true) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event); // 获取鼠标事件
            endPoint->setX(mouseEvent->x()); // 记录终止点横坐标
            endPoint->sety(mouseEvent->y()); // 记录终止点纵坐标
            return true; // 事件已处理，返回true
        }
        else if (event->type() == QEvent::MouseButtonRelease && x->isDrawing == true) {
            // 利用起始点和终止点画圆
            QPainter painter(&m_image);
            painter.setPen(QPen(colorDialog->color(), 5));
            painter.setBrush(QBrush(colorDialog->color()));
            painter.drawEllipse(startPoint->getX()-Point::distancetopoint(startPoint, endPoint), startPoint->getY()-Point::distancetopoint(startPoint, endPoint), Point::distancetopoint(startPoint, endPoint)*2 , Point::distancetopoint(startPoint, endPoint)*2 );
            painter.end();
            update();
            returnlast->savePixmap(&m_image);
            x->isDrawing = false; // 标记结束画图
            startPoint->setX(0); // 重置起始点横坐标
            startPoint->setY(0); // 重置起始点纵坐标
            endPoint->setX(0); // 重置终止点横坐标
            endPoint->setY(0); // 重置终止点纵坐标
            return true; // 事件已处理，返回true
        }

    }
    else if (m_shapeType == ShapeRect){
        if (event->type() == QEvent::MouseButtonPress && x->isDrawing == false) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event); // 获取鼠标事件
            if (mouseEvent->button() == Qt::LeftButton) {
                rect->isDrawing = true; // 标记正在画图
                startPoint->setX(mouseEvent->x()); // 记录起始点横坐标
                startPoint->sety(mouseEvent->y()); // 记录起始点纵坐标
                update();
                return true; // 事件已处理，返回true
            }
        }
        else if (event->type() == QEvent::MouseMove && rect->isDrawing == true) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event); // 获取鼠标事件
            endPoint->setX(mouseEvent->x()); // 记录终止点横坐标
            endPoint->sety(mouseEvent->y()); // 记录终止点纵坐标
            return true; // 事件已处理，返回true
        }
        else if (event->type() == QEvent::MouseButtonRelease && rect->isDrawing == true) {
            // 利用起始点和终止点画圆
            n_Rect endrect(startPoint,endPoint);
            QPainter painter(&m_image);
            painter.setPen(QPen(colorDialog->color(), 5));
            painter.setBrush(QBrush(colorDialog->color()));
            painter.drawRect(endrect.getRect_x1(),endrect.getRect_y1(),endrect.getRect_x2()-endrect.getRect_x1(),endrect.getRect_y2()-endrect.getRect_y1());
            painter.end();
            update();
            returnlast->savePixmap(&m_image);
            x->isDrawing = false; // 标记结束画图
            startPoint->setX(0); // 重置起始点横坐标
            startPoint->setY(0); // 重置起始点纵坐标
            endPoint->setX(0); // 重置终止点横坐标
            endPoint->setY(0); // 重置终止点纵坐标
            return true; // 事件已处理，返回true
        }

    }
    else if(m_shapeType ==ShapeTriangle){
        if (event->type() == QEvent::MouseButtonPress && triangle->P1 == false &&triangle->P2==false &&triangle->P3==false) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event); // 获取鼠标事件
            if (mouseEvent->button() == Qt::LeftButton) {
                rect->isDrawing = true; // 标记正在画图
                startPoint->setX(mouseEvent->x()); // 记录起始点横坐标
                startPoint->sety(mouseEvent->y()); // 记录起始点纵坐标
                update();
                triangle->P1=true;
                return true; // 事件已处理，返回true
            }
        }
        else if (event->type() == QEvent::MouseButtonPress && triangle->P1 == true &&triangle->P2==false &&triangle->P3==false) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event); // 获取鼠标事件
            if (mouseEvent->button() == Qt::LeftButton) {
                rect->isDrawing = true; // 标记正在画图
                endPoint->setX(mouseEvent->x()); // 记录起始点横坐标
                endPoint->sety(mouseEvent->y()); // 记录起始点纵坐标
                update();
                triangle->P2=true;
                QPainter painter(&m_image);
                painter.setPen(QPen(colorDialog->color(),5));
                painter.drawLine(startPoint->getX(),startPoint->getY(),endPoint->getX(),endPoint->getY());
                painter.end();
                update();
                returnlast->savePixmap(&m_image);
                return true; // 事件已处理，返回true
            }
        }
        else if (event->type() == QEvent::MouseButtonPress && triangle->P1 == true &&triangle->P2==true &&triangle->P3==false) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event); // 获取鼠标事件
            if (mouseEvent->button() == Qt::LeftButton) {
                rect->isDrawing = true; // 标记正在画图
                thirdPoint->setX(mouseEvent->x()); // 记录起始点横坐标
                thirdPoint->sety(mouseEvent->y()); // 记录起始点纵坐标
                update();
                triangle->P3=true;
                QPainter painter(&m_image);
                painter.setPen(QPen(colorDialog->color(),5));
                painter.drawLine(startPoint->getX(),startPoint->getY(),thirdPoint->getX(),thirdPoint->getY());
                painter.drawLine(endPoint->getX(),endPoint->getY(),thirdPoint->getX(),thirdPoint->getY());
                QBrush brush(colorDialog->color(), Qt::SolidPattern);
                                painter.setBrush(brush);
                                QPointF point1(startPoint->getX(),startPoint->getY());
                                QPointF point2(endPoint->getX(),endPoint->getY());
                                QPointF point3(thirdPoint->getX(),thirdPoint->getY());
                                QPointF points[3] = {point1,point2,point3};
                painter.drawPolygon(points, 3);
                painter.end();
                update();
                returnlast->savePixmap(&m_image);
                triangle->P1 = false;
                triangle->P2 = false;
                triangle->P3 = false;// 标记结束画图
                startPoint->setX(0); // 重置起始点横坐标
                startPoint->setY(0); // 重置起始点纵坐标
                endPoint->setX(0); // 重置终止点横坐标
                endPoint->setY(0); // 重置终止点纵坐标
                thirdPoint->setX(0);
                thirdPoint->sety(0);
                return true; // 事件已处理，返回true
            }

    }

}
    return false; // 事件未处理，返回false

}
//日记：更改startpoint和endpoint使其不必一直重新定义
//日记：circle完成
//编译和内部文件
//4.9 增加撤销功能

