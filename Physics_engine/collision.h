#ifndef COLLISION_H
#define COLLISION_H

#include "object.h"

#include <QDebug>
#include <cmath>
#include <algorithm>
#include <QPointF>

//![0] simplified functions
// Functions used only in this file use uppercase letters to distinguish them from variable names.

// Distance: simple distance function to calculate position-to-position
double Distance(const QPointF &a, const QPointF &b = {0 , 0})
{
    return std::sqrt(std::pow((a.x()-b.x()),2) + std::pow((a.y()-b.y()),2));
}

// Clamp: trunctate value between min and max
double Clamp(double min, double max, double value)
{
    if (value<min) value=min;
    if (value>max) value=max;
    return value;
}


//![1] collision functions
// Collision functions have names of the form 'objectVsObject',
//     return booleans, and set normal and penetration to the manifold.

// circleVsCircle:
// The manifold is passed to this function which determines the collision between the circles.
// In case of collision, calculate and set normal and penetration.
bool circleVsCircle( Manifold *m )
{
    // setup a couple pointers to each object
    Object *A = m->A;
    Object *B = m->B;

    // save the variables
    double radiusA=A->getRadius();
    double radiusB=B->getRadius();

    // vector from A to B and its distance
    QPointF positionRelative = B->position - A->position;
    double distance = Distance(positionRelative);

    // calculate sum of two radius
    double radiusTotal = radiusA+radiusB;

    // if two object is farther away, then there are no collision
    if(distance > radiusTotal)
        return false;

    // if two circles have collided, now compute manifold

    // If distance between circles is not zero
    if(distance != 0){
        // penetration is difference between radius and distance
        m->penetration = radiusTotal - distance;

        // normal is unit vector of relative position
        m->normal = positionRelative / distance;
        return true;
    }
    // if circles are on same position
    else {
    // choose random (but consistent) values
        m->penetration = radiusA;
        m->normal = QPointF(1,0);
        return true;
    }
}

// rectangleVsRectangle:
// The manifold is passed to this function which determines the collision between the circles.
// In case of collision, calculate and set normal and penetration.
// I don't consider rotation yet, normal would be have x-axis, y-axis direction
bool rectangleVsRectangle( Manifold *m )
{
    // setup a couple pointers to each object
    Object *A = m->A;
    Object *B = m->B;

    // vector from A to B
    QPointF positionRelative = B->position - A->position;

    // relative velocity from A to B
    QPointF velocityRelative = B->velocity - A->velocity;

    // get widths from rectangles
    double widthA=A->getWidth();
    double widthB=B->getWidth();

    // calculate overlap on x axis
    double overlapX = 0.5*(widthA+widthB) - abs(positionRelative.x());

    // overlapX and overlapY might be positive when it colide

    // so for the case of overlapX is positive then calculate overlapY
    if(overlapX > 0){
        // get heights form rectangles
        double heightA=A->getHeight();
        double heightB=B->getHeight();

        // calculate overlap on y axis
        double overlapY = 0.5*(heightA+heightB) - abs(positionRelative.y());

        // for the case of collision
        if(overlapY > 0) {
            // find out which axis is axis of least penetration
            // if overlapY is larger then normal would be x-axis
            if(overlapX < overlapY) {
                // direction of normal is opposite to relative velocity
                if(velocityRelative.x() > 0) { m->normal = QPointF( -1, 0 ); }
                else { m->normal = QPointF( 1, 0 ); }

                // and penetration is same as overlapX
                m->penetration = overlapX;
                return true;
            }
            // if overlapX is larger then normal would be y-axis
            // and follow same mechanism
            else {
                if(velocityRelative.y() > 0) {m->normal = QPointF( 0, -1 );}
                else { m->normal = QPointF( 0, 1 );}
                m->penetration = overlapY;
                return true;
            }
        }
    }
    // if both overlap of X and Y is not positive, then collision won't occur
    return false;
}

// rectangleVsCircle:
// Collision on the sides and on the edges are different when it colide.
// To solve this problem at once, I used the idea of 'closest'.
// 'closest' is the point on the side of the rectangle that is closest to the circle's center.
// For collision on the sides, normal would be perpendicular to the rectangle
// For collision on the edges, normal would have proper angle
bool rectangleVsCircle(Manifold *m)
{
    // setup a couple pointers to each object
    Object *A = m->A;
    Object *B = m->B;

    // vector from A to B
    QPointF positionRelative = B->position - A->position;

    // signX/signY is the sign of direction of positionRelative
    // I optimized the code by taking all the collisions in one quadrant,
    //   calculating them, and multiplying them by the sign at the end.
    const int signX = (positionRelative.x() > 0) ? 1:-1;
    const int signY = (positionRelative.y() > 0) ? 1:-1;

    // 'closest'
    // assign closest as positionRelative at first.
    QPointF closest = positionRelative;

    // get varibles of rectangle
    const double widthA=A->getWidth();
    const double heightA=A->getHeight();

    // clamp closest to inside of the rectangle
    // If the center of the circle is outside the rectangle,
    //    the closest is clamped over the side of the rectangle.
    // If the center of the circle is in the rectangle, it does not change.
    closest.rx() = Clamp(-0.5*widthA, 0.5*widthA, closest.x());
    closest.ry() = Clamp(-0.5*heightA, 0.5*heightA, closest.y());

    // boolian variable inside
    bool inside = false;

    // inside is true when center of circle is in rectangle
    if (positionRelative==closest){
        inside = true;

        // find the closest axis and Move closest over the side of the rectangle.
        // generalize the code by using signX/signY.
        if (abs(positionRelative.x()) > abs(positionRelative.y())) {
            closest.rx() = signX*0.5*widthA;
        }
        else {
            closest.ry() = signY*0.5*heightA;
        }
    }

    // calculate normal(with an indeterminate sign)
    QPointF normal = positionRelative - closest;
    double distance = Distance(normal);
    normal /=distance;

    // get radius from circle
    const double radius=B->getRadius();

    // early out of the radius is shorter than distance to closest point and
    //     Circle not inside the Rectangle
    if ((distance > radius) && (!inside)) return false;

    // collision normal needs to be flipped to point outside
    //     if circle is inside the AABB
    // penetration also should be weighted
    if (inside) {
        m->normal = -normal;
        m->penetration = radius + distance;
    }
    else {
        m->normal = normal;
        m->penetration = radius - distance;
    }
    return true;
}
//![1]


//![2] functions for after collision occur
// positionCorrection:
// This function corrects the position of two overlapping objects to their mass.
void positionCorrection(Manifold *m){
    // these values can be modified to make engnie more stable
    const double percent = 1.01; // I made 101% correction to avoid overlap
    const double  slop = 0.01; // If overlap is too slight(smaller than slop), you can ignore overlap

    // setup two objects
    Object *A=m->A;
    Object *B=m->B;

    // check if both of two objects don't have infinite mass(to avoid divided by 0)
    if (A->massInv + B->massInv != 0 ){
        // correction is basically (penetration*normal)
        QPointF correction = std::max(m->penetration - slop, 0.0 )*percent*m->normal
                             / (A->massInv + B->massInv) ;
        // and divide by the total massInv and multiply each massInv.
        A->position -= A->massInv * correction;
        B->position += B->massInv * correction;
    }
}

// resolveCollision:
// Here we calculate the impulse scalar j and calculate the velocity
//     after the collision, taking into account each mass in the normal direction.
void resolveCollision(Manifold *m){
    // setup two objects
    Object *A=m->A;
    Object *B=m->B;

    // calculate relative velocity
    QPointF velocityRelative = B->velocity - A->velocity;

    // calculate relative velocity in terms of the normal direction
    double velocityDotNormal = QPointF::dotProduct( velocityRelative, m->normal );

    // do not resolve if velocities are separating
    if(velocityDotNormal > 0) return;

    // calculate restitution
    // If restitution is larger than 0.98, then truncate the value.
    // 0.98 was obtained experimentally that makes collision stable.
    double e = std::min(std::min( A->restitution, B->restitution),0.98);

    // calculate impulse scalar 'j'
    // check if both of two objects don't have infinite mass(to avoid divided by 0)
    if (A->massInv + B->massInv != 0 ){
        // calculate j
        double j = -(1 + e) * velocityDotNormal / (A->massInv + B->massInv);

        // choose declineFactor(obtained experimentally)
        // declineFactor is constant that acts as the hyperbolic focus.
        // by adding declineFactor,
        //     when the impact force is near zero, j is greatly reduced.
        double declineFactor = 8; // 5 to 10 can be used
        declineFactor /= (A->massInv + B->massInv);

        // decline is applied only when the object collides with the fixed object
        if (A->massInv==0 | B->massInv ==0){
            // the decrement must not be greater than the original value.
            if (j > declineFactor){
                declineFactor *= declineFactor; //The process of fitting the order

                // apply the decline
                j = std::sqrt(j*j - declineFactor);
            }
            // if the constant decrement is greater than j,
            //     then use percent attenuation.
            else {
                j=0.5*j;
            }
        }

        // apply impulse
        QPointF impulse = j * m->normal;

        // change the velocity with the ratio of massInv
        A->velocity -= A->massInv * impulse;
        B->velocity += B->massInv * impulse;
    }
}
//![2]

#endif // COLLISION_H
