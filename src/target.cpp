#include "target.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <QLabel>
using namespace std;

target::target(Vector3 pos, float rad, Vector3 color)
{
    m_canCollide = false;
    m_targetPos = pos;
    m_targetRadius = 0.f;
    m_radius = rad;
    m_color = color;

    //choose random texture image

    int randNum = rand() % 4 + 1; //gets rand number between 1 and 4
    GLuint texID;
    switch (randNum)
    {
        case 1:
            texID = loadTexture(":/textures/beyonce_target1.jpg");
            break;
        case 2:
            texID = loadTexture(":/textures/beyonce_target2.jpg");
            break;
        case 3:
            texID = loadTexture(":/textures/beyonce_target3.jpg");
            break;
        case 4:
            texID = loadTexture(":/textures/beyonce_target4.jpg");
            break;

    }
    m_texID = texID;

}

target::~target()
{
}


GLuint target::loadTexture(const QString &path)
{
    QFile file(path);

    QImage image, texture;
    if(!file.exists()) { return -1; }
    image.load(file.fileName());
    texture = QGLWidget::convertToGLFormat(image);
    //Put your code here
    GLuint id = 0;
    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return id;
}

/**
  Renders the target and sets its position and size via m_targetPos and m_targetRadius
  You have to fill in this method
  **/
void target::renderTarget(GLUquadric *quadric)
{
    glPushMatrix();
    glColor3f(m_color.x, m_color.y, m_color.z);
    glTranslatef(m_targetPos.x, m_targetPos.y, m_targetPos.z);
    glScalef(m_targetRadius, m_targetRadius, m_targetRadius);

    if (m_targetRadius < m_radius)
        m_targetRadius += .01f;
    else
        m_targetRadius = m_radius;

    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_texID);
    gluSphere(quadric, 1.0, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}


/**
  Method to render the intersection sphere for the target
  You need to fill in this method
  **/
void target::renderTargetSphere(GLUquadric *quadric)
{
    //TODO: implement this method

    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.f, 0.f, 0.f);
    glTranslatef(m_targetPos.x, m_targetPos.y, m_targetPos.z);
    glScalef(m_targetRadius, m_targetRadius, m_targetRadius);



    gluSphere(quadric, 1.0, 15, 15);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
}

/**
  Sets the position of the target, and notifies the system that we are ready to attempt collisions
  **/
//void target::setTargetPosition(Vector3 pos)
//{
//    m_canCollide = true;
//    m_targetPos = pos;
//}

void target::setRadius(float rad)
{
    m_targetRadius = rad;
}

bool target::testCollide(Vector3 arrowPos, float arrowRad)
{
    if ((arrowPos - m_targetPos).length() < arrowRad + m_targetRadius)
        return true;
    else
        return false;
}
