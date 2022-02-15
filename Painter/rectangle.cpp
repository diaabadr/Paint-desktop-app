#include "rectangle.h"
#include <QPainter>
Rectangle::Rectangle(QString name,QPoint str,QPoint end,int thick,QColor color):Shape(name,str,end,thick,color)
{
setW_ByPoints();
setL_ByPoints();
}

void Rectangle::setLength(double len)
{
    this->length=len>0?len:0;
}

void Rectangle::setWidth(double wid)
{
    this->width=wid>0?wid:0;
}

void Rectangle::setW_ByPoints()
{
    this->width=qFabs(this->getEndPnt().x()-this->getStrPnt().x());
}

void Rectangle::setL_ByPoints()
{
  this->length=qFabs(this->getEndPnt().y()-this->getStrPnt().y());
}

double Rectangle::getLength() const
{
    return this->length;
}

double Rectangle::getWidth() const
{
    return this->width;
}

ToolType Rectangle::getType() const
{
    return rectangletool;
}

double Rectangle::perimeter() const
{
        return (length + width) * 2;
}

