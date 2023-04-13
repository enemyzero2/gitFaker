#ifndef RECT_H
#define RECT_H


#include<QMainWindow>
#include<QPainter>
#include<QWidget>
#include<QMouseEvent>
#include"point.h"

class n_Rect :public QWidget
{
    Q_OBJECT
    friend Point;
private:
    Point x;
    Point y;

public:
    bool isDrawing=false;
 n_Rect(Point* n_x,Point* n_y);
 ~n_Rect(){};
 double getRect_x1(){return x.getX();}
 double getRect_y1(){return x.getY();}
 double getRect_x2(){return y.getX();}
 double getRect_y2(){return y.getY();}
};

#endif // RECT_H
