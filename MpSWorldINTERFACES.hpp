/*
 * MpSWorldINTERFACES.hpp
 *
 *  Created on: Aug 12, 2014
 *      Author: brandon
 */

#ifndef MPSWORLDINTERFACES_HPP_
#define MPSWORLDINTERFACES_HPP_

#include "World.hpp"
#include "WorldTools.hpp"
#include "MapSetWorld.hpp"

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
      mWorld(world),mpsWorld(mpsworld){};

   virtual void NeighborCellBegin(){
      mNbLookUp = mpsWorld->mNeigborNums.begin();
   };
   virtual bool NeighborCellsEnd (){
      return(mNbLookUp == mpsWorld->mNeigborNums.end());
   }
   virtual GOL::cell NextNeighbor (){
      GOL::cell result;
      result.location=mNbLookUp->first;
      result.numNeighbors = mNbLookUp->*(second);
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




#endif /* MPSWORLDINTERFACES_HPP_ */
