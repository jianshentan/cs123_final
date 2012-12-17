#ifndef TARGETLANDSCAPE_H
#define TARGETLANDSCAPE_H

#include "target.h"
#include "particleemitter.h"
#include <vector>

using namespace std;
class TargetLandscape
{
public:
    TargetLandscape(GLuint texID, GLuint targetTexture1, GLuint targetTexture2, GLuint targetTexture3, GLuint targetTexture4);
    ~TargetLandscape();
    void renderTargets();
    bool testCollide(Vector3 arrowPos, float arrowRad);
    //billboarding
    void billboardCheatCylindricalBegin();
    void billboardEnd();
    //win condition
    bool get_win_state();


protected:
    void initializeGL();
    GLUquadric *m_quadric;
    std::vector<target *> m_targets;
    std::vector<GLuint> m_targettextures;


    target *m_target_win;
    GLuint m_texID;

    // particle stuff
    std::vector<ParticleEmitter *> m_emitters;

    bool m_win;
};

#endif // TARGETLANDSCAPE_H
