#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cuda_runtime.h>
#include "cudagl_widget.hpp"

//#include <cutil_gl_inline.h>
//#include <cutil_gl_error.h>
#include <cuda_gl_interop.h>


#include <qapplication.h>
#include <qtimer.h>
#include <QKeyEvent>

extern void createVertices(void * positions, float time,
  unsigned int width, unsigned int height);

cudagl_widget::cudagl_widget(int timerInterval, QWidget *parent, char *name) : 
  QGLWidget(parent)
{
  time = 0.0;
  cudaGLSetGLDevice(0);
  
  makeCurrent();
	glewInit();
  
  

  
}

void cudagl_widget::keyPressEvent(QKeyEvent *e)
{
	switch(e->key())
	{
    case Qt::Key_Escape:
    {
      paintGL();
      break;
    }
  }
}

void cudagl_widget::timeOut()
{
  
}

void cudagl_widget::timeOutSlot()
{
  
}

void cudagl_widget::initializeGL()
{

  
  glShadeModel(GL_SMOOTH);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
  glGenBuffers(1, &positionsVBO);
  glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
  unsigned int size = 256 * 256 * 4 * sizeof(float);
  glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  cudaGraphicsGLRegisterBuffer(&positionsVBO_CUDA,
    positionsVBO, cudaGraphicsMapFlagsWriteDiscard);
    
}

void cudagl_widget::resizeGL( int width, int height )
{
  height = height?height:1;

  glViewport( 0, 0, (GLint)width, (GLint)height );

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void cudagl_widget::paintGL()
{
  void * positions;
  cudaGraphicsMapResources(1, &positionsVBO_CUDA, 0);
  size_t num_bytes;
  cudaGraphicsResourceGetMappedPointer((void**)&positions, &num_bytes, positionsVBO_CUDA);
  
  createVertices(positions, time, 256, 256);
  
  // Unmap buffer object
  cudaGraphicsUnmapResources(1, &positionsVBO_CUDA, 0);
  // Render from buffer object
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
  glVertexPointer(4, GL_FLOAT, 0, 0);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_POINTS, 0, 256 * 256);
  glDisableClientState(GL_VERTEX_ARRAY);
  // Swap buffers
  swapBuffers();
  //updateGL();
  time+=.001;
}

void * cudagl_widget::get_device_ptr(unsigned int dimx, unsigned int dimy)
{


}


void cudagl_widget::draw_device_data(void * positions)
{


}
