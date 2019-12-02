#ifndef OBJECT_H
#define OBJECT_H

#include "engine.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <QPointF>

class Object : public Engine
{
public:
    Object(QString shape, double mass, double sizeX, double sizeY, double velocityX=0, double velocityY=0, double restitution=1);
    Object(double mass, double velocityX=0, double velocityY=0, double restitution=1);

    void update();

    void positionUpdate();
    void bounce();

public:
//    int *dt;
    double delta=0.1;
    QPointF position = {0, 0};
    QPointF velocity = {0, 0};
    double mass = 10;
    double restitution = 1.0;
//    bool isMoving=true;


};

class Rectangle : public Object{
public:
    Rectangle(double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution);

    QPointF Left_top() const { return QPointF(position.x()-0.5*width, position.y()-0.5*height); }
    QPointF Right_bottom() const { return QPointF(position.x()+0.5*width, position.y()+0.5*height); }

    void bounce();

public:
    double width=10, height=10;

};

class Circle : public Object{
public:
    Circle(double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution);

    void bounce();

    double radius=5;
};

//class Background : public Rectangle{
//public:
//    const position
//};



#endif // OBJECT_H
