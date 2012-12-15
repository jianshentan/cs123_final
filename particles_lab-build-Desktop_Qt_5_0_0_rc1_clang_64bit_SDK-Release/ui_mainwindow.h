/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Dec 7 00:35:14 2012
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "particlewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    ParticleWidget *widget;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QDial *velocityDial;
    QSlider *velocitySlider;
    QLabel *velocityLabel1;
    QLabel *velocityLabel2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QDial *forceDial;
    QSlider *forceSlider;
    QLabel *forceLabel1;
    QLabel *forceLabel2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QSlider *speedSlider;
    QLabel *speedLabel;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1199, 514);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new ParticleWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        velocityDial = new QDial(groupBox);
        velocityDial->setObjectName(QStringLiteral("velocityDial"));
        velocityDial->setMaximum(360);
        velocityDial->setTracking(true);
        velocityDial->setWrapping(true);
        velocityDial->setNotchesVisible(true);

        gridLayout_2->addWidget(velocityDial, 0, 0, 1, 1);

        velocitySlider = new QSlider(groupBox);
        velocitySlider->setObjectName(QStringLiteral("velocitySlider"));
        velocitySlider->setMinimum(0);
        velocitySlider->setMaximum(300);
        velocitySlider->setValue(0);
        velocitySlider->setOrientation(Qt::Vertical);

        gridLayout_2->addWidget(velocitySlider, 0, 1, 1, 1);

        velocityLabel1 = new QLabel(groupBox);
        velocityLabel1->setObjectName(QStringLiteral("velocityLabel1"));

        gridLayout_2->addWidget(velocityLabel1, 1, 0, 1, 1);

        velocityLabel2 = new QLabel(groupBox);
        velocityLabel2->setObjectName(QStringLiteral("velocityLabel2"));

        gridLayout_2->addWidget(velocityLabel2, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        forceDial = new QDial(groupBox_2);
        forceDial->setObjectName(QStringLiteral("forceDial"));
        forceDial->setMaximum(360);
        forceDial->setWrapping(true);
        forceDial->setNotchesVisible(true);

        gridLayout_3->addWidget(forceDial, 0, 0, 1, 1);

        forceSlider = new QSlider(groupBox_2);
        forceSlider->setObjectName(QStringLiteral("forceSlider"));
        forceSlider->setMinimum(0);
        forceSlider->setMaximum(300);
        forceSlider->setValue(0);
        forceSlider->setOrientation(Qt::Vertical);

        gridLayout_3->addWidget(forceSlider, 0, 1, 1, 1);

        forceLabel1 = new QLabel(groupBox_2);
        forceLabel1->setObjectName(QStringLiteral("forceLabel1"));

        gridLayout_3->addWidget(forceLabel1, 1, 0, 1, 1);

        forceLabel2 = new QLabel(groupBox_2);
        forceLabel2->setObjectName(QStringLiteral("forceLabel2"));

        gridLayout_3->addWidget(forceLabel2, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_4 = new QGroupBox(dockWidgetContents);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setSpacing(2);
        gridLayout_5->setContentsMargins(2, 2, 2, 2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        speedSlider = new QSlider(groupBox_4);
        speedSlider->setObjectName(QStringLiteral("speedSlider"));
        speedSlider->setValue(50);
        speedSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(speedSlider, 0, 0, 1, 1);

        speedLabel = new QLabel(groupBox_4);
        speedLabel->setObjectName(QStringLiteral("speedLabel"));

        gridLayout_5->addWidget(speedLabel, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "[Lab06] Particles", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Velocity", 0));
        velocityLabel1->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        velocityLabel2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Force", 0));
        forceLabel1->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        forceLabel2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Speed", 0));
        speedLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
