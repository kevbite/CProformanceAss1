#include "Employee.h"

Employee::Employee(void)
{
}
Employee::Employee(std::string actualData, int pinNo, int age, double los, std::string ethnicGrp,
				   std::string workBasis, resultsContainer results):
actualData_(actualData), pinNo_(pinNo), age_(age), lengthService_(los),
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
	//if the actual data from file is not correct size
	return actualData_.size()<=MIN_DATA_LENGTH;

	//## Old Method ##
	////if any of these fields have data then	
	////the data must be not invalid
	//if(age_!=0)
	//	return false;
	////check the first and size first
	//if(!(results_[0]==0 ||  results_.size()!=70 || hasTotalInvalidResults()))
	//	return false;
	//if(lengthService_!=0)
	//	return false;
	//if(!ethnicGroup_.empty())
	//	return false;
	//if(!workBasis_.empty())
	//	return false;

	////if we got this far all the data 
	////in employee must be invalid
	//return true;
	//######
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
	//if the emp didnt answer all the questions
	if ( results_.size() != 70)
	{
			return true;
	}
	if(hasPartialInvalidResults())
	{
		return true;
	}
	if(age_==0)
		return true;
	if(lengthService_==0)
		return true;
	if(ethnicGroup_.empty())
		return true;
	
	return workBasis_.empty();

	// ### Old Method ###
	//return age_==0 || lengthService_==0 ||
	//			ethnicGroup_.empty() ||
	//			workBasis_.empty() || hasPartialInvalidResults();

}

/*
	returns true if this employee has partial invalid results
*/
const bool Employee::hasPartialInvalidResults() const
{
	//Look though each one and try and find a 0 (faster than std::find)
	if (results_ [0] == 0 ||results_ [1] == 0 ||results_ [2] == 0 ||results_ [3] == 0 ||results_ [4] == 0 ||results_ [5] == 0 ||results_ [6] == 0 ||results_ [7] == 0 ||results_ [8] == 0 ||results_ [9] == 0 ||
				results_ [10] == 0 ||results_ [11] == 0 ||results_ [12] == 0 ||results_ [13] == 0 ||results_ [14] == 0 ||results_ [15] == 0 ||results_ [16] == 0 ||results_ [17] == 0 ||results_ [18] == 0 ||results_ [19] == 0 ||
				results_ [20] == 0 ||results_ [21] == 0 ||results_ [22] == 0 ||results_ [23] == 0 ||results_ [24] == 0 ||results_ [25] == 0 ||results_ [26] == 0 ||results_ [27] == 0 ||results_ [28] == 0 ||results_ [29] == 0 ||
				results_ [30] == 0 ||results_ [31] == 0 ||results_ [32] == 0 ||results_ [33] == 0 ||results_ [34] == 0 ||results_ [35] == 0 ||results_ [36] == 0 ||results_ [37] == 0 ||results_ [38] == 0 ||results_ [39] == 0 ||
				results_ [40] == 0 ||results_ [41] == 0 ||results_ [42] == 0 ||results_ [43] == 0 ||results_ [44] == 0 ||results_ [45] == 0 ||results_ [46] == 0 ||results_ [47] == 0 ||results_ [48] == 0 ||results_ [49] == 0 ||
				results_ [50] == 0 ||results_ [51] == 0 ||results_ [52] == 0 ||results_ [53] == 0 ||results_ [54] == 0 ||results_ [55] == 0 ||results_ [56] == 0 ||results_ [57] == 0 ||results_ [58] == 0 ||results_ [59] == 0 ||
				results_ [60] == 0 ||results_ [61] == 0 ||results_ [62] == 0 ||results_ [63] == 0 ||results_ [64] == 0 ||results_ [65] == 0 ||results_ [66] == 0 ||results_ [67] == 0 ||results_ [68] == 0 ||results_ [69] == 0 )
	{
			return true;
	}
	//all results are valid
	return false;

	/* ###OLD METHOD 
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

	*/

	//check that the emp has 70 results & values are not -1
	/*	return (results_->rend()!=std::find( results_->rbegin(), results_->rend(), 0))
		|| (results_->size()!=70); */
}
const std::string *Employee::getActualData() const
{
	return &actualData_;
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
