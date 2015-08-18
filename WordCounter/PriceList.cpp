#include "stdafx.h"
#include "PriceList.h"


PriceList::PriceList()
{
	m_Prices[TinOfBeans()] = 40;
	m_Prices[TinOfSoup()] = 90;
	m_Prices[TinOfPeaches()] = 55;
	m_Prices[Coleslaw()] = 50;
}


int PriceList::operator [](const std::string& item)
{
	return m_Prices[item];
}
