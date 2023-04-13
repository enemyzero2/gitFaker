#ifndef CIRCLE_H
#define CIRCLE_H

#include<QMainWindow>
#include<QPainter>
#include<QWidget>
#include<QMouseEvent>
#include"point.h"

class d_circle :public QWidget
{
    Q_OBJECT
private:
    double c_x;
    double c_y;
    double r;

public:
    QRect lastCircleRect;
    bool isDrawing=false;
 d_circle(double x,double y,double z)
    {   c_x=x;
        c_y=y;
        r=z;
    }
 d_circle(Point a,double x){
     c_x=a.getX();
     c_y=a.getY();
     r=x;
 }

};

#endif // CIRCLE_H
