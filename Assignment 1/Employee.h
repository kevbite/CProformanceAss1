#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>


#include "CalcSum.h"

typedef std::vector<int> resultsContainer;
typedef std::vector<int> rSetPercContainer;
typedef std::vector<std::string> textRSetPercContainer;
class Employee
{
private:
	int *pinNo_;
	int *age_;
	double *lengthService_;
	std::string *ethnicGroup_;
	std::string *workBasis_;
	resultsContainer *results_;
	rSetPercContainer *resultsSetsPerc_;
	textRSetPercContainer *textResultSet_;
public:

	Employee(void);
	Employee(int *pinNo, int *age, double *los, std::string *ethnicGrp,
		std::string *workBasis, resultsContainer *results);
	~Employee(void);

	const int *getPinNo() const;
	const int *getAge() const;
	const double *getLengthOfService() const;
	const std::string *getEthnicGroup() const;
	const std::string *getWorkBasis() const;
	const resultsContainer *getResults() const;

	rSetPercContainer *getResultSetPercentageMean();
	void calcResultSetPercentageMean();

	textRSetPercContainer *getTextResultSets();
	void calcTextResultSets();

	void clearCached();


	const bool hasTotalInvalidData() const;
	const bool hasTotalInvalidResults() const;

	const bool hasPartialInvalidData() const;
	const bool hasPartialInvalidResults() const;
};
