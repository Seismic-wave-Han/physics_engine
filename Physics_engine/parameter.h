#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>
#include <QPoint>

// Parameter: simple struct to hold object parameters
// added to simplify the code
struct Parameter
{
    // parameters of object(set default values for program safety)
    QString shape="Circle";
    double mass=10;
    QPointF size={10,10};
    QPointF position = {0, 0};
    QPointF velocity = {0, 0};
    double restitution = 1.0;
};

#endif // PARAMETER_H
