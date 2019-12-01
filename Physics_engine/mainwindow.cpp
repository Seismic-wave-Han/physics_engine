#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "engine.h"
#include "object.h"
#include <QTimer>

//#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gravityValue->setRange(0, 20);
    ui->gravityValue->setSpecialValueText(tr("9.8 (Earth)"));
    ui->frictionValue->setRange(0, 1);
    ui->velocityValueX->setRange(-100,100);
    ui->velocityValueY->setRange(-100,100);

    connect(ui->applyButton, SIGNAL(clicked()),
            this, SLOT(on_applyButton_clicked()));
    connect(ui->defaultButton, SIGNAL(clicked()),
            this, SLOT(on_defaultButton_clicked()));

    connect(ui->defaultButton, SIGNAL(clicked()),
            this, SLOT(on_defaultButton_clicked()));

    world = new World(&engine, this);
    ui->verticalLayout->addWidget(world, 0, 0);
//    bool enable=true;
//    world->setMouseTracking(enable);

//    connect(ui->shapeComboBox, SIGNAL(activated(int)),
//            this, SLOT(shapeChanged()));

//    connect(world, &World::positionXChanged, ui->positionX, SLOT(positionXShow()));

// QTimer는 Object의 event 를 triger 한다.
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, world, &World::animate); // todo: ui랑 연결이 안되어 있음..
    timer->start(10); // 계산하는 간격을 의미하는 듯. fps와 비슷.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_applyButton_clicked()
{
    double gravity = ui->gravityValue->value();
    engine.Set_gravity(gravity);
    double friction = ui->frictionValue->value();
    engine.Set_friction(friction);
}

void MainWindow::on_defaultButton_clicked()
{
    ui->gravityValue->setValue(9.8);
    engine.Set_gravity(9.8);
    ui->frictionValue->setValue(0);
    engine.Set_friction(0);
}

//void MainWindow::positionXShow(){
//    ui->positionX->setText(QString("world->positionX"));
//}

//void MainWindow::shapeChanged(){


//            RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(
//                    shapeComboBox->currentIndex(), IdRole).toInt());
//            renderArea->setShape(shape);
//}

void MainWindow::on_setButton_clicked()
{
    QString shape = ui->shapeComboBox->currentText();
    double mass = ui->massValue->value();
    double sizeX = ui->sizeValueX->value();
    double sizeY = ui->sizeValueY->value();
    double velocityX = ui->velocityValueX->value() ;
    double velocityY = ui->velocityValueY->value() ;
    double restitution = ui->velocityValueY->value();
    if (shape == "Circle"){
        Circle circle = Circle(mass, sizeX, sizeY, velocityX, velocityY, restitution, &world->dt);
        world->createCircleEvent(circle);
    } else if (shape == "Rectangle"){
        Rectangle rectangle = Rectangle(mass, sizeX, sizeY, velocityX, velocityY, restitution, &world->dt);
        world->createRectEvent(rectangle);
    }

    //    painter.drawEllipse(QPointF(x,y), radius, radius);
}
