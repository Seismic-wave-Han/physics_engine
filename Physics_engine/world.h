#ifndef WORLD_H
#define WORLD_H

#include <QOpenGLWidget>
#include <vector>
//#include <QMainWindow>
class Engine;
class Object;
class Circle;
class Rectangle;
class World : public QOpenGLWidget
{
signals:
    void mousePressed( const QPoint& );
    void positionXChanged(int positionX);
    void positionYChanged(int positionY);
public:
    World(Engine *engine, QWidget *parent);
    void animate();
    void paintEvent(QPaintEvent *event);
    void createCircleEvent(Circle circle);
    void createRectEvent(Rectangle rectangle);

private slots:
    void mousePressEvent(QMouseEvent * event);
public:
    Engine *engine;
    int dt;
    int positionX;
    int positionY;
    std::vector<Circle> circles;
    std::vector<Rectangle> rectangles;

};

#endif // WORLD_H
