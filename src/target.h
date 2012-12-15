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
    target(Vector3 pos, float rad, Vector3 color);
    ~target();
    void renderTarget();
    void renderTargetSphere(GLUquadric *quadric);
    void setTargetPosition(Vector3 pos);
    bool testCollide(Vector3 arrowPos, float arrowRad);
    Vector3 getTargetPosition() { return m_targetPos; }
    bool getCanCollide() { return m_canCollide; }
    float getRadius() {return m_targetRadius;}
    void setRadius(float rad);
protected:
    Vector3 m_targetPos;
    bool m_canCollide;
    float m_targetRadius;
    Vector3 m_color; // .x represents r, .y represents g, .z represents b

};

#endif // TARGET_H
