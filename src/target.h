#ifndef TARGET_H
#define TARGET_H
#include <QGLWidget>
#include <vector.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <QLabel>


class target
{
public:
    target(Vector3 pos, float rad, Vector3 color, GLuint texID, float rotAngle);
    ~target();
    void renderTarget(GLUquadric *quadric);
    void renderTargetSphere(GLUquadric *quadric);
    void setTargetPosition(Vector3 pos);
    virtual bool testCollide(Vector3 arrowPos, float arrowRad);
    Vector3 getTargetPosition() { return m_targetPos; }
    bool getCanCollide() { return m_canCollide; }
    float getRadius() {return m_targetRadius;}
    void setRadius(float rad);
protected:
    Vector3 m_targetPos;
    bool m_canCollide;
    float m_targetRadius;
    float m_radius;
    GLuint m_texID;
    Vector3 m_color; // .x represents r, .y represents g, .z represents b
    float m_rotAngle;

};

#endif // TARGET_H
