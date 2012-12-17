// this is a test
#include "glwidget.h"
#include "settings.h"
#include <math.h>
#include <iostream>
#include <vector.h>
#include <vector>


#include <stdio.h>
using namespace std;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent), m_timer(this), m_fps(60.0f), m_increment(0), m_angleX(0.0f), m_angleY(0.0f), m_xDiff(0.0f), m_zDiff(0.0f), m_arrowRadius(0.1), m_score(0), m_canCollide(false)
{
    // Set up the camera
    m_camera.eye.x = 0.0f, m_camera.eye.y = 0.0f, m_camera.eye.z = -5.0f;
    m_camera.center.x = 0.0f, m_camera.center.y = 0.0f, m_camera.center.z = 0.0f;
    m_camera.up.x = 0.0f, m_camera.up.y = 1.0f, m_camera.up.z = 0.0f;
    m_camera.fovy = 80.0f, m_camera.near = .5f, m_camera.far = 1000.0f;
    m_camAngleX = 0.f;
    m_camAngleY = 0.f;

    // Set up 60 FPS draw loop
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));
    m_timer.start(1000.0f / m_fps);

    m_arrowPos = Vector3(0,-.5f,-2.f);
    m_arrowhit = false;
    m_fired = false;

    //load textures for environment
    m_texture_backwall = loadTexture(":/textures/beyonce_singleladies_dance.jpg");
}

GLWidget::~GLWidget()
{
    if (m_targetLandscape)
        delete m_targetLandscape;
}



/**
  Method to render the intersection sphere for the arrow
  You need to fill in this method
  **/
void GLWidget::renderArrowSphere()
{
    //TODO: implement this method
    Vector3 arrowPos = getArrowPosition();
    float arrowRadius = getArrowRadius();

    glPushMatrix();
    glTranslatef(arrowPos.x, arrowPos.y, arrowPos.z);
    glScalef(arrowRadius, arrowRadius, arrowRadius);
    glColor3f(1.f, 0.f, 0.f);

    gluSphere(m_quadric, 1.0, 10, 10);

    glPopMatrix();
}

/**
  Called once at GL initialization time to setup OpenGL states
**/
void GLWidget::initializeGL()
{
    // Get a new quadrics obect
    m_quadric = gluNewQuadric();

    // Enable Lighting
    glEnable(GL_LIGHTING);

    //Enable blend
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_TEXTURE_2D);

    // Enable depth testing, so that objects are occluded based on depth instead of drawing order
    glEnable(GL_DEPTH_TEST);

    // Enable back-face culling, meaning only the front side of every face is rendered
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Specify that the front face is represented by vertices in counterclockwise order (this is the default)
    glFrontFace(GL_CCW);

    // Enable color materials with ambient and diffuse lighting terms
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Set up global (ambient) lighting
//    GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    // Create particle emitter
    //m_emitters = NULL;

    glClear(GL_ACCUM_BUFFER_BIT);

    // Set up GL_LIGHT0 with a position and lighting properties
    GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { 2.0f, 2.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    // Set the screen color when the color buffer is cleared (in RGBA format)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Enable light 0
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    // Load the initial settings
    updateSettings();
    updateCamera();

    //load textures for environment
    m_texture_backwall = loadTexture(":/textures/beyonce_singleladies_dance.jpg");
    //m_texture_targets = loadTexture(":/textures/beyonce_teeth.jpg");

    GLuint texIDtarget1 = loadTexture(":/textures/beyonce_texture1.jpg");
    GLuint texIDtarget2 = loadTexture(":/textures/beyonce_texture2.jpg");
    GLuint texIDtarget3 = loadTexture(":/textures/beyonce_texture3.jpg");
    GLuint texIDtarget4 = loadTexture(":/textures/beyonce_texture4.jpg");

    m_targetLandscape = new TargetLandscape(loadTexture(":/textures/beyonceface.bmp"), texIDtarget1, texIDtarget2, texIDtarget3, texIDtarget4);
}

GLuint GLWidget::loadTexture(const QString &path)
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
  The main drawing method which will be called 30 frames per second.  Here
  is where your OpenGL drawing should occur.
**/
void GLWidget::paintGL()
{
    // Get the time
    float time = m_increment++ / (float) m_fps;


    //if we haven't fired yet, update the angles so that the arrow's angles and position match the cameras
    if(!m_fired)
    {
        m_firedAngleX = m_angleX;
        m_firedAngleY = m_angleY;
        m_firedXDiff = m_xDiff;
        m_firedZDiff = m_zDiff;
    }


    // Clear the color and depth buffers to the current glClearColor
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    makeEnvironment();
    glPushMatrix();
    m_targetLandscape->renderTargets();

    glPushMatrix();
    //transform to get to camera coordinates to render the arrow
    glTranslatef(-m_xDiff, 0.0f, -m_zDiff);
    glRotatef(m_angleY, cos(M_PI*m_angleX / 180), 0.0f, sin(M_PI*m_angleX/180));
    glRotatef(-m_angleX, 0.0f, 1.0f, 0.0f);

    glRotatef(15, 0.0f, 1.0f, 0.0f);

    glTranslatef(-0.8f, 0.5f, -2.5f);
    glScalef(2.5f, 2.5f, 2.5f);
    //renderBow();

    glPopMatrix();
    glPushMatrix();

    //start arrow off at fired position i.e. camera position when the arrow was fired or current camera position if it hasn't been fired
    //set the velocity to reflect the rotation transforms we do to render the arrow
    //we keep variables for all the values we need for this to simplify the velocity vector


    //move the arrow's position based on velocity and time

    if (m_fired) {
        m_arrowVel.y -= time * .01f;
        m_arrowPos += .1f*m_arrowVel;
    }

    //look for a hit, and if we find one, stop the arrow


    if (m_canCollide && !m_arrowhit) {
        if (m_targetLandscape->testCollide(m_arrowPos, m_arrowRadius)) {
            m_arrowhit = true;
            m_canCollide = false;
        }
    }
    if (!m_arrowhit)
        renderArrowSphere();
    glPopMatrix();

}


/**
  Renders the bow object
  **/
void GLWidget::renderBow(){
    glColor3f(0.37f, 0.15f, 0.02f);
    glTranslatef(0.0, 0.0, 1.0f);
    glPushMatrix();
    glScalef(.01f, 0.5f, .01f);

    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluCylinder(m_quadric, 1.0f, 1.0f, 1.0f, 10, 10);
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, -0.125f, 0.21f);
    glScalef(.01f, 0.5f, .01f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluCylinder(m_quadric, 1.0f, 1.0f, 0.5f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glRotatef(30, 1.0f, 0.0f, 0.0f);
    glScalef(.01f, 0.01f, .5f);
    gluCylinder(m_quadric, 1.0f, 1.0f, 0.5f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    glRotatef(-30, 1.0f, 0.0f, 0.0f);
    glScalef(.01f, 0.01f, .5f);
    gluCylinder(m_quadric, 1.0f, 1.0f, 0.5f, 10, 10);
    glPopMatrix();
}

/**
  renders a quad that is visible from both front and back
  **/
void GLWidget::renderQuad(GLuint textureID)
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);

    glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);

    glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
        glTexCoord2f(0.f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(1.f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

}

/**
  Called when the screen gets resized.
  The camera is updated when the screen resizes because the aspect ratio may change.
**/
void GLWidget::resizeGL(int width, int height)
{
    // Set the viewport to fill the screen
    glViewport(0, 0, width, height);
    // Update the camera
    updateCamera();
}

/**
  Update the camera's specifications.
  It gets called in resizeGL which get called automatically on intialization
  and whenever the window is resized.
**/
void GLWidget::updateCamera()
{
    float w = width();
    float h = height();
    float aspectRatio = 1.0f * w / h;
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_camera.fovy, aspectRatio, m_camera.near, m_camera.far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(m_camera.eye.x, m_camera.eye.y, m_camera.eye.z,
              m_camera.center.x, m_camera.center.y, m_camera.center.z,
              m_camera.up.x, m_camera.up.y, m_camera.up.z);
    //rotate and translate for fps controls
    glRotatef(m_camAngleX, 0.0f, 1.0f, 0.0f);
    //glRotatef(-m_camAngleY, cos(M_PI*m_camAngleX/180), 0.0f, sin(M_PI*m_camAngleX/180));
    glTranslatef(m_xDiff, 0.0f, m_zDiff);
}

/**
  This method handles key press events to allow for movement
  **/
void GLWidget::keyPressEvent ( QKeyEvent * event )
{
    //we adjust how we move by what angle we're currently facing
    double cx = cos(-m_angleX * M_PI/180);
    double sx = sin(-m_angleX * M_PI/180);
    if(event->key() == Qt::Key_W)
    {
        m_angleY -= 2.5f;
        this->update();
    }
    else if(event->key() == Qt::Key_S)
    {
        m_angleY += 2.5f;
        this->update();
    }
    else if(event->key() == Qt::Key_D)
    {
        m_angleX += 2.5f;
        this->update();
    }
    else if(event->key() == Qt::Key_A)
    {
        m_angleX -= 2.5f;
        this->update();
    }


    else if(event->key() == Qt::Key_Escape)
    {
        m_firstPersonMode = false;
    }

    else if(event->key() == Qt::Key_Left)
    {
        m_camAngleX -= 2.f;
        updateCamera();
    }

    else if(event->key() == Qt::Key_Right)
    {
        m_camAngleX += 2.f;
        updateCamera();
    }
}

/**
  This method handles mouse movement events for camera rotation
  **/
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    /*if(m_firstPersonMode) {
        if(m_originalMouseX < 0 && m_originalMouseY < 0)
        {
            m_originalMouseX = event->globalX() - event->x() + this->width()/2;
            m_originalMouseY = event->globalY() - event->y() + this->height()/2;
            //QCursor::setPos(m_originalMouseX, m_originalMouseY);
        }
        else
        {
            float x = event->globalX();
            float y = event->globalY();
            rotateCamera(x - m_originalMouseX, y-m_originalMouseY);
            update();
            //QCursor::setPos(m_originalMouseX, m_originalMouseY);
        }
        update();
    }*/
}

/**
  This method handles click events. It enters first person mode if the user isn't in first person mode,
  shoots an arrow if the user has an arrow to shoot and picks up an arrow if the user has none
  **/
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(!m_firstPersonMode){
        m_firstPersonMode = true;
    }
    else {
        m_arrowhit = false;
        m_canCollide = true;
        m_fired = true;
        m_increment = 0.0f;
        m_arrowPos =  Vector3(-2.f*sin(-m_camAngleX*M_PI/180.f), -.5f, -2.f*cos(-m_camAngleX*M_PI/180.f));
        double cx = cos(-m_angleX * M_PI/180);
        double sx = sin(-m_angleX * M_PI/180);
        double cy = cos(m_angleY * M_PI/180);
        double omcy = 1.0-cy;
        double sy = sin(m_angleY * M_PI/180);

        double cmx = cos(M_PI*m_angleX/180);
        double smx = sin(M_PI*m_angleX/180);

        //calculates through the rotates done to get an accurate velocity vector
        m_arrowVel = Vector3(.5f*((sx*((cmx*cmx*omcy) + cy)) + (cx*cmx*smx*omcy)),
                              .5f*((sx*smx*sy) - (cx*cmx*sy)),
                              .5f*((sx*cmx*smx*omcy) + (cx*((smx*smx*omcy) + cy))));
        update();
    }

}

/**
  Called when the settings are updated through the UI.
  This is already filled in for you.
**/
void GLWidget::updateSettings()
{
    update();
}

/**
  Allows the ui to set the label to be modified to update score
  **/
void GLWidget::setLabel(QLabel* label)
{
    m_scoreLabel = label;
}

/**
  Specifies to Qt what to do when the widget needs to be updated.
  We only want to repaint the onscreen objects.
**/
void GLWidget::tick()
{
    update();
}

void GLWidget::makeEnvironment()
{

    //render the walls, floor and ceiling of our playing field
    glColor3f(1.f, 1.f, 1.f);
    /* back wall */
    glPushMatrix();
    glTranslatef(-5.0f, -1.0f, 5.0f);
    glScalef(10.0f, 6.5f, 10.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    renderQuad(m_texture_backwall);
    glPopMatrix();

    /* front wall*/
//    glPushMatrix();
//    glTranslatef(-5.0f, -1.0f, -3.0f);
//    glScalef(10.0f, 10.0f, 10.0f);
//    glRotatef(90, 0.0f, 1.0f, 0.0f);
//    renderQuad(m_texture_backwall);
//    glPopMatrix();

    /* right wall */
    glPushMatrix();
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glTranslatef(-5.0f, 9.0f, -3.0f);
    glScalef(10.0f, 10.0f, 10.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    renderQuad(m_texture_backwall);
    glPopMatrix();

    /* left wall */
    glPushMatrix();
    glTranslatef(5.0f, 9.0f, -3.0f);
    glScalef(10.0f, 10.0f, 10.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    renderQuad(m_texture_backwall);
    glPopMatrix();

    /* not in sight */
//    glPushMatrix();
//    glTranslatef(5.0f, 5.0f, -3.0f);
//    glScalef(10.0f, 10.0f, 10.0f);
//    glRotatef(90, 0.0f, 0.0f, 1.0f);
//    renderQuad();
//    glPopMatrix();

    /* floor */
    glPushMatrix();
    glTranslatef(5.0f, -1.0f, -3.0f);
    glScalef(10.0f, 10.0f, 10.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    renderQuad(m_texture_backwall);
    glPopMatrix();

}
