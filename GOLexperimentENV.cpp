/*
 * GOLtestingENV.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: brandon
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

#include "WorldTools.hpp"
#include "God.hpp"
#include "Angel.hpp"
#include "GameOfLife.hpp"

#include "World.hpp"

#include "MapSetWorld.hpp"

#include <map>
#include <set>
#include <utility>

#include <stdexcept> //for catching out of range



using namespace std;

/*class smallWorldB: public WorldBuilder {

};*/

/*struct mycordinate{
      int x,y;

      bool operator() ( const mycordinate &lhs ,
            const mycordinate &rhs ) const {
         //lhs<rhs return true > return false
         //coords are sorted with y highest priority to facilitate console output

         if ( lhs.y < rhs.y ){
            //cerr << "y " << lhs.y << " less than " << rhs.y << endl;
            return true;
         }
         else if((lhs.y == rhs.y) && (lhs.x < rhs.x)){
            //cerr << "x " << lhs.x << " less than " << rhs.x << endl;
            return true;
         }
         else
            return false;

      }

 };*/

/*struct cordComp{
   bool operator() ( const GOL::cordinate &lhs ,
         const GOL::cordinate &rhs ) const {
      //lhs<rhs return true > return false
      //coords are sorted with y highest priority to facilitate console output

      if ( lhs.y < rhs.y )
         return true;
      else if(lhs.x < rhs.x)
         return true;
      else
         return false;

   }
};*/

/*class testWorldAccess{};

testWorldAccess* getID(){
   return new testWorldAccess;
}*/

int inta,intb;
//testing generation switching
void generation (int *pThisGen, int *pNextGen){

   cout << "this:" << *pThisGen << " next:" << *pNextGen << endl;
   cout << "this:" << pThisGen << " next:" << pNextGen << endl;

   int *pTemp = pThisGen;
   pThisGen = pNextGen;
   pNextGen = pTemp;

   cout << "~~~~~~~~~~~switched~~~~~~~~~~" << endl;

   cout << "this:" << *pThisGen << " next:" << *pNextGen << endl;
   cout << "this:" << pThisGen << " next:" << pNextGen << endl;



   //todo double check this assignment

}

void MapTesting();

int main () {

   //MapTesting();

   //test cases
   GOL::cordinate tests[5] = {
         GOL::GetCord(3,4),
         GOL::GetCord(2,2),
         GOL::GetCord(9,9),
         GOL::GetCord(4,0),
         GOL::GetCord(0,0)
   };

   //testing MooreNB function

   cout << "testing neighbor calculation in a 10by10 zero counting (0-9) world"
         << "\nY axis increases downward for ease of print out"
         << "cordinates form: x/y" << endl << endl;

   for (int var = 0; var < 5; ++var) {

      cout << "neighbors of " << tests[var].x << "/" << tests[var].y << endl;

      GOL::cordinate neighbors[8];
      MapSetWorld::YourNeighbors(tests[var],neighbors,10,10);

      //MapSetWorld myWorld(10,10,)

      /*for(int i=0;i<8;i++){
         cout << neighbors[i].x << "/" << neighbors[i].y << "  ";
         if(i==2||i==4) cout << endl;
         if(i==3) cout << "     ";
      }*/
      typedef std::set<GOL::cordinate,GOL::cordinate> cordSet;
      cordSet sortedCords;
      //graphical output
      //sortedCords.insert(tests[var]); //to display considerd cell
      for(int i=0;i<8;i++){
         sortedCords.insert(neighbors[i]);
      }

      //this format should work,  todo move to final implementation
      string output;
      GOL::cordinate lastCord = GOL::GetCord(-1,0);
      output.append(10,'-'); output+='\n';
      for(cordSet::iterator it= sortedCords.begin(); it!= sortedCords.end(); it++){
         if(it->y>lastCord.y){
            output.append(it->y-lastCord.y,'\n');
            lastCord.x=-1;
         }
         output.append((it->x-lastCord.x-1),' ');
         output+="#";
         lastCord = *it;

      }

      output.append(10-lastCord.y,'\n'); //always at least 1

      output.append(10,'-');
      cout << output << endl << endl;
   }

}

void MapTesting(){
   /*//WORLD *myWorld;

   //ANGELofLIFE myAngel(myWorld);

   inta=5;
   intb=7;

   generation(new int(2),new int(4));

   //map<WORLD::WorldAgentID,int> cellAccessors;
   //map<WORLD::WorldAgentID,neighborMap::iterator> neigborAccessors;




   testWorldAccess *accessA = getID();
   testWorldAccess *accessB = getID();

   cout << "pointer a:" << accessA << endl;
   cout << "pointer b value:" << accessB << endl;
   cout << "they are " << ((accessA==accessB)? " equal": " not equal") << endl;
   accessA=accessB;
   cout << "after copy they are " << ((accessA==accessB)? " equal": " not equal") << endl;

   ////maptesting
   //cout << "continue to map testing?";
   //getchar();

   //typedef set<GOL::cordinate, int, cordComp> coordSet;

   //coordSet mySet;

   //typedef set<GOL::cordinate,GOL::cordinate> cordset;


   ///temporary to test int pointer
   typedef std::set<GOL::cordinate,GOL::cordinate> cordSet;
   typedef std::pair<GOL::cordinate,int*> NeighborCount;
   typedef std::map<GOL::cordinate,int*,GOL::cordinate> neighborMap;

   cordSet myset;



   GOL::cordinate a; a.x=2; a.y=2;
   GOL::cordinate b; b.x=1; b.y=3;
   GOL::cordinate c; c.x=4; c.y=5;
   GOL::cordinate d; d.x=2; d.y=4;
   GOL::cordinate e; e.x=2; e.y=4;
   GOL::cordinate f; f.x=77; f.y = 3;

   myset.insert(c);
   myset.insert(a);
   myset.insert(b);
   myset.insert(d);
   myset.insert(e);
   myset.insert(f);
   //myset.insert(GOL::cordinate(10,3));


   cordSet::iterator it = myset.begin();

   for(;it!=myset.end();it++){
      cout << it->x << "," << it->y << endl;
   }

   neighborMap myMap;

   myMap.insert(NeighborCount(GOL::GetCord(3,4),new int(3)));
   myMap.insert(NeighborCount(GOL::GetCord(4,6),new int(4)));
   myMap.insert(NeighborCount(GOL::GetCord(4,3),new int(5)));

   //*myMap.at(GOL::GetCord(3,4))++;
   cout << "there are " << myMap.count(GOL::GetCord(4,6)) << " 4,6" << endl;
   cout << "there are " << myMap.count(GOL::GetCord(3,3)) << " 4,6" << endl;
   cout << "location 3,4 has " << *myMap.at(GOL::GetCord(3,4)) << " neighbors" << endl;

   //cout << "location 70,4 has " << myMap.at(GOL::GetCord(70,4)) << " neighbors" << endl;
   //this terminates ofter throwing std::out_of_range

   int neighbors;
   try{
      neighbors = *myMap.at(GOL::GetCord(70,4));
   }catch(std::out_of_range){  //wow, this is a new approach!
      neighbors = 0;
   }

   ++*myMap.at(GOL::GetCord(3,4)); //this will be the syntax for count

   try{
      ++*myMap.at(GOL::GetCord(3,4));
   }catch(std::out_of_range){  //wow, this is a new approach!
      myMap.insert(NeighborCount(GOL::GetCord(3,4),0));
   }

   try{
      ++*myMap.at(GOL::GetCord(60,4));
   }catch(std::out_of_range){  //wow, this is a new approach!
      myMap.insert(NeighborCount(GOL::GetCord(60,4),0));
   }//doesnt work

   cout << "location 70,4 has " << neighbors << " neighbors" << endl;

   cout << endl;

   neighborMap::iterator mt = myMap.begin();

   for(; mt!= myMap.end(); mt++){
      cout << mt->first.x << "/" << mt->first.y << "  nb:"<< *mt->second << endl;
   }*/
}


/***********************************************************
 * OUTPUT ALGORITHM
 *
//this format should work,  todo move to final implementation
   string output;
   GOL::cordinate lastCord = GOL::GetCord(-1,0);
   for(cordSet::iterator it= sortedCords.begin(); it!= sortedCords.end(); it++){
      if(it->y>lastCord.y){
         output.append(it->y-lastCord.y,'\n');
         lastCord.x=-1;
      }
      output.append((it->x-lastCord.x-1),' ');
      output+="#";
      lastCord = *it;

   }

   output.append(10-lastCord.y,'\n'); //always at least 1
 */
