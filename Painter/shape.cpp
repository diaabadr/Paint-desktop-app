#include "shape.h"


Shape::Shape(QString Name,QPoint str,QPoint end,int thick,QColor color)
{
 this->name =Name;
    this->startPoint=str;
    this->endPoint=end;
    this->thickness=thick;
    this->Color=color;
}

void Shape::setStrPnt(QPoint str)
{
    this->startPoint=str;
}

void Shape::setEndPnt(QPoint end)
{
    this->endPoint = end;
}

QPoint Shape::getStrPnt()const
{
    return this->startPoint;
}

QPoint Shape::getEndPnt()const
{
    return this->endPoint;
}

int Shape::getThickness()const
{
    return this->thickness;
}

QString Shape::getName()
{
    return this->name;
}

void Shape::setColor(QColor col)
{
    this->Color=col;
}

Shape::~Shape(){}

