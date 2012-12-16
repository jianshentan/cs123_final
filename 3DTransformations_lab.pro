QT += core gui opengl

TARGET = 3DTransformations_lab
TEMPLATE = app

INCLUDEPATH += src \
    src/lib \
    src/math \
    src/support

DEPENDPATH += src \
    src/lib \
    src/math \
    src/support

SOURCES += src/settings.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/glwidget.cpp \
    src/databinding.cpp \
    src/target.cpp \
    src/particleemitter.cpp \
    src/lib/targa.cpp \
    src/lib/glm.cpp \
    src/support/resourceloader.cpp \

HEADERS += src/vector.h \
    src/settings.h \
    src/mainwindow.h \
    src/glwidget.h \
    src/databinding.h \
    src/camera.h \
    src/target.h \
    src/particleemitter.h \
    src/lib/targa.h \
    src/lib/glm.h \
    src/math/vector.h \
    src/support/resourceloader.h


FORMS += src/mainwindow.ui

RESOURCES += \
    textures/images.qrc

OTHER_FILES += \
    src/shaders/refract.vert \
    src/shaders/refract.frag \
    src/shaders/reflect.vert \
    src/shaders/reflect.frag \
    src/shaders/brightpass.frag \
    src/shaders/blur.frag
