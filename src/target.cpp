#include "target.h"

target::target()
{
    m_canCollide = false;
    m_targetPos = Vector3(0, 0, 0);
}

target::~target()
{
}


/**
  Renders the target and sets its position and size via m_targetPos and m_targetRadius
  You have to fill in this method
  **/
void target::renderTarget()
{
    //TODO: implement this method
    glPushMatrix();

    glTranslatef(0, 0, 3);

    glBegin(GL_TRIANGLES);

    float a = 10;

    for (int i = 0; i < a ; i++)
    {
        glVertex3f(0.5 * cos ((i + 1) * (2 * M_PI)/a), 0.5 * sin ((i + 1) * (2 * M_PI/a)), 0);
        glVertex3f(0.5 * cos (i * (2 * M_PI)/a), 0.5 * sin (i * (2 * M_PI/a)),0);
        glVertex3f(0, 0, 0);
    }

    glEnd();

    glPopMatrix();

    setTargetPosition(Vector3(0, 0, 3));

}


/**
  Method to render the intersection sphere for the target
  You need to fill in this method
  **/
void target::renderTargetSphere(GLUquadric *quadric)
{
    //TODO: implement this method

    glPushMatrix();
    glTranslatef(m_targetPos.x, m_targetPos.y, m_targetPos.z);
    glScalef(m_targetRadius, m_targetRadius, m_targetRadius);

    gluSphere(quadric, 1.0, 10, 10);

    glPopMatrix();
}

/**
  Sets the position of the target, and notifies the system that we are ready to attempt collisions
  **/
void target::setTargetPosition(Vector3 pos)
{
    m_canCollide = true;
    m_targetPos = pos;
}

void target::setRadius(float rad) {
    m_targetRadius = rad;
}