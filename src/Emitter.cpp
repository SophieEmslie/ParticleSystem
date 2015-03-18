#include "Emitter.h"
#include <ngl/Random.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>




Emitter::Emitter(ngl::Vec3 _pos, int _numParticles)
{
    m_particles.resize(_numParticles);
    m_numberParticles=_numParticles;
    m_position=_pos;
    ngl::Random *rng=ngl::Random::instance();
    Particle p;
    for(int i=0; i<m_numberParticles; ++i)
    {
        p.life=0;
        p.maxLife=rng->randomPositiveNumber(100)+5;
        p.pos=m_position;
        p.dir=rng->getRandomNormalizedVec3();
        p.colour.set(
                      rng->randomPositiveNumber(1.0),
                      rng->randomPositiveNumber(1.0),
                      rng->randomPositiveNumber(1.0)
                    );
        m_particles[i]=p;
    }
}

void Emitter::draw() const
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    ngl::Transformation t;
    ngl::Mat4 MVP;
    shader ->use ("nglColourShader");

    for (int i=0; i<m_numberParticles; i++)
    {
    t.setPosition(m_particles[i].pos);
    t.setScale(0.1,0.1,0.1);
    MVP=t.getMatrix() * m_camera->getVPMatrix();
    shader->setShaderParamFromMat4("MVP", MVP);
    shader->setShaderParam4f("Colour",
                             m_particles[i].colour.m_x,
                             m_particles[i].colour.m_y,
                             m_particles[i].colour.m_z,
                             1.0f
                             );

    ngl::VAOPrimitives::instance()->draw("cube");

    }
}


void Emitter::update()
{
    ngl::Random *rng = ngl::Random::instance();
    for (int i=0; i <m_numberParticles; ++i)
    {
        m_particles[i].pos+=m_particles[i].dir;

        if(++m_particles[i].life > m_particles[i].maxLife)

        {
            //m_particles[i].pos.m_x=cos(ngl::radians(m_particles[i].rot))*15;
            m_particles[i].pos.set(m_position);
            m_particles[i].life=0;
            m_particles[i].maxLife=rng->randomPositiveNumber(100)+5;
            m_particles[i].pos=m_position;
            m_particles[i].dir=rng->getRandomNormalizedVec3();
            m_particles[i].colour.set(
                          rng->randomPositiveNumber(1.0),
                          rng->randomPositiveNumber(1.0),
                          rng->randomPositiveNumber(1.0)
                        );
        }
    }
}


