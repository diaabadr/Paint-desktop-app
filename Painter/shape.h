#ifndef SHAPE_H
#define SHAPE_H
#include <QPen>
#include <QString>
#include "Constants.h"
#include <QtMath>
class Shape:public QPen
{
    private:
    QString name;
    QPoint startPoint;
    QPoint endPoint;
    int thickness;
    QColor Color;
public:
    Shape(QString Name,QPoint str,QPoint end,int thick,QColor color);

    QString getName();

    void setStrPnt(QPoint str);

        void setEndPnt(QPoint end);

        QPoint getStrPnt()const;

        QPoint getEndPnt()const;

        int getThickness()const;

        virtual double perimeter()const = 0;

        void setColor(QColor col);

        virtual ToolType getType() const = 0;

    ~Shape();
};

#endif // SHAPE_H
