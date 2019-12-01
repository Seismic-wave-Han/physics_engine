#include "world.h"
#include "engine.h"
#include "object.h"

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
    dt = (dt+qobject_cast<QTimer*>(sender())->interval())%1000;
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
    for (auto &circle: objects){
        qDebug() << "drawing circles.";
        qDebug() << circle.position.rx();
        circle.update();
//        qDebug() << circle.position.x();
//        {
//            double g=circle.Get_gravity();
//            circle.position.operator+=(circle.velocity);
//            circle.position.setY(circle.position.y()+circle.velocity.y()*qreal(dt));
//            circle.velocity.setY(circle.velocity.y()+g*(dt));
//        }
        painter.drawEllipse(QPointF(circle.position.rx(), circle.position.ry()), circle.radius, circle.radius);

//        painter.translate(QPointF(100,100));
    }
    qDebug() << "---cycle---";

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
    objects.push_back(circle);
//    paintCircle
}
void World::createRectEvent(Rectangle rectangle){
//    objects.push_back(rectangle);
//    QPainter painter;
//    painter.drawRect(rectangle.position.x(),rectangle.position.y(), rectangle.width, rectangle.height);

}
