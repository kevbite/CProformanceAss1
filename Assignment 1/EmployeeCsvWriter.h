#pragma once

#include <fstream>

#include "Employee.h"

typedef std::vector<Employee*> empContainer;

class EmployeeCsvWriter
{
private:
	class WriteCsvLine
	{
	private:
		std::fstream &file_;

	public:
		WriteCsvLine(std::fstream &file);
		void operator() (Employee* emp);
	};

	class WriteCsvSummaryLine
	{
	private:
		std::fstream &file_;

	public:
		WriteCsvSummaryLine(std::fstream &file);
		void operator() (Employee* emp);
	};

	class WriteCsvTextSummaryLine
	{
	private:
		std::fstream &file_;

	public:
		WriteCsvTextSummaryLine(std::fstream &file);
		void operator() (Employee* emp);
	};

public:
	void saveData(const empContainer *emp, const char* filePath) const;
	void saveSummary(const empContainer *emp, const char* filePath) const;
	void saveTextSummary(const empContainer *emp, const char* filePath) const;


};
