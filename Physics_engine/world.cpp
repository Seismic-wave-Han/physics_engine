#include "world.h"
#include "engine.h"
#include "object.h"
#include "parameter.h"

#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>

#include <iostream> // delete after testing

//![0] constructor
// constructor
World::World(Engine *engine, QWidget *parent):
    QOpenGLWidget(parent), engine(engine)
{
    // set screen size
    screenSize = 500;
    setFixedSize(screenSize, screenSize);
    setAutoFillBackground(false);
}
//![0]

//![1] functions
// animate: to update the world
void World::animate()
{
    update();
}

// createObject
void::World::createObject(){
    // calculate press point to release point
    QPointF mouseMovedDistance = pressPos-releasePos; // It assigned to velocity

    // check shape and create appropriate object
    if (shape == "Circle"){
        Circle circle = Circle(engine, false, mass, size.x(), releasePos, mouseMovedDistance, restitution, isMovingY);
        circles.push_back(circle);
    } else if (shape == "Rectangle"){
        Rectangle rectangle = Rectangle(engine, false, mass, size, releasePos, mouseMovedDistance, restitution, isMovingY);
        rectangles.push_back(rectangle);
    }
}

// setStaticParameters: to set parameters gotten from UI
void World::setStaticParameters(Parameter paramBox)
{
    this->shape = paramBox.shape;
    this->mass = paramBox.mass;
    this->size = size;
    this->restitution = restitution;
    this->isMovingY = isMovingY;
}


void World::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(event->rect(), QBrush(Qt::white));

    painter.setPen(QPen(Qt::black));
    painter.translate(QPointF(0.5*screenSize, 0.5*screenSize));

    size_t sizeC=circles.size();
    size_t sizeR=rectangles.size();

    for (auto iter=background.begin(); iter!=background.end(); iter++){
        Object *backObject = &iter->second;
        painter.drawRect(int(backObject->Left_top().rx()), int(backObject->Left_top().ry()), int(backObject->getWidth()), int(backObject->getHeight()));
    }

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
        for(size_t j=i+1; j<sizeC; ++j){
            Object *circleB = &circles[j];
            Manifold *cc= new Manifold(circleA, circleB);
            cc->updateCircleVsCircle();
        }
        for (auto iter=background.begin(); iter!=background.end(); iter++){
            Object *backObject = &iter->second;
            Manifold *bc= new Manifold(backObject, circleA);
            bc->updateRectangleVsCircle();
        }
        circleA->positionUpdate();
        double massNormalized = circleA->mass / 100;
        int opacity = static_cast<int>(255* massNormalized);
        int redness = static_cast<int>(255* circleA->restitution);
        int blueness = static_cast<int>(255* (1-circleA->restitution));
        painter.setBrush(QColor(redness, 0, blueness, opacity));
        painter.drawEllipse(QPointF(circleA->position.rx(), circleA->position.ry()), circleA->getRadius(), circleA->getRadius());

    }

    for (size_t i=0; i<sizeR; ++i){
        Object *rectangleA = &rectangles[i];

        for(size_t j=i+1; j<sizeR; ++j){
            Object *rectangleB = &rectangles[j];
            Manifold *rr= new Manifold(rectangleA, rectangleB);
            rr->updateRectangleVsRectangle();
        }
        for (auto iter=background.begin(); iter!=background.end(); iter++){
            Object *backObject = &iter->second;
            Manifold *br= new Manifold(backObject, rectangleA);
            br->updateRectangleVsRectangle();
        }
        rectangleA->positionUpdate();
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



    createObject();

}


