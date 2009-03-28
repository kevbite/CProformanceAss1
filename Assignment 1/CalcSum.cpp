#include "CalcSum.h"

/*
	Constructor for CalcSum
	-Set the sum to 0
*/
CalcSum::CalcSum(void)
{
	sum_ = new int(0);
}

CalcSum::~CalcSum(void)
{
}
/*
	Get the current Sum
*/
int *CalcSum::getSum() const
{
	return sum_;
}
/*
	Add a given value to the count
*/
void CalcSum::operator ()(const int &i)
{
	*sum_+=i;
}
/*
	Resets the count to 0
*/
void CalcSum::clear()
{
	*sum_=0;
}
