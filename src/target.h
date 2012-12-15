#ifndef TARGET_H
#define TARGET_H
#include <QGLWidget>
#include <vector.h>


class target
{
public:
    target();
    ~target();
    void renderTarget();
    void renderTargetSphere(GLUquadric *quadric);
    void setTargetPosition(Vector3 pos);
    Vector3 getTargetPosition() { return m_targetPos; }
    bool getCanCollide() { return m_canCollide; }
    float getRadius() {return m_targetRadius;}
    void setRadius(float rad);
protected:
    Vector3 m_targetPos;
    bool m_canCollide;
    float m_targetRadius;

};

#endif // TARGET_H
