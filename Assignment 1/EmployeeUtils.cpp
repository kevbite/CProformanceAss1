#include "EmployeeUtils.h"

CheckEmployeeData::CheckEmployeeData(int *partialResponses, empContainer *valid)
:partialResponses_(partialResponses), valid_(valid)
{}
void CheckEmployeeData::operator ()(Employee *emp)
{
	if(emp->hasTotalInvalidData())
	{
		return;
	}
	if(emp->hasPartialInvalidData())
	{
		boost::mutex::scoped_lock lock(count_mutex_);
		++(*partialResponses_);
		return;
	}

	boost::mutex::scoped_lock lock(pushback_mutex_);
	valid_->push_back(emp);
	return;

}
EmployeeUtils::LessThan::LessThan(const int &age)
:age_(age)
{
}

bool EmployeeUtils::LessThan::operator ()(Employee *emp)
{
	return std::less<int>()(*(emp->getAge()), age_);
}

EmployeeUtils::EmployeeAgeBetween::EmployeeAgeBetween(const int &minAge, const int &maxAge)
:minAge_(minAge), maxAge_(maxAge)
{
}

bool EmployeeUtils::EmployeeAgeBetween::operator ()(Employee *emp)
{
	//std::cout << emp->getAge() << " > " << minAge_ << " && " << emp->getAge() << " < " << maxAge_ << std::endl;
	bool result = ((*(emp->getAge())<minAge_) || (*(emp->getAge())>maxAge_));
	return result;
}

void EmployeeUtils::CalcEmpMeanSets::operator()(Employee *emp) const
{
	emp->getResultSetPercentageMean();
}

void EmployeeUtils::CalcEmpTextMeanSets::operator ()(Employee *emp) const
{
	emp->calcTextResultSets();
}
