#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>
#include "camera.h"
#include "targetlandscape.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void updateSettings();
    void updateCamera();
    void rotateCamera(float deltaX, float deltaY);
    void setLabel(QLabel* label);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent ( QKeyEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    GLuint loadTexture(const QString& path);
    void makeEnvironment();



protected slots:
    void tick();

private:
    void renderArrowSphere();

    void renderQuad(GLuint textureID);
    void renderArrow();
    void renderBow();
    void setTargetPosition(Vector3 pos);

    Vector3 getArrowPosition() { return m_arrowPos; }
    float getArrowRadius() { return m_arrowRadius; }


    LabCamera m_camera;
    QTimer m_timer;
    float m_fps;
    float m_increment;
    float m_angleX, m_angleY, m_camAngleX, m_camAngleY;
    bool m_firstPersonMode, m_fired;
    float m_firedAngleX, m_firedAngleY;
    float m_firedXDiff, m_firedZDiff;
    float m_xDiff, m_zDiff;
    int m_score;
    QLabel * m_scoreLabel;
    bool m_canCollide;
    bool m_arrowhit;
    bool m_active;
    GLUquadric *m_quadric;

    TargetLandscape *m_targetLandscape;

    //This vector will automatically contain the arrow's position x,y,z coordinates
    Vector3 m_arrowPos;
    float m_arrowRadius;
    Vector3 m_arrowVel;

    // texture stuff
    GLuint m_texture_backwall;
};

#endif // GLWIDGET_H
