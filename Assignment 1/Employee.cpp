#include "Employee.h"

Employee::Employee(void)
{
}
Employee::Employee(int *pinNo, int *age, double *los, std::string *ethnicGrp,
				   std::string *workBasis, resultsContainer *results):
pinNo_(pinNo), age_(age), lengthService_(los),
ethnicGroup_(ethnicGrp), workBasis_(workBasis), results_(results),resultsSetsPerc_(0)
 {}
Employee::~Employee(void)
{
	delete pinNo_;
	delete age_;
	delete lengthService_;
	delete ethnicGroup_;
	delete workBasis_;
	delete results_;
	delete resultsSetsPerc_;
	delete textResultSet_;
	
}
const bool Employee::hasTotalInvalidData() const
{
	//if any of these fields have data then	
	//the data must be not invalid
	if(age_!=0)
		return false;
	if(!hasTotalInvalidResults())
		return false;
	if(lengthService_!=0 && *lengthService_!=0)
		return false;
	if(!ethnicGroup_->empty())
		return false;
	if(!workBasis_->empty())
		return false;

	//if we got this far all the data 
	//in employee must be invalid
	return true;

}
const bool Employee::hasTotalInvalidResults() const
{
	//sums all the results up and returns if = 0
	
	return std::accumulate(results_->begin(),results_->end(), 0) == 0;
}
const bool Employee::hasPartialInvalidData() const
{
	return age_==0 || lengthService_==0 ||
				ethnicGroup_->empty() ||
				workBasis_->empty() || hasPartialInvalidResults()
				|| *lengthService_==0;

}
const bool Employee::hasPartialInvalidResults() const
{
	//to calc vector size
	int vecSize(0);
	resultsContainer::iterator it = results_->begin();
	resultsContainer::const_iterator end = results_->end();

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
	return pinNo_;
}
const int *Employee::getAge() const
{
	return age_;
}
const double *Employee::getLengthOfService() const
{
	return lengthService_;
}
const std::string *Employee::getEthnicGroup() const
{
	return ethnicGroup_;
}
const std::string *Employee::getWorkBasis() const
{
	return workBasis_;
}
const resultsContainer *Employee::getResults() const
{
	return results_;
}

rSetPercContainer *Employee::getResultSetPercentageMean()
{
	//if not in cached calc it
	if(resultsSetsPerc_==0)  calcResultSetPercentageMean();

	return resultsSetsPerc_;
}
void Employee::calcResultSetPercentageMean()
{
	//create the int and reserve memory
	resultsSetsPerc_ = new std::vector<int>();
	resultsSetsPerc_->reserve(7);
	CalcSum sum;
	//iterate though each Employee

	for(int i(0); i < 70; )
	{
		int j(i+10);
		sum.clear();
		for( ; i<j; ++i)
		{
			sum((*results_)[i]);
		}
		int perc = (*sum.getSum() * 2);
		resultsSetsPerc_->push_back(perc);
	}

	//for(resultsContainer::const_iterator start(results_->begin()); start!=results_->end(); start+=10)
	//{
	//	std::cout << "start: " << *start << " end: " << *(start+10) << std::endl;
	//	//Calc the sum for the Set
	//	int *sumPtr(std::for_each(start, start+10, CalcSum()).getSum());

	//	//double the result to get % as its currenly out of 50 marks
	//	resultsSetsPerc_->push_back(*sumPtr * 2);

	//	//delete the sum from memory
	//	delete sumPtr;
	//}
	return;
}
textRSetPercContainer *Employee::getTextResultSets()
{
	//if not already loaded text data
	if(textResultSet_==0)
		calcTextResultSets();

	return textResultSet_;
}
void Employee::calcTextResultSets()
{
	textResultSet_ = new textRSetPercContainer();
	textResultSet_->reserve(7);

	for(resultsContainer::const_iterator start(results_->begin()); start!=results_->end(); start+=10)
	{
		int *sumPtr(std::for_each(start, start+10, CalcSum()).getSum());
	
		//Select the text based on
		//•	Red < 40,
		//•	Amber >= 40 and < 60,
		//•	Green >= 60 and <= 100

		if(*sumPtr<20) // < 40% mark
		{
			textResultSet_->push_back(&RED_TEXT);
		}else if(*sumPtr>=30) // >= 60% mark
		{
			textResultSet_->push_back(&GREEN_TEXT);
		}else //40% ~ 59%
		{
			textResultSet_->push_back(&AMBER_TEXT);
		}
	}

}

void Employee::clearCached()
{
	delete resultsSetsPerc_;
	resultsSetsPerc_ = 0;

	delete textResultSet_;
	textResultSet_ = 0;
}
