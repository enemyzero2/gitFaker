#ifndef POINT_H
#define POINT_H
#include<QMainWindow>
#include<QPainter>
#include<QWidget>
#include<QMouseEvent>
#include<math.h>
class Point: public QPoint
{

    friend class mainwindow;
private:
    double m_x;
    double m_y;
public:
    bool drawPoint=false;
    Point(double x,double y):m_x(x),m_y(y){};
    Point(){};
    ~Point(){};
    void setX(double newx){m_x=newx;}
    void sety(double newy){m_y=newy;}
    double getX();
    double getY();
    void pushButton_clicked(QImage &m_image);
    static double distancetopoint(Point* a,Point* b){
        return sqrt(fabs(pow(a->getX()-b->getX(),2)+pow(a->getY()-b->getY(),2)));
    }

};

#endif // POINT_H
