#pragma once
#include"Mecro.h"
#include"DrawManager.h"

class Stone
{
private:
	int m_ix;
	int m_iy;
	string m_strShape;
public:
	void SetPosition(int _ix, int _iy);
	void SetPosition(int _ix, int _iy,string _strShape);
	void DrawStone();
	void DrawUndoStone();
	void EraseStone(int _iWidth,int _iHeight);
	bool Compare(Stone stone);
	bool Compare(int _ix,int _iy);
	void Disable(int _iWidth, int _iHeight, bool EraseStatus = false);
	inline int GetX(){ return m_ix; }
	inline int GetY(){ return m_iy; }
	inline void SetLeft(){ m_ix--; }
	inline void SetRight(){ m_ix++; }
	inline void SetUp(){ m_iy--; }
	inline void SetDown(){ m_iy++; } 
	inline void SetShape(string _strShape) { m_strShape = _strShape; }
	Stone();
	Stone(int _ix,int _iy);
	Stone(int _ix, int _iy, string _strShape);
	~Stone();
};

