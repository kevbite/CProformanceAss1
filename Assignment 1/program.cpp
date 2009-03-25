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

#include "EmployeeCsvReader.h"
#include "EmployeeCsvWriter.h"
#include "DisplayEmployeesData.h"
#include "EmployeeUtils.h"

#include "MethodTimer.h"

const char *CSV_DATA_FILE = "D:\\Uni Year 4\\Effective C++\\Performance Assignment\\data.csv";
const char *CSV_VALID_DATA_FILE = "D:\\Uni Year 4\\Effective C++\\Performance Assignment\\valid.csv";
const char *CSV_MEAN_DATA_FILE = "D:\\Uni Year 4\\Effective C++\\Performance Assignment\\mean.csv";
const char *CSV_RAG_DATA_FILE = "D:\\Uni Year 4\\Effective C++\\Performance Assignment\\RAG.csv";

void question4_i(empContainer *empsPtr)
{
	//Loop though each emp and calc their mean score sets
	std::for_each(empsPtr->begin(), empsPtr->end(),
		EmployeeUtils::CalcEmpMeanSets());
}

empContainer *question4_ii(empContainer *emps)//gets emps 30-39 and calc means sets
{
	//create a new container for 30-39's
	empContainer *emps30_39 = new empContainer();
	emps30_39->reserve(1400);
	//arrange the data so emps 30-39 are at end
	std::remove_copy_if(emps->begin(),emps->end(), 
							std::back_inserter(*emps30_39),
							EmployeeUtils::EmployeeAgeBetween(30, 39));

	//get there mean results
	std::for_each(emps30_39->begin(), emps30_39->end(), EmployeeUtils::CalcEmpMeanSets());

	//return the valid data
	return emps30_39;
}

empContainer *question4_iii(empContainer *emps)//gets emps 30-39 and calc text means sets
{
	//create a new container for 30-39's
	empContainer *emps30_39 = new empContainer();
	emps30_39->reserve(1400);
	//arrange the data so emps 30-39 are at end
	std::remove_copy_if(emps->begin(),emps->end(), 
							std::back_inserter(*emps30_39),
							EmployeeUtils::EmployeeAgeBetween(30, 39));

	//get there mean results
	std::for_each(emps30_39->begin(), emps30_39->end(), EmployeeUtils::CalcEmpTextMeanSets());

	//return the valid data
	return emps30_39;
}
int _tmain(int argc, _TCHAR* argv[])
{
	//#########################################################
	//####################Start everything#####################
	//#########################################################	

	MethodTimer timer;


	//#########################################################
	//##################Run Question 1#########################
	//#########################################################
	timer.displayStart("Question 1");
	timer.start();
	
	empContainer *emps = EmployeeCsvReader().loadData(CSV_DATA_FILE, 7184);
	
	timer.end();
	timer.displayEnd();

	//#########################################################
	//##################Run Question 2#########################
	//#########################################################
	int *partialResponses = new int(0);
	empContainer *valid = new empContainer();
	valid->reserve(1603);

	timer.displayStart("Question 2 - Strip all valid data");
	timer.start();
	//total reponses is 7184
	//arrange the data so that all bad data is at end

	std::remove_copy_if(emps->begin(),
		emps->end(), std::back_inserter(*valid),
							CheckEmployeeData(partialResponses));
	timer.end();
	//output the counts
	std::cout << "Partial Invalid Results count :" << *partialResponses << std::endl;
	//All Invalid should be 5582
	std::cout << "All Data Invalid count :" << (emps->size() - valid->size()) << std::endl;
	//Valid should be 1602
	std::cout << "Valid Data Count :" << valid->size() << std::endl;
	
	timer.displayEnd();

	//Run Question 2 Save
	std::cout << "Question 2 - Saving Data" << std::endl;
	EmployeeCsvWriter().saveData(valid, CSV_VALID_DATA_FILE);

	//#########################################################
	//##################Run Question 3#########################
	//#########################################################	
	//Run Question 3 Load Valid Data
	int lessThan30Count;
	std::cout << "Question 3 - Load Data" << std::endl;
	empContainer *validEmpsQ3 = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE, 3616);

	//Run Question 3 
	timer.displayStart("Question 3 - Count employees less than 30");
	timer.start();
	lessThan30Count = std::count_if(validEmpsQ3->begin(),
						validEmpsQ3->end(), EmployeeUtils::LessThan(30));
	timer.end();
	std::cout << "Emps less than 30: " << lessThan30Count << std::endl;
	timer.displayEnd();

	//#########################################################
	//##################Run Question 4#########################
	//#########################################################	

	//Load 3 sets of questions for Question 4
	std::cout << "Question 4 - Load Data" << std::endl;
	empContainer *EmpsQ4_i = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE, 3616);
	empContainer *EmpsQ4_ii = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE, 3616);
	empContainer *EmpsQ4_iii = EmployeeCsvReader().loadData(CSV_VALID_DATA_FILE, 3616);

	//Run Q4 i - Run Find Percentage Mean Score for sub Sets
	timer.displayStart("Question 4i - % Mean sub Sets");
	timer.start();
	question4_i(EmpsQ4_i);
	timer.end();
	timer.displayEnd();

	//Run Q4 ii - Strip anyone thats not 30-39
	timer.displayStart("Question 4ii - % Mean sub Sets + Age30-39");
	timer.start();
	empContainer *EmpsQ4_ii_c = question4_ii(EmpsQ4_ii);
	timer.end();
	//save the data
	std::cout << "Saving Data for Question 4ii" << std::endl;
	EmployeeCsvWriter().saveSummary(EmpsQ4_ii_c, CSV_MEAN_DATA_FILE);
	timer.displayEnd();
	
	//Run Q4 iii - age 30-39 + text summery
	timer.displayStart("Question 4iii - 30-39+% Means txt");
	timer.start();
	empContainer *EmpsQ4_iii_c = question4_iii(EmpsQ4_iii);
	timer.end();
	//save data from Q4 iii
	std::cout << "Saving data for Question 4iii" << std::endl;
	timer.displayEnd();
 	EmployeeCsvWriter().saveTextSummary(EmpsQ4_iii_c, CSV_RAG_DATA_FILE);


	//#########################################################
	//##################Distroy everything#####################
	//#########################################################	

	std::cin.get();
	//while(!_kbhit());//Makes my laptop like a oven
	
}