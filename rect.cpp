#include "rect.h"
n_Rect::n_Rect(Point* n_x,Point* n_y)
{
    x.setX(n_x->getX());
    x.sety(n_x->getY());
    y.setX(n_y->getX());
    y.sety(n_y->getY());
}
