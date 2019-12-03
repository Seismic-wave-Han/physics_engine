#include "object.h"
#include "collision.h"
#include "engine.h"

#include <QDebug>
#include <cmath>
#include <algorithm>


Object::Object(Engine *engine, QString shape, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution){
    if (shape == "Rectangle"){
        Rectangle(engine, mass, sizeX, sizeY, velocityX, velocityY, restitution, true);
    }
    else {
        Circle(engine, mass, sizeX, sizeY, velocityX, velocityY, restitution, true);
    }
}

Object::Object(Engine *engine, double mass, double velocityX, double velocityY, double restitution, bool isMovingY):
    engine(engine), mass(mass), velocity(QPointF(velocityX,velocityY)), restitution(restitution), isMovingY(isMovingY)
{
    setMassInversion();
    qDebug() << "Object is created.";
}

void Object::positionUpdate(){
    double g=engine->getGravity();
    double delta=engine->getDelta();
    position.rx()+=velocity.rx()*delta;
    if(isMovingY){
        position.ry()+=velocity.ry()*delta;
        velocity.ry()+=g*delta;
    }
//    qDebug() << position.rx()<< ", "<< position.ry();
}

Rectangle::Rectangle(Engine *engine, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution, bool isMovingY):
   Object(engine, mass,velocityX, velocityY, restitution, isMovingY), width(sizeX), height(sizeY)//, isMovingY(isMoving)
{}

void Rectangle::bounce(){
    bool collision =rectangleVsGround(*this);
    if (collision) {
        qDebug() << "rec bounce!";
        velocity.setY(-restitution*std::sqrt(std::abs(velocity.ry()*velocity.ry()-5))*0.98);
    }
}

Circle::Circle(Engine *engine, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution, bool isMovingY):
    Object(engine, mass,velocityX, velocityY, restitution, isMovingY), radius(sizeX)//, isMovingY(isMoving)
{}

void Circle::bounce(){
    bool collision =circleVsGround(*this);
    if (collision) {
        qDebug() << "cir bounce!";
        velocity.setY(-restitution*std::sqrt(std::abs(velocity.ry()*velocity.ry()-5))*0.98); // 0.98 for stability
    }
}

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
