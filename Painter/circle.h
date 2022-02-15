#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"
class Shape;
class Circle :public Shape
{
private:
    double radius;
public:
    Circle(QString name,QPoint str,QPoint end,int thick,QColor color);

    virtual double perimeter() const;

    void setR_ByPoints();

    virtual ToolType getType() const ;
};
#endif
