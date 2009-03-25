#include "EmployeeCsvReader.h"

EmployeeCsvReader::EmployeeCsvReader(void)
{
}

EmployeeCsvReader::~EmployeeCsvReader(void)
{
}

empContainer* EmployeeCsvReader::loadData(const char *filePath, const int &reserve) const
{
	std::fstream file(filePath, std::ios::in);
	
	/*
	//Do we care if the file is not there or already open?
	if(!file.is_open())
	{
		std::cout << "File not found!\n";
		return 1;
	}*/

	// create an emp container
	empContainer *employees = new empContainer();
	employees->reserve(7200);

	//load CSV data
	parseCSV(file, employees);

	//release the file
	file.close();

	//return the list of employees
	return employees;
}

void EmployeeCsvReader::parseCSV(std::istream &input, empContainer *output) const
{
	std::string csvLine;
	//read the first line as its the headers
	std::getline(input, csvLine);
	// read every line from the stream
	while( std::getline(input, csvLine) )
	{
		//wrap a stream round the line
		std::istringstream csvStream(csvLine);
		
		//parse the CSV line
		Employee *tmpEmp(parseCSVLine(csvStream));
		
		output->push_back(tmpEmp);
	}
}

Employee *EmployeeCsvReader::parseCSVLine(std::istringstream &csvStream) const
{
		//temp used for getting each string between ','s
		std::string tmpColumn;

		//declare Employee varibles
		int *pinNo = 0;
		int *age = 0;
		double *los = 0;
		std::string* ethnicGroup = new std::string();
		std::string* workBasis = new std::string();

		//get the Pin No
		std::getline(csvStream, tmpColumn, ',');
		if(!tmpColumn.empty())
			pinNo = new int(atoi(tmpColumn.c_str()));

		//get the age
		std::getline(csvStream, tmpColumn, ',');
		if(!tmpColumn.empty())
			age = new int(atoi(tmpColumn.c_str()));

		//get Length of Service
		std::getline(csvStream, tmpColumn, ',');
		if(!tmpColumn.empty())
			los = new double(atof(tmpColumn.c_str()));

		//get Ethnic Group
		std::getline(csvStream, *ethnicGroup, ',');
		//Get work Basis
		std::getline(csvStream, *workBasis, ',');
		
		//declare the container for the results
		resultsContainer* results = new resultsContainer();
		results->reserve(70);
		//get all the results from the file
		while( std::getline(csvStream, tmpColumn, ',') )
		{
			if(!tmpColumn.empty())
				results->push_back(atoi(tmpColumn.c_str()));
		}
		
		return new Employee(pinNo, age,
							los, ethnicGroup, workBasis, results);
}