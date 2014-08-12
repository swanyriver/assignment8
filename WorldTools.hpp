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

class WorldDisplayInterface{
private:
   WORLD *outputWorld;

public:
   WorldDisplayInterface(WORLD *world):outputWorld(world){};

   //used to iterate over living cells
   bool LivingCellsEnd (){
      return outputWorld->LivingCellsEnd();
   }
   GOL::cordinate NextLivingCellLoc(){
      return outputWorld->NextLivingCellLoc();
   }
   long int NumLiving(){
      return outputWorld->NumLiving();
   }

};


class WorldBuilder {
protected:
   const int WORLD_WIDTH;
   const int WORLD_HEIGHT;

public:
   WorldBuilder ( int width , int height ) :
         WORLD_WIDTH( width ), WORLD_HEIGHT( height ) {
   }
   virtual WORLD* buildWord () = 0;
};


#endif /* WORLDBUILDER_HPP_ */
