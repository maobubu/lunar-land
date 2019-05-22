# This is an implementation of the lunar land game with C++


## Install dependencies
```
libglfw libGL(from nvidia) libc6
```
## Build the code and run the game
```
make
./lunar
```

## Game features
* Press "R" to reset the game. "P" to pause the game, "LEFT" "RIGHT" "UP" to rotate. "DOWN" to add thrust.
* The score will start decrease from 2000 when the game started, you have about 30 seconds to play the game before the score drops to 0. A collision will also causes Game over!
* The total speed, vertical speed and horizontal speed will show on the window.
* Successful landing happens when the horizontal and vertical speed are both smaller than 5m/s.
(I don't want to make the game too hard, so I set the threshold to 5m/s instead of 1m/s)
* The speed can be changed by adding Thrust based on the orientation, you can speed up the lander if it's facing the right side or slow down the lander if it's facing the left.
* The feul decreases from 120 when you start adding the thrust and will show "WARNING!! RUNNING OUT OF FEUL.THRUST IS DISABLED" on the window when the feul drops to zero.
* You will get a 0 if you causes a collision or the score drops to 0. The final score will be the remaining score+3 * remaining feuls.
* Enjoy the game! A little trick, use the "UP" bottom to rotate faster, only use the "LEFT"and "RIGHT" button to make small changes. If you feel the game is too hard, you can change the initial score amout and feul amout in the **lander.h**, I added comments so it's not hard to find!


Huicheng Liu
Jan-31-2019


