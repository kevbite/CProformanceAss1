#pragma once
#include "Employee.h"

typedef std::vector<Employee*> empContainer;
	class CheckEmployeeData
	{
	public:
		int *partialResponses_;
		empContainer *valid_;
	public:
		CheckEmployeeData(int *,empContainer *valid);
		void operator() (Employee*);

	};

class EmployeeUtils
{
public:
	class LessThan
	{
	private:
		int age_;
	public:
		LessThan(const int&);
		bool operator() (Employee*);
	};

	class EmployeeAgeBetween
	{
	private:
		int minAge_;
		int maxAge_;
	public:
		EmployeeAgeBetween(const int &minAge, const int &maxAge);
		bool operator() (Employee*);

	};
	class CalcEmpMeanSets
	{
	public:
		void operator()(Employee *emp) const;

	};
	class CalcEmpTextMeanSets
	{
	public:
		void operator()(Employee *emp) const;

	};
};
