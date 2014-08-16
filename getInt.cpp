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
#include <climits>

using namespace std;

void demonstrateComponent();



/******************************************************************************
 *    purpose: receive a value from the user, screen for alpha input
 *             and overflow, restrict input to specific range
 *
 *    entry: a string to be used to clarify desired input to user
 *
 *    exit: a value between rangeMin and rangeMax
 ******************************************************************************/

int GetInt ( string prompt , int rangeMin=INT_MIN , int rangeMax = INT_MAX) {
   int int_rtrn;
   string parse_string;
   bool firstTimeThrough = true;

   do {
      if ( !firstTimeThrough ) {
         cout << "Please keep the input within these bounds [" << rangeMin
               << " - " << rangeMax << "]";
      }
      firstTimeThrough = false;
      parse_string = swansonInput::GetString( prompt );

      while ( !swansonString::AllNumbers( parse_string ) || parse_string.empty() ) {

         cout << "lets try to restrain ourselves to only whole numbers";
         parse_string = swansonInput::GetString( prompt );
      }

      stringstream extract(parse_string);
      extract >> int_rtrn;

   } while ( !(int_rtrn >= rangeMin && int_rtrn <= rangeMax) );

   return int_rtrn;
}


/////////////////////////////////////////////////
////////////Introduction and repetition ////////
////////////////////////////////////////////////
int main(){

   string intro = "";

   do{

     cout << intro;
     demonstrateComponent();

   } while ( swansonInput::yesNo( "Would you like to enter another number" ) );

   return 0;

}


/////////////////////////////////////////////////
////////////Exercise Component /////////////////
////////////////////////////////////////////////

void demonstrateComponent(){

   int inptNum = GetInt("What is the number [-1000,1000]:",-1000,1000);
   cout << "the number is " << inptNum
         << " and as a hex " << std::hex << inptNum
         << std::dec << endl;

}




