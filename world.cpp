// world.cpp


#include "world.h"
#include "lander.h"
#include "ll.h"
#include "gpuProgram.h"
#include "strokefont.h"
#include "landscape.h"
#include <sstream>
#include <time.h>




void World::updateState( float elapsedTime )

{
  // See if any keys are pressed for thrust

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { // right arrow
		lander->rotateCW(elapsedTime);
		//cout << "right" << endl;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { // left arrow
		lander->rotateCCW(elapsedTime);
		//cout << "left" << endl;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { // down arrow
		if (lander->feul_ammount() > 0) {
			lander->addThrust(elapsedTime);
			lander->feul_decrease(elapsedTime);
		}
		//cout << "down" << endl;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { // down arrow
		lander->Spin(elapsedTime);
		//cout << "up" << endl;
	}

  // Update the position and velocity

  lander->updatePose( elapsedTime );

  // See if the lander has touched the terrain

  vec3 closestTerrainPoint = landscape->findClosestPoint( lander->centreBottom() );
  float closestDistance = ( closestTerrainPoint - lander->centreBottom() ).length();
  altitude = landscape->altitude(lander->centreBottom());
  // Find if the view should be zoomed

  zoomView = (closestDistance < ZOOM_RADIUS);

  if (altitude <= 12.0||lander->Score_ammount()==0)
  {
	  gameover = true;
	  //cout << "game over" << endl;
  }
  else gameover = false;

  // Check for landing or collision and let the user know


}



void World::draw()

{
  mat4 worldToViewTransform;

  if (!zoomView) {

    // Find the world-to-view transform that transforms the world
    // to the [-1,1]x[-1,1] viewing coordinate system, with the
    // left edge of the landscape at the left edge of the screen, and
    // the bottom of the landscape BOTTOM_SPACE above the bottom edge
    // of the screen (BOTTOM_SPACE is in viewing coordinates).

	  float s = 2.0 / (landscape->maxX()-landscape->minX());

    worldToViewTransform
      = translate( -1, -1 + BOTTOM_SPACE, 0 )
      * scale( s, s, 1 )
      * translate( -landscape->minX(), -landscape->minY(), 0 );//-0,-0
      //y axis doesn't flipp so just minus minY
      //What is this step for?

  } else {
    float s = 2.0 / ZOOM_WIDTH;						//ZOOM_WIDTH is set to 600.
	worldToViewTransform
		= translate(-1, -1 + BOTTOM_SPACE, 0)
		* scale(s, s, 1)
		*translate(-lander->centrePosition().x + ZOOM_WIDTH/ 2, -lander->centrePosition().y+ZOOM_WIDTH/2, 0);
	//translate(-lander->centrePosition().x + (landscape->maxX() + landscape->minX()) / 2, -lander->centrePosition().y+(maxY()+minY())/2, 0);

	// calculate the diffenrence between middle of the object and the center of the world cordinate system


    // Find the world-to-view transform that is centred on the lander
    // and is ZOOM_WIDTH wide (in world coordinates).


  }

  // Draw the landscape and lander, passing in the worldToViewTransform
  // so that they can append their own transforms before passing the
  // complete transform to the vertex shader.

  landscape->draw( worldToViewTransform);
  lander->draw( worldToViewTransform );




  // Draw the heads-up display (i.e. all text).

  stringstream ss,sf,sd;
  drawStrokeString("AUTHOR HUICHENG LIU,DOWN THRUST,OTHER ROTATE,P pause,R reset", -1.0, 0.95, 0.05, glGetUniformLocation(myGPUProgram->id(), "MVP"));
  drawStrokeString( "LUNAR LANDER", -0.2, 0.85, 0.06, glGetUniformLocation( myGPUProgram->id(), "MVP") );

  ss.setf( ios::fixed, ios::floatfield );
  ss.precision(1);
  sf.setf(ios::fixed, ios::floatfield);
  sf.precision(1);
  sd.setf(ios::fixed, ios::floatfield);
  sd.precision(1);
  score = lander->Score_ammount();
  if (gameover || score == 0) {
	  if ((lander->horizontal() < 3.0) && (-lander->vertical() < 5.0)&&score!=0)
	  {
		  drawStrokeString("SUCCESFUL LAND SCORE + 3*TIMES REMAIN FEUL", -0.95, 0.45, 0.06, glGetUniformLocation(myGPUProgram->id(), "MVP"));
		  score = score + lander->feul_ammount() * 3;
	  }
	  else {
		  score = 0;
		  drawStrokeString("GAME OVER SCORE SET TO ZERO", -0.75, 0.45, 0.06, glGetUniformLocation(myGPUProgram->id(), "MVP"));
	  }
  }
  ss << "SPEED " << lander->speed()<< " m/s";
  ss << " Hor up " << lander->horizontal() << " m/s";
  ss << " Vert -> " << -lander->vertical() << " m/s";

  drawStrokeString( ss.str(), -0.95, 0.75, 0.06, glGetUniformLocation( myGPUProgram->id(), "MVP") );
  sf << "SCORE " << score << " p";
  sf << "TIME " << (clock() - lander->start()) / CLOCKS_PER_SEC << " s ";//set a end clock and minus the start clock
  sf << "ALTITUDE " << altitude-11.5 << " m";

  drawStrokeString(sf.str(), -0.95, 0.65, 0.06, glGetUniformLocation(myGPUProgram->id(), "MVP"));
  sd << "FEUL " << lander->feul_ammount() << " Galon";
  if(lander->feul_ammount()>0) drawStrokeString(sd.str(), -0.95, 0.55, 0.06, glGetUniformLocation(myGPUProgram->id(), "MVP"));
  else drawStrokeString("WARNING!! RUNNING OUT OF FEUL, THRUST IS DISABLED", -0.95, 0.55, 0.05, glGetUniformLocation(myGPUProgram->id(), "MVP"));


   (modify the above code, too)
}
