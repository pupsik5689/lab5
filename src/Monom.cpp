#include "Monom.h"

TMonom::TMonom(int cval, int ival)
{
	coeff = cval;
	index = ival;
}

TDatValue* TMonom::GetCopy()
{
	TDatValue* tmp = new TMonom(coeff, index);
	return tmp;
}

void TMonom::SetCoeff(int cval)
{
	coeff = cval;
}

void TMonom::SetIndex(int ival)
{
	index = ival;
}

int TMonom::GetCoeff()
{
	return coeff;
}

int TMonom::GetIndex()
{
	return index;
}

TMonom& TMonom::operator=(const TMonom& tm)
{
	coeff = tm.coeff;
	index = tm.index;
	return *this;
}

int TMonom::operator==(const TMonom& tm)
{
	return (coeff == tm.coeff) && (index == tm.index);
}

int TMonom::operator<(const TMonom& tm)
{
	return index < tm.index;
}
