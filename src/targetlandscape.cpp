#include "targetlandscape.h"

TargetLandscape::TargetLandscape()
{
    m_quadric = gluNewQuadric();
    target *curtarget = new target(Vector3(0,-1.5f,3.f), 1.f, Vector3(1.0f, 1.f, 1.0f));
    m_targets.push_back(curtarget);
    curtarget = new target(Vector3(0, -.6, 3.f), .3f, Vector3(1.0f, 1.0f, 1.0f));
    m_targets.push_back(curtarget);
    curtarget = new target(Vector3(0, -.3f, 3.f), .3f, Vector3(1.0f, 1.f, 1.0f));
    m_targets.push_back(curtarget);
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

TargetLandscape::renderTargets()
{
    m_target_win->renderTarget(m_quadric);
    if (settings.showIntersectSpheres)
        m_target_win->renderTargetSphere(m_quadric);

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

bool TargetLandscape::testCollide()
{
    //look for a hit, and if we find one, stop the arrow
    int numtargets = m_targets.size();
    for (int i = 0; i < numtargets; i++) {
        target *curtarget = m_targets.at(i);
        if (curtarget->testCollide(m_arrowPos, m_arrowRadius)) {
            m_canCollide = false;

            float3 position = float3(m_arrowPos.x - 3 * m_arrowRadius, m_arrowPos.y - 3 * m_arrowRadius, m_arrowPos.z);
           // m_scoreLabel->setText("Score: " + QString::number(++m_score));
            ParticleEmitter *emitter = new ParticleEmitter(m_texID), position,
                                            float3(1.0f, 1.0f, 1.0f), float3(0.0001f, 0.0001f, 0.0001f),
                                            float3(0.0f, 0.0001f, 0.0f), .6f, 50.0f, 1.f/10000.0f, 50);
            m_emitters.push_back(emitter);

            target *curtarget = new target(m_arrowPos, .3f, Vector3(1.0f, 1.0f, 1.0f));
            m_targets.push_back(curtarget);
            return true;
        }
    }
    return false;
}
