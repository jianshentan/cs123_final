#ifndef TARGETLANDSCAPE_H
#define TARGETLANDSCAPE_H

#include "target.h"
#include "particleemitter.h"
#include <vector>


class TargetLandscape
{
public:
    TargetLandscape(GLuint texID);
    ~TargetLandscape();
    void renderTargets();
    bool testCollide(Vector3 arrowPos, float arrowRad);
protected:
    void initializeGL();
    GLUquadric *m_quadric;
    std::vector<target *> m_targets;
    std::vector<GLuint> m_targettextures;


    target *m_target_win;
    GLuint m_texID;

    // particle stuff
    std::vector<ParticleEmitter *> m_emitters;
};

#endif // TARGETLANDSCAPE_H
