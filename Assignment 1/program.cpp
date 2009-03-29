// program.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <conio.h>

#include <boost/bind.hpp> 
#include "threadpool.hpp"

#include "EmployeeCsvReader.h"
#include "EmployeeCsvWriter.h"
#include "EmployeeUtils.h"

#include "MethodTimer.h"

//File Paths
const std::string CSV_DATA_FILE = "c:\\temp\\data.csv";
const std::string CSV_VALID_DATA_FILE = "c:\\temp\\valid.csv";
const std::string CSV_MEAN_DATA_FILE = "c:\\temp\\mean.csv";
const std::string CSV_RAG_DATA_FILE = "c:\\temp\\RAG.csv";

/*
Deletes all the objects the container of pointers are pointing too
*/
void empContainerCleaner(empContainer *container)
{
	//loop though all the items
	for(empContainer::const_iterator it =container->begin(); it!=container->end(); ++it)
	{
		//delete it
		delete (*it);
	}
	//clear valid of the pointers
	container->clear();
	//delete valid
	delete container;
	//set pointer to null
	container = 0;
}
void Q2startSplit(empContainer::const_iterator &begin, empContainer::const_iterator &end,
				  EmployeeUtils::CheckEmployeeData *check, int* partialCount)
{
	//loop though all the emps
	for(empContainer::const_iterator it = begin;it!=end;++it)
		//call the functor on the emp
		(*check)(*it, partialCount);
}
void RunQuestion2(const empContainer *emps)
{
	//#########################################################
	//###################### Set Up ###########################
	//#########################################################

	//create our thread pool
	boost::threadpool::pool pool(4);
	//get our timer instance
	MethodTimer *timer = MethodTimer::Current();

	//#########################################################
	//################# Run Question 2 ########################
	//#########################################################
	std::cout << "Question 2" << std::endl;
	std::cout << "==========" << std::endl;

	std::cout << "-Stripping all valid data" << std::endl;

	//set the start time on timer
	timer->start();

	//create a int to store partial Responses
	//int *partialResponses = new int(0);
	//create a new valid container
	empContainer *valid = new empContainer();
	//reserve some space
	valid->reserve(1603);

	//get the vec size
	int vecSize(emps->size());
	//get a split size if we split it in to the amount of threads in pool
	int splitSize(vecSize/4);
	//create the check functor
	EmployeeUtils::CheckEmployeeData check(valid);
	
	//get the iterator positions for each thread to process
	empContainer::const_iterator it1(emps->begin());
	empContainer::const_iterator it2(it1+splitSize);
	empContainer::const_iterator it3(it2+splitSize);
	empContainer::const_iterator it4(it3+splitSize);
	empContainer::const_iterator it5(emps->end());

	//create the partialCounts
	int partialCount1(0);
	int partialCount2(0);
	int partialCount3(0);
	int partialCount4(0);

	//schedule stuff on to the pool
	pool.schedule(boost::bind<void>(&Q2startSplit, it1, it2, &check, &partialCount1));
	pool.schedule(boost::bind<void>(&Q2startSplit, it2, it3, &check, &partialCount2));
	pool.schedule(boost::bind<void>(&Q2startSplit, it3, it4, &check, &partialCount3));
	pool.schedule(boost::bind<void>(&Q2startSplit, it4, it5, &check, &partialCount4));

	//wait until the pool finishes all its processing
	pool.wait();

	//Add counts together
	int partialCount(partialCount1 + partialCount2 + partialCount3 + partialCount4);
	//stop the timer
	timer->end();

	//output the counts
	//All Records should be 7184
	std::cout << "Record count:" << emps->size() << std::endl;
	//Partial
	std::cout << "Partial Invalid count:" << partialCount << std::endl;
	//All Invalid should be 5582
	std::cout << "All fields Invalid:" << (emps->size() - valid->size()) - partialCount << std::endl;
	//Valid should be 1602
	std::cout << "Valid Data Count :" << valid->size() << std::endl;
	
	//display the time it took to get these results
	timer->displayTimeTaken();

	//Run Question 2 Save
	std::cout << "Question 2: Saving Data" << std::endl;

	EmployeeCsvWriter().saveData(valid, CSV_VALID_DATA_FILE.c_str());

	//Clean Up things
	//we will clear and delete the employees later in the main
	//clear valid of the pointers
	valid->clear();
	//delete valid
	delete valid;
	valid = 0;
}
void RunQuestion3()
{
	//Set up somethings
	MethodTimer *timer = MethodTimer::Current();

	std::cout << "Question 3" << std::endl;
	std::cout << "==========" << std::endl;
	
	//Load Valid Data
	std::cout << "-Loading Data" << std::endl;
	empContainer *validEmpsQ3 = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE.c_str(), 3616);

	std::cout << "-Counting employees less than 30" << std::endl;

	timer->start();
	//count how manny emps as less than 30
	int lessThan30Count = std::count_if(validEmpsQ3->begin(),
						validEmpsQ3->end(), EmployeeUtils::LessThan(30));
	//get end time
	timer->end();
	//display count
	std::cout << std::endl << "Emps less than 30: " << lessThan30Count << std::endl;
	//display time taken
	timer->displayTimeTaken();

	//Clean up
	empContainerCleaner(validEmpsQ3);

}

void RunQuestion4i(empContainer *empsPtr)
{
	//Loop though each emp and calc their mean score sets
	std::for_each(empsPtr->begin(), empsPtr->end(),
		EmployeeUtils::CalcEmpMeanSets());
}

void RunQuestion4ii(empContainer *emps)//gets emps 30-39 and calc means sets
{
	//arrange the data so emps 30-39 are at end
	empContainer::iterator new_end =
		remove_if(emps->begin(), emps->end(), EmployeeUtils::EmployeeAgeBetween(30, 39));

	//erase the data at the end
	emps->erase(new_end, emps->end());

	//get there mean results
	std::for_each(emps->begin(), emps->end(), EmployeeUtils::CalcEmpMeanSets());
}

void RunQuestion4iii(empContainer *emps)//gets emps 30-39 and calc text means sets
{
	//arrange the data so emps 30-39 are at end
	empContainer::iterator new_end =
		remove_if(emps->begin(), emps->end(), EmployeeUtils::EmployeeAgeBetween(30, 39));

	//erase the data at the end
	emps->erase(new_end, emps->end());

	//get the means
	std::for_each(emps->begin(), emps->end(), EmployeeUtils::CalcEmpTextMeanSets());
	
}
void RunQuestion4()
{
	//Set up bit
	//timer we use for timing
	MethodTimer *timer = MethodTimer::Current();
	//create our thread pool for subQuestions
	boost::threadpool::pool pool(2);

	std::cout << "Question 4" << std::endl;
	std::cout << "==========" << std::endl;
	
	//Load 3 sets of questions for Question 4
	std::cout << "-Loading Data" << std::endl;
	empContainer *EmpsQ4_i = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE.c_str(), 3616);
	empContainer *EmpsQ4_ii = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE.c_str(), 3616);
	empContainer *EmpsQ4_iii = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE.c_str(), 3616);

	std::cout << "-running subquestions i, ii, iii" << std::endl;
	timer->start();
	

	//Run Q4 i - Run Find Percentage Mean Score for sub Sets
	pool.schedule(boost::bind<void>(&RunQuestion4i, EmpsQ4_i));
	

	//Runs Q4 ii - emps 30-39 and calc means sets
	//question4_ii(EmpsQ4_ii, EmpsQ4_ii_c, &poolQii);
	pool.schedule(boost::bind<void>(&RunQuestion4ii, EmpsQ4_ii));

	//while we wait for the other threads to process we might as well complete
	//the less heavy question before waiting for threads.
	//Run Q4 iii - age 30-39 + text summery
	RunQuestion4iii( EmpsQ4_iii);

	//wait till all our threads have completed
	pool.wait();
	//stop the timer
	timer->end();
	timer->displayTimeTaken();
	//output EmpQ4i Size
	std::cout << "EmpQ4i Result Count: " << EmpsQ4_i->size() << std::endl;
	//save data from Q4 iii
	std::cout << "-Saving all data" << std::endl;

	//Save the data we have just got
	EmployeeCsvWriter().saveSummary(EmpsQ4_ii, CSV_MEAN_DATA_FILE.c_str());
 	EmployeeCsvWriter().saveTextSummary(EmpsQ4_iii, CSV_RAG_DATA_FILE.c_str());

	std::cout << "-Cleaning up" << std::endl;
	//clean stuff up :)
	empContainerCleaner(EmpsQ4_i);
	empContainerCleaner(EmpsQ4_ii);
	empContainerCleaner(EmpsQ4_iii);

}
int _tmain(int argc, _TCHAR* argv[])
{
	//#########################################################
	//####################Start everything#####################
	//#########################################################	
	
	//Set priority of this process to realtime
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	//timer for timing stuff
	MethodTimer timer;
    
	//output assignment name number and my name
	std::cout << "Effective C++ Assignment 1 (Proformance)" << std::endl;
	std::cout << "By Kevin Smith (15018229)" << std::endl << std::endl;

	//#########################################################
	//################# Run Question 1 ########################
	//#########################################################
	std::cout << "Question 1" << std::endl;
	std::cout << "==========" << std::endl;
	std::cout << "-Loading data from file: " << CSV_DATA_FILE << std::endl;
	//load data from file
	empContainer *emps = EmployeeCsvReader().loadData(CSV_DATA_FILE.c_str(), 7184);

	if(emps->size()==0)//no items loaded
	{
		std::cout << "No data has been loaded! Processing Stopping." << std::endl;
		std::cout << "Press any key to quit";
		std::cin.get();
		return 1;
	}
	std::cout << std::endl;
	
	//#########################################################
	//################# Run Question 2 ########################
	//#########################################################
	RunQuestion2(emps);
	std::cout << std::endl;

	//#########################################################
	//##################Run Question 3#########################
	//#########################################################	
	RunQuestion3();
	std::cout << std::endl;

	//#########################################################
	//##################Run Question 4#########################
	//#########################################################	
	RunQuestion4();
	std::cout << std::endl;

	//#########################################################
	//##################Distroy everything#####################
	//#########################################################	

	//delete the stuff the container is pointing to
	empContainerCleaner(emps);
	
	std::cout << "Cleanup: Destroying Timer..." << std::endl;
	MethodTimer::DeleteCurrent();

	std::cout << "Program Finished" << std::endl;
	std::cin.get();
	//while(!_kbhit());//Makes my laptop like a oven
	
}