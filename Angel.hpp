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
public:

   ANGELofLIFE ( WORLD *world ) :
         myWorld( world ) {}



   virtual void ReapandSow () {
      GOL::cell myCell;
      //mark cells in next generation of world for life
      for ( ; !myWorld->NeighborCellsEnd() ;
            myCell = myWorld->NextNeighbor() ) {
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
