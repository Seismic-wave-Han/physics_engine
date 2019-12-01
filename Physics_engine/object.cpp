#include "object.h"
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

Rectangle::Rectangle(double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution):
   Object(mass,velocityX, velocityY, restitution), width(sizeX), height(sizeY)
{

}

Circle::Circle(double mass, double sizeX, double sizeY, double velocityX, double velocityY, double restitution):
    Object(mass,velocityX, velocityY, restitution), radius(sizeX)
{

}
