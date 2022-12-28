#include "HeadRing.h"

THeadRing::THeadRing()
{
	InsLast();
	pHead = pFirst;
	listLen = 0;
	pStop = pHead;
	Reset();
	pFirst->SetNextLink(pFirst);
}

THeadRing::~THeadRing()
{
	TDatList::DelList();
	DelLink(pHead);
	pHead = NULL;
}

void THeadRing::InsFirst(PTDatValue pVal)
{
	TDatList::InsFirst(pVal);
	pHead->SetNextLink(pFirst);
}

void THeadRing::DelFirst()
{
	TDatList::DelFirst();
	pHead->SetNextLink(pFirst);
}
