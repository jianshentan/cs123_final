#include "targetlandscape.h"
#include "settings.h"
#include <vector>

TargetLandscape::TargetLandscape(GLuint texID, GLuint targetTexture1, GLuint targetTexture2, GLuint targetTexture3, GLuint targetTexture4)
{
    m_texID = texID;
    m_quadric = gluNewQuadric();

    target *curtarget;
    int randNum;
    GLuint targetTexture;
    for (int b = 0; b < 3 ; b++)
    {
        for (int a = 0; a < 5 ; a++)
        {
            randNum = rand() % 4 + 1;
            if (randNum == 1) targetTexture = targetTexture1;
            else if (randNum == 2) targetTexture = targetTexture2;
            else if (randNum == 3) targetTexture = targetTexture3;
            else if (randNum == 4) targetTexture = targetTexture4;
            curtarget = new target(Vector3(-1.0f,-0.6f + b*0.5f,0.5f + a*0.5f), 0.2f, Vector3(1.0f, 1.f, 1.0f), targetTexture);
            m_targets.push_back(curtarget);

            randNum = rand() % 4 + 1;
            if (randNum == 1) targetTexture = targetTexture1;
            else if (randNum == 2) targetTexture = targetTexture2;
            else if (randNum == 3) targetTexture = targetTexture3;
            else if (randNum == 4) targetTexture = targetTexture4;
            curtarget = new target(Vector3(-0.5f,-0.6f + b*0.5f,0.5f + a*0.5f), 0.2f, Vector3(1.0f, 1.f, 1.0f), targetTexture);
            m_targets.push_back(curtarget);

            randNum = rand() % 4 + 1;
            if (randNum == 1) targetTexture = targetTexture1;
            else if (randNum == 2) targetTexture = targetTexture2;
            else if (randNum == 3) targetTexture = targetTexture3;
            else if (randNum == 4) targetTexture = targetTexture4;
            curtarget = new target(Vector3(0,-0.6f + b*0.5f,0.5f + a*0.5f), 0.2f, Vector3(1.0f, 1.f, 1.0f), targetTexture);
            m_targets.push_back(curtarget);

            randNum = rand() % 4 + 1;
            if (randNum == 1) targetTexture = targetTexture1;
            else if (randNum == 2) targetTexture = targetTexture2;
            else if (randNum == 3) targetTexture = targetTexture3;
            else if (randNum == 4) targetTexture = targetTexture4;
            curtarget = new target(Vector3(0.5f,-0.6f + b*0.5f,0.5f + a*0.5f), 0.2f, Vector3(1.0f, 1.f, 1.0f), targetTexture);
            m_targets.push_back(curtarget);

            randNum = rand() % 4 + 1;
            if (randNum == 1) targetTexture = targetTexture1;
            else if (randNum == 2) targetTexture = targetTexture2;
            else if (randNum == 3) targetTexture = targetTexture3;
            else if (randNum == 4) targetTexture = targetTexture4;
            curtarget = new target(Vector3(1.0f,-0.6f + b*0.5f,0.5f + a*0.5f), 0.2f, Vector3(1.0f, 1.f, 1.0f), targetTexture);
            m_targets.push_back(curtarget);
        }
    }
}

TargetLandscape::~TargetLandscape()
{
    gluDeleteQuadric(m_quadric);
    int numtargets = m_targets.size();
    for (int i = 0; i < numtargets; i++) {
        target *curtarget = m_targets.at(i);
        delete curtarget;
    }
    //backup emitter destroyer:
    for (int i = 0; i < m_emitters.size() ; i++)
    {
        delete m_emitters[i];
    }

}

void TargetLandscape::renderTargets()
{
    glPushMatrix();
    int numtargets = m_targets.size();
    for (int i = 0; i < numtargets; i++) {
        target *curtarget = m_targets.at(i);
        curtarget->renderTarget(m_quadric);
        if (settings.showIntersectSpheres)
            curtarget->renderTargetSphere(m_quadric);
    }
    glPopMatrix();

    for (int i = 0 ; i < m_emitters.size() ; i++)
    {
        if (m_emitters[i])
            m_emitters[i]->updateParticles();         //Draw the particles
    }

    /* PARTICLES */
    for (int i = 0 ; i < m_emitters.size() ; i++)
    {
        if (m_emitters[i]) {
//            if (m_emitters[i]->check_for_termination())
//                //terminate
//            {
//                delete m_emitters[i];
//                break;
//            }
//            else
//            {
                glDepthMask(GL_FALSE);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);

                m_emitters[i]->drawParticles();         //Draw the particles

                //  create trailers
                glAccum(GL_MULT, .5f);
                glAccum(GL_ACCUM, .5f);
                glAccum(GL_RETURN, 1.f);

                glDepthMask(GL_TRUE);
                //glFlush();
                glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
                //swapBuffers();
                //glDepthMask(GL_TRUE);
//            }
        }
    }
}

bool TargetLandscape::testCollide(Vector3 arrowPos, float arrowRad)
{
    //look for a hit, and if we find one, stop the arrow
    int numtargets = m_targets.size();
    for (int i = 0; i < numtargets; i++)
    {
        target *curtarget = m_targets.at(i);
        if (curtarget->testCollide(arrowPos, arrowRad))
        {

            float3 position;
            position.x = curtarget->getTargetPosition().x - curtarget->getRadius();//float3(arrowPos.x - 3 * arrowRad, arrowPos.y - 3 * arrowRad, arrowPos.z);
            position.y = curtarget->getTargetPosition().y - curtarget->getRadius();
            position.z = curtarget->getTargetPosition().z - curtarget->getRadius();
            // m_scoreLabel->setText("Score: " + QString::number(++m_score));
            ParticleEmitter *emitter = new ParticleEmitter(m_texID, position,
                                            float3(1.0f, 1.0f, 1.0f), float3(0.0001f, 0.0001f, 0.0001f),
                                            float3(0.0f, 0.0001f, 0.0f), .6f, 50.0f, 1.f/10000.0f, 50);
            m_emitters.push_back(emitter);

            //target *curtarget = new target(arrowPos, .3f, Vector3(1.0f, 1.0f, 1.0f), m_texID);
            //m_targets.push_back(curtarget);

            m_targets.erase(m_targets.begin() + i);

            return true;
        }
    }
    return false;
}
