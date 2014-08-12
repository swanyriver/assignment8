/*
 * GameOfLife.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef GAMEOFLIFE_HPP_
#define GAMEOFLIFE_HPP_

class GOL{
public:
   static struct cordinate{
      int x,y;
   };

   static struct cell{
      bool alive;
      cordinate location;
      int numNeighbors;
   };
};



#endif /* GAMEOFLIFE_HPP_ */
