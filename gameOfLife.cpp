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

int repeatCheck(const Chronicle &chrono);


int main(){

   //Initialization activities
   swansonUtil::SeedRandom();

   //local variables and objects
   GOL::LivingCellStartSet genesis;
   Walker myCreator(WORLD_WIDTH,WORLD_HEIGHT);

   Chronicle WorldStates;
   string worldNow;
   bool NowRepeating;
   int RepeatPeriod = 0;

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





   God myGod(new MpSWorldBuilder(WORLD_WIDTH,WORLD_HEIGHT,genesis));

   WorldDisplayInterface *VoiceOfGod = myGod.GetWorldDisplayInt();

   while(VoiceOfGod->NumLiving()!=0){
      worldNow = outputWorldINT(VoiceOfGod);



      cout  << string(22, '\n') << worldNow
            << "GENERATIONS PASSED:" << myGod.GenerationsPassed();


      //checking for repeat state
      WorldStates.push_back(worldNow);
      if(WorldStates.size()>MAX_PERIODS_STORED) WorldStates.pop_front();
      if(!NowRepeating){
         RepeatPeriod = repeatCheck(WorldStates);
         if(RepeatPeriod != 0) NowRepeating = true;
      }


      if(NowRepeating){
         switch (RepeatPeriod) {
            case 1:
               cout << " the world is now Still-Life";
               break;
            case 2:
               cout << " the world is now Oscillating between two states";
               break;
            default:
               cout << " the World is in a repeating pattern with a period of "
                  << RepeatPeriod;
               break;
         }
      }

      cout.flush();



      getchar();
      myGod.Generation();
   }

   //todo clean up this output
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

int repeatCheck(const Chronicle &chrono){
   string world = chrono.back();
   for(Chronicle::const_reverse_iterator it=++(chrono.rbegin());
         it!= chrono.rend(); it++){
      if(*it == world){
         //return distance(it,chrono.rbegin());
         return distance(chrono.rbegin(),it);
      }
   }
   return 0; //false, no matches
}
