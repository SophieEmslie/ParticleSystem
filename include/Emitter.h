#ifndef EMITTER_H__
#define EMITTER_H__
#include <ngl/Vec3.h>
#include <vector>
#include <ngl/Camera.h>


class Emitter
{

public:
    Emitter(ngl::Vec3 _pos, int _numberParticles);
    void draw() const;
    void update();
    void setCamera(ngl::Camera *_cam){m_camera = _cam; }


private:

    typedef struct
    {
        int life;
        ngl::Vec3 dir;
        ngl::Vec3 colour;
        ngl::Vec3 pos;
        int maxLife;
        float rot;

    }Particle;

    std::vector<Particle> m_particles;

    int m_numberParticles;
    ngl::Vec3 m_position;

    ngl::Camera *m_camera;

};


#endif
