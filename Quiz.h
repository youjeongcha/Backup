#pragma once
class Quiz
{
private:
	int m_iSum;
	int m_iStartNum;
	int m_iEndNum;
public:
	Quiz();
	Quiz(int iNum);
	Quiz(int iNum1,int iNum2);
	void SetSum();
	inline int GetSum()
	{
		return m_iSum;
	}
	~Quiz();
};

