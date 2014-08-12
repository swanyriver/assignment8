/*
 * GameOfLife.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef GAMEOFLIFE_HPP_
#define GAMEOFLIFE_HPP_

namespace GOL{

   struct cordinate{
      int x,y;

      bool operator() ( const GOL::cordinate &lhs ,
            const GOL::cordinate &rhs ) const {
         //lhs<rhs return true > return false
         //coords are sorted with y highest priority to facilitate console output

         if ( lhs.y < rhs.y ){
            //cerr << "y " << lhs.y << " less than " << rhs.y << endl;
            return true;
         }
         else if((lhs.y == rhs.y) && (lhs.x < rhs.x)){
            //cerr << "x " << lhs.x << " less than " << rhs.x << endl;
            return true;
         }
         else
            return false;

      }

   };

   struct cell{
      bool alive;
      cordinate location;
      int numNeighbors;
   };
};



#endif /* GAMEOFLIFE_HPP_ */
