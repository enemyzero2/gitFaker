#ifndef TRIANGLE_H
#define TRIANGLE_H
#include<QMainWindow>
#include<QPainter>
#include<QWidget>
#include<QMouseEvent>
#include"point.h"

class Triangle :public QWidget
{
    Q_OBJECT
private:
    Point x1;
    Point x2;
    Point x3;
public:
    bool P1=false;
    bool P2=false;
    bool P3=false;
    Triangle(Point* new_x1,Point* new_x2,Point* new_x3);
    //void set_x1(Point* p1);
    //void set_x2(Point* p2);
    //void set_x3(Point* p3);
};

#endif // TRIANGLE_H
