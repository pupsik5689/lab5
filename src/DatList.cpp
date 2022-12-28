#include "DatList.h"

PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink)
{
	PTDatLink tmp = new TDatLink(pVal, pLink);
	if (tmp == NULL)
		throw "Error";

	return tmp;
}

void TDatList::DelLink(PTDatLink pLink)
{
	if (pLink != NULL)
	{
		if (pLink->pValue != NULL)
			delete pLink->pValue;

		delete pLink;
	}
}

TDatList::TDatList()
{
	pFirst = NULL;
	pLast = NULL;
	pStop = NULL;
	listLen = 0;
	Reset();
}

TDatList::~TDatList()
{
	DelList();
}

PTDatValue TDatList::GetDatValue(TLinkPos mode)
{
	PTDatLink tmp;

	switch (mode)
	{
	case FIRST:
		tmp = pFirst;
		break;
	case LAST:
		tmp = pLast;
		break;
	default:
		tmp = pCurrLink;
		break;
	}
	
	if (tmp == NULL)
	{
		return NULL;
	}
	else
		return tmp->pValue;
}

int TDatList::IsEmpty() 
{
	return pFirst == pStop;
}

int TDatList::GetListLength() 
{
	return listLen;
}

void TDatList::SetCurrentPos(int pos)
{
	Reset();
	for (int i = 0; i < pos; i++, GoNext());
}

int TDatList::GetCurrentPos()
{
	return currPos;
}

void TDatList::Reset()
{
	pPrevLink = pStop;

	if (IsEmpty())
	{
		pCurrLink = pStop;
		currPos = -1;
	}
	else
	{
		pCurrLink = pFirst;
		currPos = 0;
	}
}

int TDatList::IsListEnded()
{
	return pCurrLink == pStop;
}

void TDatList::GoNext()
{
	if (pCurrLink != pStop)
	{
		pPrevLink = pCurrLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		currPos++;
	}
}

void TDatList::InsFirst(PTDatValue pVal)
{
	PTDatLink tmp = GetLink(pVal, pFirst);

	if (tmp != NULL)
	{
		pFirst = tmp;
		listLen++;
		if (listLen == 1)
		{
			pLast = tmp;
			Reset();
		}
		else
		{
			if (currPos == 0)
				pCurrLink = tmp;
			else
				currPos++;
		}
	}
}

void TDatList::InsLast(PTDatValue pVal)
{
	PTDatLink tmp = GetLink(pVal, pStop);
	
	if (tmp == NULL)
		throw "Error";

	if (pLast != NULL)
		pLast->SetNextLink(tmp);

	pLast = tmp;
	listLen++;

	if (listLen == 1)
	{
		pFirst = tmp;
		Reset();
	}

	if (IsListEnded())
		pCurrLink = tmp;
}

void TDatList::InsCurrent(PTDatValue pVal)
{
	if (IsEmpty() || (pCurrLink == pFirst))
	{
		InsFirst(pVal);
	}
	else
		if (IsListEnded())
			InsLast(pVal);
		else
			if (pPrevLink == pStop)
				throw "Error";
			else
			{
				PTDatLink tmp = GetLink(pVal, pCurrLink);
				if (tmp != NULL)
				{
					pCurrLink = tmp;
					pPrevLink->SetNextLink(tmp);
					listLen++;
				}
			}
}

void TDatList::DelFirst()
{
	if (IsEmpty())
		throw "Error";

	PTDatLink tmp = pFirst;
	pFirst = (PTDatLink)pFirst->GetNextLink();
	DelLink(tmp);
	listLen--;

	if (IsEmpty())
	{
		pLast = pStop;
		Reset();
	}
	else
		if (currPos == 0)
			pCurrLink = pFirst;
		else
			if (currPos == 1)
				pPrevLink = pStop;
	
	if (currPos > 0)
		currPos--;
}

void TDatList::DelCurrent()
{
	if (pCurrLink == pStop)
		throw "Error";
	if (pCurrLink == pFirst)
	{
		DelFirst();
	}
	else
	{
		PTDatLink tmp = pCurrLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		pPrevLink->SetNextLink(pCurrLink);
		DelLink(tmp);
		listLen--;

		if (pCurrLink == pLast)
		{
			pLast = pPrevLink;
			pCurrLink = pStop;
		}
	}
}

void TDatList::DelList()
{
	while (!IsEmpty())
		DelFirst();

	pFirst = pLast = pStop = pCurrLink = pPrevLink;
	currPos = -1;
}
