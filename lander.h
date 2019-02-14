// lander.h
//
// Unit of length is the meter


#ifndef LANDER_H
#define LANDER_H

#include "headers.h"
#include <time.h>


class Lander {

  static float landerVerts[];	// lander segments as vertex pairs
  int numSegments;		// number of line segments in the lander model

  GLuint VAO;			// VAO for lander geometry

  vec3 position;		// position in world coordinates (m)
  vec3 velocity;		// velocity in world coordinates (m/s)
  vec3 bottom;
  vec4 temp;
  float currenttime;
  float startTime;
  clock_t t1;
  float orientation;		// orientation (radians CCW)
  float angularVelocity;	// angular velocity (radians/second CCW)
  float feul;
  int Score;
  float worldMaxX, worldMaxY;	// world dimensions

 public:

  Lander( float maxX, float maxY ) {
    worldMaxX = maxX;
    worldMaxY = maxY;
    reset();
    setupVAO();
  };

  void setupVAO();

  void draw( mat4 &worldToViewTransform );

  void updatePose( float deltaT );

  void reset() {
    position = vec3( 0.05 * worldMaxX, 0.7 * worldMaxY, 0.0  );
    velocity = vec3( 30.0f, 0.0f, 0.0f );
	t1 = clock();			//set a start rpclock
    orientation = 0;
    angularVelocity = 0;
	feul=120;			//change the feul
	Score = 2000;		//change the score

  }

  void rotateCW( float deltaT );
  void rotateCCW( float deltaT );
  void addThrust( float deltaT );
  void Spin(float deltaT);
  void feul_decrease(float deltaT);

  vec3 centrePosition() { return position; }
  vec3 centreBottom() { return bottom; }
  float vertical() { return velocity.y; }
  float horizontal() { return velocity.x; }
  float feul_ammount() { return feul; }
  int Score_ammount() { return Score; }
  float start() { return t1; }

  float speed() { return velocity.length(); }
};


#endif
