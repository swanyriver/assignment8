/*
 * ToyLife.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: Brandon
 *
 *      Attempting to test out some ideas for next week Game of Life
 */

#include <iostream>
#include <utility>
#include <set>
#include <map>
#include <cstdio>

using namespace std;

struct cord {
   int x;
   int y;
};

struct cell {
   bool alive;
   cord loc;
   int neighbors;
};

class WORLD {

protected:

   const int WORLD_WIDTH;
   const int WORLD_HEIGHT;
   //const ostream MY_OUTS;

   virtual cord* YourNeighbors ( const cord &loc , const int &width ,
         const int &height )=0;
   //return [8] cords

public:
   //////necesary conditions///////////
   /*
    * 2 Generations tracked,
    * living is mapped onto next generation
    * next generations starts off blank
    *    (required to avoid the unchecked isolated cells persisting)
    *
    */

   WORLD ( int width , int height , ostream outs , set<cord> start ) :
         WORLD_WIDTH( width ), WORLD_HEIGHT( height ) ////MY_OUTS(outs)
   {
   }
   ;

   ////////////////////////////
   //called by GOD ////////////
   ////////////////////////////
   virtual void generation () = 0; ///switch generaton data set pointers
   virtual void CountNeighbors ()=0; //mutator method, increments neighbor counts

   ////////////////////////////
   //called by Angel//////////
   ////////////////////////////

   //used to iterate over living cells and their Auroa (neighbor cells)
   // for( ; !world.NeighborCellsEnd() ; myCell = NextNeighbor() ){ }
   virtual bool NeighborCellsEnd () = 0;
   virtual cell NextNeighbor () = 0;

   //answer if there is a living cell in location
   virtual bool IsLiving ( const cord &loc )=0;

   //used to iterate over living cells
   //currently don't plan to use, but I will make it available
   virtual bool LivingCellsEnd () = 0;
   virtual cell NextCell () = 0;

   //called by Angel after Calculations
   virtual void Live ( const cord &loc )=0;
   virtual void Birth ( const cord &loc )=0; //under current design dupes Live
   virtual void Die ( const cord &loc )=0;  //under current design does nothing

   //////////////CALLED BY SOME I/O CONTROLLER////////////
   virtual char** DisplayWorld()=0;
   //or maybe
   //friend ostream& operator << ( ostream &outs , const WORLD* &i );

};

class WorldBuilder {
protected:
   const int WORLD_WIDTH;
   const int WORLD_HEIGHT;
   //ostream MY_OUTS;
public:
   WorldBuilder ( int width , int height , ostream &outs ) :
         WORLD_WIDTH( width ), WORLD_HEIGHT( height ) {
   } //, MY_OUTS(outs) {};
   virtual WORLD* buildWord () = 0;
};

class ANGELofLIFE {
private:
   WORLD *myWorld;
public:
   ANGELofLIFE ( WORLD *world ) :
         myWorld( world ) {
   }
   ;

   virtual void Generation () {
      cell myCell;
      for ( ; !myWorld->NeighborCellsEnd() ;
            myCell = myWorld->NextNeighbor() ) {
         if ( myCell.alive ) {
            if ( myCell.neighbors == 2 )
               myWorld->Live( myCell.loc );
            else
               myWorld->Die( myCell.loc );
         } else { //not living cell
            if ( myCell.neighbors == 3 )
               myWorld->Birth( myCell.loc );
         }
      }
   }
   //mark cells in next generation of world for life
};

class GOD {
private:
   WORLD *myWORLD;
   ANGELofLIFE *myAngel;
public:

   GOD ( WorldBuilder *creator );

   void Generation () {
      myWORLD->generation();
      myWORLD->CountNeighbors();
      myAngel->Generation();
   }
};

int main () {
   pair<int, int> cord1( 5 , 1 );
   pair<int, int> cord2( 1 , 4 );
   pair<int, int> cord3( 3 , 1 );
   pair<int, int> cord4( 3 , 1 );

   std::map<pair<int, int>, int> neighbors;
   //map<int,int> neighbors;

   neighbors.insert( pair<pair<int, int>, int>( cord1 , 7 ) );
   neighbors.insert( pair<pair<int, int>, int>( cord2 , 4 ) );
   neighbors.insert( pair<pair<int, int>, int>( cord3 , 2 ) );
   neighbors.insert( pair<pair<int, int>, int>( cord4 , 3 ) );
   neighbors.insert( pair<pair<int, int>, int>( pair<int, int>( 3 , 5 ) , 3 ) );

   for ( map<pair<int, int>, int>::iterator it = neighbors.begin() ;
         it != neighbors.end() ; it++ ) {
      cout << "cell at " << it->first.first << "/" << it->first.second;
      cout << " has " << it->second << " neighbors" << endl;
   }

   /*
    * I need to learn how to write a custom .less() function object
    * for this to work
    * But storing x,y as first and second in a pair is dangerous
    *
    */
   /*map<cord,int> neighbors2;

    neighbors2.insert(pair<cord,int>(cord{1,1},2));
    neighbors2.insert(pair<cord,int>(cord{5,8},1));
    neighbors2.insert(pair<cord,int>(cord{5,7},3));
    neighbors2.insert(pair<cord,int>(cord{3,1},2));

    cout << "~~~~~~COORD MAP~~~~~~" << endl;

    for(map<cord,int>::iterator it=neighbors2.begin();
    it!=neighbors2.end();it++){
    cout << "cell at " << it->first.x << "/" << it->first.y;
    cout << " has " << it->second << " neighbors" << endl;
    }
    */

}

