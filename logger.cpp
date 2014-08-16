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
#include <iomanip>
#include <vector>
#include "SwansonLibs/swansonInput.hpp"
//#include "SwansonObjects/menu.hpp"

using namespace std;

class Building {
private:

   class Occupant {
   public:
      string name;
      Occupant ( string nameCons ) :
            name( nameCons ) {
      }
   };

   vector<Building::Occupant> occupants;
   typedef vector<Building::Occupant>::iterator logBook;

public:

   bool IsInBuilding ( string name );
   bool RemoveFromBuilding ( string name );
   bool EnterBuilding ( string name );
   int NumberOfOcupants ();
   string GetNamebyNumber ( int logBookNumber ) {
      return occupants.at( logBookNumber - 1 ).name;
   }

   friend ostream& operator << ( ostream& out , Building& bld );

};

//true if occupant of that name is in building
bool Building::IsInBuilding ( string name ) {
   for ( logBook lb = occupants.begin() ; lb != occupants.end() ; lb++ ) {
      if ( name == lb->name )
         return true;
   }
   return false;
}

//removes occupant, returns false if person of that name is not in building
bool Building::RemoveFromBuilding ( string name ) {
   if ( !IsInBuilding( name ) )
      return false;
   for ( logBook lb = occupants.begin() ; lb != occupants.end() ; lb++ ) {
      if ( name == lb->name ) {
         occupants.erase( lb );
         break;
      }
   }
   return true;

}

//inserts new Ocupant, returns false if person of that name is in building
bool Building::EnterBuilding ( string name ) {

   if ( IsInBuilding( name ) )
      return false;
   this->occupants.push_back( Occupant( name ) );
   return true;

}

//return the number of people in the building
int Building::NumberOfOcupants () {
   return this->occupants.size();
}

//this function could also be built using the public methods,
//num tenets and tenet name by number
ostream& operator << ( ostream& out , Building& bld ) {

   //ios::fmtflags flagSettings = out.flags();
   //todo try collumn output

   out <<
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl <<
"~~~~~~~~~~~~~~~~~~~~~~~~~~~BUILDING OCUPANTS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl <<
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl;

   for ( int i = 0 ; i < bld.occupants.size() ; i++ ) {
      out << i + 1 << ": " << bld.occupants.at( i ).name << endl;
   }

   //out.flags(flagSettings);

   out <<
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            << endl;

   return out;
}

/////////////////////////////////////////////////
////////////Introduction and repetition ////////
////////////////////////////////////////////////
struct BldOption {
   int number;
   string title;
};

int displayMenu ( BldOption* options , int numOptions ) {
   for ( int i = 0 ; i < numOptions ; i++ ) {
      cout << options[i].number << ") " << options[i].title << endl;
   }
   return swansonInput::GetInt( "chose an option:" , 1 , numOptions );
}

int main () {

   const BldOption bldIN = { 1, "Admit a person to the building" };
   const BldOption bldOUT = { 2,
         "Log the exit of a person from the building (by Name)" };
   const BldOption bldOUTnm = { 3,
         "Log the exit of a person from the building (by Number)" };
   const BldOption bldDISP = { 4, "Show the occupants of the building" };
   const BldOption bldQUIT = { 5, "Quit Program" };

   int optionNum = 5;
   BldOption options[] = { bldIN, bldOUT, bldOUTnm, bldDISP, bldQUIT };

   string intro = "This will log the Ins and Outs of individuals in a building";

   cout << intro << endl;

   bool exit = false;
   Building myBuilding;

   do {

      int selection = displayMenu( options , optionNum );

      if ( selection == bldIN.number ) {
         string Inname = swansonInput::GetString(
               "What is the name of the new person: " );
         if ( myBuilding.EnterBuilding( Inname ) ) {
            cout << Inname << " added to building logbook" << endl;
         } else {
            cout << "there is already a person of that name in the building"
                  << "\n(this building has weird rules, no duplicate names)"
                  << endl;
         }

      } else if ( selection == bldOUTnm.number ) {

         if(myBuilding.NumberOfOcupants()==0){
            cout << "the building is empty right now\n" << endl;
         }else{
            cout << myBuilding;
            int lbNum = swansonInput::GetInt(
                  "Select the person who is leaving:" ,
                  1 , myBuilding.NumberOfOcupants() );
            myBuilding.RemoveFromBuilding(
                  myBuilding.GetNamebyNumber( lbNum ) );
         }



      }

      else if ( selection == bldOUT.number ) {
         if(myBuilding.NumberOfOcupants()==0){
           cout << "the building is empty right now\n" << endl;
         }else{
            string Outname = swansonInput::GetString(
                  "What is the name of the leaving person: " );
            if ( myBuilding.RemoveFromBuilding( Outname ) ) {
               cout << Outname << " removed from building logbook" << endl;
            } else {
               cout << "there no person of that name in the building" << endl;
            }
         }

      } else if ( selection == bldDISP.number ) {

         cout << myBuilding;

      } else if ( selection == bldQUIT.number ) {
         exit = true;
      }

   } while ( !exit );

   return 0;

}

/////////////////////////////////////////////////
////////////Exercise Component /////////////////
////////////////////////////////////////////////

