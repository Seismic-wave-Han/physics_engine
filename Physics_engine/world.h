#ifndef WORLD_H
#define WORLD_H

#include <QOpenGLWidget>
//#include <QMainWindow>
class Engine;
class World : public QOpenGLWidget
{
signals:
    void mousePressed( const QPoint& );
//    void positionXChanged(int positionX);
//    void positionYChanged(int positionY);
public:
    World(Engine *engine, QWidget *parent);
    void animate();

    void mousePressEvent(QMouseEvent * event);
public:
    Engine *engine;
    int elapsed;
    int positionX;
    int positionY;
};

#endif // WORLD_H
