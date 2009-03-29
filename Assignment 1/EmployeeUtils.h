#pragma once

#include <boost/thread/mutex.hpp>

#include "Employee.h"

typedef std::vector<Employee*> empContainer;

/*	Employee Utils holds Functors for processing on Employee objects	*/
class EmployeeUtils
{
public:
	/*	Functor that check a given employees data	*/
	class CheckEmployeeData
	{
	private:
		//boost::mutex count_mutex_;//lock used for part count
		boost::mutex pushback_mutex_;//lock used for container
		//int *partialResponses_;//partial count
		empContainer *valid_;//emp container

	public:
		CheckEmployeeData(empContainer *valid);
		void operator() (Employee *emp, int &partialCount);

	};

	/*	Functor that check that a given employee is less
		than a given age which is specified in the constructor */
	class LessThan
	{
	private:
		int age_;
	public:
		LessThan(const int&);
		bool operator() (Employee*);
	};

	/*	Functor that check that a given employee is between
		2 given age which are specified in the constructor */
	class EmployeeAgeBetween
	{
	private:
		int minAge_;
		int maxAge_;
	public:
		EmployeeAgeBetween(const int &minAge, const int &maxAge);
		bool operator() (Employee*);

	};

	/*	Functor that Calcs the MeanSets for a given employee */
	class CalcEmpMeanSets
	{
	public:
		void operator()(Employee *emp) const;

	};

	/*	Functor that Calcs the MeanTextSets for a given employee */
	class CalcEmpTextMeanSets
	{
	public:
		void operator()(Employee *emp) const;

	};
};
