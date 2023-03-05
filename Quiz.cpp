#include "Quiz.h"



Quiz::Quiz()
{
	m_iStartNum = 1;
	m_iEndNum = 10;
	SetSum();
}


Quiz::Quiz(int iNum)
{
	m_iStartNum = 1;
	m_iEndNum = iNum;
	SetSum();
}

Quiz::Quiz(int iNum1, int iNum2)
{
	if (iNum1 > iNum2)
	{
		m_iStartNum = iNum2;
		m_iEndNum = iNum1;
	}
	else
	{
		m_iStartNum = iNum1;
		m_iEndNum = iNum2;
	}
	SetSum();
}

void Quiz::SetSum()
{
	m_iSum = 0;
	for (int i = m_iStartNum; i <= m_iEndNum; i++)
		m_iSum += i;
}

Quiz::~Quiz()
{
}
