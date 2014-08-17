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

using namespace std;

void demonstrateComponent();
string openFile(ifstream &stream, string prompt);
int Average (int a, int b);
int FileValAt(string filename, int position, bool average=false);
bool even(int eveodd);

/////////////////////////////////////////////////
////////////Introduction and repetition ////////
////////////////////////////////////////////////
int main(){

   string intro = "I will open a file containing sorted ints and tell you the "
         "three quartiles.\nI will use the Ti-83 method and not include the"
         " median in the percentiles for 1st and 3rd quartile";

   do{

     cout << endl << endl << intro << endl << endl;
     demonstrateComponent();

   } while ( swansonInput::yesNo( "Would you like to see that again" ) );

   return 0;

}


/////////////////////////////////////////////////
////////////Exercise Component /////////////////
////////////////////////////////////////////////

void demonstrateComponent(){
   ifstream dataF;

   int median;
   int quartiles[3];
   string quartileNames[3] = {" first ", " second " , " third "};

   int ignoredNumber;

   int NUM_ENTRIES=0;

   int numFiftyPercent;

   string filename=openFile(dataF, "What is the file/path of the data file: ");

   //count number of entries
   while (dataF >> ignoredNumber) NUM_ENTRIES++;

   ///////////testing code/////////////////////////////////
  /* cout << "num entries is:" << NUM_ENTRIES << endl;
   cout << endl << "number at 10 is:" << FileValAt(filename,10);
   cout << endl << "number at 45 is:" << FileValAt(filename,45);
   cout << endl << "average at 39 and 40 is:" << FileValAt(filename,39,true);*/
   /////////////////end testing code//////////////////////


   //find median
   if(even(NUM_ENTRIES)){
      numFiftyPercent = NUM_ENTRIES/2;
      median = FileValAt(filename,numFiftyPercent,true);

   }else{
      numFiftyPercent = (NUM_ENTRIES-1)/2;
      median = FileValAt(filename,numFiftyPercent+1);
   }

   quartiles[1] = median;


   //find first and second quartile
   if(even(numFiftyPercent)){
      quartiles[0] = FileValAt(filename,numFiftyPercent/2,true);
      quartiles[2] = FileValAt(filename,NUM_ENTRIES-(numFiftyPercent/2),true);
   }else{
      quartiles[0] = FileValAt(filename,(numFiftyPercent+1)/2);
      quartiles[2] = FileValAt(filename,NUM_ENTRIES-((numFiftyPercent-1)/2));
   }

   cout << endl << "Resluts:" << endl;

   for(int i=0;i<3;i++){
      cout << "The" << quartileNames[i] << "is:" << quartiles[i] << endl;
   }
   cout << endl << endl;



}

string openFile(ifstream &stream, string prompt){
   string filename;
   system("ls");
   filename = swansonInput::GetString(prompt);
   stream.open(filename.c_str());
   while(stream.fail()){
      cout << "\n\ni was unable to open that file please" <<
            " check that it exists and try again" << endl;
      system("ls");
      filename = swansonInput::GetString(prompt);
      stream.open(filename.c_str());
   }

   return filename;

}

int FileValAt(string filename, int position, bool avg){
   ifstream dataF(filename.c_str());
   int ignoredNumber, retrievedNumber;
   int ReadEntries = 1;

   while(ReadEntries<position && dataF >> ignoredNumber) ReadEntries++;

   dataF >> retrievedNumber;

   if(avg){
      int nextNumber;
      dataF >> nextNumber;
      retrievedNumber = Average(nextNumber, retrievedNumber);
   }

   dataF.close();

   return retrievedNumber;

}

int Average (int a, int b){
   return (a+b)/2;
}

bool even(int eveodd){
   return (eveodd%2 == 0);
}



