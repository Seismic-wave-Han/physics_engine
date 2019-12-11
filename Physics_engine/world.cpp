#include "world.h"
#include "engine.h"
#include "object.h"
//#include "collision.h" // 이거 넣으니까 안되더라

#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>

#include <iostream> // delete after testing

World::World(Engine *engine, QWidget *parent):
    QOpenGLWidget(parent), engine(engine)
{
    dt = 0;
    screenSize = 500;
    setFixedSize(screenSize, screenSize);
    setAutoFillBackground(false);
}

void World::animate()
{
    dt = (dt+qobject_cast<QTimer*>(sender())->interval())%1000; //todo: Does 'dt' need?
    update();
}

void World::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
//    engine->paint(&painter, event);
    painter.fillRect(event->rect(), QBrush(Qt::white));
//    painter.save();
//    painter.setBrush(QBrush(Qt::red));
    painter.setPen(QPen(Qt::black));
    painter.translate(QPointF(0.5*screenSize, 0.5*screenSize));
//    for (auto &circle: circles){
//        circle.bounce();
//        circle.positionUpdate();
////        qDebug() << "radius: " << object->getRadius();
//        painter.drawEllipse(QPointF(circle.position.rx(), circle.position.ry()), circle.radius, circle.radius);
//    }
//    for (auto &rectangle: rectangles){
//        rectangle.bounce();
//        rectangle.positionUpdate();
////        qDebug() << rectangle.Right_bottom().ry();
//        painter.drawRect(int(rectangle.Left_top().rx()), int(rectangle.Left_top().ry()), int(rectangle.width), int(rectangle.height)); // todo: use int spinbox, and change type of width, height to int?
//    }
    size_t sizeC=circles.size();
    size_t sizeR=rectangles.size();

    for (size_t i=0; i<sizeC; ++i){
        Object *circleA = &circles[i];
        for (size_t i=0; i<sizeR; ++i){
            Object *rectangleA = &rectangles[i];
            Manifold *rc= new Manifold(rectangleA, circleA);
            rc->updateRectangleVsCircle();
        }
    }

    for (size_t i=0; i<sizeC; ++i){
        Object *circleA = &circles[i];
        circleA->positionUpdate();
        circleA->bounce();
        for(size_t j=i+1; j<sizeC; ++j){
            Object *circleB = &circles[j];
            Manifold *cc= new Manifold(circleA, circleB);
            cc->updateCircleVsCircle();
        }
        double massNormalized = circleA->mass / 100;
        int opacity = static_cast<int>(255* massNormalized);
        int redness = static_cast<int>(255* circleA->restitution);
        int blueness = static_cast<int>(255* (1-circleA->restitution));
        painter.setBrush(QColor(redness, 0, blueness, opacity));
        painter.drawEllipse(QPointF(circleA->position.rx(), circleA->position.ry()), circleA->getRadius(), circleA->getRadius());

    }

    for (size_t i=0; i<sizeR; ++i){
        Object *rectangleA = &rectangles[i];
        rectangleA->positionUpdate();
        rectangleA->bounce();
        for(size_t j=i+1; j<sizeR; ++j){
            Object *rectangleB = &rectangles[j];
            Manifold *rr= new Manifold(rectangleA, rectangleB);
            rr->updateRectangleVsRectangle();
        }
        double massNormalized = rectangleA->mass / 100;
        int opacity = static_cast<int>(255* massNormalized);
        int redness = static_cast<int>(255* rectangleA->restitution);
        int blueness = static_cast<int>(255* (1-rectangleA->restitution));
        painter.setBrush(QColor(redness, 0, blueness, opacity));
        painter.drawRect(int(rectangleA->Left_top().rx()), int(rectangleA->Left_top().ry()), int(rectangleA->getWidth()), int(rectangleA->getHeight())); // todo: use int spinbox, and change type of width, height to int?

    }

//    qDebug() << "---cycle---";

    painter.end();
}

//void World::mousePressEvent(QMouseEvent *event)
//{
//    pressX=  event->x()-0.5*screenSize;
//    pressY = event->y()-0.5*screenSize;
//    qDebug() << pressX << "," << pressY;
//}



//void World::mouseReleased()
//{
//    QMouseEvent *event;
//    mouseReleaseEvent(event);

////    releaseX =  event->x()-0.5*screenSize;
////    releaseY = event->y()-0.5*screenSize;
//    qDebug() << releaseX << "," << releaseY;
//}

void World::clicked(){
//    emit mouseReleaseEvent;
}

void World::createCircleEvent(Circle circle){
    circles.push_back(circle);
//    paintCircle
}
void World::createRectEvent(Rectangle rectangle){
    rectangles.push_back(rectangle);
}


void World::mousePressEvent(QMouseEvent *event)
{
    pressPos = event->pos();
    QPointF correctionFactor = {0.5*screenSize, 0.5*screenSize};
    pressPos = pressPos - correctionFactor;

}

void World::mouseReleaseEvent(QMouseEvent *event)
{
    releasePos = event->pos();
    QPointF correctionFactor = {0.5*screenSize, 0.5*screenSize};
    releasePos = releasePos - correctionFactor;

    QPointF mouseMovedDistance = pressPos-releasePos;

//    shoot(pressX, pressY, releaseX, releaseY);
    if (shape == "Circle"){
        Circle circle = Circle(engine, mass, size.x(), releasePos, mouseMovedDistance, restitution, isMovingY);
        createCircleEvent(circle);
    } else if (shape == "Rectangle"){
        Rectangle rectangle = Rectangle(engine, mass, size, releasePos, mouseMovedDistance, restitution, isMovingY);
        createRectEvent(rectangle);
    }
}

void World::setParameters(QString shape, double mass, QPointF size, double restitution, bool isMovingY)
{
    this->shape = shape;
    this->mass =mass;
    this->size = size;
    this->restitution = restitution;
    this->isMovingY = isMovingY;
}

