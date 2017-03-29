# 2D-Shooting-Game
This is a simple game in which the player shoots down some objects.   

# Features

* Developed a 2D shooting game like "Galaga" using C++ 
* Designed core game engine for collision detection, movement of objects, drawing objects, and event process.
* Development environment: Microsoft Visual Studio 10 Professional, Windows 8.1


# This game satisfies the requirement as follows. 

1.  Place the cannon (triangle) to the middle of the bottom part of the screen (window).
2.  Make sure the cannon smoothly turns with the help of the cursor keys (to the left, to the right) in a range of -90 to 90 degrees from the basic direction (the basic direction is upwards).
3.  Pushing the SPACE key makes the cannon shoot a projectile – a small object consisting of lines. The projectile flies in the direction the cannon is turned to.
4.  It has to be possible to shoot several projectiles if the player holds the SPACE.
5.  Create an object – a clock with hands, approximately with dimensions of 100x100 pixels, which shows the real time.
6.  Display two clocks at the same time at random spots on the screen; both have to show time all the time.
7.  Set the clocks in motion – random speed and direction. When bumping into a screen margin, the clocks rebound; when bumping into each other both the objects rebound away from each other (the direction of their movement in x and y reversed as appropriate).
8.  Make sure there is a testing of collisions of the clocks with the projectiles shot from the cannon. When the clocks are shot down, they change into two smaller clocks and the projectile disappears. If the too small clocks are shot down, they disappear completely (small = approximately of 5x5 pixels).
9.  Once the last clocks are shot down, the two big clocks appear again (see point 6) and the whole procedure repeats.

# Demo Video
<img src="https://github.com/chc2212/2D-Shooting-Game/blob/master/demo.gif" width="500" align ="left">


