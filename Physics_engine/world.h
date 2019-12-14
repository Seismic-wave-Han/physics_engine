#ifndef WORLD_H
#define WORLD_H

#include <QOpenGLWidget>
#include <vector>

class Engine;
class Object;
class Circle;
class Rectangle;
class Parameter;

class World : public QOpenGLWidget
{
//    Q_OBJECT

public:
    World(Engine *engine, QWidget *parent);

public:
    // to update the world
    void animate();
    // to create object
    void createObject();
    // to set parameters gotten from UI
    void setStaticParameters(Parameter paramBox);

protected:
    // mouse event related to movement
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    // to manage and draw all the thing related objects
    void paintEvent(QPaintEvent *event) override;

public:
    Engine *engine;
    int screenSize = 500;

    // parameters related to movement(dynamic)
    QPointF pressPos={0,0};
    QPointF releasePos={0,0};

    // parameters not related to movement(static)
    QString shape="Circle";
    double mass=10;
    QPointF size={10,10};
    double restitution = 1.0;
    bool isMovingY = true;

    // containers for holding objects
    std::vector<Circle> circles;
    std::vector<Rectangle> rectangles;
    std::map<QString, Rectangle> background;
};

#endif // WORLD_H
