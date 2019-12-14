#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>
#include <QPoint>

class Parameter
{
public:
    Parameter();

public:
    QString shape="Circle";
    double mass=10;
    QPointF size={10,10};
    QPointF position = {0, 0};
    QPointF velocity = {0, 0};
    double restitution = 1.0;
    bool isMovingY = true;
};

#endif // PARAMETER_H
