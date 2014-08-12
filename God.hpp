/*
 * God.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef GOD_HPP_
#define GOD_HPP_


class GOD {
private:
   WORLD *myWORLD;
   ANGELofLIFE *myAngel;
public:

   GOD ( WorldBuilder *creator );

   void Generation () {

      myWORLD->CountNeighbors();
      myAngel->ReapandSow();
      myWORLD->generation();

      //output,  who instigates?
   }
};


#endif /* GOD_HPP_ */
