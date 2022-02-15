#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

class Rectangle:public Shape
{
private:
    double length;
        double width;
public:
    Rectangle(QString name,QPoint str,QPoint end,int thick,QColor color);

    void setLength(double len);

    void setWidth(double wid);

    void setW_ByPoints();

    void setL_ByPoints();

    double getLength()const;

    double getWidth()const;

    virtual ToolType getType() const ;

    virtual double perimeter()const;
};

#endif // RECTANGLE_H
