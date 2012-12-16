#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>
#include "camera.h"
#include "particleemitter.h"
#include "target.h"
#include <vector>

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



protected slots:
    void tick();

private:
    void renderTarget();
    void renderTargetSphere();
    void renderArrowSphere();

    void renderQuad();
    void renderArrow();
    void renderBow();
    void setTargetPosition(Vector3 pos);
    //Vector3 getTargetPosition() { return m_targetPos; }
    Vector3 getArrowPosition() { return m_arrowPos; }
    //float getTargetRadius() { return m_targetRadius; }
    float getArrowRadius() { return m_arrowRadius; }


    GLUquadric *m_quadric;
    LabCamera m_camera;
    QTimer m_timer;
    float m_fps;
    float m_increment;
    float m_angleX, m_angleY;
    float m_originalMouseX;
    float m_originalMouseY;
    bool m_firstPersonMode, m_fired;
    float m_firedAngleX, m_firedAngleY;
    float m_firedXDiff, m_firedZDiff;
    float m_xDiff, m_zDiff;
    int m_score;
    QLabel * m_scoreLabel;
    bool m_canCollide;

    bool m_arrowhit;
    bool m_active;

    //This vector will automatically contain the arrow's position x,y,z coordinates
    Vector3 m_arrowPos;
    float m_arrowRadius;
    Vector3 m_arrowVel;

    //This vector will be initialized to 0,0,0. You will need to set it in the renderTarget method

    std::vector<target *> m_targets;

    // particle stuff
    ParticleEmitter *m_emitter;


};

#endif // GLWIDGET_H
