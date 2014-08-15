/*
 * WalkerMaker.hpp
 *
 *  Created on: Aug 14, 2014
 *      Author: brandon
 */

#ifndef WALKERMAKER_HPP_
#define WALKERMAKER_HPP_

#include "GameOfLife.hpp"
#include <string>
#include <set>
#include <utility>
#include <istream>
#include <sstream>
#include "../SwansonLibs/swansonString.hpp"
#include "../SwansonLibs/swansonUtils.hpp"

#include <iostream>

using namespace std;

class Walker {
private:

   GOL::LivingCellStartSet mySet;
   set<char> inputKeys;

   const int WORLD_WIDTH, WORLD_HEIGHT;

   static const int North = 'w';
   static const int South = 's';
   static const int West = 'a';
   static const int East = 'd';
   static const int NW = 'q';
   static const int SW = 'z';
   static const int NE = 'e';
   static const int SE = 'c';


   void up ( GOL::cordinate &pos ) {
      pos.y = (pos.y + WORLD_HEIGHT - 1) % WORLD_HEIGHT;
   }
   void down ( GOL::cordinate &pos ) {
      pos.y = (pos.y + 1) % WORLD_HEIGHT;
   }
   void left ( GOL::cordinate &pos ) {
      pos.x = (pos.x + WORLD_WIDTH - 1) % WORLD_WIDTH;
   }
   void right ( GOL::cordinate &pos ) {
      pos.x = (pos.x + 1) % WORLD_WIDTH;
   }

public:

   static const int upper = 'a' - 'A';
   static const char terminate = '!';

   static const char inputChars[];
   static const string glider;

   Walker ( int width , int height ) :
         WORLD_WIDTH( width ), WORLD_HEIGHT( height ) {
      //myKeys.insert(walkChar('w',true));
      inputKeys.insert( Walker::North );
      inputKeys.insert( South );
      inputKeys.insert( East );
      inputKeys.insert( West );
      inputKeys.insert( NW );
      inputKeys.insert( NE );
      inputKeys.insert( SE );
      inputKeys.insert( SW );

      for ( set<char>::iterator it = inputKeys.begin() ; it != inputKeys.end() ;
            it++ ) {
         inputKeys.insert( *it - upper );
      }

   }

   void getSet ( GOL::LivingCellStartSet &cellSet, std::istream &myStream,
         int startx = 0 , int starty = 0) {

      char nextchar;

      GOL::cordinate position = GOL::GetCord( startx , starty );

      while ( nextchar != terminate ) {
         myStream >> nextchar;

         if ( inputKeys.count( nextchar ) ) {
            bool cursorOn = (nextchar < 'a');
            if ( cursorOn )
               nextchar += upper;

            switch (nextchar) {
            case Walker::North:
               up( position );
               break;
            case Walker::South:
               down( position );
               break;
            case Walker::East:
               right( position );
               break;
            case Walker::West:
               left( position );
               break;
            case NW:
               up( position );
               left( position );
               break;
            case NE:
               up( position );
               right( position );
               break;
            case SE:
               down( position );
               right( position );
               break;
            case SW:
               down( position );
               left( position );
               break;
            default:
               break;
            }

            if ( cursorOn ){
               cellSet.insert(position);
            }

         } //end of if
      }//end of while
   }//end of function

   void getSet ( GOL::LivingCellStartSet &cellSet, string input,
         int startx = 0 , int starty = 0 ) {
      istringstream mystream(input);
      getSet(cellSet,mystream, startx, starty);
   }
};

const char Walker::inputChars[] = {North,South,West,East,SW,SE,NW,NE};
const string Walker::glider = "WCSAA";


class RandomWalker{
private:
   static const float DEFAULT_CLUSTERING;

   static string Walk(int &cellNumber, float clustering){
      char nextStep = Walker::inputChars[swansonUtil::GetRandomInRange(7)];
      if(swansonUtil::GetRandomInRange(100)>(clustering*100)){
         nextStep -= Walker::upper;
         cellNumber++;
      }
      return swansonString::GetString(nextStep);
   }

public:
   static string GetWalkString(int maxCells, float saturation,
         float clustring = RandomWalker::DEFAULT_CLUSTERING){
      string walkStr;
      int cellNumber = 0;
      int saturationNumber = maxCells * saturation;
      while(cellNumber<saturationNumber){
         walkStr += Walk(cellNumber,clustring);
      }

      walkStr += swansonString::GetString(Walker::terminate);
      return walkStr;


   }
   static string GetWalkString(int maxCells, int steps,
         float clustring = RandomWalker::DEFAULT_CLUSTERING){
      string walkStr;
      int cellNumber = 0;
      int takenSteps = 0;

      while(takenSteps<steps && cellNumber<maxCells){
         walkStr += Walk(cellNumber,clustring);
         takenSteps++;
      }
      walkStr += swansonString::GetString(Walker::terminate);
      return walkStr;

   }


};

const float RandomWalker::DEFAULT_CLUSTERING = .5;


#endif /* WALKERMAKER_HPP_ */
