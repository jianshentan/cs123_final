#ifndef TARGETLANDSCAPE_H
#define TARGETLANDSCAPE_H

#include "target.h"
#include "particleemitter.h"
#include <vector>


class TargetLandscape
{
public:
    TargetLandscape();
    ~TargetLandscape();
    void renderTargets();
    bool testCollide();
protected:
    void initializeGL();
    GLUquadric *m_quadric;
    std::vector<target *> m_targets;
    target *m_target_win;

    // particle stuff
    std::vector<ParticleEmitter *> m_emitters;
};

#endif // TARGETLANDSCAPE_H
