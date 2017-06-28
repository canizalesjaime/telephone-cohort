/*************************************************************************************************************************************
 * File    : cohort.cpp
 * Author  : Jaime Canizales
 * Purpose : The implementation file for the cohort class and the setOfCohorts class. These functions are used for the max-size, 
 *           max-activity, cohort-ids and info operations performed by the main file. setOfCohorts is a priority queue that can be
 *           heapified in two different ways and also implements heap sort for the sorting of the cohorts. 
 ************************************************************************************************************************************/

#include "cohort.h"
#include <iostream>

cohort::cohort( string tNumber)
{
    telephone_Numbers.push_back(tNumber); 
    cohortSet = -1;
}

cohort::cohort( int id, double v ) 
{
    size_ = 2;
    volume = v;
    activity = volume/size_;
    cohort_ID = id;
}

int cohort::size()
{
    return size_;
}

cohort &cohort::operator=(const cohort& r)
{
    size_ = r.size_;
    volume = r.volume;
    cohort_ID = r.cohort_ID;
    activity = r.activity;    
    return *this;
}

//********************************************************************************************************************************
// set of cohorts functions 

setOfCohorts::setOfCohorts()
{
    cohort p1( "aa");                      //creates one null cohort as a place holder to optimize priority queue performance 
    p1.size_ = -1;
    p1.activity = -1;
    p1.volume = -1;
    p1.cohort_ID = -1;
    all_Cohorts.push_back(p1);
    last = 0;
}

void setOfCohorts::insert(cohort x)
{
    all_Cohorts.push_back(x);
    int hole = last + 1;
    for( ; hole > 1 && x.cohort_ID < all_Cohorts[ hole / 2 ].cohort_ID; hole /= 2 )
         all_Cohorts[ hole ] = all_Cohorts[ hole / 2 ];
    all_Cohorts[ hole ] = x;
    last++;
}

void setOfCohorts::combineCohorts(int s1, int s2)
{    
    int set1, set2;
    for(int i = 0; i < all_Cohorts.size(); i++)
    {
        if ( all_Cohorts[i].cohort_ID == s1 )
            set1 = i;   
        
        else if ( all_Cohorts[i].cohort_ID == s2)
            set2 = i;
    }
    
    if(all_Cohorts[set1].size_ > all_Cohorts[set2].size_ || all_Cohorts[set1].size_ == all_Cohorts[set2].size_)
    {
        all_Cohorts[set1].size_ = all_Cohorts[set1].size_ + all_Cohorts[set2].size_;
        all_Cohorts[set1].volume = all_Cohorts[set1].volume + all_Cohorts[set2].volume;
        all_Cohorts[set1].activity = all_Cohorts[set1].volume / all_Cohorts[set1].size_ ;
        
         vector<cohort>::const_iterator it = all_Cohorts.begin();
         it = it + set2;
         all_Cohorts.erase(it);
         last--;
    }    
    
    else {
            all_Cohorts[set2].size_ = all_Cohorts[set2].size_ + all_Cohorts[set1].size_;
            all_Cohorts[set2].volume = all_Cohorts[set2].volume + all_Cohorts[set1].volume;
            all_Cohorts[set2].activity = all_Cohorts[set2].volume / all_Cohorts[set2].size_ ;
  
            vector<cohort>::const_iterator it = all_Cohorts.begin();
            it = it + set1;
            all_Cohorts.erase(it);
            last--;
         }
}

void setOfCohorts::updateCohort(int domSet, double v)
{
    for(int i = 0; i < all_Cohorts.size(); i++)
    {
        if ( all_Cohorts[i].cohort_ID == domSet )
        {
            all_Cohorts[i].volume += v;
            all_Cohorts[i].size_++;
            all_Cohorts[i].activity = all_Cohorts[i].volume / all_Cohorts[i].size_;
            break;
        }
    }
}

void setOfCohorts::updateVolume(int domSet, double v)
{
    for(int i =0; i < all_Cohorts.size(); i++)
    {
        if(all_Cohorts[i].cohort_ID == domSet )
        {
            all_Cohorts[i].volume += v;
            all_Cohorts[i].activity = all_Cohorts[i].volume / all_Cohorts[i].size_;
            break;
        }
    }
}

void setOfCohorts::heapifySize()
{
   for ( int i = last/2; i > 0; i--)
        percolateDownSize(i);
}

void setOfCohorts::percolateDownSize( int hole )
{
    int child;
    cohort tmp (0,0);  
    tmp = all_Cohorts[ hole ];                   
    for( ; hole * 2 <= last; hole = child )
    {
        child = hole * 2 ;
        if( child != last && all_Cohorts[child + 1].size() > all_Cohorts[child].size())
           child++;
        
        if( all_Cohorts[ child ].size() > tmp.size() )
           all_Cohorts[ hole ] = all_Cohorts[ child ];
        
        else break;
    }
    all_Cohorts[ hole ] = tmp;
}

void setOfCohorts::biggestCohort(ostream& out)
{
    out<<"Cohort ID : "<<all_Cohorts[1].cohort_ID<<"\n"
       <<"Size      : "<<all_Cohorts[1].size_<<"\n"
       <<"Volume    : "<<all_Cohorts[1].volume<<"\n"
       <<"Activity  : "<<all_Cohorts[1].activity<<"\n"<<"\n";
    
    for(int i = 2; i <= last; i++)
    {
        if (all_Cohorts[1].size_ == all_Cohorts[i].size_)
        {
              out<<"Cohort ID : "<<all_Cohorts[i].cohort_ID<<"\n"
                 <<"Size      : "<<all_Cohorts[i].size_<<"\n"
                 <<"Volume    : "<<all_Cohorts[i].volume<<"\n"
                 <<"Activity  : "<<all_Cohorts[i].activity<<"\n"<<"\n";
        }
        
        else break;
    }
   
    out<<"---------------------------------------------------------------------------------------------------------"<<"\n";
}

void setOfCohorts::mostActiveCohort(ostream& out)
{
    out<<"Cohort ID : "<<all_Cohorts[1].cohort_ID<<"\n"
       <<"Size      : "<<all_Cohorts[1].size_<<"\n"
       <<"Volume    : "<<all_Cohorts[1].volume<<"\n"
       <<"Activity  : "<<all_Cohorts[1].activity<<"\n"<<"\n";
    
    for(int i = 2; i <= last; i++)
    {
        if (all_Cohorts[1].activity == all_Cohorts[i].activity)
        {
              out<<"Cohort ID : "<<all_Cohorts[i].cohort_ID<<"\n"
                 <<"Size      : "<<all_Cohorts[i].size_<<"\n"
                 <<"Volume    : "<<all_Cohorts[i].volume<<"\n"
                 <<"Activity  : "<<all_Cohorts[i].activity<<"\n"<<"\n";
        }
        
        else break;
    }

    out<<"---------------------------------------------------------------------------------------------------------"<<"\n";
}

void setOfCohorts::heapifyActivity()
{
   for ( int i = last/2; i > 0; i--)
        percolateDownActivity(i);
}

void setOfCohorts::percolateDownActivity( int hole )
{
    int child;
    cohort tmp (0,0);  
    tmp = all_Cohorts[ hole ];                   
    for( ; hole * 2 <= last; hole = child )
    {
        child = hole * 2 ;
        if( child != last && all_Cohorts[child + 1].activity > all_Cohorts[child].activity )
           child++;
        
        if( all_Cohorts[ child ].activity > tmp.activity  )
           all_Cohorts[ hole ] = all_Cohorts[ child ];
        
        else break;
    }
    all_Cohorts[ hole ] = tmp;
}

void setOfCohorts::heapSortID()
{
   for ( int i = all_Cohorts.size()/2; i > 0; i--)
        percolateDownID(i, all_Cohorts.size());
   
   for ( int j = all_Cohorts.size() - 1; j > 0; j--) 
   {
       std::swap (all_Cohorts[1] ,all_Cohorts[j]) ;
       percolateDownID (1, j) ;
   }

}

void setOfCohorts::percolateDownID(int hole, int j)
{
    int child ;
    cohort tmp = all_Cohorts[ hole ];
    while ( hole * 2 <= j - 1 ) 
    {
        child = hole * 2 ;
        if ( child != j -1 && all_Cohorts [child + 1].cohort_ID > all_Cohorts[child].cohort_ID)
            child ++;
        
        if ( all_Cohorts[child].cohort_ID > tmp.cohort_ID )
            all_Cohorts[hole] = all_Cohorts[child];
        
        else break ;
        
        hole = child ;
    }
    all_Cohorts[hole] = tmp ;

}

void setOfCohorts::printIDs(ostream& out, int choose)
{
    
   if(choose == -1)
   {
        for(int i = 1; i <= last; i++)
        {
           out<<"Cohort ID : "<<all_Cohorts[i].cohort_ID<<"\n";
        }
        out<<"\n";
   } 
   else if(choose == -2)
   {
     for(int i = 1; i <= last; i++)
     {
         out<<"Cohort ID : "<<all_Cohorts[i].cohort_ID<<"\n"
            <<"Size      : "<<all_Cohorts[i].size_<<"\n"
            <<"Volume    : "<<all_Cohorts[i].volume<<"\n"
            <<"Activity  : "<<all_Cohorts[i].activity<<"\n"<<"\n";
     }
   }
  
   else if (choose > -1)
   {
       for(int i = 1; i <= last; i++)
       {
           if(all_Cohorts[i].cohort_ID == choose)
           {
                 out<<"Cohort ID : "<<all_Cohorts[i].cohort_ID<<"\n"
                    <<"Size      : "<<all_Cohorts[i].size_<<"\n"
                    <<"Volume    : "<<all_Cohorts[i].volume<<"\n"
                    <<"Activity  : "<<all_Cohorts[i].activity<<"\n"<<"\n";
                 break;
           }
       }
   }
  
   out<<"---------------------------------------------------------------------------------------------------------"<<"\n";
}




