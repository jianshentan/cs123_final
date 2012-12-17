#include "targetlandscape.h"
#include "settings.h"

TargetLandscape::TargetLandscape(GLuint texID)
{
    /*GLuint texIDtarget;
    texIDtarget = loadTexture(":/textures/beyonce_target1.jpg");
    m_targettextures.push_back(texIDtarget);
    texIDtarget = loadTexture(":/textures/beyonce_target2.jpg");
    m_targettextures.push_back(texIDtarget);
    texIDtarget = loadTexture(":/textures/beyonce_target3.jpg");
    m_targettextures.push_back(texIDtarget);
    texIDtarget = loadTexture(":/textures/beyonce_target4.jpg");
    m_targettextures.push_back(texIDtarget);
*/

    m_texID = texID;
    m_quadric = gluNewQuadric();
    target *curtarget = new target(Vector3(0,-1.5f,3.f), 1.f, Vector3(1.0f, 1.f, 1.0f), m_texID);
    m_targets.push_back(curtarget);
    curtarget = new target(Vector3(0, -.6, 3.f), .3f, Vector3(1.0f, 1.0f, 1.0f), m_texID);
    m_targets.push_back(curtarget);
    curtarget = new target(Vector3(0, -.3f, 3.f), .3f, Vector3(1.0f, 1.f, 1.0f), m_texID);
    m_targets.push_back(curtarget);

    //choose random texture image

//    int randNum = rand() % 4 + 1; //gets rand number between 1 and 4
//    GLuint texID;
//    switch (randNum)
//    {
//        case 1:
//            texID = loadTexture(":/textures/beyonce_target1.jpg");
//            break;
//        case 2:
//            texID = loadTexture(":/textures/beyonce_target2.jpg");
//            break;
//        case 3:
//            texID = loadTexture(":/textures/beyonce_target3.jpg");
//            break;
//        case 4:
//            texID = loadTexture(":/textures/beyonce_target4.jpg");
//            break;

//    }

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
    for (int i = 0; i < numtargets; i++) {
        target *curtarget = m_targets.at(i);
        if (curtarget->testCollide(arrowPos, arrowRad)) {

            float3 position = float3(arrowPos.x - 3 * arrowRad, arrowPos.y - 3 * arrowRad, arrowPos.z);
            // m_scoreLabel->setText("Score: " + QString::number(++m_score));
            ParticleEmitter *emitter = new ParticleEmitter(m_texID, position,
                                            float3(1.0f, 1.0f, 1.0f), float3(0.0001f, 0.0001f, 0.0001f),
                                            float3(0.0f, 0.0001f, 0.0f), .6f, 50.0f, 1.f/10000.0f, 50);
            m_emitters.push_back(emitter);

            target *curtarget = new target(arrowPos, .3f, Vector3(1.0f, 1.0f, 1.0f), m_texID);
            m_targets.push_back(curtarget);
            return true;
        }
    }
    return false;
}
