/***********************************************************
 *
 * * Author: Brandon Swanson
 *
 * * Date Created: 08-5-2014
 *
 * * Last Modification Date: 08-5-2014
 *
 * * Filename:
 *
 *
 * * Overview: Week 8 Exercise Component #
 * *
 * * Input:
 * *
 * * Output:
 * *
 * ***********************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "SwansonLibs/swansonInput.hpp"
//#include "SwansonObjects/menu.hpp"

using namespace std;



class Building{
private:

   class Occupant{
   private:
      string name;
   public:
      Occupant(string nameCons):name(nameCons){}
   };

   vector<Occupant> occupants;
   typedef vector<Occupant>::iterator logBook;
   int NumOcupants;

public:
   Building():NumOcupants(0){}

   bool IsInBuilding(string name);
   bool RemoveFromBuilding(string name);
   bool EnterBuilding(string name);


};

bool Building::IsInBuilding(string name){
   for(logBook lb = occupants.begin(); lb != occupants.end(); lb++){
      if(name == *lb) return true;
   }
   return false;
}
bool Building::RemoveFromBuilding(string name){
   if(!IsInBuilding(name)) return false;
   for(logBook lb = occupants.begin(); lb != occupants.end(); lb++){
      if(name == *lb){
         occupants.erase(lb);
         return true;
      }
   }

}
bool Building::EnterBuilding(string name){

   //to do insert

}

/////////////////////////////////////////////////
////////////Introduction and repetition ////////
////////////////////////////////////////////////
int main(){

   struct MenuItem{
      int number;
      string title;
   };

   string intro = "This will log the Ins and Outs of individuals in a building";

   do{

     cout << intro << endl;



   } while ( swansonInput::yesNo( "Would you like to see that again" ) );

   return 0;

}


/////////////////////////////////////////////////
////////////Exercise Component /////////////////
////////////////////////////////////////////////






