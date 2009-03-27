#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

#include <numeric>
#include <boost/foreach.hpp>

#include "CalcSum.h"

typedef std::vector<int> resultsContainer;
typedef std::vector<int> rSetPercContainer;
typedef std::vector<const std::string*> textRSetPercContainer;

const std::string RED_TEXT = "Red";
const std::string GREEN_TEXT = "Green";
const std::string AMBER_TEXT = "Amber";

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

	const char *Employee::GreenText;
	const char *Employee::RedText;
	const char *Employee::Amber;

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