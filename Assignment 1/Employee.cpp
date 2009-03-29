#include "Employee.h"

Employee::Employee(void)
{
}
Employee::Employee(int pinNo, int age, double los, std::string ethnicGrp,
				   std::string workBasis, resultsContainer results):
pinNo_(pinNo), age_(age), lengthService_(los),
ethnicGroup_(ethnicGrp), workBasis_(workBasis), results_(results),resultsSetsPerc_(0),
textResultSet_(0)
 {}
Employee::~Employee(void)
{
	delete resultsSetsPerc_;
	delete textResultSet_;
}
/*
	Returns true if all data in this Employee is invalid
*/
const bool Employee::hasTotalInvalidData() const
{
	//if any of these fields have data then	
	//the data must be not invalid
	if(age_!=0)
		return false;
	//check the first and size first
	if(!(results_[0]==0 ||  results_.size()!=70 || hasTotalInvalidResults()))
		return false;
	if(lengthService_!=0)
		return false;
	if(!ethnicGroup_.empty())
		return false;
	if(!workBasis_.empty())
		return false;

	//if we got this far all the data 
	//in employee must be invalid
	return true;

}

/*
	returns true if this Employee has invalid results
*/
const bool Employee::hasTotalInvalidResults() const
{
	//sums all the results up and returns if = 0
	
	return std::accumulate(results_.begin(),results_.end(), 0) == 0;
}

/*
	returns true if this Employee has partial invalid data
*/
const bool Employee::hasPartialInvalidData() const
{
	return age_==0 || lengthService_==0 ||
				ethnicGroup_.empty() ||
				workBasis_.empty() || hasPartialInvalidResults();

}

/*
	returns true if this employee has partial invalid results
*/
const bool Employee::hasPartialInvalidResults() const
{
	//to calc vector size
	int vecSize(0);
	resultsContainer::const_iterator it = results_.begin();
	resultsContainer::const_iterator end = results_.end();

	while(it!=end)
	{
		if(*it==0)
			return true;
		++vecSize;
		++it;
	}

	return vecSize!=70;

	//check that the emp has 70 results & values are not -1
	/*	return (results_->rend()!=std::find( results_->rbegin(), results_->rend(), 0))
		|| (results_->size()!=70); */
}
const int *Employee::getPinNo() const
{
	return &pinNo_;
}
const int *Employee::getAge() const
{
	return &age_;
}
const double *Employee::getLengthOfService() const
{
	return &lengthService_;
}
const std::string *Employee::getEthnicGroup() const
{
	return &ethnicGroup_;
}
const std::string *Employee::getWorkBasis() const
{
	return &workBasis_;
}
const resultsContainer *Employee::getResults() const
{
	return &results_;
}

/*
	get the result set mean percentage for this instance of employee
	-requires previous call to calcResultSetPercentageMean
*/
rSetPercContainer *Employee::getResultSetPercentageMean()
{
	return resultsSetsPerc_;
}

/*
	Calcs the sub Set means percentage this this instance of Employee
*/
void Employee::calcResultSetPercentageMean()
{
	//create the int and reserve memory
	resultsSetsPerc_ = new std::vector<int>();
	resultsSetsPerc_->reserve(7);
	
	/*
	//##### Old Method #####

	CalcSum sum;
	//iterate though each Employee

	for(int i(0); i < 70; )
	{
		int j(i+10);
		sum.clear();
		for( ; i<j; ++i)
		{
			sum(results_[i]);
		}
		int perc = (*sum.getSum() * 2);
		resultsSetsPerc_->push_back(perc);
	}
*/
	
	//work out the iterators needed
	resultsContainer::const_iterator it(results_.begin());
	resultsContainer::const_iterator end(results_.end());
	
	//loop though each
	for(; it!=end; it+=10)
	{
		//sum is 50% of mark
		int sum(std::accumulate(it,it+10, 0));
		//times by 2 so we get %
		sum *= 2;
		//add it to the results
		resultsSetsPerc_->push_back(sum);
	}

	return;
}

/*
	Returns the Text results sets for this employee
	-Requires previous call to calcTextResultSets
*/
textRSetPercContainer *Employee::getTextResultSets()
{
	return textResultSet_;
}

/*
	Calculates the Text Result set
	for this isntance of Employee
*/
void Employee::calcTextResultSets()
{
	//create new textRSetPercContainer
	textResultSet_ = new textRSetPercContainer();
	//reserve the space
	textResultSet_->reserve(7);

	//work out the iterators needed
	resultsContainer::const_iterator it(results_.begin());
	resultsContainer::const_iterator end(results_.end());
	
	//loop though each
	for(; it!=end; it+=10)
	{
		//sum is 50% of mark
		int sum(std::accumulate(it,it+10, 0));
		
		//Select the text based on
		//•	Red < 40,
		//•	Amber >= 40 and < 60,
		//•	Green >= 60 and <= 100

		//add the result by the lookup table
		textResultSet_->push_back(markTextTable[sum]);

		//Old Method
		//if(sum<20) // < 40% mark
		//{
		//	textResultSet_->push_back(&RED_TEXT);
		//}else if(sum>=30) // >= 60% mark
		//{
		//	textResultSet_->push_back(&GREEN_TEXT);
		//}else //40% ~ 59%
		//{
		//	textResultSet_->push_back(&AMBER_TEXT);
		//}
	}

}

/*
	clears cashed results
	-resultsSetsPerc_
	-textResultSet_
*/
void Employee::clearCached()
{
	delete resultsSetsPerc_;
	resultsSetsPerc_ = 0;

	delete textResultSet_;
	textResultSet_ = 0;
}
