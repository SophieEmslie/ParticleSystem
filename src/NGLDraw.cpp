#include "NGLDraw.h"
#include <ngl/ShaderLib.h>
#include <ngl/NGLInit.h>

NGLDraw::NGLDraw()
{

  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
   // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  m_emitter = new Emitter(ngl::Vec3(0,0,0),500);

  m_camera = new ngl::Camera(ngl::Vec3(20,20,20),
                             ngl::Vec3(0,0,0),
                             ngl::Vec3(0,1,0));

  m_camera->setShape(45.0f,1.2,0.01,500);
  m_emitter->setCamera(m_camera);

}

NGLDraw::~NGLDraw()
{
  ngl::NGLInit *Init = ngl::NGLInit::instance();
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  Init->NGLQuit();
}

void NGLDraw::resize(int _w, int _h)
{
  glViewport(0,0,_w,_h);
}

void NGLDraw::draw()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_emitter->update();
  m_emitter->draw();
}


//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::mouseMoveEvent (const SDL_MouseMotionEvent &_event)
{
}


//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::mousePressEvent (const SDL_MouseButtonEvent &_event)
{
}

//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::mouseReleaseEvent (const SDL_MouseButtonEvent &_event)
{
}

//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::wheelEvent(const SDL_MouseWheelEvent &_event)
{

}
//----------------------------------------------------------------------------------------------------------------------
