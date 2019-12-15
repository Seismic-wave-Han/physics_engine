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

//![1] Inherent functions
// animate: to update the world
void World::animate()
{
    update();
}

// createObject
void::World::createObject()
{
    // calculate position and velocity through press and release point
    paramBox.position = releasePos;
    paramBox.velocity = pressPos-releasePos; // difference of two position assigned to velocity

    // check shape and create appropriate object
    if (paramBox.shape == "Circle"){
        Circle circle = Circle(engine, paramBox, isFixed);
        circles.push_back(circle); // save circle object in container circles
    } else if (paramBox.shape == "Rectangle"){
        Rectangle rectangle = Rectangle(engine, paramBox, isFixed);
        rectangles.push_back(rectangle); // save rectangle in container rectangles
    }
}

// setStaticParameters: to set parameters gotten from UI
void World::setStaticParameters(Parameter paramBox)
{
    this->paramBox = paramBox;
}

// paintBackgrounds: paint all background objects in background container
void World::paintBackgrounds(QPainter *painter)
{
    // iteration of background container
    for (auto iter=background.begin(); iter!=background.end(); iter++){
        // the data type is a pair of QString and Rectangle: map<QString, Rectangle>
        // so assign second thing to Object
        Object *backObject = &iter->second;

        // paint background(rectangle): cf) drawRect(x of left, y of top, Width, Height)
        painter->drawRect(int(backObject->Left_top().rx()), int(backObject->Left_top().ry()),
                          int(backObject->getWidth()), int(backObject->getHeight()));
    }
}

// checkRectangleVsCircle:
// to check rectangle vs circle crossed collision before to test each container
void World::checkRectangleVsCircle()
{
    // iteration of circles container
    for (size_t i=0; i<circles.size(); ++i){
        Object *circleA = &circles[i];

        // iteration of rectangles container
        for (size_t i=0; i<rectangles.size(); ++i){
            Object *rectangleA = &rectangles[i];

            // Mainfold rc holds rectangle and circle
            Manifold *rc= new Manifold(rectangleA, circleA);

            // update each object velocity if it has collision
            rc->updateRectangleVsCircle();
        }
    }
}

// updateCircles:
// for every circle in container, check collision with other circles and backgrounds.
// then update the position and paint the circle
void World::updateCircles(QPainter *painter)
{
    // iteration of circles container
    for (size_t i=0; i<circles.size(); ++i){
        Object *circleA = &circles[i];

        // iteration after i-th circle
        for(size_t j=i+1; j<circles.size(); ++j){
            Object *circleB = &circles[j];

            // Mainfold cc holds two different circle
            Manifold *cc= new Manifold(circleA, circleB);

            // update each object velocity if it has collision
            cc->updateCircleVsCircle();
        }

        // iteration of background objects
        for (auto iter=background.begin(); iter!=background.end(); iter++){
            Object *backObject = &iter->second;

            // Mainfold bc holds background and circle object
            Manifold *bc= new Manifold(backObject, circleA);

            // update each object velocity if it has collision
            bc->updateRectangleVsCircle();
        }

        // update position after taking into account all of the above conflicts
        circleA->positionUpdate();

        // finally, paint one i-th circle
        paintCircle(painter, circleA);
    }
}

// paintCircle: Draw a visually colored circle
void World::paintCircle(QPainter *painter, Object *circleA)
{
    double massNormalized = circleA->mass/100;
    int opacity = static_cast<int>(255* massNormalized); // Light objects are transparent
    int redness = static_cast<int>(255* circleA->restitution); // high restiturion
    int blueness = static_cast<int>(255* (1-circleA->restitution)); // low restitution

    // set brush with above settings before paint
    painter->setBrush(QColor(redness, 0, blueness, opacity));

    // paint circle: cf) drawEllipse(x of center, y of center, radius, radius)
    painter->drawEllipse(QPointF(circleA->position.rx(), circleA->position.ry()),
                         circleA->getRadius(), circleA->getRadius());
}

// updateRectangles: exactly same mechanism as the updateCircles
void World::updateRectangles(QPainter *painter)
{
    for (size_t i=0; i<rectangles.size(); ++i){
        Object *rectangleA = &rectangles[i];

        // update each object velocity between Rectangle if it has collision
        for(size_t j=i+1; j<rectangles.size(); ++j){
            Object *rectangleB = &rectangles[j];

            Manifold *rr= new Manifold(rectangleA, rectangleB);
            rr->updateRectangleVsRectangle();
        }

        // update rectangle velocity after collision with background if it has collision
        for (auto iter=background.begin(); iter!=background.end(); iter++){
            Object *backObject = &iter->second;

            Manifold *br= new Manifold(backObject, rectangleA);
            br->updateRectangleVsRectangle();
        }

        // update position after taking into account all of the above conflicts
        rectangleA->positionUpdate();

        // finally, paint i-th rectangle
        paintRectangle(painter, rectangleA);
    }
}

// paintRectangle: exactly same mechanism as the paintCircle
void World::paintRectangle(QPainter *painter, Object *rectangleA)
{
    double massNormalized = rectangleA->mass / 100;
    int opacity = static_cast<int>(255* massNormalized);
    int redness = static_cast<int>(255* rectangleA->restitution);
    int blueness = static_cast<int>(255* (1-rectangleA->restitution));
    painter->setBrush(QColor(redness, 0, blueness, opacity));

    // paint rectangle: cf) drawRect(x of left, y of top, Width, Height)
    painter->drawRect(int(rectangleA->Left_top().rx()), int(rectangleA->Left_top().ry()),
                      int(rectangleA->getWidth()), int(rectangleA->getHeight()));

}
//![1]

//![2] inherited functions
// paintEvent: manage all collision and drawing of objects
void World::paintEvent(QPaintEvent *event){
    // create QPainter object
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // fill white color to screen
    painter.fillRect(event->rect(), QBrush(Qt::white));

    // set pen color
    painter.setPen(QPen(Qt::black));

    // move the center of the coordinate system to the center of screen
    painter.translate(QPointF(0.5*screenSize, 0.5*screenSize));

    // from here, all collision and drawing objects process is proceed
    paintBackgrounds(&painter); // first, painting all background objects
    checkRectangleVsCircle(); // cross check collision of different type of object
    updateCircles(&painter); // then update circles in sequence and draw them
    updateRectangles(&painter); // also update rectangles in sequence and draw them

    painter.end();
}

// mousePressEvent: if world(OpenGL) is pressed then this function will be operated
// assign mouse pressed position to member variable pressPos with coordinattion correnction
void World::mousePressEvent(QMouseEvent *event)
{
    pressPos = event->pos();
    QPointF correctionFactor = {0.5*screenSize, 0.5*screenSize}; // the center is (0, 0)
    pressPos = pressPos - correctionFactor;

}

// mouseReleaseEvent: if world(OpenGL) is pressed then this function will be operated
// assign mouse release position to member variable releasePos with coordinattion correnction
// then create an object with the specified parameters
void World::mouseReleaseEvent(QMouseEvent *event)
{
    releasePos = event->pos();
    QPointF correctionFactor = {0.5*screenSize, 0.5*screenSize}; // the center is (0, 0)
    releasePos = releasePos - correctionFactor;

    createObject();
}
//![2]
