#include "DisplayEmployeesData.h"

DisplayEmployeesData::DisplayEmployeesData(const bool &showPin,
										   const bool &showAge,
										   const bool &showLOS,
										   const bool &showEthGrp,
										   const bool &showWrkBasis,
										   const bool &showResults,
										   const bool &showResultPerc)
										   :showPin_(showPin), showAge_(showAge),
										   showLOS_(showLOS), showEthGrp_(showEthGrp),
										   showWrkBasis_(showWrkBasis), showResults_(showResults),
										   showResultPerc_(showResultPerc)
{
}
DisplayEmployeesData::~DisplayEmployeesData(void)
{
}
void DisplayEmployeesData::operator()(Employee *emp)
{
	if(showPin_)
		std::cout << *(emp->getPinNo()) << "\t";
	if(showAge_)
		std::cout << *(emp->getAge()) << "\t";
	if(showLOS_)
		std::cout << *(emp->getLengthOfService()) << "\t";
	if(showEthGrp_)
		std::cout << *(emp->getEthnicGroup()) << "\t";
	if(showWrkBasis_)
		std::cout << *(emp->getWorkBasis()) << "\t";
	if(showResults_)
	{
		for(resultsContainer::const_iterator it = emp->getResults()->begin();
			it != emp->getResults()->end(); ++it)
			std::cout << *it << "\t";
	}
	if(showResultPerc_)
	{
		for(resultsContainer::const_iterator it = emp->getResultSetPercentageMean()->begin();
			it != emp->getResultSetPercentageMean()->end(); ++it)
			std::cout << *it << "\t";
	}

}
