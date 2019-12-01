#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

class Engine{
public:
    Engine();

    void Set_gravity(double value){
        g=value;
    }
    double Get_gravity() {return g;}
    void Set_friction(double value){
        mu=value;
    }
    double Get_friction() {return mu;}
    
private:
    double g = 9.8;
    double mu = 0;

};
#endif // ENGINE_H
