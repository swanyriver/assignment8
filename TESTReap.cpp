/*
 * TESTReap.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: brandon
 */

#include<iostream>
#include "WorldTools.hpp"
#include "MapSetWorld.hpp"
#include "GameOfLife.hpp"
#include "SwansonLibs/swansonString.hpp"
#include "SwansonLibs/swansonInput.hpp"
#include "Angel.hpp"
#include <string>

string outputWorld ( GOL::LivingCellStartSet &cells , int height );
string outputWorldINT ( WorldDisplayInterface* display , int height );
string outputNeighbors ( WorldReapingInterface *lAngel , int height );

const int WORLD_SIZE = 10;

int main () {

   GOL::LivingCellStartSet start;



   start.insert( GOL::GetCord( 0 , 0 ) );
   start.insert( GOL::GetCord( 4 , 4 ) );
   start.insert( GOL::GetCord( 3 , 1 ) );
   start.insert( GOL::GetCord( 2 , 4 ) );
   start.insert( GOL::GetCord( 6 , 6 ) );
   start.insert( GOL::GetCord( 5 , 5 ) );
   start.insert( GOL::GetCord( 7 , 5 ) );


   //start world
   string output;
   cout << "Starting World" << endl;
   output.append(WORLD_SIZE,'-'); output+='\n';
   output+= outputWorld( start , WORLD_SIZE );
   output.append(WORLD_SIZE,'-'); output+='\n';
   cout << output;


   MapSetWorld myWorld( WORLD_SIZE , WORLD_SIZE , start );
   WorldReapingInterface *angel = myWorld.GetReapingInterface();
   ANGELofLIFE *RealAngel = new ANGELofLIFE(angel);
   WorldDisplayInterface *display = myWorld.GetDisplayInterface();

   int generation = 0;

   do {

      myWorld.CountNeighbors();

      cout << endl << "neighbor number " << endl;
      output.clear();
      output.append(WORLD_SIZE,'-'); output+='\n';
      output+= outputNeighbors(angel,WORLD_SIZE);
      output.append(WORLD_SIZE,'-'); output+='\n';
      cout << output;

      RealAngel->ReapandSow();
      myWorld.generation();
      generation++;

      cout << "generation " << generation << endl;
      output.clear();
      output.append(WORLD_SIZE,'-'); output+='\n';
      output+= outputWorldINT( display , WORLD_SIZE );
      output.append(WORLD_SIZE,'-'); output+='\n';
      cout << output;

   } while (swansonInput::yesNo("keep going"));

}

string outputWorld ( GOL::LivingCellStartSet &cells , int height ) {
   string output;
   GOL::cordinate lastCord = GOL::GetCord( -1 , 0 );
   for ( GOL::LivingCellStartSet::iterator it = cells.begin() ;
         it != cells.end() ; it++ ) {
      if ( it->y > lastCord.y ) {
         output.append( it->y - lastCord.y , '\n' );
         lastCord.x = -1;
      }
      output.append( (it->x - lastCord.x - 1) , ' ' );
      output += "#";
      lastCord = *it;

   }
   output.append( height - lastCord.y , '\n' ); //always at least 1
   return output;
}

string outputWorldINT ( WorldDisplayInterface* display , int height ){
   string output;
   GOL::cordinate lastCord = GOL::GetCord( -1 , 0 );
   display->LivingCellBegin();
   while ( !display->LivingCellsEnd()) {
      GOL::cordinate nextCord = display->NextLivingCellLoc();
      if ( nextCord.y > lastCord.y ) {
         output.append( nextCord.y - lastCord.y , '\n' );
         lastCord.x = -1;
      }
      output.append( (nextCord.x - lastCord.x - 1) , ' ' );
      output += "#";
      lastCord = nextCord;

   }
   output.append( height - lastCord.y , '\n' ); //always at least 1
   return output;
}

string outputNeighbors ( WorldReapingInterface *lAngel , int height ) {
   string output;
   //GOL::cell nextCell;
   GOL::cordinate lastCord = GOL::GetCord( -1 , 0 );
   lAngel->NeighborCellBegin();
   while (  !lAngel->NeighborCellsEnd() ) {
      GOL::cell nextCell = lAngel->NextNeighbor();
      if ( nextCell.location.y > lastCord.y ) {
         output.append( nextCell.location.y - lastCord.y , '\n' );
         lastCord.x = -1;
      }
      output.append( (nextCell.location.x - lastCord.x - 1) , ' ' );
      output += swansonString::GetString(nextCell.numNeighbors);
      lastCord = nextCell.location;
   }
   output.append( height - lastCord.y , '\n' ); //always at least 1
   return output;
}
