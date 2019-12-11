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
//    Q_OBJECT
public:
//    void mouseClicked(QMouseEvent * event);
//    void clicked(){
//        emit mouseReleaseEvent();
//    }
    void positionXChanged(int positionX);
    void positionYChanged(int positionY);
public:
    World(Engine *engine, QWidget *parent);
    void animate();
    void clicked();
    void paintEvent(QPaintEvent *event) override;
    void createCircleEvent(Circle circle);
    void createRectEvent(Rectangle rectangle);
    //todo: 소켓을 만들어 같이 옮기기
    void setParameters(QString shape, double mass, QPointF size, double restitution, bool isMovingY);

signals:
//    void shoot(double x1, double y1, double x2, double y2);

public:
    Engine *engine;
    int dt=0;
    QPointF pressPos={0,0};
    QPointF releasePos={0,0};
    int screenSize = 500;
    QString shape="Circle";
    double mass=10;
    QPointF size={10,10};
    double restitution = 1.0;
    bool isMovingY = true;
    std::vector<Circle> circles;
    std::vector<Rectangle> rectangles;
    std::map<QString, Rectangle> background;


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


};

#endif // WORLD_H
