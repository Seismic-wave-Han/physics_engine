#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

// Engine: very simple class to hold and apply the global variables
class Engine{
public:
    Engine(){}
    Engine(Engine &engine):g(engine.g), mu(engine.mu){}

    void setGravity(double value){ g=value; }
    double getGravity() { return g; }

    void setFriction(double value){ mu=value; }
    double getFriction() {return mu;}

    void setTimeInterval(double value){ dt=value; }
    double getTimeInterval() {return dt;}
    
private:
    double dt=0.1;
    double g = 9.8;
//    double g=0; // for setting non gravity motion as default
    double mu = 0;




};
#endif // ENGINE_H
