#include "object.h"
#include "collision.h"
#include "engine.h"

#include <QDebug>


//Object::Object(QString shape, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution){
//    if (shape == "Rectangle"){
//        Rectangle(engine, mass, sizeX, sizeY, velocityX, velocityY, restitution);
//    }
//    else {
//        Circle(engine, mass, sizeX, sizeY, velocityX, velocityY, restitution);
//    }
//}

Object::Object(Engine *engine, double mass, double velocityX, double velocityY, double restitution):
    engine(engine), mass(mass), velocity(QPointF(velocityX,velocityY)), restitution(restitution)
{
    qDebug() << "Object is created.";
}

void Object::update(){
//    if(isMoving==true){
    positionUpdate();
//    }
//    bounce();
}

void Object::positionUpdate(){
    double g=engine->getGravity();
    double delta=engine->getDelta();
    position.rx()+=velocity.rx()*delta;
    position.ry()+=velocity.ry()*delta;
    velocity.ry()+=g*delta;
//    qDebug() << position.rx()<< ", "<< position.ry();
}

Rectangle::Rectangle(Engine *engine, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution):
   Object(engine, mass,velocityX, velocityY, restitution), width(sizeX), height(sizeY)
{

}

void Rectangle::bounce(){
    if (rectangleVsGround(*this)) velocity.ry()=-restitution*velocity.ry();
}

Circle::Circle(Engine *engine, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution):
    Object(engine, mass,velocityX, velocityY, restitution), radius(sizeX)
{

}

void Circle::bounce(){
    if (circleVsGround(*this)) {
        qDebug() << "moving!";
        velocity.setY(-restitution*velocity.ry()*0.98); // 0.98 for stability
    }
}
