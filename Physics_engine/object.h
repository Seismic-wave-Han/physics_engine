#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <QPointF>

struct Manifold;
class Engine;

class Object
{
public:
    Object(Engine *engine, double mass, QPointF position, QPointF velocity, double restitution=0.95, bool isMovingY=true);
    //, bool isFixed=false);
    Object(Engine *engine, QPointF position, bool isFixed=true, double mass=0, QPointF velocity={0,0}, double restitution=0.95, bool isMovingY=false);

    virtual ~Object(){}

//    void update();

    void positionUpdate();
    virtual void bounce()=0;


    void setMassInversion(){
        if(mass==0) massInv=0;
        else massInv=1/mass;
    }

    void stopY(){isMovingY=false;}

    virtual QPointF Left_top()const{return QPointF(0,0);}
    virtual QPointF Right_bottom()const{return QPoint(0,0);}
    virtual double getRadius(){return 0;}
    virtual double getWidth(){return 0;}
    virtual double getHeight(){return 0;}


public:
    Engine *engine;
    double mass = 10;
    QPointF position = {0, 0};
    QPointF velocity = {0, 0};
    double massInv;
    double restitution = 0.95;
    bool isMovingY = true;
    bool isFixed = false;
};

class Rectangle : public Object{
public:
    Rectangle(Engine *engine, double mass, QPointF size, QPointF position, QPointF velocity, double restitution, bool isMovingY);
    Rectangle(Engine *engine, bool isFixed, QPointF size, QPointF position);

    QPointF Left_top() const override { return QPointF(position.x()-0.5*width, position.y()-0.5*height); }
    QPointF Right_bottom() const override { return QPointF(position.x()+0.5*width, position.y()+0.5*height); }
    double getWidth() override {return width;}
    double getHeight() override {return height;}

    void bounce() override;

public:
    double width=10, height=10;
//    bool isMovingY=true;


};

class Circle : public Object{
public:
    Circle(Engine *engine, double mass, double radius, QPointF position, QPointF velocity, double restitution, bool isMovingY);
    Circle(Engine *engine, bool isFixed, double radius, QPointF position);

    void bounce() override;
//    void stopY(){isMovingY=false;};
    double getRadius() override {return radius;}

    double radius=5;
//    bool isMovingY=true;

};

struct Manifold{
    Manifold(Object *A, Object *B, double penetration=0, QPointF normal=QPointF(0, 0)):
        A(A), B(B), penetration(penetration), normal(normal)
    {}

    void updateCircleVsCircle();
    void updateRectangleVsRectangle();
    void updateRectangleVsCircle();


    Object *A;
    Object *B;
    double penetration=0;
    QPointF normal={0,0};
};



#endif // OBJECT_H
