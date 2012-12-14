#include "particleemitter.h"

ParticleEmitter::ParticleEmitter(GLuint textureId, float3 color, float3 velocity,
                                 float3 force, float scale, float fuzziness, float speed,
                                 unsigned maxParticles) :
                    m_maxParticles(maxParticles), m_textureID(textureId), m_speed(speed),
                    m_fuzziness(fuzziness), m_scale(scale), m_color(color), m_velocity(velocity),
                    m_force(force)
{
    m_particles = new Particle[maxParticles];
    resetParticles();


    for (unsigned i = 0; i < m_maxParticles; ++i)
        m_particles[i].active = false;
}

ParticleEmitter::~ParticleEmitter()
{
    if (m_particles)
    {
        delete[] m_particles;
        m_particles = 0;
    }
    glDeleteTextures(1, &m_textureID);

}

/**
  * You need to fill this in.
  *
  * Resets the particle at the given index to its initial state. Should reset the
  * position, direction, force, color, life, and decay of the particle.
  */
void ParticleEmitter::resetParticle(unsigned i)
{
    m_particles[i].pos.zero();
    m_particles[i].life = 1.0f;
    m_particles[i].decay = urand(.0025f, .15f);
    m_particles[i].color = m_color;
    m_particles[i].force.x = urand(-m_fuzziness*.01f, (m_fuzziness*.01f + m_force.x));
    m_particles[i].force.y = urand(-m_fuzziness*.01f, (m_fuzziness*.01f + m_force.y));
    m_particles[i].force.z = urand(-m_fuzziness*.01f, (m_fuzziness*.01f + m_force.z));
    m_particles[i].dir.x = urand(-m_fuzziness, m_fuzziness + m_velocity.x);
    m_particles[i].dir.y = urand(-m_fuzziness, m_fuzziness + m_velocity.y);
    m_particles[i].dir.z = urand(-m_fuzziness, m_fuzziness + m_velocity.z);
}

/**
  * Resets all particles in this emitter to their initial states
  */
void ParticleEmitter::resetParticles()
{
    for (unsigned i = 0; i < m_maxParticles; i++)
        resetParticle(i);
}

/**
  * You need to fill this in.
  *
  * Performs one step of the particle simulation. Should perform all physics
  * calculations and maintain the life property of each particle.
  */
void ParticleEmitter::updateParticles()
{
    for(unsigned i = 0; i < m_maxParticles; ++i)
    {
        if (!m_particles[i].active) {
            m_particles[i].active = true;
            resetParticle(i);
        } else {
            Particle *cur = &(m_particles[i]);
            cur->pos.x += cur->dir.x * m_speed;
            cur->pos.y += cur->dir.y * m_speed;
            cur->pos.z += cur->dir.z * m_speed;
            cur->dir.x += cur->force.x;
            cur->dir.y += cur->force.y;
            cur->dir.z += cur->force.z;
            cur->life -= cur->decay;
            if (cur->life < 0)
                cur->active = false;
        }
    }
}

/**
  * You need to fill this in.
  *
  * Draws each particle as a small, texture-mapped square of side-length m_scale.
  * Each square should be in the X/Y plane at Z = the particle's position's Z-coordinate.
  */
void ParticleEmitter::drawParticles()
{
    //Put your code here
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glBegin(GL_QUADS);

    for(unsigned i = 0; i < m_maxParticles; ++i)
    {
        Particle *cur = &(m_particles[i]);
        glColor4f(float(cur->color.r), float(cur->color.g), float(cur->color.b), float(sqrt(cur->life)));

        glTexCoord2f(0.f, 1.f);
        glVertex3f(cur->pos.x, cur->pos.y, cur->pos.z);

        glTexCoord2f(1.f, 1.f);
        glVertex3f(cur->pos.x + m_scale, cur->pos.y, cur->pos.z);

        glTexCoord2f(1.f, 0.f);
        glVertex3f(cur->pos.x + m_scale, cur->pos.y + m_scale, cur->pos.z);

        glTexCoord2f(0.f, 0.f);
        glVertex3f(cur->pos.x, cur->pos.y + m_scale, cur->pos.z);

    }
    glEnd();

}
