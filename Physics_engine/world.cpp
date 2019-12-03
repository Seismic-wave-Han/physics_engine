#include "world.h"
#include "engine.h"
#include "object.h"
//#include "collision.h"

#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>

World::World(Engine *engine, QWidget *parent):
    QOpenGLWidget(parent), engine(engine)
{
    dt = 0;
    setFixedSize(500,500);
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
    painter.save();
    painter.setBrush(QBrush(Qt::red));
    painter.setPen(QPen(Qt::blue));
    painter.translate(QPointF(100,100));
    for (auto &circle: circles){
        circle.bounce();
        circle.positionUpdate();
//        qDebug() << "radius: " << object->getRadius();
        painter.drawEllipse(QPointF(circle.position.rx(), circle.position.ry()), circle.radius, circle.radius);
    }
//    for (auto &rectangle: rectangles){
//        rectangle.bounce();
//        rectangle.positionUpdate();
////        qDebug() << rectangle.Right_bottom().ry();
//        painter.drawRect(int(rectangle.Left_top().rx()), int(rectangle.Left_top().ry()), int(rectangle.width), int(rectangle.height)); // todo: use int spinbox, and change type of width, height to int?
//    }
//    size_t sizeC=circles.size();
//    size_t sizeR=rectangles.size();

//    for (size_t i=0; i<sizeC; ++i){
////        Object *circleA = &circles[i];
////        circleA->bounce();
////        circleA->positionUpdate();
//        circles[i].bounce();
//        circles[i].positionUpdate();
////        qDebug() << "radius: " << object->getRadius();
////        for(size_t j=i+1; j<sizeC; ++j){
////            Object *circleB = &circles[j];
////            Manifold m(circleA, circleB);
////            bool isCollided = circleVsCircle(&m);
////            if (isCollided){
////                positionCorrection(&m);
////                resolveCollision(&m);
////            }
////        }
//        painter.drawEllipse(QPointF(circles[i].position.rx(), circles[i].position.ry()), circles[i].getRadius(), circles[i].getRadius());
////        painter.drawEllipse(QPointF(circleA->position.rx(), circleA->position.ry()), circleA->getRadius(), circleA->getRadius());
//    }
    for (auto &rectangle: rectangles){
        rectangle.bounce();
        rectangle.positionUpdate();
//        qDebug() << rectangle.Right_bottom().ry();
        painter.drawRect(int(rectangle.Left_top().rx()), int(rectangle.Left_top().ry()), int(rectangle.width), int(rectangle.height)); // todo: use int spinbox, and change type of width, height to int?
    }


//    qDebug() << "---cycle---";

    painter.end();
}

void World::mousePressEvent(QMouseEvent *event)
{
    positionX=  event->x();
    positionY = event->y();
    QString x = QString::number(event->x());
    QString y = QString::number(event->y());
    qDebug() << x << "," << y;
//    emit mousePressed(event->pos());
//    emit positionXChanged(positionX);
//    emit positionYChanged(positionY);

}

void World::createCircleEvent(Circle circle){
    circles.push_back(circle);
//    paintCircle
}
void World::createRectEvent(Rectangle rectangle){
    rectangles.push_back(rectangle);
}
