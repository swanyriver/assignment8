/*
 * TESTReap.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: brandon
 */

#include<iostream>
#include "GOL/WorldTools.hpp"
#include "GOL/MapSetWorld.hpp"
#include "GOL/GameOfLife.hpp"
#include "SwansonLibs/swansonString.hpp"
#include "SwansonLibs/swansonInput.hpp"
#include "GOL/Angel.hpp"
#include <string>

#include "GOL/WalkerMaker.hpp"


string outputWorld ( GOL::LivingCellStartSet &cells , int height );
string outputWorldINT ( WorldDisplayInterface* display , int height );
string outputNeighbors ( WorldReapingInterface *lAngel , int height );

const int WORLD_SIZE = 8;

int main () {

   GOL::LivingCellStartSet start;



   /*start.insert( GOL::GetCord( 0 , 0 ) );
   start.insert( GOL::GetCord( 4 , 4 ) );
   start.insert( GOL::GetCord( 3 , 1 ) );
   start.insert( GOL::GetCord( 2 , 4 ) );
   start.insert( GOL::GetCord( 6 , 6 ) );
   start.insert( GOL::GetCord( 5 , 5 ) );
   start.insert( GOL::GetCord( 7 , 5 ) );
*/
   start.insert( GOL::GetCord( 9 , 4 ) );
   start.insert( GOL::GetCord( 0 , 20 ) );

   int generationCount=15;
   /*cin >> generationCount;
   int pos;
   while(std::cin>>pos && std::cin.peek()!='\n'){
      start.insert( GOL::GetCord( pos/10 , pos%10 ) );
   }*/

   Walker myWalker(WORLD_SIZE,WORLD_SIZE);

   cout << "getting set" << endl;

   myWalker.getSet(start);

   cout << "function exited" << endl;

   swansonInput::yesNo("continue");

   cout << "set gotten size:" << start.size() << endl;



   //start world
  /* string output;
   cout << "Starting World" << endl;
   output.append(WORLD_SIZE,'-'); output+='\n';
   output+= outputWorld( start , WORLD_SIZE );
   output.append(WORLD_SIZE,'-'); output+='\n';
   cout << output;*/

   WorldBuilder *myBuilder = new MpSWorldBuilder(WORLD_SIZE,WORLD_SIZE,start);
   //WORLD *myWorld = myBuilder->buildWord();
   God myGod(myBuilder);

   //MapSetWorld myWorld( WORLD_SIZE , WORLD_SIZE , start );
   //WorldReapingInterface *angel = myWorld->GetReapingInterface();
   //ANGELofLIFE *RealAngel = new ANGELofLIFE(angel);
   //WorldDisplayInterface *display = myWorld->GetDisplayInterface();

   WorldDisplayInterface *display = myGod.GetWorldDisplayInt();

   string output;
   output.append(WORLD_SIZE,'-'); output+='\n';
   output+= outputWorldINT( display , WORLD_SIZE );
   output.append(WORLD_SIZE,'-'); output+='\n';
   cout << output;


   for(int generation = 2; generation <= generationCount ; generation++) {

      /*myWorld->CountNeighbors();

      cout << endl << "neighbor number " << endl;
      output.clear();
      output.append(WORLD_SIZE,'-'); output+='\n';
      output+= outputNeighbors(angel,WORLD_SIZE);
      output.append(WORLD_SIZE,'-'); output+='\n';
      cout << output;

      if(generation == 7){
         cout << "here is the problem" << endl;
      }

      RealAngel->ReapandSow();*/
      myGod.Generation();

      cout << "generation " << generation << " living cells:"
            << display->NumLiving() << endl ;

      output.clear();
      output.append(WORLD_SIZE,'-'); output+='\n';
      output+= outputWorldINT( display , WORLD_SIZE );
      output.append(WORLD_SIZE,'-'); output+='\n';
      cout << output;

   }

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
