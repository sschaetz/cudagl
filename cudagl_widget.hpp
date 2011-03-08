#ifndef CUDAGL_WIDGET_HPP
#define CUDAGL_WIDGET_HPP

#include <qgl.h>

class QTimer;

class cudagl_widget : public QGLWidget
{
	Q_OBJECT
	
public:
	cudagl_widget(int timerInterval=0, QWidget *parent=0, char *name=0);
  void * get_device_ptr(unsigned int dimx, unsigned int dimy);
  void draw_device_data(void * positions);
protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	
	void keyPressEvent(QKeyEvent *e);
	
	void timeOut();
	
protected slots:
	void timeOutSlot();
	
private:
	QTimer *m_timer;
  GLuint bufferID;
  GLuint textureID;
  unsigned int dimx_;
  unsigned int dimy_;
  
  GLuint positionsVBO;
  struct cudaGraphicsResource* positionsVBO_CUDA;
  float time;

};

#endif // CUDAGL_WIDGET_HPP
