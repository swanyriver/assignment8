/*
 * MapSetWorld.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef MAPSETWORLD_HPP_
#define MAPSETWORLD_HPP_

#include "World.hpp"
//#include "MpSWorldINTERFACES.hpp"
#include "WorldTools.hpp"
#include "God.hpp"
#include "GameOfLife.hpp"

#include <map>
#include <set>
#include <utility>
#include <iterator>

class MpSWorldDisplay;
class MpSWorldReap;

using namespace std;


class MapSetWorld: public WORLD{
   friend class MpSWorldDisplay;
   friend class MpSWorldReap;
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


   //todo write counting algorithm;
   //private functions
   virtual GOL::cordinate* YourNeighbors
   ( const GOL::cordinate &loc , const int &width, const int &height ){
      //return [8] cords
      //todo implement
   }



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
   ( int width , int height , GOL::LivingCellStartSet start ) :
         WORLD(width,height,start){
      //assign start to be current gen
      pThisGen = &mLivingCellsA;
      pNextGen = &mLivingCellsB;
      *pThisGen = start;

   }


   ////////////////////////////
   //called by GOD ////////////
   ////////////////////////////

   //mutator method, increments neighbor counts
   void CountNeighbors (){
      for(cordSet::iterator st = pThisGen->begin(); st!=pThisGen->end();st++){
         /*GOL::cordinate *mooreNB = YourNeighbors(*st,this->WORLD_HEIGHT,this->WORLD_HEIGHT);
         for(int i=0; i<8; i++){ //increment all of the moore neighborhood
            if(mNeigborNums.count(mooreNB[i])==1){
               ++*mNeigborNums.at(mooreNB[i]);
            }else{
               mNeigborNums.insert(NbCountPair(mooreNB[i], new int(0)));
            }
         }*/ //todo figure out out to return the array
      }
   }

   ///switch generaton data set pointers
   void generation (){
      cordSet *pTemp = pThisGen;
      pThisGen = pNextGen;
      pNextGen = pTemp;

      pNextGen->clear();
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

class MpSWorldDisplay: public WorldDisplayInterface{
private:
   MapSetWorld *mpsWorld;
   MapSetWorld::cordSet::iterator mCellLookUp;
public:
   MpSWorldDisplay(MapSetWorld *world):mpsWorld(world){};
   bool LivingCellsEnd (){
      return(mCellLookUp == mpsWorld->pThisGen->end());
   }
   void LivingCellBegin(){
      mCellLookUp = mpsWorld->pThisGen->begin();
   }
   GOL::cordinate NextLivingCellLoc(){
      return *mCellLookUp++;
   }
   long int NumLiving(){
      return mpsWorld->pThisGen->size();
   }
};

class MpSWorldReap: public WorldReapingInterface{
private:
   MapSetWorld *mpsWorld;
   MapSetWorld::neighborMap::iterator mNbLookUp;
public:
   MpSWorldReap(WORLD *world, MapSetWorld *mpsworld ):
      WorldReapingInterface(world),mpsWorld(mpsworld){};

   virtual void NeighborCellBegin(){
      mNbLookUp = mpsWorld->mNeigborNums.begin();
   };
   virtual bool NeighborCellsEnd (){
      return(mNbLookUp == mpsWorld->mNeigborNums.end());
   }
   virtual GOL::cell NextNeighbor (){
      GOL::cell result;
      result.location=mNbLookUp->first;
      result.numNeighbors = *(mNbLookUp->second);
      result.alive = mpsWorld->pThisGen->count(mNbLookUp->first);
      mNbLookUp++;
      return result;
   }

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



#endif /* MAPSETWORLD_HPP_ */
