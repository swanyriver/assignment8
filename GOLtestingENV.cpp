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

//#include "WorldTools.hpp"
//#include "God.hpp"
#include "GameOfLife.hpp"

#include <map>
#include <set>

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

int main () {

   //typedef set<GOL::cordinate, int, cordComp> coordSet;

   //coordSet mySet;

   typedef set<GOL::cordinate,GOL::cordinate> cordset;

   cordset myset;



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


   cordset::iterator it = myset.begin();

   for(;it!=myset.end();it++){
      cout << it->x << "," << it->y << endl;
   }


}
