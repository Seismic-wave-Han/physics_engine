#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "engine.h"
#include "world.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// MainWindow: It has engine and world, so all the things related with UI and objects are managed in here.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // set global variables in engine
    void on_applyButton_clicked();
    void on_defaultButton_clicked();
    // set properties of object to create
    void on_setButton_clicked();
    // create an object with set values
    void on_createButton_clicked();
    // start or stop to move the objects in world
    void on_startButton_clicked();
    void on_stopButton_clicked();
    // delete all objects in the world
    void on_resetButton_clicked();
    // make the next object to be fixed
    void on_fixCheckBox_stateChanged(int arg1);
    // set or unset ground, wall roof by checkbox button
    void on_groundCheckBox_stateChanged(int arg1);
    void on_rightWallCheckBox_stateChanged(int arg1);
    void on_leftWallCheckBox_stateChanged(int arg1);
    void on_roofCheckBox_stateChanged(int arg1);


public:
    // get and set position and velocity values from mouse positions
    void getDynamicParameters();

private:
    // member variables
    Ui::MainWindow *ui;
    Engine engine;
    World *world;

};
#endif // MAINWINDOW_H
