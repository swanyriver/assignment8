READ ME FIRST (roadmap to my code):
The code in gameOfLife.cpp is merely a controller and view implementation with
 very little functionality of the Game Of Life,  This code creates a 
 WorldBuilder Object after selecting the options for generating a starting set.
  
It then hands over this builder object to the God class that uses it to 
construct a MapSetWorld instance that it references through a pointer to the 
abstract type WORLD.  The god class delivers a WordDisplayInterface to the int
 main() controller and WordReapingInterface to its private instance Angel.
 
From here the world is advanced by calling Generation() on the God class and 
displayed by creating a string using the WordlDisplayInterface methods.

God calls countNeighbors on the world to prepare it for Reaping 
(executing game of life rule)  then the angels method ReapAndSow() is called to
 mark cells in the next generation for life, death, or birth using information
 provided about the cells via the WorldReapingInterface provided to it.  Then 
 the worlds method generation() is called causing its pointers for thisGen and 
 nextGen to be swapped.
 
The WORLD subclass uses a Map of coordinates (x and y struct defined in 
GameOfLife.hpp) as the key and an int (number of neighbors), and two sets of 
coordinates to represent living cells in this generation and next generations.