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

#include <boost/foreach.hpp>
#include <boost/bind.hpp> 
#include "threadpool.hpp"


#include "EmployeeCsvReader.h"
#include "EmployeeCsvWriter.h"
#include "DisplayEmployeesData.h"
#include "EmployeeUtils.h"

#include "MethodTimer.h"

const char *CSV_DATA_FILE = "c:\\temp\\data.csv";
const char *CSV_VALID_DATA_FILE = "c:\\temp\\valid.csv";
const char *CSV_MEAN_DATA_FILE = "c:\\temp\\mean.csv";
const char *CSV_RAG_DATA_FILE = "c:\\temp\\RAG.csv";

void question4_i(empContainer *empsPtr)
{
	//Loop though each emp and calc their mean score sets
	std::for_each(empsPtr->begin(), empsPtr->end(),
		EmployeeUtils::CalcEmpMeanSets());
}

void question4_ii(empContainer *emps, empContainer *results /*return*/)//gets emps 30-39 and calc means sets
{
	//reserve the space
	results->reserve(1400);
	//arrange the data so emps 30-39 are at end
	std::remove_copy_if(emps->begin(),emps->end(), 
							std::back_inserter(*results),
							EmployeeUtils::EmployeeAgeBetween(30, 39));

	//get there mean results
	std::for_each(results->begin(), results->end(), EmployeeUtils::CalcEmpMeanSets());
}

void question4_iii(empContainer *emps, empContainer *results /*return*/)//gets emps 30-39 and calc text means sets
{
	//reserve space
	results->reserve(1400);
	//arrange the data so emps 30-39 are at end
	std::remove_copy_if(emps->begin(),emps->end(), 
							std::back_inserter(*results),
							EmployeeUtils::EmployeeAgeBetween(30, 39));

	//get the means
	std::for_each(results->begin(), results->end(), EmployeeUtils::CalcEmpTextMeanSets());
	
}

void startSplit(empContainer::const_iterator &begin, empContainer::const_iterator &end,
				CheckEmployeeData *check)
{
	
	for(empContainer::const_iterator it = begin;it!=end;++it)
		(*check)(*it);

}
void RunQuestion2(const empContainer const *emps)
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

	std::cout << "_____Question 2 - Strip all valid data______" << std::endl;

	//set the start time on timer
	timer->start();

	//create a int to store partial Responses
	int *partialResponses = new int(0);
	//create a new valid container
	empContainer *valid = new empContainer();
	//reserve some space
	valid->reserve(1603);

	//get the vec size
	int vecSize(emps->size());
	//get a split size if we split it 4 times
	int splitSize(vecSize/4);
	//create the check functor
	CheckEmployeeData check(partialResponses, valid);
	
	//schedule stuff on to the pool
	pool.schedule(boost::bind<void>(&startSplit, emps->begin(), emps->begin()+splitSize, &check));
	pool.schedule(boost::bind<void>(&startSplit, emps->begin()+splitSize, emps->begin()+(splitSize*2), &check));
	pool.schedule(boost::bind<void>(&startSplit, emps->begin()+(splitSize*2), emps->begin()+(splitSize*3), &check));
	pool.schedule(boost::bind<void>(&startSplit, emps->begin()+(splitSize*3), emps->end(), &check));

	//wait until the pool finishes all its processing
	pool.wait();

	//stop the timer
	timer->end();

	//output the counts
	//All Records should be 7184
	std::cout << "All Record count :" << emps->size() << std::endl;
	//Partial
	std::cout << "Partial Invalid Results count :" << *partialResponses << std::endl;
	//All Invalid should be 5582
	std::cout << "Records with all fields Invalid :" << (emps->size() - valid->size()) - *partialResponses << std::endl;
	//Valid should be 1602
	std::cout << "Valid Data Count :" << valid->size() << std::endl;
	
	//display the time it took to get these results
	timer->displayTimeTaken();

	//Run Question 2 Save
	std::cout << "Question 2 - Saving Data" << std::endl;
	EmployeeCsvWriter().saveData(valid, CSV_VALID_DATA_FILE);

}
void RunQuestion3()
{
	//Set up somethings
	MethodTimer *timer = MethodTimer::Current();

	//Load Valid Data
	std::cout << "______Question 3 - Load Data______" << std::endl;
	empContainer *validEmpsQ3 = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE, 3616);

	std::cout << "______Question 3 - Count employees less than 30____" << std::endl;

	timer->start();
	//count how manny emps as less than 30
	int lessThan30Count = std::count_if(validEmpsQ3->begin(),
						validEmpsQ3->end(), EmployeeUtils::LessThan(30));
	//get end time
	timer->end();
	//display count
	std::cout << "Emps less than 30: " << lessThan30Count << std::endl;
	//display time taken
	timer->displayTimeTaken();
}
void RunQuestion4()
{
	//Set up bit
	//timer we use for timing
	MethodTimer *timer = MethodTimer::Current();
	//create our thread pool for subQuestions
	boost::threadpool::pool pool(2);
	
	//Load 3 sets of questions for Question 4
	std::cout << "_________Question 4 - Load Data__________" << std::endl;
	empContainer *EmpsQ4_i = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE, 3616);
	empContainer *EmpsQ4_ii = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE, 3616);
	empContainer *EmpsQ4_iii = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE, 3616);

	std::cout << "_______Running all Question 4 subitems________" << std::endl;
	timer->start();
	
	//create our pointer that will return our results
	empContainer *EmpsQ4_ii_c = new empContainer();
	empContainer *EmpsQ4_iii_c = new empContainer();


	//Runs Q4 ii - emps 30-39 and calc means sets
	//question4_ii(EmpsQ4_ii, EmpsQ4_ii_c, &poolQii);
	pool.schedule(boost::bind<void>(&question4_ii, EmpsQ4_ii, EmpsQ4_ii_c));
	//Run Q4 iii - age 30-39 + text summery
	//question4_iii(EmpsQ4_iii, EmpsQ4_iii_c, &poolQii);
	pool.schedule(boost::bind<void>(&question4_iii, EmpsQ4_iii, EmpsQ4_iii_c));

	//while we wait for the other threads to process we might as well complete
	//the less heavy question before waiting for threads.
	//Run Q4 i - Run Find Percentage Mean Score for sub Sets
	question4_i(EmpsQ4_i);

	//wait till all our threads have completed
	pool.wait();
	//stop the timer
	timer->end();
	timer->displayTimeTaken();

	//save data from Q4 iii
	std::cout << "Saving All data for Question" << std::endl;

	//Save the data we have just got
	EmployeeCsvWriter().saveSummary(EmpsQ4_ii_c, CSV_MEAN_DATA_FILE);
 	EmployeeCsvWriter().saveTextSummary(EmpsQ4_iii_c, CSV_RAG_DATA_FILE);
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
    

	//#########################################################
	//################# Run Question 1 ########################
	//#########################################################
	std::cout << "_____Question 1_____" << std::endl;
	std::cout << "Loading Data from file: " << CSV_DATA_FILE << std::endl;
	//load data from file
	empContainer *emps = EmployeeCsvReader().loadData(CSV_DATA_FILE, 7184);
	
	
	//#########################################################
	//################# Run Question 2 ########################
	//#########################################################
	RunQuestion2(emps);

	//#########################################################
	//##################Run Question 3#########################
	//#########################################################	
	RunQuestion3();

	//#########################################################
	//##################Run Question 4#########################
	//#########################################################	
	RunQuestion4();

	//#########################################################
	//##################Distroy everything#####################
	//#########################################################	
	std::cout << "Destroying Timer..." << std::endl;
	MethodTimer::DeleteCurrent();

	std::cout << "Program Finished" << std::endl;
	std::cin.get();
	//while(!_kbhit());//Makes my laptop like a oven
	
}