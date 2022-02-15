#include "straightline.h"

StraightLine::StraightLine(QString name,QPoint str,QPoint end,int thick,QColor color):Shape(name,str,end,thick,color)
{
setL_ByPoints();
}

void StraightLine::setLength(double len)
{
    this->length=len;
}

void StraightLine::setL_ByPoints()
{
 double w;
 double h;
 w=qFabs(this->getEndPnt().x()-this->getStrPnt().x());
 h=qFabs(this->getEndPnt().y()-this->getStrPnt().y());
 this->length=qSqrt(qPow(w,2)+qPow(h,2));
}

double StraightLine:: perimeter() const
{
    return length;
}

ToolType StraightLine::getType() const
{
    return linetool;
}
