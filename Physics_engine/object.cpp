#include "object.h"
#include "collision.h"
#include "engine.h"
#include "parameter.h"

#include <QDebug>
#include <cmath>
#include <algorithm>

//![0] Constructor
// custom constructor
Object::Object(Engine *engine, Parameter paramBox, bool isFixed):
    engine(engine),
    mass(paramBox.mass),
    position(paramBox.position),
    velocity(paramBox.velocity),
    restitution(paramBox.restitution),
    isFixed(isFixed)
{
    if (isFixed){
        this->mass=0;
        this->velocity={0,0};
    }
    setMassInversion();
    qDebug() << "Object is created.";
}

//Object::Object(Engine *engine, QPointF position, bool isFixed, double mass, QPointF velocity, double restitution, bool isMovingY):
//    engine(engine), mass(mass), position(position), velocity(velocity), restitution(restitution), isMovingY(isMovingY), isFixed(isFixed)
//{}

void Object::positionUpdate(){
    if (isFixed==false){
        double g=engine->getGravity();
        double dt=engine->getTimeInterval();
        position.rx()+=velocity.rx()*dt;
//        if(isMovingY){
            position.ry()+=velocity.ry()*dt;
            velocity.ry()+=g*dt;
//        }
    }
}

void Object::setMassInversion(){
    if(mass==0) massInv=0;
    else massInv=1/mass;
}

Rectangle::Rectangle(Engine *engine, Parameter paramBox, bool isFixed):
   Object(engine, paramBox, isFixed),
   width(paramBox.size.x()),
   height(paramBox.size.y())
{}


Circle::Circle(Engine *engine, Parameter paramBox, bool isFixed):
    Object(engine, paramBox, isFixed),
    radius(paramBox.size.x())
{}

Manifold::Manifold(Object *A, Object *B, double penetration, QPointF normal):
    A(A), B(B), penetration(penetration), normal(normal)
{}

void Manifold::updateCircleVsCircle(){
    bool collision = circleVsCircle(this);
    if (collision) {
        positionCorrection(this);
        resolveCollision(this);
    }
}

void Manifold::updateRectangleVsRectangle(){
    bool collision = rectangleVsRectangle(this);
    if (collision) {
        positionCorrection(this);
        resolveCollision(this);
    }
}

void Manifold::updateRectangleVsCircle(){
    bool collision = rectangleVsCircle(this);
    if (collision) {
        positionCorrection(this);
        resolveCollision(this);
    }
}
