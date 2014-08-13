/*
 * Angel.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef ANGEL_HPP_
#define ANGEL_HPP_

#include "WorldTools.hpp"


class ANGELofLIFE {
private:
   WorldReapingInterface *myWorld;
public:

   ANGELofLIFE ( WorldReapingInterface *world ) :
         myWorld( world ) , me(WORLD::getCellAccessID()) {}



   virtual void ReapandSow () {
      GOL::cell myCell;
      //mark cells in next generation of world for life
      for ( myWorld->NeighborCellBegin(); !myWorld->NeighborCellsEnd() ;
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

   //possibly faster to decide death for all !2 && !3 then check for life
   //opens up to itterating over all possible locations though

};


#endif /* ANGEL_HPP_ */
