/*
 * WorldBuilder.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef WORLDBUILDER_HPP_
#define WORLDBUILDER_HPP_

#include "GameOfLife.hpp"
#include "World.hpp"

class WorldBuilder {
protected:
   const int WORLD_WIDTH;
   const int WORLD_HEIGHT;
   //ostream MY_OUTS;
public:
   WorldBuilder ( int width , int height , ostream &outs ) :
         WORLD_WIDTH( width ), WORLD_HEIGHT( height ) {
   } //, MY_OUTS(outs) {};
   virtual WORLD* buildWord () = 0;
};


#endif /* WORLDBUILDER_HPP_ */
