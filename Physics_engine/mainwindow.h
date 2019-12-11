#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "engine.h"
#include "world.h"

#include <QMainWindow>
//#include <QHBoxLayout>
//#include <QComboBox>
//#include <QLabel>
//#include <QTextLayout>
//#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE
//class Engine;
//class World;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void shooting(double x1, double y1, double x2, double y2);
    void on_applyButton_clicked();
    void on_defaultButton_clicked();
//    void positionXShow();
    void on_setButton_clicked();
//    void shapeChanged();

    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_resetButton_clicked();

    void on_groundCheckBox_stateChanged(int arg1);

    void on_rightWallCheckBox_stateChanged(int arg1);

    void on_leftWallCheckBox_stateChanged(int arg1);

    void on_roofCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Engine engine;
    World *world;

//    World *world;
//    QLabel *title;

//    World *world;
//    QLabel *properties;
//    QLabel *gravity;
//    QTextLayout *gravityValue;
//    QLabel *friction;
//    QTextLayout *frictionValue;

//    QPushButton *defaultButton;
//    QPushButton *applyButton;

//    QLabel *object;
//    QLabel *shape;
//    QComboBox *shapeSelect;
//    QLabel *mass;
//    QTextLayout *massValue;
//    QLabel *size;
//    QTextLayout *sizeFirst;
//    QTextLayout *sizeSecond;

//    QLabel *velocity;
//    QTextLayout *velocityX;
//    QTextLayout *velocityY;

//    QLabel *restitution;
//    QTextLayout *restitutionValue;

//    QPushButton *setButton;
};
#endif // MAINWINDOW_H
