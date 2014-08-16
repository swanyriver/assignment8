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
#include <list>

const int WORLD_WIDTH = 80;
const int WORLD_HEIGHT = 22;
const float SATURATION = .3f;
const int MAX_PERIODS_STORED = 200;

typedef list<string> Chronicle;

string outputWorldINT ( WorldDisplayInterface* display ,
      int height = WORLD_HEIGHT );

int repeatCheck(Chronicle chrono, string world);


int main(){

   //Initialization activities
   swansonUtil::SeedRandom();

   //local variables and objects
   GOL::LivingCellStartSet genesis;
   Walker myCreator(WORLD_WIDTH,WORLD_HEIGHT);

   Chronicle WorldStates;
   string worldNow;

   //random world
   int max = WORLD_HEIGHT*WORLD_WIDTH;
   myCreator.getSet(genesis,RandomWalker::GetWalkString(max,SATURATION),
         WORLD_WIDTH/2,WORLD_HEIGHT/2);

   /*//glider world
   genesis.clear();
   myCreator.getGliderWorld(genesis);

   //tumbler
   genesis.clear();
   myCreator.getSet(genesis,Walker::Tumbler,WORLD_WIDTH/2,WORLD_HEIGHT/2);

   //line of 10
   genesis.clear();
   myCreator.getSet(genesis,swansonString::UpperCase(string(10, Walker::East)),
         (WORLD_WIDTH/2)-5,WORLD_HEIGHT/2);*/


   genesis.clear();
      myCreator.getSet(genesis,Walker::Tumbler,WORLD_WIDTH/2,WORLD_HEIGHT/2);



   God myGod(new MpSWorldBuilder(WORLD_WIDTH,WORLD_HEIGHT,genesis));

   WorldDisplayInterface *VoiceOfGod = myGod.GetWorldDisplayInt();

   while(VoiceOfGod->NumLiving()!=0){
      swansonUtil::ClearScreen(); //todo change to pointer for -s simple
      //todo why is it not clearing the screen
      worldNow = outputWorldINT(VoiceOfGod);

      WorldStates.push_back(worldNow);
      if(WorldStates.size()>MAX_PERIODS_STORED) WorldStates.pop_front();

      cout << worldNow << endl
            << "GENERATIONS PASSED:" << myGod.GenerationsPassed()
            << "    matches generation ago:"
            <<repeatCheck(WorldStates,worldNow)
            << "      generations checked:" << WorldStates.size();
      cout.flush();



      getchar();
      myGod.Generation();
   }

   cout << "there is now no more life in this world";

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

int repeatCheck(Chronicle chrono, string world){
   for(Chronicle::reverse_iterator it=++(chrono.rbegin());
         it!= chrono.rend(); it++){
      if(*it == world){
         //return distance(it,chrono.rbegin());
         return distance(chrono.rbegin(),it);
      }
   }
   return 0; //false, no matches
}
