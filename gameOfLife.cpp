//put header here

#include <iostream>
#include <cstdio>
#include <ctime>
#include "SwansonLibs/swansonInput.hpp"
#include "SwansonObjects/menu.hpp"
#include "GOL/GameOfLife.hpp"
#include "GOL/God.hpp"
#include "GOL/WalkerMaker.hpp"
//#include "GOL/WorldTools.hpp"
#include "GOL/MapSetWorld.hpp"
#include <list>
#include <cstdlib>

const int WORLD_WIDTH = 80;
const int WORLD_HEIGHT = 22;
const float SATURATION = .3f;
const int MAX_PERIODS_STORED = 200;
const char QUIT = 'q';

typedef list<string> Chronicle;

//global members
// regetbly global so that menu functions can modify them
Walker myCreator(WORLD_WIDTH,WORLD_HEIGHT);
GOL::LivingCellStartSet genesis;
bool leaveProgram=false;

const string INTRO = "\n\nWelcome to Brandon Swanson's Game of Life"
      "\n\nWhen simulation runs press enter to advance one generations or"
      "\nHold down enter to watch the generations zoom by"
      "\nPress 'q' and enter to exit simulation\n\n";

const string WALK_EXP = "\n\n\n"
      "You can input manually using the below keys to move a cursor"
      " around the world"
      "\nUppercase indicates cursor on, and lower case off\nwith living cells"
      " marked at the spot moved to"
      "\n\n"
      "        q   w  e  \n"
      "        a      d  \n"
      "        z   s  c  \n"
      "\nYour cursor will start at the middle of the screen"
      "\nUse ! to indicate that you are finished marking live cells"
      "\n\nas an example a single glider can be made with: WCSAA!"
      "\nand a bi-block with ASDWdDDSA! ";

Menu mainMenu(INTRO);
Menu preDefMenu("Please Select one of these pre-defined starting worlds");

//menu functions
void preDefShow(){
   preDefMenu.showMenu();
}
void randomCells(){
   genesis.clear();
   int max = WORLD_HEIGHT*WORLD_WIDTH;
   myCreator.getSet(genesis,RandomWalker::GetWalkString(max,SATURATION),
         WORLD_WIDTH/2,WORLD_HEIGHT/2);
}

void pdGliderWorld(){
   genesis.clear();
   myCreator.getGliderWorld(genesis);
}

void pdEdgeGliders(){
   genesis.clear();
   myCreator.getSet(genesis,Walker::glider,
         WORLD_WIDTH-Walker::GLIDER_SIZE-2,WORLD_HEIGHT/2);
   myCreator.getSet(genesis,Walker::glider,
         WORLD_WIDTH/2,WORLD_HEIGHT-Walker::GLIDER_SIZE-2);
}

void pdTumbler(){
   genesis.clear();
   myCreator.getSet(genesis,Walker::Tumbler,WORLD_WIDTH/2,WORLD_HEIGHT/2);
}

void pdTen(){
   genesis.clear();
   myCreator.getSet(genesis,swansonString::UpperCase(string(10, Walker::East)),
         (WORLD_WIDTH/2)-5,WORLD_HEIGHT/2);
}

void quit(){
   leaveProgram = true;
}

void userGen(){
   cout << WALK_EXP << endl;
   //todo possibly update display
   genesis.clear();
   myCreator.getSet(genesis, cin, WORLD_WIDTH/2, WORLD_HEIGHT/2);
   cin.ignore(1000,'\n');
}

//Function declarations
string outputWorldINT ( WorldDisplayInterface* display ,
      int height = WORLD_HEIGHT );

int repeatCheck(const Chronicle &chrono);

void RunSimulation ();


int main(){

   //Initialization activities
   swansonUtil::SeedRandom();

   ///menu for starting set
   mainMenu.addItem(new GoItem(preDefShow, "Pre-Defined Worlds", ""));
   mainMenu.GetLastItem()->hasIntro=false;
   mainMenu.GetLastItem()->itemRepeat=false;
   preDefMenu.addItem(new GoItem(pdGliderWorld, "Glider World", ""));
   preDefMenu.GetLastItem()->hasIntro=false;
   preDefMenu.GetLastItem()->itemRepeat=false;
   preDefMenu.addItem(new GoItem(pdEdgeGliders, "Edge Gliders", ""));
   preDefMenu.GetLastItem()->hasIntro=false;
   preDefMenu.GetLastItem()->itemRepeat=false;
   preDefMenu.addItem(new GoItem(pdTumbler, "Tumbler", ""));
   preDefMenu.GetLastItem()->hasIntro=false;
   preDefMenu.GetLastItem()->itemRepeat=false;
   preDefMenu.addItem(new GoItem(pdTen, "Line of 10", ""));
   preDefMenu.GetLastItem()->hasIntro=false;
   preDefMenu.GetLastItem()->itemRepeat=false;

   mainMenu.addItem(new GoItem(randomCells, "Randomly Generate World", ""));
   mainMenu.GetLastItem()->hasIntro=false;
   mainMenu.GetLastItem()->itemRepeat=false;

   mainMenu.addItem(new GoItem(userGen, "Manually Input World", ""));
   mainMenu.GetLastItem()->hasIntro=false;
   mainMenu.GetLastItem()->itemRepeat=false;

   mainMenu.addItem(new GoItem(quit, "Exit Program", ""));
   mainMenu.GetLastItem()->hasIntro=false;
   mainMenu.GetLastItem()->itemRepeat=false;

   mainMenu.menuRepeat=false;
   mainMenu.demoAllItem=false;
   mainMenu.clearScreenON = false;
   mainMenu.exitMenuItem = false;

   preDefMenu.menuRepeat=false;
   preDefMenu.demoAllItem=false;
   preDefMenu.clearScreenON = false;
   preDefMenu.exitMenuItem = false;


   while(!leaveProgram){
      mainMenu.showMenu(); //chose starting position
      if(!leaveProgram)RunSimulation(); //run game of life
   }


}

void RunSimulation () {
   //local variables and objects
   Chronicle WorldStates;
   string worldNow;
   bool NowRepeating = false;
   int RepeatPeriod = 0;
   //pass generated cells to builder and builder to god,  world is born
   God myGod( new MpSWorldBuilder( WORLD_WIDTH , WORLD_HEIGHT , genesis ) );
   WorldDisplayInterface* VoiceOfGod = myGod.GetWorldDisplayInt();
   bool exit = false;
   while ( !exit ) {
      worldNow = outputWorldINT( VoiceOfGod );
      cout << string( 22 , '\n' ) << worldNow << "GENERATIONS PASSED:"
            << myGod.GenerationsPassed();
      //checking for repeat state
      WorldStates.push_back( worldNow );
      if ( WorldStates.size() > MAX_PERIODS_STORED )
         WorldStates.pop_front();

      if ( !NowRepeating ) {
         RepeatPeriod = repeatCheck( WorldStates );
         if ( RepeatPeriod != 0 )
            NowRepeating = true;
      }
      if ( NowRepeating ) {
         switch (RepeatPeriod) {
         case 1:
            cout << " the world is now Still-Life";
            break;
         case 2:
            cout << " Life is Oscillating between two states";
            break;
         default:
            cout << " Life now repeating with a period of: " << RepeatPeriod;
            break;
         }
      }
      cout << " (q:Quit)";
      if ( VoiceOfGod->NumLiving() == 0 ) {
         cout << "\n there is now no more life in this world";
      }
      cout.flush();
      char input = getchar();
      if ( input == QUIT )
         exit = true;

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
