#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

#include <numeric>
#include <boost/foreach.hpp>

#include "CalcSum.h"

//some typedef for the containers
typedef std::vector<int> resultsContainer;
typedef std::vector<int> rSetPercContainer;
typedef std::vector<const std::string*> textRSetPercContainer;

//the strings to use for red, green and amber
const std::string RED_TEXT = "Red";
const std::string GREEN_TEXT = "Green";
const std::string AMBER_TEXT = "Amber";
//look up table for text Mark
//results 0-50
static const std::string* markTextTable[] = 
{
  &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT,
  &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT, &RED_TEXT,
  &AMBER_TEXT,&AMBER_TEXT,&AMBER_TEXT,&AMBER_TEXT,&AMBER_TEXT,&AMBER_TEXT,&AMBER_TEXT,&AMBER_TEXT,&AMBER_TEXT, &AMBER_TEXT,
  &GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,
  &GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,&GREEN_TEXT,
  &GREEN_TEXT
	
};

class Employee
{
	
private:
	resultsContainer results_;
	std::string actualData_;
	std::string ethnicGroup_;
	std::string workBasis_;
	double lengthService_;
	int pinNo_;
	int age_;
	static const int MIN_DATA_LENGTH=80;
	rSetPercContainer *resultsSetsPerc_;
	textRSetPercContainer *textResultSet_;

public:
	Employee(void);
	Employee(std::string actualData, int pinNo, int age, double los, std::string ethnicGrp,
		std::string workBasis, resultsContainer results);
	~Employee(void);

	const std::string *getActualData() const;
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