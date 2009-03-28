#pragma once

/*	Keeps a running total of a sum	*/
class CalcSum
{
private:
	int *sum_;

public:
	CalcSum(void);
	~CalcSum(void);
	int *getSum() const;
	void operator()(const int &i);
	void clear();

};
