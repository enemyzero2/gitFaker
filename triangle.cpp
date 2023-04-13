#include "triangle.h"

Triangle::Triangle(Point* new_x1,Point* new_x2,Point* new_x3){
 x1.setX(new_x1->getX());
 x1.sety(new_x1->getY());

 x2.setX(new_x2->getX());
 x2.sety(new_x2->getY());

 x3.setX(new_x3->getX());
 x3.sety(new_x3->getY());
}
