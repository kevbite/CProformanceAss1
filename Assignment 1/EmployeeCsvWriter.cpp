#include "EmployeeCsvWriter.h"

EmployeeCsvWriter::EmployeeCsvWriter(void)
{
}

EmployeeCsvWriter::~EmployeeCsvWriter(void)
{
}

void EmployeeCsvWriter::saveData(const empContainer *emps, const char *filePath) const
{
	//open the file
	std::fstream file(filePath, std::ios::out);
	//write the headings to the stream
	file << "PIN No,Age,Length Of Service,Ethnic Group,Work Basis,Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8,Q9,Q10,Q11,Q12,Q13,Q14,Q15,Q16,Q17,Q18,Q19,Q20,Q21,Q22,Q23,Q24,Q25,Q26,Q27,Q28,Q29,Q30,Q31,Q32,Q33,Q34,Q35,Q36,Q37,Q38,Q39,Q40,Q41,Q42,Q43,Q44,Q45,Q46,Q47,Q48,Q49,Q50,Q51,Q52,Q53,Q54,Q55,Q56,Q57,Q58,Q59,Q60,Q61,Q62,Q63,Q64,Q65,Q66,Q67,Q68,Q69,Q70" << std::endl;
	//loop though each emp and add them to the file
	std::for_each(emps->begin(),
					emps->end(),
					WriteCsvLine(file));
	//close the file
	file.close();
}
void EmployeeCsvWriter::saveSummary(const empContainer *emps, const char *filePath) const
{
	//open the file
	std::fstream file(filePath, std::ios::out);
	//write the headings to the stream
	file << "PIN No,Q Set1,Q Set2,Q Set3,Q Set4,Q Set5,Q Set6,Q Set7" << std::endl;
	//loop though each emp and add them to the file
	std::for_each(emps->begin(),
					emps->end(),
					WriteCsvSummaryLine(file));
	//close the file
	file.close();
}
void EmployeeCsvWriter::saveTextSummary(const empContainer *emps, const char *filePath) const
{
	//open the file
	std::fstream file(filePath, std::ios::out);
	//write the headings to the stream
	file << "PIN No,Q Set1,Q Set2,Q Set3,Q Set4,Q Set5,Q Set6,Q Set7" << std::endl;
	//loop though each emp and add them to the file
	std::for_each(emps->begin(),
					emps->end(),
					WriteCsvTextSummaryLine(file));
	//close the file
	file.close();
}
EmployeeCsvWriter::WriteCsvLine::WriteCsvLine(std::fstream &file):file_(file){}

void EmployeeCsvWriter::WriteCsvLine::operator ()(Employee *emp)
{
	//output pin, age, los, ethnicGrp, workBasic to stream
	file_ << *(emp->getPinNo()) << ',' << *(emp->getAge()) << ',' << *(emp->getLengthOfService()) << ',' << *(emp->getEthnicGroup()) << ',' << *(emp->getWorkBasis()) << ',';

	//loop though each item in the result
	for(int i(0); i < emp->getResults()->size(); ++i)
	{
		//output the item to the stream
		file_ << (*(emp->getResults()))[i];
		//if its not the last item
		if(i!=(emp->getResults()->size()-1))
			//we need to add a commer
			file_ << ',';
	}
	//write a end line
	file_ << std::endl;
}
EmployeeCsvWriter::WriteCsvSummaryLine::WriteCsvSummaryLine(std::fstream &file):file_(file){}

void EmployeeCsvWriter::WriteCsvSummaryLine::operator ()(Employee *emp)
{
	//output pin, age, los, ethnicGrp, workBasic to stream
	file_ << *(emp->getPinNo()) << ',';

	//loop though each item in the result
	for(int i(0); i < emp->getResultSetPercentageMean()->size(); ++i)
	{
		//output the item to the stream
		file_ << (*emp->getResultSetPercentageMean())[i];
		//if its not the last item
		if(i!=(emp->getResultSetPercentageMean()->size()-1))
			//we need to add a commer
			file_ << ',';
	}
	//write a end line
	file_ << std::endl;
}
EmployeeCsvWriter::WriteCsvTextSummaryLine::WriteCsvTextSummaryLine(std::fstream &file):file_(file){}

void EmployeeCsvWriter::WriteCsvTextSummaryLine::operator ()(Employee *emp)
{
	//output pin, age, los, ethnicGrp, workBasic to stream
	file_ << *(emp->getPinNo()) << ',';

	//loop though each item in the result
	for(int i(0); i < emp->getResultSetPercentageMean()->size(); ++i)
	{
		//output the item to the stream
		file_ << *((*emp->getTextResultSets())[i]);
		//if its not the last item
		if(i!=(emp->getResultSetPercentageMean()->size()-1))
			//we need to add a commer
			file_ << ',';
	}
	//write a end line
	file_ << std::endl;
}