/*
 * Angel.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef ANGEL_HPP_
#define ANGEL_HPP_

#include "World.hpp"


class ANGELofLIFE {
private:
   WORLD *myWorld;
   WORLD::WorldAgentID me;
public:

   ANGELofLIFE ( WORLD *world ) :
         myWorld( world ) , me(WORLD::getCellAccessID()) {}



   virtual void ReapandSow () {
      GOL::cell myCell;
      //mark cells in next generation of world for life
      for ( ; !myWorld->NeighborCellsEnd(me) ;
            myCell = myWorld->NextNeighbor(me) ) {
         if ( myCell.alive ) {
            if ( myCell.numNeighbors == 2 )
               myWorld->Live( myCell.location );
            else
               myWorld->Die( myCell.location );
         } else { //not living cell
            if ( myCell.numNeighbors == 3 )
               myWorld->Birth( myCell.location );
         }
      }
   }

};


#endif /* ANGEL_HPP_ */
