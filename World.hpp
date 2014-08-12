/*
 * World.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include "GameOfLife.hpp"


class WORLD {

protected:

   const int WORLD_WIDTH;
   const int WORLD_HEIGHT;

   set<GOL::cordinate> startLivingCells;

   virtual GOL::cordinate* YourNeighbors
   ( const GOL::cordinate &loc , const int &width , const int &height )=0;
   //return [8] cords

public:
   //////necesary conditions///////////
   /*
    * 2 Generations tracked,
    * living is mapped onto next generation
    * next generations starts off blank
    *    (required to avoid the unchecked isolated cells persisting)
    *
    */

   WORLD ( int width , int height , set<GOL::cordinate> start ) :
         WORLD_WIDTH( width ), WORLD_HEIGHT( height ),
         startLivingCells(start){};


   ////////////////////////////
   //called by GOD ////////////
   ////////////////////////////
   virtual void generation () = 0; ///switch generaton data set pointers
   virtual void CountNeighbors ()=0; //mutator method, increments neighbor counts

   ////////////////////////////
   //called by Angel//////////
   ////////////////////////////

   //used to iterate over living cells and their Auroa (neighbor cells)
   // for( ; !world.NeighborCellsEnd() ; myCell = NextNeighbor() ){ }
   virtual bool NeighborCellsEnd () = 0;
   virtual GOL::cell NextNeighbor () = 0;

   //answer if there is a living cell in location
   virtual bool IsLiving ( const GOL::cordinate &loc )=0;

   //used to iterate over living cells
   //currently don't plan to use, but I will make it available
   virtual bool LivingCellsEnd () = 0;
   virtual GOL::cell NextLivingCell () = 0;
   //for display interface, interface on living set.
   virtual long int NumLiving()=0;
   virtual GOL::cordinate NextLivingCellLoc() = 0;

   //called by Angel after Calculations
   virtual void Live ( const GOL::cordinate &loc )=0;
   virtual void Birth ( const GOL::cordinate &loc )=0; //under current design dupes Live
   virtual void Die ( const GOL::cordinate &loc )=0;  //under current design does nothing

};



#endif /* WORLD_HPP_ */
