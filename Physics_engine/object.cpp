#include "object.h"
#include "collision.h"

#include <QDebug>


Object::Object(QString shape, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution){
    if (shape == "Rectangle"){
        Rectangle(mass, sizeX, sizeY, velocityX, velocityY, restitution);
    }
    else {
        Circle(mass, sizeX, sizeY, velocityX, velocityY, restitution);
    }
}

Object::Object(double mass, double velocityX, double velocityY, double restitution):
    mass(mass), velocity(QPointF(velocityX,velocityY)), restitution(restitution)
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
    double g=Get_gravity();
    position.rx()+=velocity.rx()*delta;
    position.ry()+=velocity.ry()*delta;
    velocity.ry()+=g*delta;
    qDebug() << position.rx()<< ", "<< position.ry();
}

Rectangle::Rectangle(double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution):
   Object(mass,velocityX, velocityY, restitution), width(sizeX), height(sizeY)
{

}

void Rectangle::bounce(){
    if (rectangleVsGround(*this)) velocity.ry()=-restitution*velocity.ry();
}

Circle::Circle(double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution):
    Object(mass,velocityX, velocityY, restitution), radius(sizeX)
{

}

void Circle::bounce(){
    if (circleVsGround(*this)) {
        qDebug() << "moving!";
        velocity.setY(-restitution*velocity.ry()*0.98); // 0.98 for stability
    }
}
