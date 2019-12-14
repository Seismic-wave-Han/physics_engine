/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *versionLabel;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayoutTop;
    QLabel *frictionLabel;
    QPushButton *defaultButton;
    QPushButton *applyButton;
    QDoubleSpinBox *gravityValue;
    QLabel *propertiesLabel;
    QDoubleSpinBox *frictionValue;
    QLabel *gravityLabel;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayoutBottom;
    QLabel *objectLabel;
    QPushButton *setButton;
    QLabel *massLabel;
    QLabel *restitutionLabel;
    QDoubleSpinBox *velocityValueY;
    QLabel *shapeLabel;
    QComboBox *shapeComboBox;
    QDoubleSpinBox *massValue;
    QLabel *velocityLabel;
    QDoubleSpinBox *sizeValueY;
    QDoubleSpinBox *velocityValueX;
    QLabel *sizeLabel;
    QDoubleSpinBox *restitutionValue;
    QDoubleSpinBox *sizeValueX;
    QLabel *positionLabel;
    QDoubleSpinBox *positionValueX;
    QDoubleSpinBox *positionValueY;
    QPushButton *createButton;
    QPushButton *resetButton;
    QCheckBox *leftWallCheckBox;
    QCheckBox *rightWallCheckBox;
    QCheckBox *roofCheckBox;
    QCheckBox *groundCheckBox;
    QPushButton *startButton;
    QPushButton *stopButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(948, 659);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(30, 10, 701, 571));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(verticalLayoutWidget_2);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

        verticalLayout->addWidget(titleLabel);

        versionLabel = new QLabel(verticalLayoutWidget_2);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));

        verticalLayout->addWidget(versionLabel);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(620, 40, 251, 151));
        gridLayoutTop = new QGridLayout(gridLayoutWidget);
        gridLayoutTop->setObjectName(QString::fromUtf8("gridLayoutTop"));
        gridLayoutTop->setContentsMargins(0, 0, 0, 0);
        frictionLabel = new QLabel(gridLayoutWidget);
        frictionLabel->setObjectName(QString::fromUtf8("frictionLabel"));

        gridLayoutTop->addWidget(frictionLabel, 2, 0, 1, 1);

        defaultButton = new QPushButton(gridLayoutWidget);
        defaultButton->setObjectName(QString::fromUtf8("defaultButton"));

        gridLayoutTop->addWidget(defaultButton, 3, 0, 1, 1);

        applyButton = new QPushButton(gridLayoutWidget);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));

        gridLayoutTop->addWidget(applyButton, 3, 1, 1, 1);

        gravityValue = new QDoubleSpinBox(gridLayoutWidget);
        gravityValue->setObjectName(QString::fromUtf8("gravityValue"));

        gridLayoutTop->addWidget(gravityValue, 1, 1, 1, 1);

        propertiesLabel = new QLabel(gridLayoutWidget);
        propertiesLabel->setObjectName(QString::fromUtf8("propertiesLabel"));

        gridLayoutTop->addWidget(propertiesLabel, 0, 0, 1, 1);

        frictionValue = new QDoubleSpinBox(gridLayoutWidget);
        frictionValue->setObjectName(QString::fromUtf8("frictionValue"));

        gridLayoutTop->addWidget(frictionValue, 2, 1, 1, 1);

        gravityLabel = new QLabel(gridLayoutWidget);
        gravityLabel->setObjectName(QString::fromUtf8("gravityLabel"));

        gridLayoutTop->addWidget(gravityLabel, 1, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(620, 210, 321, 253));
        gridLayoutBottom = new QGridLayout(gridLayoutWidget_2);
        gridLayoutBottom->setObjectName(QString::fromUtf8("gridLayoutBottom"));
        gridLayoutBottom->setContentsMargins(0, 0, 0, 0);
        objectLabel = new QLabel(gridLayoutWidget_2);
        objectLabel->setObjectName(QString::fromUtf8("objectLabel"));

        gridLayoutBottom->addWidget(objectLabel, 0, 0, 1, 1);

        setButton = new QPushButton(gridLayoutWidget_2);
        setButton->setObjectName(QString::fromUtf8("setButton"));

        gridLayoutBottom->addWidget(setButton, 7, 0, 1, 1);

        massLabel = new QLabel(gridLayoutWidget_2);
        massLabel->setObjectName(QString::fromUtf8("massLabel"));

        gridLayoutBottom->addWidget(massLabel, 2, 0, 1, 1);

        restitutionLabel = new QLabel(gridLayoutWidget_2);
        restitutionLabel->setObjectName(QString::fromUtf8("restitutionLabel"));

        gridLayoutBottom->addWidget(restitutionLabel, 6, 0, 1, 1);

        velocityValueY = new QDoubleSpinBox(gridLayoutWidget_2);
        velocityValueY->setObjectName(QString::fromUtf8("velocityValueY"));

        gridLayoutBottom->addWidget(velocityValueY, 5, 2, 1, 1);

        shapeLabel = new QLabel(gridLayoutWidget_2);
        shapeLabel->setObjectName(QString::fromUtf8("shapeLabel"));

        gridLayoutBottom->addWidget(shapeLabel, 1, 0, 1, 1);

        shapeComboBox = new QComboBox(gridLayoutWidget_2);
        shapeComboBox->addItem(QString());
        shapeComboBox->addItem(QString());
        shapeComboBox->setObjectName(QString::fromUtf8("shapeComboBox"));

        gridLayoutBottom->addWidget(shapeComboBox, 1, 1, 1, 1);

        massValue = new QDoubleSpinBox(gridLayoutWidget_2);
        massValue->setObjectName(QString::fromUtf8("massValue"));

        gridLayoutBottom->addWidget(massValue, 2, 1, 1, 1);

        velocityLabel = new QLabel(gridLayoutWidget_2);
        velocityLabel->setObjectName(QString::fromUtf8("velocityLabel"));

        gridLayoutBottom->addWidget(velocityLabel, 5, 0, 1, 1);

        sizeValueY = new QDoubleSpinBox(gridLayoutWidget_2);
        sizeValueY->setObjectName(QString::fromUtf8("sizeValueY"));

        gridLayoutBottom->addWidget(sizeValueY, 3, 2, 1, 1);

        velocityValueX = new QDoubleSpinBox(gridLayoutWidget_2);
        velocityValueX->setObjectName(QString::fromUtf8("velocityValueX"));

        gridLayoutBottom->addWidget(velocityValueX, 5, 1, 1, 1);

        sizeLabel = new QLabel(gridLayoutWidget_2);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));

        gridLayoutBottom->addWidget(sizeLabel, 3, 0, 1, 1);

        restitutionValue = new QDoubleSpinBox(gridLayoutWidget_2);
        restitutionValue->setObjectName(QString::fromUtf8("restitutionValue"));

        gridLayoutBottom->addWidget(restitutionValue, 6, 1, 1, 1);

        sizeValueX = new QDoubleSpinBox(gridLayoutWidget_2);
        sizeValueX->setObjectName(QString::fromUtf8("sizeValueX"));

        gridLayoutBottom->addWidget(sizeValueX, 3, 1, 1, 1);

        positionLabel = new QLabel(gridLayoutWidget_2);
        positionLabel->setObjectName(QString::fromUtf8("positionLabel"));

        gridLayoutBottom->addWidget(positionLabel, 4, 0, 1, 1);

        positionValueX = new QDoubleSpinBox(gridLayoutWidget_2);
        positionValueX->setObjectName(QString::fromUtf8("positionValueX"));

        gridLayoutBottom->addWidget(positionValueX, 4, 1, 1, 1);

        positionValueY = new QDoubleSpinBox(gridLayoutWidget_2);
        positionValueY->setObjectName(QString::fromUtf8("positionValueY"));

        gridLayoutBottom->addWidget(positionValueY, 4, 2, 1, 1);

        createButton = new QPushButton(gridLayoutWidget_2);
        createButton->setObjectName(QString::fromUtf8("createButton"));

        gridLayoutBottom->addWidget(createButton, 7, 1, 1, 1);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(800, 540, 112, 32));
        leftWallCheckBox = new QCheckBox(centralwidget);
        leftWallCheckBox->setObjectName(QString::fromUtf8("leftWallCheckBox"));
        leftWallCheckBox->setGeometry(QRect(10, 310, 86, 20));
        rightWallCheckBox = new QCheckBox(centralwidget);
        rightWallCheckBox->setObjectName(QString::fromUtf8("rightWallCheckBox"));
        rightWallCheckBox->setGeometry(QRect(530, 310, 86, 20));
        roofCheckBox = new QCheckBox(centralwidget);
        roofCheckBox->setObjectName(QString::fromUtf8("roofCheckBox"));
        roofCheckBox->setGeometry(QRect(280, 60, 86, 20));
        groundCheckBox = new QCheckBox(centralwidget);
        groundCheckBox->setObjectName(QString::fromUtf8("groundCheckBox"));
        groundCheckBox->setGeometry(QRect(280, 580, 86, 20));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(810, 470, 107, 32));
        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(814, 500, 101, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 948, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        titleLabel->setText(QApplication::translate("MainWindow", "Newton Physics engine ", nullptr));
        versionLabel->setText(QApplication::translate("MainWindow", "version:", nullptr));
        frictionLabel->setText(QApplication::translate("MainWindow", "mu", nullptr));
        defaultButton->setText(QApplication::translate("MainWindow", "default", nullptr));
        applyButton->setText(QApplication::translate("MainWindow", "apply", nullptr));
        propertiesLabel->setText(QApplication::translate("MainWindow", "Properties", nullptr));
        gravityLabel->setText(QApplication::translate("MainWindow", "gravity", nullptr));
        objectLabel->setText(QApplication::translate("MainWindow", "Object", nullptr));
        setButton->setText(QApplication::translate("MainWindow", "set", nullptr));
        massLabel->setText(QApplication::translate("MainWindow", "mass", nullptr));
        restitutionLabel->setText(QApplication::translate("MainWindow", "restitution", nullptr));
        shapeLabel->setText(QApplication::translate("MainWindow", "shape", nullptr));
        shapeComboBox->setItemText(0, QApplication::translate("MainWindow", "Circle", nullptr));
        shapeComboBox->setItemText(1, QApplication::translate("MainWindow", "Rectangle", nullptr));

        velocityLabel->setText(QApplication::translate("MainWindow", "velocity", nullptr));
        sizeLabel->setText(QApplication::translate("MainWindow", "size", nullptr));
        positionLabel->setText(QApplication::translate("MainWindow", "position", nullptr));
        createButton->setText(QApplication::translate("MainWindow", "create", nullptr));
        resetButton->setText(QApplication::translate("MainWindow", "reset", nullptr));
        leftWallCheckBox->setText(QString());
        rightWallCheckBox->setText(QString());
        roofCheckBox->setText(QString());
        groundCheckBox->setText(QString());
        startButton->setText(QApplication::translate("MainWindow", "start", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
