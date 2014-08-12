/*
 * MapSetWorld.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef MAPSETWORLD_HPP_
#define MAPSETWORLD_HPP_

#include "World.hpp"
#include "God.hpp"
#include "GameOfLife.hpp"

#include <map>
#include <set>
#include <utility>

class MapSetWorld: public World{
protected:
   virtual GOL::cordinate* YourNeighbors ( const GOL::cordinate &loc , const int &width ,
            const int &height );
      //return [8] cords
   virtual GOL::cordinate* YourNeighbors ( const GOL::cordinate &loc , const int &width ,
         const int &height );
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

   MapSetWorld
   ( int width , int height , ostream outs , set<GOL::cordinate> start ) :
         World(width,height,start){
      //assign start to be current gen, and then call count neighbors
   }


   ////////////////////////////
   //called by GOD ////////////
   ////////////////////////////
   void generation (); ///switch generaton data set pointers
   void CountNeighbors (); //mutator method, increments neighbor counts

   ////////////////////////////
   //called by Angel//////////
   ////////////////////////////

   //used to iterate over living cells and their Auroa (neighbor cells)
   // for( ; !world.NeighborCellsEnd() ; myCell = NextNeighbor() ){ }
   bool NeighborCellsEnd ();
   GOL::cell NextNeighbor ();

   //answer if there is a living cell in location
   bool IsLiving ( const GOL::cordinate &loc );

   //used to iterate over living cells
   //currently don't plan to use, but I will make it available
   bool LivingCellsEnd ();
   GOL::cell NextLivingCell ();
   //for display interface, interface on living set.
   long int NumLiving();
   GOL::cordinate NextLivingCellLoc();

   //called by Angel after Calculations
   void Live ( const GOL::cordinate &loc );
   void Birth ( const GOL::cordinate &loc ); //under current design dupes Live
   void Die ( const GOL::cordinate &loc );  //under current design does nothing

};

#endif /* MAPSETWORLD_HPP_ */
