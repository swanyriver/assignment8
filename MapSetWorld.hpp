/*
 * MapSetWorld.hpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#ifndef MAPSETWORLD_HPP_
#define MAPSETWORLD_HPP_

#include "World.hpp"
#include "WorldTools.hpp"
#include "God.hpp"
#include "GameOfLife.hpp"

#include <map>
#include <set>
#include <utility>
#include <iterator>



using namespace std;

class MpSWorldDisplay;
class MpSWorldReap;


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

public:



   MapSetWorld
   ( int width , int height , GOL::LivingCellStartSet start ) :
         WORLD(width,height,start){
      //assign start to be current gen
      pThisGen = &mLivingCellsA;
      pNextGen = &mLivingCellsB;
      *pThisGen = start;

   }

   //used internally, but does not depend on internal state, so made static
   //for ease of testing and re-usability.
   static GOL::cordinate* YourNeighbors
   ( const GOL::cordinate &loc , const int &width, const int &height ){
      //return [8] cords
      //todo implement
      GOL::cordinate *mooreNB = new GOL::cordinate[8];
      //order changed to match print/set-sort order
      //y increases downward

      //row 1
      mooreNB[0].x = (loc.x+width-1)%width; mooreNB[0].y = (loc.y+height-1)%height;
      mooreNB[1].x = loc.x; mooreNB[1].y = (loc.y+height-1)%height;
      mooreNB[2].x = (loc.x+1)%width; mooreNB[2].y = (loc.y+height-1)%height;

      //row 2
      mooreNB[3].x = (loc.x+width-1)%width; mooreNB[3].y = loc.y;
      mooreNB[4].x = (loc.x+1)%width; mooreNB[4].y = loc.y;

      //row 3
      mooreNB[5].x = (loc.x+width-1)%width; mooreNB[5].y = (loc.y+1)%height;
      mooreNB[6].x = loc.x; mooreNB[6].y = (loc.y+1)%height;
      mooreNB[7].x = (loc.x+1)%width; mooreNB[7].y = (loc.y+1)%height;

      return mooreNB;
   }
   ////////////////////////////
   //called by GOD ////////////
   ////////////////////////////

   //mutator method, increments neighbor counts
   void CountNeighbors (){
      for(cordSet::iterator st = pThisGen->begin(); st!=pThisGen->end();st++){
         GOL::cordinate *mooreNB = YourNeighbors(*st,this->WORLD_HEIGHT,this->WORLD_HEIGHT);
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

   //factory methods //todo incomplete type, forward declaration
   WorldDisplayInterface* GetDisplayInterface();
   WorldReapingInterface* GetReapingInterface();
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

WorldDisplayInterface* MapSetWorld::GetDisplayInterface(){
   return new MpSWorldDisplay(this);
}
WorldReapingInterface* MapSetWorld::GetReapingInterface(){
   return new MpSWorldReap(this,this);
}



#endif /* MAPSETWORLD_HPP_ */
