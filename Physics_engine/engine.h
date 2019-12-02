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
    Engine(){}
    Engine(Engine &engine):g(engine.g), mu(engine.mu){}

    void setGravity(double value){
        g=value;
    }
    double getGravity() {return g;}
    void setFriction(double value){
        mu=value;
    }
    double getFriction() {return mu;}
    void setDelta(double value){
        delta=value;
    }
    double getDelta() {return delta;}
    
private:
    double delta=0.1;
    double g = 9.8;
    double mu = 0;
    std::vector<std::vector<bool>> ObjectvsObject;
    std::vector<bool> ObjectvsGround;

};
#endif // ENGINE_H
