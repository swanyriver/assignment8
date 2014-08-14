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
#include <string>

string outputWorld ( GOL::LivingCellStartSet &cells , int height );
string outputNeighbors ( WorldReapingInterface *lAngel , int height );

int main () {

   GOL::LivingCellStartSet start;

   cout << "test case b" << endl;

   start.insert( GOL::GetCord( 0 , 0 ) );
   start.insert( GOL::GetCord( 4 , 4 ) );
   start.insert( GOL::GetCord( 3 , 1 ) );
   start.insert( GOL::GetCord( 2 , 4 ) );
   start.insert( GOL::GetCord( 6 , 6 ) );
   start.insert( GOL::GetCord( 5 , 5 ) );
   start.insert( GOL::GetCord( 7 , 5 ) );


   //start world
   string output;
   output.append(10,'-'); output+='\n';
   output+= outputWorld( start , 10 );
   output.append(10,'-'); output+='\n';
   cout << output;


   MapSetWorld myWorld( 10 , 10 , start );
   WorldReapingInterface *angel = myWorld.GetReapingInterface();

   myWorld.CountNeighbors();

   cout << endl << "neighbor number " << endl;
   output.clear();
   output.append(10,'-'); output+='\n';
   output+= outputNeighbors(angel,10);
   output.append(10,'-'); output+='\n';
   cout << output;

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

string outputNeighbors ( WorldReapingInterface *lAngel , int height ) {
   string output;
   //GOL::cell nextCell;
   GOL::cordinate lastCord = GOL::GetCord( -1 , 0 );
   for ( lAngel->NeighborCellBegin(); !lAngel->NeighborCellsEnd() ;) {
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
