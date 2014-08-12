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
#include <iterator>

class MapSetWorld: public World{
protected:

   //typedefs
   typedef std::set<GOL::cordinate,GOL::cordinate> cordSet;
   typedef std::pair<GOL::cordinate,int*> NbCountPair;
   typedef std::map<GOL::cordinate,int*,GOL::cordinate> neighborMap;


   //member variables
   cordSet mLivingCellsA;
   cordSet mLivingCellsB;
   cordSet *pThisGen;
   cordSet *pNextGen;

   neighborMap mNeigborNums;

   //access iterator
   cordSet::iterator mLivingIter;



   //todo write counting algorithm;
   //private functions
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
      //assign start to be current gen
      pThisGen = cordSetA;
      pNextGen = cordsetB;
      *pThisGen = start;
   }


   ////////////////////////////
   //called by GOD ////////////
   ////////////////////////////

   //mutator method, increments neighbor counts
   void CountNeighbors (){
      for(cordSet::iterator st = *pThisGen.begin(); st!=*pThisGen.end();st++){
         GOL::cordinate mooreNB[8] = YourNeighbors(*st);
         for(int i=0; i<8; i++){ //increment all of the moore neighborhood
            if(mNeigborNums.count(mooreNB[i])==1){
               ++*mNeigborNums.at(mooreNB[i]);
            }else{
               mNeigborNums.insert(NbCountPair(mooreNB[i], new int(0)));
            }
         }
      }
   }

   ///switch generaton data set pointers
   void generation (){
      cordSet *pTemp = pThisGen;
      pThisGen = pNextGen;
      pNextGen = pTemp;

      pNextGen->clear();

      mLivingIter = pThisGen->begin();

      //todo double check this assignment

   }

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
   bool LivingCellsEnd (){ return (mLivingIter == pThisGen->end());}
   GOL::cell NextLivingCell (){
      GOL::cell result;
      result.location;

      ///trouble, if angel itererates over set then display
      //each class interacting needs its own iterator
      //todo work on this
   }
   //for display interface, interface on living set.
   long int NumLiving(){
      return pThisGen->size();
   }
   GOL::cordinate NextLivingCellLoc(){
      //behavior after .end() undefined
      return *mLivingIter++;
   }

   //called by Angel after Calculations
   void Live ( const GOL::cordinate &loc ){
      pNextGen->insert(loc);
   }
   void Birth ( const GOL::cordinate &loc ){
      //duplicate behavior of life (for now)
      Live(loc);
   }

   void Die ( const GOL::cordinate &loc ){
      //intentionally left blank in this implementation
   };

};

#endif /* MAPSETWORLD_HPP_ */
