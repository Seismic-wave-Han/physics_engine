#ifndef OBJECT_H
#define OBJECT_H

#include "engine.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <QPointF>

struct Manifold;
class Object;

class Object
{
public:
    Object(Engine *engine, QString shape, double mass, double sizeX, double sizeY, double velocityX=0, double velocityY=0, double restitution=0.95);
    Object(Engine *engine, double mass, double velocityX=0, double velocityY=0, double restitution=0.95, bool isMovingY=true);

    virtual ~Object()=0;

    void update();

    void positionUpdate();
//    virtual void bounce();
//    virtual void bounce()=0;

//    void setMassInversion(){
//        if(mass==0) massInv=0;
//        else massInv=1/mass;
//    }

    void stopY(){isMovingY=false;}

    virtual QPointF Left_top()const{return QPointF(0,0);}
    virtual QPointF Right_bottom()const{return QPoint(0,0);}
    virtual double getRadius(){return 0;}
    virtual double getWidth(){return 0;}
    virtual double getHeight(){return 0;}


public:
    Engine *engine;

    QPointF position = {0, 0};
    QPointF velocity = {0, 0};
    double mass = 10;
//    double massInv = 0.1;
    double restitution = 0.95;
    bool isMovingY=true;
};

class Rectangle : public Object{
public:
    Rectangle(Engine *engine, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution, bool isMovingY);

    QPointF Left_top() const override { return QPointF(position.x()-0.5*width, position.y()-0.5*height); }
    QPointF Right_bottom() const override { return QPointF(position.x()+0.5*width, position.y()+0.5*height); }
    double getWidth() override {return width;}
    double getHeight() override {return height;}

    void bounce() ;

public:
    double width=10, height=10;
//    bool isMovingY=true;


};

class Circle : public Object{
public:
    Circle(Engine *engine, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution, bool isMovingY);

    void bounce() ;
//    void stopY(){isMovingY=false;};
    double getRadius() override {return radius;}

    double radius=5;
//    bool isMovingY=true;

};

struct Manifold{
    Manifold(Object *A, Object *B, double penetration=0, QPointF normal=QPointF(0, 0)):
        A(A), B(B), penetration(penetration), normal(normal)
    {}

    Object *A;
    Object *B;
    double penetration=0;
    QPointF normal={0,0};
};

//struct ManifoldCC{
//    ManifoldCC(Circle *A, Circle *B, double penetration, QPointF normal):
//        A(A), B(B), penetration(penetration), normal(normal)
//    {}

//    Circle *A;
//    Circle *B;
//    double penetration;
//    QPointF normal;
//};

//struct ManifoldRR{
//    ManifoldRR(Rectangle *A, Rectangle *B, double penetration, QPointF normal):
//        A(A), B(B), penetration(penetration), normal(normal)
//    {}

//    Rectangle *A;
//    Rectangle *B;
//    double penetration;
//    QPointF normal;
//};

//struct ManifoldRC{
//    ManifoldRC(Rectangle *A, Circle *B, double penetration, QPointF normal):
//        A(A), B(B), penetration(penetration), normal(normal)
//    {}

//    Rectangle *A;
//    Circle *B;
//    double penetration;
//    QPointF normal;
//};

#endif // OBJECT_H
