#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "engine.h"
#include "object.h"
#include "parameter.h"

#include <QTimer>
#include <QDebug>

//![0] constructor & distructor
// constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //// World object
    world = new World(&engine, this); // create World object which contain engine
    ui->verticalLayout->addWidget(world); // add to ui

    //// ui basic settings
    /// global variables
    // gravity
    ui->gravityValue->setRange(0, 100);
    ui->gravityValue->setValue(9.8); // default value is 9.8
    // friction(not connected yet)
    ui->frictionValue->setRange(0, 1);
    /// object variables
    // mass
    ui->massValue->setRange(0, 100); // have to be positive
    ui->massValue->setValue(10);
    // size
    ui->sizeValueX->setRange(5,100); // circle have only sizeX(radius)
    ui->sizeValueY->setRange(5,100);
    ui->sizeValueX->setValue(10);
    ui->sizeValueY->setValue(10);
    // position
    double maxRange = 0.5*world->screenSize;
    ui->positionValueX->setRange(-maxRange, maxRange);
    ui->positionValueY->setRange(-maxRange, maxRange);
    // velocity
    ui->velocityValueX->setRange(-100,100);
    ui->velocityValueY->setRange(-100,100);
    // restitution
    ui->restitutionValue->setRange(0,1); // min=0 , max=1(complete elastic collision)
    ui->restitutionValue->setValue(1.0);
    /// other ui setting
    // ground
    ui->groundCheckBox->setChecked(true); // ground will exist for default setting

    //// basket ball example(commented)
//    Rectangle Object1= Rectangle(&engine, true, {10,50}, {200,-150});
//    world->background.insert(std::make_pair("goal", Object1));
//    Rectangle Object2= Rectangle(&engine, true, {10,480}, {240,10});
//    world->background.insert(std::make_pair("goalde", Object2));

    //// poket ball example(commented)
    // in this example some other parameters also need to be modified manually
//    double e=0.7;
//    double mass=10;
//    double root3=1.732;
//    double r=15;
//    for (int i=0; i<4; i++){
//        double x = 100 + i*root3*r;
//        double y= -r*i;
//        for (int j=0; j<i+1; j++){
//            Circle circle(&engine, mass, r, {x,y},{0,0}, e, true);
//            world->createCircleEvent(circle);
//            y += 2*r;
//        }
//    }

    //// QTimer
    // QTimer for animation
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, world, &World::animate);
    timer->start(1); // update rate
}    

// destructor
MainWindow::~MainWindow()
{
    delete ui;
}
//![0]

//![1] slots related with ui
// apply: apply global variables which are written in ui
void MainWindow::on_applyButton_clicked()
{
    // set gravity
    double gravity = ui->gravityValue->value();
    engine.setGravity(gravity);

    // set friction(not developed yet)
    double friction = ui->frictionValue->value();
    engine.setFriction(friction);
}

// default: set gravity as 9.8
void MainWindow::on_defaultButton_clicked()
{
    ui->gravityValue->setValue(9.8);
    engine.setGravity(9.8);
    ui->frictionValue->setValue(0);
    engine.setFriction(0);
    on_applyButton_clicked();
}

// set: set object properties(not create object) that will be applyed to mouse event
void MainWindow::on_setButton_clicked()
{
    Parameter paramBox;

    // get values form ui
    paramBox.shape = ui->shapeComboBox->currentText();
    paramBox.mass = ui->massValue->value();
    double sizeX = ui->sizeValueX->value();
    double sizeY = ui->sizeValueY->value();
    paramBox.size = {sizeX, sizeY};
    double positionX = ui->positionValueX->value();
    double positionY = ui->positionValueY->value();
    paramBox.position = {positionX, positionY};
    double velocityX = ui->velocityValueX->value();
    double velocityY = ui->velocityValueY->value();
    paramBox.velocity = {velocityX, velocityY};
    paramBox.restitution = ui->restitutionValue->value();

    // send parameters to world
    world->setStaticParameters(paramBox);

    // initialize the mouse positions: for the case of clicking create button right after set button
    world->pressPos = paramBox.position + paramBox.velocity;
    world->releasePos = paramBox.position;
}

// creat: create an object with set values
void MainWindow::on_createButton_clicked()
{
    // get position and velocity from mouse clicked information
    getDynamicParameters();

    Parameter paramBox;
    // get values form ui
    paramBox.shape = ui->shapeComboBox->currentText();
    paramBox.mass = ui->massValue->value();
    double sizeX = ui->sizeValueX->value();
    double sizeY = ui->sizeValueY->value();
    paramBox.size = {sizeX, sizeY};
    double positionX = ui->positionValueX->value();
    double positionY = ui->positionValueY->value();
    paramBox.position = {positionX, positionY};
    double velocityX = ui->velocityValueX->value();
    double velocityY = ui->velocityValueY->value();
    paramBox.velocity = {velocityX, velocityY};
    paramBox.restitution = ui->restitutionValue->value();

    // send parameters to world
    world->setStaticParameters(paramBox);

    // create an object based on sended parameters
    world->createObject();
}

// start: set dt=0.1(default value)
void MainWindow::on_startButton_clicked()
{
    double dt=0.1;
    engine.setTimeInterval(dt);
    qDebug()<< "restart!";

}

// stop: stop the objects by setting dt=0
void MainWindow::on_stopButton_clicked()
{
    engine.setTimeInterval(0);
    qDebug()<< "stop!";
}

// reset: clear all circles and rectangles except background
void MainWindow::on_resetButton_clicked()
{
    world->circles.clear();
    world->rectangles.clear();
}

// is fixed :make the next object to be fixed
void MainWindow::on_fixCheckBox_stateChanged(int arg1)
{
    if (arg1){
        world->isFixed = true;
    } else {
        world->isFixed = false;
    }
}

// ground check box: make/delete ground(fixed object) to bounce
void MainWindow::on_groundCheckBox_stateChanged(int arg1)
{
    double maxSize = world->screenSize;
    if (arg1){
        // ground is Rectangle which have infinite mass
        // create object with appropriate values
        Parameter paramBox;
        paramBox.mass = 0;
        paramBox.size = {maxSize, maxSize};
        paramBox.position = {0, maxSize};
        Rectangle ground = Rectangle(&engine, paramBox, true);

        // insert ground to backgound container in world
        world->background.insert(std::make_pair("ground", ground));
    } else {
        // delete ground from backgound container in world
        world->background.erase("ground");
    }
}

// right wall check box: create/delete right side wall(same mechanism)
void MainWindow::on_rightWallCheckBox_stateChanged(int arg1)
{
    double maxSize = world->screenSize;
    if (arg1){
        Parameter paramBox;
        paramBox.mass = 0;
        paramBox.size = {maxSize, maxSize};
        paramBox.position = {maxSize, 0};
        Rectangle rightWall = Rectangle(&engine, paramBox, true);
        world->background.insert(std::make_pair("right wall", rightWall));
    } else {
        world->background.erase("right wall");
    }
}

// left wall check box(same mechanism)
void MainWindow::on_leftWallCheckBox_stateChanged(int arg1)
{
    double maxSize = world->screenSize;
    if (arg1){
        Parameter paramBox;
        paramBox.mass = 0;
        paramBox.size = {maxSize, maxSize};
        paramBox.position = {-maxSize, 0};
        Rectangle leftWall = Rectangle(&engine, paramBox, true);
        world->background.insert(std::make_pair("left wall", leftWall));
    } else {
        world->background.erase("left wall");
    }
}

// roof check box(same mechanism)
void MainWindow::on_roofCheckBox_stateChanged(int arg1)
{
    double maxSize = world->screenSize;
    if (arg1){
        Parameter paramBox;
        paramBox.mass = 0;
        paramBox.size = {maxSize, maxSize};
        paramBox.position = {0, -maxSize};
        Rectangle roof = Rectangle(&engine, paramBox, true);
        world->background.insert(std::make_pair("roof", roof));
    } else {
        world->background.erase("roof");
    }
}
//![1]

//![2] functions
// getMousePositions: get and set position and velocity values from mouse positions
void MainWindow::getDynamicParameters()
{
    ui->positionValueX->setValue(world->releasePos.x());
    ui->positionValueY->setValue(world->releasePos.y());
    QPointF velocity = world->pressPos - world->releasePos;
    ui->velocityValueX->setValue(velocity.x());
    ui->velocityValueY->setValue(velocity.y());

}
//![2]
