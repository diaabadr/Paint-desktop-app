#include "circle.h"

Circle::Circle (QString name,QPoint str,QPoint end,int thick,QColor color):Shape(name,str,end,thick,color)
{
 setR_ByPoints();
}

double Circle::perimeter() const
{
    return 2*3.14*this->radius;
}

void Circle::setR_ByPoints()
{
 double w;
 double h;
 w=qFabs(this->getEndPnt().x()-this->getStrPnt().x());
 h=qFabs(this->getEndPnt().y()-this->getStrPnt().y());
 this->radius=qSqrt(qPow(w,2)+qPow(h,2));
 this->radius/=2;
}

ToolType Circle::getType() const
{
return circletool;
}
