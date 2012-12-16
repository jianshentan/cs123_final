QT += core gui opengl

CONFIG += x86
CONFIG -= ppc

TARGET = 3DTransformations_lab
TEMPLATE = app

INCLUDEPATH += src
DEPENDPATH += src

SOURCES += src/settings.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/glwidget.cpp \
    src/databinding.cpp \
    src/particleemitter.cpp \
    src/target.cpp

HEADERS += src/vector.h \
    src/settings.h \
    src/mainwindow.h \
    src/glwidget.h \
    src/databinding.h \
    src/camera.h \
    src/particleemitter.h \
    src/common.h \
    src/target.h

FORMS += src/mainwindow.ui

RESOURCES += \
    textures/images.qrc

OTHER_FILES +=
