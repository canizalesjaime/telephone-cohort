/************************************************************************************************************************************
 * File    : DisjSets.cpp
 * Author  : Jaime Canizales
 * Purpose : The implementation file for the DisjSets class. These are the functions needed to perform the data line algortihm, find and 
 *           members from the main file.
 ************************************************************************************************************************************/

#include "DisjSets.h"
#include <vector>
#include "cohort.h"
#include <iostream>

using namespace std;

DisjSets::DisjSets()
{
}
 
int DisjSets::Union( int root1 , int root2 ) 
{ 
    if (root1 != root2)
    {
        if ( s[root2].cohortSet < s[root1].cohortSet ) 
        {       
            //root2 is deeper
             s[root2].cohortSet += s[root1].cohortSet; 
             s[root1].cohortSet = root2; 
             for(int i = 0; i < s[root1].telephone_Numbers.size(); i++)
             {
                 s[root2].telephone_Numbers.push_back(s[root1].telephone_Numbers[i]);
             }
             return root2;
        }
        
        else {
                // root1 is deeper 
               s[root1].cohortSet += s[root2].cohortSet; 
               s[root2].cohortSet = root1;
               for(int i = 0; i < s[root2].telephone_Numbers.size(); i++)
               {
                   s[root1].telephone_Numbers.push_back(s[root2].telephone_Numbers[i]);
               }
               return root1;
            }
    }
    
}

int DisjSets::find( int x ) 
{ 
    if ( s[ x ].cohortSet < 0 ) 
        return x; 
    
    else return s[ x ].cohortSet = find( s[ x ].cohortSet );
}

void DisjSets::add( string tNumber)
{
    cohort temp( tNumber);
    s.push_back(temp); 
}

void DisjSets::members(ostream& out, int id)
{
    if( id < 0 || id > s.size() || s[id].cohortSet > -1)
    {
        out<<"\n";
        return;
    }    
    
    out<<"Telephone list"<<"\n";
    
    for(int i = 0; i < s[id].telephone_Numbers.size(); i++)
    {
        out<<s[id].telephone_Numbers[i]<<"\n";         
    }
   
    out<<"\n"<<"---------------------------------------------------------------------------------------------------------"<<"\n";
}
