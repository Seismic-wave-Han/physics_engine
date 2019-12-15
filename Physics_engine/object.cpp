#include "object.h"
#include "collision.h"
#include "engine.h"
#include "parameter.h"

#include <QDebug>
#include <cmath>
#include <algorithm>

//![0] class Object
// constructor
// It is called by Rectangle and Circle
// Also it is responsible for the initial setting
Object::Object(Engine *engine, Parameter paramBox, bool isFixed):
    engine(engine),
    mass(paramBox.mass),
    position(paramBox.position),
    velocity(paramBox.velocity),
    restitution(paramBox.restitution),
    isFixed(isFixed)
{
    // if isFixed is true, zero will be assigned to mass, velocity
    if (isFixed){
        // actually mass is infinity, but 0 means infinite here
        this->mass=0;
        this->velocity={0,0};
    }
    // so if mass is 0, massInv will be assigned as 0 through this function
    setMassInversion();
}

// positionUpdate: for not fixed object, it updates motion under gravity
void Object::positionUpdate(){
    if (isFixed==false){
        // get gravity and time interval
        double g=engine->getGravity();
        double dt=engine->getTimeInterval();
        // update x-direction motion: constant velocity motion
        position.rx()+=velocity.rx()*dt;
        // update y-direction motion: uniformly accelerated motion
        position.ry()+=velocity.ry()*dt;
        velocity.ry()+=g*dt;
    }
}

// setMassInversion: calculate inversion of mass
//     because we usually use inversion of mass in practical
void Object::setMassInversion(){
    // case of infinity mass(fixed object)
    if(mass==0) massInv=0;

    // else in general
    else massInv=1/mass;
}
//![0]


//![1] Rectangle
// constructor: assign width and height, call Object constructor
Rectangle::Rectangle(Engine *engine, Parameter paramBox, bool isFixed):
   Object(engine, paramBox, isFixed),
   width(paramBox.size.x()),
   height(paramBox.size.y())
{}
//![1]


//![2] Circle
// constructor: assign radius, and call Object constructor
Circle::Circle(Engine *engine, Parameter paramBox, bool isFixed):
    Object(engine, paramBox, isFixed),
    radius(paramBox.size.x())
{}
//![2]


//![3] Manifold
// constructor
// usually created with two objects and default values of penetration and normal
// penetration and normal will be updated by update related functions
Manifold::Manifold(Object *A, Object *B, double penetration, QPointF normal):
    A(A), B(B), penetration(penetration), normal(normal)
{}

// 3 functions to update penetration and normal
// First check two objects are collided
// If collision is occured, proceed position correction and resolve collision
// penetration and normal would be updated at resolveCollision function

// updateCircleVsCircle: if A and B are Circle, use this function
void Manifold::updateCircleVsCircle(){
    bool collision = circleVsCircle(this);
    if (collision) {
        positionCorrection(this);
        resolveCollision(this);
    }
}

// updateRectangleVsRectangle: if A and B are Rectangle, use this function
void Manifold::updateRectangleVsRectangle(){
    bool collision = rectangleVsRectangle(this);
    if (collision) {
        positionCorrection(this);
        resolveCollision(this);
    }
}

// updateRectangleVsCircle: if A is Rectangle and B is Circle, use this function
void Manifold::updateRectangleVsCircle(){
    bool collision = rectangleVsCircle(this);
    if (collision) {
        positionCorrection(this);
        resolveCollision(this);
    }
}
