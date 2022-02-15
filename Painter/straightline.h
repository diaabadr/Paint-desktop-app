#ifndef STRAIGHTLINE_H
#define STRAIGHTLINE_H
#include "shape.h"
#include <QPainter>

class StraightLine:public Shape
{
private:
    double length;
public:
    StraightLine(QString name,QPoint str,QPoint end,int thick,QColor color);

    void setLength(double len);

    void setL_ByPoints();

    virtual double perimeter()const;

virtual ToolType getType() const;


};

#endif // STRAIGHTLINE_H
