#pragma once
class ObjectManager
{
private:
public:
	//ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 ture를 리턴한다.
	virtual bool BumpCheck();
};

