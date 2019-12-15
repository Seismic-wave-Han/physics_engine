#ifndef WORLD_H
#define WORLD_H

#include <parameter.h>

#include <QOpenGLWidget>
#include <vector>

class Engine;
class Object;
class Circle;
class Rectangle;
struct Parameter;

class World : public QOpenGLWidget
{
//    Q_OBJECT // I don't know why it doesn't work

public:
    World(Engine *engine, QWidget *parent);

public:
    // to update the world
    void animate();
    // to create object
    void createObject();
    // to set parameters gotten from UI
    void setStaticParameters(Parameter paramBox);
    // to paint all background objects in background container
    void paintBackgrounds(QPainter *painter);
    // to check rectangle vs circle crossed collision
    void checkRectangleVsCircle();
    // to update circles
    void updateCircles(QPainter *painter);
    void paintCircle(QPainter *painter, Object *circleA);
    // to update rectangles
    void updateRectangles(QPainter *painter);
    void paintRectangle(QPainter *painter, Object *rectangleA);

protected:
    // mouse event related to movement
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override; // this function create an object
    // to manage and draw all the thing related objects
    void paintEvent(QPaintEvent *event) override;

public:
    /// member variables
    Engine *engine;
    int screenSize = 500;

    // parameters related to movement(dynamic)
    QPointF pressPos={0,0};
    QPointF releasePos={0,0};

    // parameters
    Parameter paramBox; // shape, mass, size, position, velocity, restitution
    bool isFixed=false; // connected with is fixed check box in UI

    // containers for holding objects
    std::vector<Circle> circles;
    std::vector<Rectangle> rectangles;
    std::map<QString, Rectangle> background; // (ground, right wall, left wall, roof)
};

#endif // WORLD_H
