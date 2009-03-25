#pragma once

#include <iostream>

#include "Employee.h"

class DisplayEmployeesData
{
private:
	const bool &showPin_;
	const bool &showAge_;
	const bool &showLOS_;
	const bool &showEthGrp_;
	const bool &showWrkBasis_;
	const bool &showResults_;
	const bool &showResultPerc_;
public:
	DisplayEmployeesData(const bool &showPin = true,
						   const bool &showAge = false,
						   const bool &showLOS = false,
						   const bool &showEthGrp = false,
						   const bool &showWrkBasis = false,
						   const bool &showResults = false,
						   const bool &showResultPerc = true);
	~DisplayEmployeesData(void);

	void operator()(Employee *emp);

};
