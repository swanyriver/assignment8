//put header here

#include <iostream>
#include <cstdio>
#include <ctime>
#include "SwansonLibs/swansonInput.hpp"
#include "GOL/GameOfLife.hpp"
#include "GOL/God.hpp"
#include "GOL/WalkerMaker.hpp"
//#include "GOL/WorldTools.hpp"
#include "GOL/MapSetWorld.hpp"

const int WORLD_WIDTH = 80;
const int WORLD_HEIGHT = 22;
const float SATURATION = .3f;

string outputWorldINT ( WorldDisplayInterface* display ,
      int height = WORLD_HEIGHT );

int main(){

   cout << Walker::glider;
   swansonInput::yesNo("huh");

   swansonUtil::SeedRandom();

   GOL::LivingCellStartSet genesis;

   Walker myCreator(WORLD_WIDTH,WORLD_HEIGHT);
   int max = WORLD_HEIGHT*WORLD_WIDTH;
   myCreator.getSet(genesis,RandomWalker::GetWalkString(max,SATURATION),
         WORLD_WIDTH/2,WORLD_HEIGHT/2);

   God myGod(new MpSWorldBuilder(WORLD_WIDTH,WORLD_HEIGHT,genesis));

   WorldDisplayInterface *VoiceOfGod = myGod.GetWorldDisplayInt();

   while(true){
      swansonUtil::ClearScreen(); //todo change to pointer for -s simple
      cout << outputWorldINT(VoiceOfGod) << endl;
      getchar();
      myGod.Generation();
   }

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
