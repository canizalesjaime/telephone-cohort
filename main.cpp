/****************************************************************************************************************************************
 * File    :  main.cpp
 * Author  :  Jaime Canizales
 * Abstract:  This project is a simplification of the problem of inferring relationships from social networking data. 
 * Purpose :  The program takes a file as input and displays the output on the terminal. The file given will contain data that represents
 *            instructions on how to organize the data and operations that will extract useful information from the data. Described in
 *            further detail below :
 *            1. Money exchanged between two distinct telephone numbers (data that will be stored and updated).
 *                 note*: Telephone numbers must be in the form xxx-xxx-xxxx where x is a non-negative integer
 *            2. The word "find" followed by a telephone number (which outputs the cohort id of the telephone number)
 *            3. The word "members" followed by a cohort id (which outputs the cohort id of the telephone number)
 *            4. The word "max-size" (which outputs the cohort containing the most telephone numbers)
 *            5. The word "max-activity" (which outputs the cohort that has the largest summation of money exchanged to 
 *                   number of telephone numbers ratio.
 *            6. The word "cohort-ids" (which outputs the existing cohorts in increasing order of cohort id)
 *            7. The word "info" followed by a cohort id or "-2"
 *                    (which outputs either all the information of all the cohorts or the information of the given cohort)
 * Usage  : The program will join telephone numbers into a common cohort when money is exchanged amongst them. The amount of money 
 *          that has been excahnged amongst the telephone numbers is also stored in the cohort and is represented in this code as
 *          the private variable volume. Each cohort has a unique id number(cohort id), volume, activity(which is calculated using 
 *          using the amount of telephone numbers in the cohort and the cohorts volume), size (the amount of telephone numbers in the 
 *          cohort), and a list of the telephone numbers in the cohort.
 ****************************************************************************************************************************************/

#include <cstdlib>
#include <unordered_map>
#include <string>
#include "DisjSets.h"
#include "cohort.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef> 

using namespace std;

int main(int argc, char * argv[]) 
{
    
    if(!argv[1])
      {
          cerr<<"A file was not provided on the command line"<<endl;
          return 0;
      }
 
    ifstream input(argv[1]);

    if ( input.fail() )
       {
          cerr<<"failed to open file"<<endl;
          return 0;
       }
    
 //end of file error checking 
//********************************************************************************************************************************
    
     unordered_map<string, int> hashTable;           //data structures used 
     DisjSets myList;                               //
     setOfCohorts my_Cohorts;                      //
     
    int counter = 0;               //used to assign cohort ids
    string line, read;   
    
    while( !input.eof() )
    {
        bool trigger = false;
        bool turn = false;
        getline(input, line);
        stringstream strStream(line); 
        getline(strStream, read, ' ');                   

// end of object declaration
//***************************************************************************************************************************************
        if(read == "data")
        {
            string t1, t2;
            getline(strStream, t1, ' ');
            size_t errorFound = t1.find_first_not_of("0123456789-");
            if ( errorFound != string::npos )
            {
                 cerr<<"error found in input file. line skipped. "<<endl;
                  continue;
            }

            unordered_map<string,int>::const_iterator got = hashTable.find(t1);
            if(got == hashTable.end()) //checks if the first telephone number exists , if it doesnt it adds it to the set 
            {
                hashTable.insert({t1, counter});
                myList.add(t1);
                counter++;
                trigger = true;
            }

            getline(strStream, t2, ' '); 
            errorFound = t2.find_first_not_of("0123456789-");
            if ( errorFound != string::npos )
            {
                 cerr<<"error found in input file. line skipped. "<<endl;
                  continue;
            }
            unordered_map<string,int>::const_iterator got2 = hashTable.find(t2);
            if(got2 == hashTable.end())     //checks if the second telephone number exists , if it doesnt it adds it to the set
            {
                hashTable.insert({t2, counter});
                myList.add(t2);
                counter++;
                turn = true;
            }

            int set1 = myList.find(hashTable[t1]);
            int set2 = myList.find(hashTable[t2]);
            string tAmount;
            getline(strStream, tAmount, ' ');
            string::size_type sz;     // alias of size_t
            double transAmount = stod (tAmount,&sz); 
            if ( transAmount <= 0)
            {
               cerr<<"error found in input file. line skipped. "<<endl;
               continue;
            }

            int dominantSet =  myList.Union(set1, set2);

            if ( trigger && turn)                                              //setofcohort size ++            
            {
               cohort temp(hashTable[t1], transAmount); 
               my_Cohorts.insert(temp);
            }

            else if ( !trigger && !turn)                                   //setofcohort size --
            {                                                              //the only case where its possible to add two complex cohorts 
                if(set1 == set2)
                {
                    my_Cohorts.updateVolume(set1, transAmount);
                }
                
                else {
                        my_Cohorts.updateVolume(set1, transAmount);
                        my_Cohorts.combineCohorts(set1, set2);
                     }
                
            }
            
            else {   //setofcohorts size remains the same. You are taking the dominant set and adding a  telephone # to it 
                    
                    if(trigger)
                    {                  
                        my_Cohorts.updateCohort(dominantSet, transAmount);
                    }
                    
                    else if(turn)
                    {
                       my_Cohorts.updateCohort(dominantSet, transAmount);
                    }

                }
          
        }
 // end of data line algorithm (performs a union between cohorts as well as updating the variables associated with cohorts accessed)
 //****************************************************************************************************************************************
        
        else if(read == "find")
        {
            string number;
            getline(strStream, number);
            size_t errorFound = number.find_first_not_of("0123456789- ");
            if ( errorFound != string::npos )
            {
                 cerr<<"error found in input file. line skipped. "<<endl;
                  continue;
            }
            
            unordered_map<string,int>::const_iterator got3 = hashTable.find(number);
            if(got3 == hashTable.end())
            {
                cout<<number<<" : -1"<<endl;                         //-1 to identify as a non-existent phone number amongst the cohorts
                cout<<"---------------------------------------------------------------------------------------------------------"<<endl;
            }
            
            else {
                   int foundCohortID = myList.find(hashTable[number]);
                   cout<<number<<" : "<<foundCohortID<<endl;
                   cout<<"---------------------------------------------------------------------------------------------------------"<<endl;
                 }
        }
        
 // end of find algorithm (uses a telephone number as a key and find the cohort it belongs to in O(1) )
 //*******************************************************************************************************************************
        
        else if (read == "members")
        {
            string cidflon;
            getline(strStream, cidflon);
            int cohortIDforListOfNumbers;  
            stringstream cohortIDconverter(cidflon);
            cohortIDconverter>>cohortIDforListOfNumbers;
            if (cohortIDforListOfNumbers < 0)
            {
                 cerr<<"error found in input file. line skipped. "<<endl;
                  continue;
            }
            
            myList.members(cout, cohortIDforListOfNumbers);
            
        }
        
        else if (read == "max-size")                 
        {
            my_Cohorts.heapifySize();
            my_Cohorts.biggestCohort(cout);
        }
        
        else if (read == "max-activity")
        {
            my_Cohorts.heapifyActivity();
            my_Cohorts.mostActiveCohort(cout);
        }
        
        else if( read == "cohort-ids")
        {
            my_Cohorts.heapSortID();
            my_Cohorts.printIDs(cout, -1);
        }
        
        else if( read == "info")
        {
            string c;
            getline(strStream, c);
            int cid;  
            stringstream cohortIDconverter(c);
            cohortIDconverter>>cid;
            if (cid < -2)
            {
                 cerr<<"error found in input file. line skipped. "<<endl;
                  continue;
            }
         
            my_Cohorts.heapSortID();
            my_Cohorts.printIDs(cout, cid);
           
        }

        else continue;
                  
        
    } // end of while 
    
    input.close();
    return 0;
}
