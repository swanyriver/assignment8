/*
 * God.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef GOD_HPP_
#define GOD_HPP_

#include "WorldTools.hpp"
#include "World.hpp"
#include "Angel.hpp"

class God {
private:
   WORLD *myWORLD;
   ANGELofLIFE *myAngel;
public:

   God ( WorldBuilder *creator ){
      myWORLD = creator->buildWord();
      myAngel = new ANGELofLIFE(myWORLD);

   }

   void Generation () {

      myWORLD->CountNeighbors();
      myAngel->ReapandSow();
      myWORLD->generation();
   }

   WorldDisplayInterface GetWorldDisplayInt(){
      return WorldDisplayInterface(myWORLD);
   }
};


#endif /* GOD_HPP_ */
