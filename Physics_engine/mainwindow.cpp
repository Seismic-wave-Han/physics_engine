#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "engine.h"
#include "object.h"
#include <QTimer>
#include <QDebug>

//#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui basic settings
    ui->gravityValue->setRange(0, 100);
    ui->gravityValue->setValue(9.8);
    ui->frictionValue->setRange(0, 1);
    ui->massValue->setRange(0, 100);
    ui->massValue->setValue(10);
    ui->sizeValueX->setRange(5,100);
    ui->sizeValueY->setRange(5,100);
    ui->sizeValueX->setValue(10);
    ui->sizeValueY->setValue(10);
    ui->velocityValueX->setRange(-100,100);
    ui->velocityValueY->setRange(-100,100);
    ui->restitutionValue->setRange(0,1);
    ui->restitutionValue->setValue(1.0);

    // create World object
    world = new World(&engine, this);
    ui->verticalLayout->addWidget(world); // add to ui
    ui->verticalLayout->addWidget(world); // add to ui

    double maxRange = 0.5*world->screenSize;
    ui->positionValueX->setRange(-0.5*maxRange, 0.5*maxRange);
    ui->positionValueY->setRange(-0.5*maxRange, 0.5*maxRange);
    ui->groundCheckBox->setChecked(true);

    Rectangle baseObject = Rectangle(&engine, true, {0, 0}, {1000,1000});
    world->background.insert(std::make_pair("base", baseObject));

    // basket ball
    Rectangle Object1= Rectangle(&engine, true, {10,50}, {200,-150});
    world->background.insert(std::make_pair("goal", Object1));

    Rectangle Object2= Rectangle(&engine, true, {10,480}, {240,10});
    world->background.insert(std::make_pair("goalde", Object2));

    // QTimer for animation
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, world, &World::animate);
    timer->start(1);
}    

// destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// slots related with ui
void MainWindow::on_applyButton_clicked()
{
    double gravity = ui->gravityValue->value();
    engine.setGravity(gravity);
    double friction = ui->frictionValue->value();
    engine.setFriction(friction);
}

void MainWindow::on_defaultButton_clicked()
{
    ui->gravityValue->setValue(9.8);
    engine.setGravity(9.8);
    ui->frictionValue->setValue(0);
    engine.setFriction(0);
}

// todo: set 말고 다른 버튼하나 만들기.
void MainWindow::on_setButton_clicked()
{
    QString shape = ui->shapeComboBox->currentText();
    double mass = ui->massValue->value();
    double sizeX = ui->sizeValueX->value();
    double sizeY = ui->sizeValueY->value();
    QPointF size(sizeX, sizeY);
    double positionX = ui->positionValueX->value();
    double positionY = ui->positionValueY->value();
    QPointF position(positionX, positionY);
    double velocityX = ui->velocityValueX->value();
    double velocityY = ui->velocityValueY->value();
    QPointF velocity(velocityX, velocityY);
    double restitution = ui->restitutionValue->value();
    bool isMovingY=true;

    world->setParameters(shape, mass, size, restitution, isMovingY);
}

//void MainWindow::shooting(double x1, double y1, double x2, double y2){
//    qDebug() << "shoot!!";
//}

void MainWindow::on_startButton_clicked()
{
    double dt=0.1;
    engine.setDelta(dt);
}

void MainWindow::on_stopButton_clicked()
{
    engine.setDelta(0);
    qDebug()<< "stop!";
}

void MainWindow::on_resetButton_clicked()
{
    world->circles.clear();
    world->rectangles.clear();
}


void MainWindow::on_groundCheckBox_stateChanged(int arg1)
{
    double maxSize = world->screenSize;
    if (arg1){
        Rectangle ground = Rectangle(&engine, true, {maxSize, maxSize}, {0.0, maxSize});
        world->background.insert(std::make_pair("ground", ground));
    } else {
        world->background.erase("ground");
    }
}

void MainWindow::on_rightWallCheckBox_stateChanged(int arg1)
{
    double maxSize = world->screenSize;
    if (arg1){
        Rectangle rightWall = Rectangle(&engine, true, {maxSize, maxSize}, {maxSize, 0.0});
        world->background.insert(std::make_pair("right wall", rightWall));
    } else {
        world->background.erase("right wall");
    }
}

void MainWindow::on_leftWallCheckBox_stateChanged(int arg1)
{
    double maxSize = world->screenSize;
    if (arg1){
        Rectangle leftWall = Rectangle(&engine, true, {maxSize, maxSize}, {-maxSize, 0.0});
        world->background.insert(std::make_pair("left wall", leftWall));
    } else {
        world->background.erase("left wall");
    }
}

void MainWindow::on_roofCheckBox_stateChanged(int arg1)
{
    double maxSize = world->screenSize;
    if (arg1){
        Rectangle roof = Rectangle(&engine, true, {maxSize, maxSize}, {0.0, -maxSize});
        world->background.insert(std::make_pair("roof", roof));
    } else {
        world->background.erase("roof");
    }
}
