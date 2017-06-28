/**************************************************************************************************************************************
 * File    : DisjSets.h
 * Author  : Jaime Canizales
 * Purpose : THe header file for the DisjSets class. Responsible for creating sets and combining sets using union.
 * 
 **************************************************************************************************************************************/

#ifndef DISJSETS_H
#define DISJSETS_H

#include<vector>
#include"cohort.h"

using namespace std;

class DisjSets 
{

public: 
    
    DisjSets();   // Default Construtor
    
/** Union two disjoint sets. 
  * Assume root1 and root2 are distinct and represent set names. 
  * @param root1 is the root of set 1.
  * @param root2 is the root of set 2. */
    int Union( int root1, int root2); 
    
/** 
  * Perform a recursive find with path compression.  
  * @param x is the element to be found 
  * @return the set containing x. */
    int find(int x); 

/** 
  * Adds a new cohort to the set. 
  * @param tNumber is the telephone m=number associated with the new cohort.  */
    void add( string tNumber);
    
/** 
  * Finds a given set and displays all telephone numbers associated with the given set.  
  * @param out refers to the output stream where the telephone numbers will be displayed. 
  * @param id is the cohort id for the cohort with the desired telephone numbers. */
    void members (ostream& out, int id);
    
private: 
    vector<cohort> s;
};

#endif /* DISJSETS_H */

