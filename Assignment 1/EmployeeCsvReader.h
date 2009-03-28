#pragma once
#include <string>
#include <fstream>
#include <string>
#include <sstream>

#include "Employee.h"

typedef std::vector<Employee*> empContainer;

/* Loads data from a Csv file to a empContainer */
class EmployeeCsvReader
{
private:
	void parseCSV(std::istream &input, empContainer *output) const;
	Employee *parseCSVLine(std::istringstream &csvStream) const;

public:
	empContainer* loadData(const char *filePath, const int &reserve) const;


};
