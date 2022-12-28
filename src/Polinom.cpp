#include "Polinom.h"

TPolinom::TPolinom(int monoms[][2], int km)
{
	PTMonom pMonom = new TMonom(0, -1);
	pHead->SetDatValue(pMonom);

	for (int i = 0; i < km; i++)
	{
		if (monoms[i][1] > 999 || monoms[i][1] < 0)
			throw "Error";

		pMonom = new TMonom(monoms[i][0], monoms[i][1]);
		InsLast(pMonom);
	}
}

TPolinom::TPolinom(TPolinom& q)
{
	PTMonom pMonom = new TMonom(0, -1);
	pHead->SetDatValue(pMonom);

	for (q.Reset(); !q.IsListEnded(); q.GoNext())
	{
		PTMonom pMonom = q.GetMonom();
		InsLast(pMonom->GetCopy());
	}
}

PTMonom TPolinom::GetMonom()
{
	return (PTMonom)GetDatValue();
}

TPolinom& TPolinom::operator+(TPolinom& q)
{
	PTMonom pm, qm, rm;
	Reset();
	q.Reset();
	
	while (true)
	{
		pm = GetMonom();
		qm = q.GetMonom();

		if (pm->index < qm->index)
		{
			rm = new TMonom(qm->coeff, qm->index);
			InsCurrent(rm);
			q.GoNext();
		}
		else
			if (pm->index > qm->index)
				GoNext();
			else
			{
				if (pm->index == -1)
					break;

				pm->coeff += qm->coeff;
				if (pm->coeff != 0)
				{
					GoNext();
					q.GoNext();
				}
				else
				{
					DelCurrent();
					q.GoNext();
				}
			}
	}

	return *this;
}

TPolinom& TPolinom::operator=(TPolinom& q)
{
	DelList();
	for (q.Reset(); !q.IsListEnded(); q.GoNext())
	{
		PTMonom pMonom = q.GetMonom();
		InsLast(pMonom->GetCopy());
	}
	return *this;
}

int TPolinom::CalculatePolinom(int x, int y, int z)
{
	int res = 0;
	int indexX;
	int indexY;
	int indexZ;

	for (Reset(); !IsListEnded(); GoNext())
	{
		indexX = GetMonom()->index / 100;
		indexY = (GetMonom()->index / 10) % 10;
		indexZ = GetMonom()->index % 10;
		res += GetMonom()->coeff * std::pow(x, indexX) * std::pow(y, indexY) * std::pow(z, indexZ);
	}

	return res;
}

std::ostream& operator<<(std::ostream& os, TPolinom& q)
{
	int k = 1;
	for (q.Reset(); !q.IsListEnded(); q.GoNext(), k++)
	{
		if (!(k== 1))
		{
			std::cout << " + " << *q.GetMonom();
		}
		else
			std::cout << *q.GetMonom();
	}
	return os;
}

std::istream& operator>>(std::istream& is, TPolinom& q)
{
	int coef = 0;
	int amMon = 0;
	std::string indexStr;
	if (q.listLen != 0)
		q.DelList();

	std::cout << "Enter the count of monoms: ";
	is >> amMon;

	for (q.Reset(); q.currPos < amMon; q.GoNext())
	{
		std::cout << "Coeffs?: ";
		is >> coef;
		if (coef == 0)
			continue;

		std::cout << "Degrees?: " << std::endl << "3-digit number, in a row without symbols: ";
		is >> indexStr;

		if (indexStr.length() > 3)
			throw "Error";

		for (int i = 0; i < indexStr.length(); i++)
		{
			if (isdigit(indexStr[i] == 0))
				throw "Error";
		}

		PTMonom tmp = new TMonom(coef, atoi(indexStr.c_str()));
		q.InsLast(tmp);
	}
	return is;
}
