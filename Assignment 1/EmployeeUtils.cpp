#include "EmployeeUtils.h"

/*
Constructor for 
EmployeeUtils::CheckEmployeeData::CheckEmployeeData
*/
EmployeeUtils::CheckEmployeeData::CheckEmployeeData(int *partialResponses, empContainer *valid)
:partialResponses_(partialResponses), valid_(valid)
{}

/*
Checks if a user has valid data (Thread Safe)
--Increments partialResponses_ if partial responses is found
--If valid data then added to a valid_ container
*/
void EmployeeUtils::CheckEmployeeData::operator ()(Employee *emp)
{
	if(emp->hasTotalInvalidData())
	{
		return;
	}
	if(emp->hasPartialInvalidData())
	{
		//requires lock until end of scope
		boost::mutex::scoped_lock lock(count_mutex_);
		++(*partialResponses_);
		return;
	}

	//requires lock until end of scope
	boost::mutex::scoped_lock lock(pushback_mutex_);
	valid_->push_back(emp);
	return;
}

/*
Constructor for
EmployeeUtils::LessThan::LessThan
-Sets the age to check less than
*/
EmployeeUtils::LessThan::LessThan(const int &age)
:age_(age)
{
}

/*
Checks to see if a employee's age is less than age_
*/
bool EmployeeUtils::LessThan::operator ()(Employee *emp)
{
	return *(emp->getAge()) < age_;
	//return std::less<int>()(*(emp->getAge()), age_); <-- Slow
}

/*
Constructor for 
EmployeeUtils::EmployeeAgeBetween::EmployeeAgeBetween
-Sets the minAge_ and maxAge to check if the employee age is between
*/
EmployeeUtils::EmployeeAgeBetween::EmployeeAgeBetween(const int &minAge, const int &maxAge)
:minAge_(minAge), maxAge_(maxAge)
{
}

/*
Checks to see if the employee is in the age
range is Between minAge_ and maxAge_
*/
bool EmployeeUtils::EmployeeAgeBetween::operator ()(Employee *emp)
{
	//Slow
	/*return !(std::less<int>()(*(emp->getAge()), minAge_)
			|| std::greater<int>()(*(emp->getAge()), maxAge_));*/
	
	return ((*(emp->getAge())>maxAge_)||(*(emp->getAge())<minAge_));
}

/*
Calls the Employee::getResultSetPercentageMean on the employee object given
*/
void EmployeeUtils::CalcEmpMeanSets::operator()(Employee *emp) const
{
	emp->calcResultSetPercentageMean();
}
/*
Calls the Employee::calcTextResultSets on the employee object given
*/
void EmployeeUtils::CalcEmpTextMeanSets::operator ()(Employee *emp) const
{
	emp->calcTextResultSets();
}
