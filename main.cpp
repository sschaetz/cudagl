#include <stdio.h>
#include <qapplication.h>
#include <cuda_runtime.h>

#include "cudagl_widget.hpp"



int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	
	cudagl_widget *w = new cudagl_widget();




  w->show();
  

  
	return a.exec();
}
