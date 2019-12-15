#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <QPointF>

struct Manifold;
class Engine;
class Parameter;

// Object: parent for Rectangle and Circle
// it holds general properties of object and Engine
class Object
{
public:
    // Constructor: to create Object. it is called from Rectangle or Circle
    Object(Engine *engine, Parameter paramBox, bool isFixed=false);

    // Distructor(it needs virtual mark!)
    virtual ~Object(){}

    // calculate the position and velocity after dt and update the values.
    void positionUpdate();
    // calculate the massInv
    void setMassInversion();

    // virtual funcions(overridden in a child class.)
    virtual QPointF Left_top()const{return QPointF(0,0);}
    virtual QPointF Right_bottom()const{return QPoint(0,0);}
    virtual double getRadius(){return 0;}
    virtual double getWidth(){return 0;}
    virtual double getHeight(){return 0;}

public:
    // member variables(Engine and parameters)
    Engine *engine;

    double mass = 10;
    QPointF position = {0, 0};
    QPointF velocity = {0, 0};
    double massInv;
    double restitution = 0.95;

    bool isFixed = false;

};


// Rectangle: children of Object class
// hold width and height, calculate position related function
class Rectangle : public Object
{
public:
    // Constructor: set width and height, call constructor of Object
    Rectangle(Engine *engine, Parameter paramBox, bool isFixed=false);

    // to calculated left-top, right-bottom position, used to check for conflicts.
    QPointF Left_top() const override{ return QPointF(position.x()-0.5*width,
                                                      position.y()-0.5*height); }
    QPointF Right_bottom() const override { return QPointF(position.x()+0.5*width,
                                                           position.y()+0.5*height); }
    // to access member variables of a rectangle from an object.
    double getWidth() override {return width;}
    double getHeight() override {return height;}

public:
    // member variable
    double width=10;
    double height=10;

};


// Circle: children of Object class and it holds radius
class Circle : public Object
{
public:
    // Constructor: set radius, and call constructor of Object
    Circle(Engine *engine, Parameter paramBox, bool isFixed=false);

    // to access member variable of a circle from an object.
    double getRadius() override {return radius;}

public:
    // member variable
    double radius=10;

};


// Manifold: hold two Objects and their penetration and normal of collision
// this class also hold functions dealing with the collision process
struct Manifold
{
    // Constructor
    Manifold(Object *A, Object *B, double penetration=0, QPointF normal={0, 0});

    // functions dealing with 3 different collision process
    void updateCircleVsCircle();
    void updateRectangleVsRectangle();
    void updateRectangleVsCircle();

    // member variables
    Object *A;
    Object *B;
    double penetration=0;
    QPointF normal={0,0};

};



#endif // OBJECT_H
