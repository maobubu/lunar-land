// world.h


#ifndef WORLD_H
#define WORLD_H


#include "headers.h"
#include "landscape.h"
#include "lander.h"
#include "ll.h"
#include <time.h>

#define BOTTOM_SPACE 0.1f // amount of blank space below terrain (in viewing coordinates) 


class World {

  Landscape *landscape;
  Lander    *lander;
  bool       zoomView; // show zoomed view when lander is close to landscape
  GLFWwindow *window;
  bool		gameover;
  float altitude;
  int score;
	

 public:

  World( GLFWwindow *w ) {
    landscape = new Landscape();
    lander    = new Lander( maxX(), maxY() ); // provide world size to help position lander
    zoomView  = false;
	gameover = false;
    window    = w;
	
  }

  void draw();

  void updateState( float elapsedTime );
  bool pause() { return gameover; }

  void resetLander() {
    lander->reset();
	zoomView = false;	//reset the zoomView
	gameover = false;	//reset the gameover
	
  }

  // World extremes (in world coordinates)

  float minX() { return 0; }
  float maxX() { return landscape->maxX(); }
  //Landscape width

  float minY() { return 0; }
  float maxY() { return (landscape->maxX() - landscape->minX()) / SCREEN_ASPECT * (2 - BOTTOM_SPACE) / 2; }
};


#endif