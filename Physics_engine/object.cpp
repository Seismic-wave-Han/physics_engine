#include "object.h"
#include <QDebug>


Object::Object(QString shape, double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution, int *elapsed){
    if (shape == "Rectangle"){
        Rectangle(mass, sizeX, sizeY, velocityX, velocityY, restitution, elapsed);
    }
    else {
        Circle(mass, sizeX, sizeY, velocityX, velocityY, restitution, elapsed);
    }
}

Object::Object(double mass, double velocityX, double velocityY, double restitution, int *elapsed):
    mass(mass), velocity(QPointF(velocityX,velocityY)), restitution(restitution), dt(elapsed)
{
    qDebug() << "Object is created.";
}

void Object::update(){
    positionUpdate();
}

void Object::positionUpdate(){
    double g=Get_gravity();
    position.rx()+=velocity.rx()*delta;
    position.ry()+=velocity.ry()*delta;
    velocity.ry()+=g*delta;
    qDebug() << position.rx()<< ", "<< position.ry();
}

Rectangle::Rectangle(double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution,  int *elapsed):
   Object(mass,velocityX, velocityY, restitution, elapsed), width(sizeX), height(sizeY)
{

}

Circle::Circle(double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution, int *elapsed):
    Object(mass,velocityX, velocityY, restitution, elapsed), radius(sizeX)
{

}
