This is the core code of the lunar land game implemented with C++.
I made the code run using visual studio 2017 on the Windows 10 system at CASLAB.
Just simply build and debug it.(don't forget to change the debug configuration to X86 instead of X64)

Game features:
1. Press "R" to reset the game. "P" to pause the game, "LEFT" "RIGHT" "UP" to rotate.
"DOWN" to add thrust.
2.The score will start decrease from 2000 as soon as the game started, you have about 30 seconds to play the game 
before the time score drops to 0 and that means Game over. Also, a collision also causes Game over!
3. The total speed, vertical speed and horizontal speed will show on the window.
4.Successful landing happens when the horizontal and vertical speed are both smaller than 5m/s
(I don't want to make the game too hard, so I choose the threshlod to be 5m/s instead of 1m/s)
5.The speed can be changed by adding Thrust based on the orientation, you can speed up the lander if it's facing 
the right side
or speed cut the lander if it's facing the left.
6.The feul decreases from 120 when you start adding the thrust and will show "WARNING!! RUNNING OUT OF FEUL.THRUST IS DISABLED"
on the window when the feul drops to zero.
7. You will get a 0 score if you cause a collision or the score runs to 0. The final score will be remaining score+3*remaing feuls.
8.Enjoy the game! A little trick, use the "UP" bottom to rotate because it's faster, only use the "LEFT"and "RIGHT" button to make small
changes. If you feel the game is too hard, you can change the initial score amout and feul amout from "lander.h", 
I added comments so it's not hard to find!


Huicheng Liu
Jan-31-2018


