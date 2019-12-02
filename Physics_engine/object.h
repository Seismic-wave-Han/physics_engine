#ifndef OBJECT_H
#define OBJECT_H

#include "engine.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <QPointF>

class Object
{
public:
    Object(Engine *engine, QString shape, double mass, double sizeX, double sizeY, double velocityX=0, double velocityY=0, double restitution=0.95);
    Object(Engine *engine, double mass, double velocityX=0, double velocityY=0, double restitution=0.95, bool isMovingY=true);

    void update();

    void positionUpdate();
    void bounce();
    void stopY(){isMovingY=false;};

public:
    Engine *engine;

    QPointF position = {0, 0};
    QPointF velocity = {0, 0};
    double mass = 10;
    double restitution = 0.95;
    bool isMovingY=true;
};

class Rectangle : public Object{
public:
    Rectangle(Engine *engine, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution, bool isMovingY);

    QPointF Left_top() const { return QPointF(position.x()-0.5*width, position.y()-0.5*height); }
    QPointF Right_bottom() const { return QPointF(position.x()+0.5*width, position.y()+0.5*height); }

    void bounce();


public:
    double width=10, height=10;
//    bool isMovingY=true;


};

class Circle : public Object{
public:
    Circle(Engine *engine, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution, bool isMovingY);

    void bounce();
//    void stopY(){isMovingY=false;};


    double radius=5;
//    bool isMovingY=true;

};

//class Background : public Rectangle{
//public:
//    const position
//};



#endif // OBJECT_H
