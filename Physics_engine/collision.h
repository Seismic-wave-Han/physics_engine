#ifndef COLLISION_H
#define COLLISION_H

#include "object.h"

// simple distance function: position to position
double Distance(const QPointF &a, const QPointF &b = {0 , 0}){
    return std::sqrt(std::pow((a.x-b.x),2) + std::pow((a.y-b.y),2));
}

// collision detectrion function: rectangle vs rectangle
bool Rec_vs_rec(const Rectangle &rec1, const Rectangle &rec2){
    // if objects impulsed, it return true. otherwise return false
    if(rec1.Right_top().x < rec2.Left_bottom().x or rec1.Left_bottom().x > rec2.Right_top().x) return false;
    if(rec1.Right_top().y < rec2.Left_bottom().y or rec1.Left_bottom().y > rec2.Right_top().y) return false;
    return true;
}

bool Cir_vs_cir(const Circle &cir1, const Circle &cir2){
    if (Distance(cir1.position, cir2.position) > cir1.radius + cir2.radius) return false;
    return true;
}

bool Rec_vs_cir(const Rectangle &rec, const Circle &cir){
    QPointF diff(std::abs(cir.position.x - rec.position.x),
            std::abs(cir.position.y - rec.position.y));

    QPointF margin;
    margin.x = diff.x - 0.5 * rec.width;
    margin.y = diff.y - 0.5 * rec.height;

    if (margin.x > cir.radius or margin.y > cir.radius) return false;
    if (margin.x > 0 and margin.y > 0 and Distance(margin) > cir.radius) return false;

    return true;
}

#endif // COLLISION_H