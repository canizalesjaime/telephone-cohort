/************************************************************************************************************************************** 
 * File    : cohort.h
 * Author  : Jaime Canizales 
 * Purpose : The header file for the cohort class and the setOfCohorts class. A cohort is the set of telephone have exchanged currency 
             between each other or have a common telephone where currency was exchanged. setOfCohorts class represents the set of all 
             cohorts and the functions needed to perform operations with this set. 
 **************************************************************************************************************************************/

#ifndef COHORT_H
#define COHORT_H

#include<vector>
#include<string>
#include <iostream>

using namespace std;

class cohort 
{
  
public:

     /** Constructor. 
 * Constructor with application to DisjSets class. 
 * cohortSet value is intialized to -1 to represent a new set.
 * @param tNumber is the phone number to be added to the new cohort object.
 *  */
    cohort( string tNumber);    

     /** Constructor. 
 * Constructor with application to setOfCohorts class.
 * size_ is initialized to 2 , because every time this constructor is called it creates a cohort of size 2.
 * activity is initialized based off the given value of size_ and the parameter value of v
 * @param id is the cohort id given to the new cohort.
 * @param v is value of the volume when the cohort is constructed.
 *  */
    cohort(int id, double v);

        /** The quantity of telephone numbers in the cohort. 
 * @returns the private variable size_.
 *  */
    int size();

       /** Overloading operator=. 
 * Assigns the values of the right hand side cohort object to the left hand side cohort object. 
 * @param r is the cohort consisting of the information to be copied.
 * @returns the cohort that called the operator with the updated values.
 *  */
    cohort& operator=(const cohort& r);

private:
    int size_;
    double activity;
    double volume;
    int cohort_ID;
    //variables above work with setOfCohorts; variables below work with DisjSets
    vector<string> telephone_Numbers;
    int cohortSet;
    
    friend class DisjSets;
    friend class setOfCohorts;
  
};


//************************************************************************************************************************************
// set of cohorts class using two priority queues

class setOfCohorts
{
    
public :
// Constructor ; intialized with a null cohort
  setOfCohorts();

    /** Insert 
 * Inserts cohort into priority queue. 
 * @param x is a cohort to be added to the the priority queue.
 * @post cohort is postioned into priority queue based off increasing cohort ids order. private variable last is incremented.
 *  */
  void insert(cohort x);

     /** combineCohorts 
 * Takes two existing cohorts and combines them into one. 
 * @param s1 is the cohort ID for one of the two cohorts to be combined.
 * @param s2 is the cohort ID for one of the two cohorts to be combined.
 *  */
     void combineCohorts(int s1, int s2);

     /** updateCohort
 * Updates an existing cohort by adding a telephone number to the set and updating its private variables.
 * @param domSet is the cohort ID for the cohort to be updated.
 * @param v is the transaction amount used to update the variables of the cohort to be updated.
 *  */
     void updateCohort(int domSet, double v);

     /** updateVolume
 * This is function is used when two telephone numbers in the same cohort perform a transaction. Size_ of cohort is not incremented
 * everything else is identical to updateCohort.
 *  */
     void updateVolume(int domSet, double v);
     
  // Creates a max heap based on size
     void heapifySize();

      /** percolateDownSize
 * Organizes a cohort in the appropirate position in accordance with size .
 * @param hole is the starting position of algortihm.
 *  */
     void percolateDownSize(int hole);

   /** biggestCohort
 * Displays the cohort with the largest size, if there is more than one it will display them all.
 * @param out is the stream the output will be displayed onto.
 *  */
     void biggestCohort(ostream& out );
     
  // Creates a max heap based on activity.
     void heapifyActivity();

      /** percolateDownAcitivity 
 * Organizes a cohort in the appropirate position in accordance with activity.
 * @param hole is the starting position of algortihm.
 *  */
     void percolateDownActivity(int hole);

  /** mostActiveCohort
 * Displays the cohort with the largest activity, if there is more than one it will display them all.
 * @param out is the stream the output will be displayed onto.
 *  */
     void mostActiveCohort(ostream& out );
     
   // Sorts the private variable all_Cohorts by cohort ids.
     void heapSortID();

      /** percolateDownID
 * Modified version of percolate down, creates a max heap in accordance with cohort ids, but also decrements the range of the vector 
 * for collaboration with heapSortID .
 * @param hole is the starting position of algortihm.
 * @param j decrements the range of the percolate down algortihm from the end. 
 *  */
     void percolateDownID(int hole, int j);

  /** printIDs
 * Displays the cohort ids in increasing order, displays all cohorts and relating information in increasing order of cohort ids or
 * displays one given cohort and its relating information.
 * @param out is the stream the output will be displayed onto.
 * @param choose is the variable that decides what will be displayed. if choose is -2 it displays all cohort ids and relating information,
 * if choose is -1 it displays all cohort ids in increasing order without the relating information, and if choose is greater than 
 * or equal to 0 it will display the relating information of the cohort whose id is equivalent to choose. 
 *  */
     void printIDs(ostream& out, int choose);

private :
    vector<cohort> all_Cohorts;
    int last;     
};




#endif /* COHORT_H */
