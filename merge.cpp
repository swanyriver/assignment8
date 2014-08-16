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
#include <set>
#include <cstdlib>
#include "SwansonLibs/swansonInput.hpp"


#include "SwansonLibs/swansonUtils.hpp"

using namespace std;

void demonstrateComponent();

void mergeFiles(ifstream &fileA, ifstream &fileB, ofstream &output);

void openFile(ifstream &stream, string prompt);
void openFile(ofstream &stream, string prompt);


/////////////////////////////////////////////////
////////////Introduction and repetition ////////
////////////////////////////////////////////////
int main(){

   string intro = "I will take in two files of numbers and merge them";

   do{

     cout << intro << endl << endl;
     demonstrateComponent();

   } while ( swansonInput::yesNo( "Would you like to see that again" ) );

   return 0;

}


/////////////////////////////////////////////////
////////////Exercise Component /////////////////
////////////////////////////////////////////////

void demonstrateComponent(){

   //string filename1,filename2,outputfilename;
   ifstream file1in, file2in;
   ofstream output;

   //open two files succesfully
   openFile(file1in,
         "Please enter the path/name of the first number file: ");
   openFile(file2in,
         "Please enter the path/name of the second number file: ");

   //open ofstream
   openFile(output,
            "Please enter the path/name of an output file: ");

   //call merge function

   mergeFiles(file1in,file2in,output);

   file1in.close();
   file2in.close();
   output.close();


}

void openFile(ifstream &stream, string prompt){
   system("ls");
   stream.open(swansonInput::GetString(prompt).c_str());
   while(stream.fail()){
      cout << "i was unable to open that file please" <<
            " check that it exists and try again" << endl;
      system("ls");
      stream.open(swansonInput::GetString(prompt).c_str());
   }

}
void openFile(ofstream &stream, string prompt){
   stream.open(swansonInput::GetString(prompt).c_str());
   while(stream.fail()){
      cout << "i was unable to open that file please" <<
            " check that it exists and try again" << endl;
      stream.open(swansonInput::GetString(prompt).c_str());
   }

}

void mergeFiles(ifstream &fileA, ifstream &fileB, ofstream &output){

   //this is an easy and lightweight solution but if time allows i will
   //implement something more in the spirit of the exercise
   //todo try out zipper merge, synced in and out
   typedef std::multiset<int> sorter;

   sorter myNumbers;
   int number;
   while(fileA >> number) myNumbers.insert(number);
   while(fileB >> number) myNumbers.insert(number);

   for(sorter::iterator it = myNumbers.begin(); it != myNumbers.end(); it++){
      cout << "outputting to file:" << *it << endl;
      output << *it << endl;
   }

}





