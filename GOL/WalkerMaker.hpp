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
#include "../SwansonLibs/swansonString.hpp"


using namespace std;

class Walker{
private:

   GOL::LivingCellStartSet mySet;
   set<char> inputKeys;


   const int WORLD_WIDTH, WORLD_HEIGHT;

   static const int North = 'w';
   static const char South;
   static const char West;
   static const char East;
   static const char NW;
   static const char SW;
   static const char NE;
   static const char SE;
   static const int upper;
   static const char terminate;

   void up(GOL::cordinate &pos){
      pos.y = (pos.y + WORLD_HEIGHT - 1)%WORLD_HEIGHT;
   }
   void down(GOL::cordinate &pos){
      pos.y = (pos.y + 1)%WORLD_HEIGHT;
   }
   void left(GOL::cordinate &pos){
      pos.x = (pos.x + WORLD_WIDTH - 1)%WORLD_WIDTH;
   }
   void right(GOL::cordinate &pos){
      pos.x = (pos.x + 1)%WORLD_WIDTH;
   }


public:

   Walker(int width, int height): WORLD_WIDTH(width), WORLD_HEIGHT(height){
      //myKeys.insert(walkChar('w',true));
      inputKeys.insert(Walker::North);
      inputKeys.insert(South);
      inputKeys.insert(East);
      inputKeys.insert(West);
      inputKeys.insert(NW);
      inputKeys.insert(NE);
      inputKeys.insert(SE);
      inputKeys.insert(SW);



      for(set<char>::iterator it=inputKeys.begin();
            it!= inputKeys.end(); it++){
         inputKeys.insert(*it+upper);
      }

   };

   GOL::LivingCellStartSet getSet
      (std::istream in, GOL::LivingCellStartSet &set ){

      char nextchar;

      GOL::cordinate position = GOL::GetCord(0,0);

      while(in >> nextchar){
         if(nextchar==terminate) break;
         else{
            if(inputKeys.count(nextchar)){
               bool cursorOn = (nextchar>'z');
               if(cursorOn) nextchar -= upper;

               switch (nextchar) {
                  case Walker::North:
                     up(position);
                     break;
                  case Walker::South:
                     down(position);
                     break;
                  case Walker::East:
                     right(position);
                     break;
                  case Walker::West:
                     left(position);
                     break;
                  case NW:
                     up(position);
                     left(position);
                     break;
                  case NE:
                     up(position);
                     right(position);
                     break;
                  case SE:
                     down(position);
                     right(position);
                     break;
                  case SW:
                     down(position);
                     left(position);
                     break;
                  default:
                     break;
               }

               if(cursorOn) set.insert(position);

            }
         }
      }


   };
};

//const char Walker::North = 'w';
const char Walker::South = 's';
const char Walker::West = 'a';
const char Walker::East = 'd';
const char Walker::NW = 'q';
const char Walker::SW = 'z';
const char Walker::NE = 'e';
const char Walker::SE = 'c';
const int Walker::upper = 'A' - 'a';
const char Walker::terminate = '!';




#endif /* WALKERMAKER_HPP_ */
