#include "CalcSum.h"

CalcSum::CalcSum(void)
{
	sum_ = new int(0);
}

CalcSum::~CalcSum(void)
{
}
int *CalcSum::getSum() const
{
	return sum_;
}
void CalcSum::operator ()(const int &i)
{
	*sum_+=i;
}
void CalcSum::clear()
{
	*sum_=0;
}