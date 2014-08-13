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

/*
 * ALL SUBCLASSES OF WORLD MUST HAVE AN IMPLEMENTATION OF
 *    -WorldDisplayInterface
 *    -WorldReapingInterface
 *    -WorldBuilder
 */

class WorldDisplayInterface{
   //private mSubclassWorld,  pass in on construction
   //each instance need to itterate seperatly
public:

   //used to iterate over living cells
   virtual bool LivingCellsEnd ()=0;
   virtual void LivingCellBegin() = 0;
   virtual GOL::cordinate NextLivingCellLoc()= 0;
   virtual long int NumLiving() = 0;



};

class WorldReapingInterface{
private:
   WORLD *mWorld;
   //private mSubclassWorld,  pass in on construction
public:

   WorldReapingInterface(WORLD *world):mWorld(world){};

   virtual void NeighborCellBegin() = 0;
   virtual bool NeighborCellsEnd () = 0;
   virtual GOL::cell NextNeighbor () = 0;

   void Live ( const GOL::cordinate &loc ){
      mWorld->Live(loc);
   }
   void Birth ( const GOL::cordinate &loc ){
      mWorld->Birth(loc);
   }
   void Die ( const GOL::cordinate &loc ){
      mWorld->Die(loc);
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
