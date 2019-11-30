#ifndef OBJECT_H
#define OBJECT_H

#include "engine.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

class Object : public Engine
{
public:
    Object();
    Object(XY xy): position(xy){}
    
    void Velocity(double &t){
        double g = Get_gravity();
//        velocity.y=ve-g*t
    }

public:
    XY position = {0, 0};
    XY velocity = {0, 0};
    double mass = 10;
    double restitution = 1.0;

};

class Rectangle : public Object{
public:
    Rectangle(){}
    Rectangle(double width, double height): width(width), height(height){}
    Rectangle(XY position): Object(position) {}

    XY Left_bottom() const { return XY(position.x-0.5*width, position.y-0.5*height); }
    XY Right_top() const { return XY(position.x+0.5*width, position.y+0.5*height); }


public:
    double width=10, height=10;
};

class Circle : public Object{
public:
    double radius=5;
};

//class Background : public Rectangle{
//public:
//    const position
//};



#endif // OBJECT_H
