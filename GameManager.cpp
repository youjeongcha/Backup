#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_CreateType = SHAPE_CIRCLE;
	m_CreateTime = CREATE_SEC;
	srand(time(NULL));

	m_Obstacle_B.Init(OBSTACLE_X, OBSTACLE_Y, OBSTACLE_W, OBSTACLE_H);
}

GameManager::~GameManager()
{
	for (auto cList : m_CircleList)
	{
		delete cList;
	}
}

void GameManager::Init(HWND hWnd, HDC m_frontDC)
{
	RECT clientRect;

	m_HWND = hWnd;
	m_backDC = CreateCompatibleDC(m_frontDC); // 'Memory DC'
	//CreateCompatibleDC 함수를 사용해서 DC를 생성하면 이 DC와 연결된 비트맵 객체에는 그림이 그려지지만 화면에는 출력이 되지 않는다.
	//CreateCompatibleDC 함수로 만들어진 DC를 'Memory DC'라고 부른다.
	GetClientRect(m_HWND, &clientRect); //윈도우의 클라이언트의 영역을 알려준다.
	m_Window_WH.x = clientRect.right - clientRect.left;
	m_Window_WH.y = clientRect.bottom - clientRect.top;


	//도형 초기화
	//m_circle.Init(50, 50, 30);
	//m_Box.Init(300, 50, 50, 50); ////////////////////////////
	//중력(아래로만 떨어지고 있기 때문)
	Gravity.y = GRAVITY_VALUE;
}

void GameManager::RandCreateShaoe(float deltaTime)
{
	//5초마다 번갈아가며 도형 생성
	if (m_CreateTime >= CREATE_SEC)
	{
		m_CreateTime = 0;
		//int iRand = int(deltaTime) % 100; //맵의 최대 w으로 설정 ////////////////////////////
		int iRand = rand();

		switch (m_CreateType)
		{
		case SHAPE_CIRCLE:
		{
			//m_CreateType = SHAPE_BOX;

			Circle* newCircle = new Circle();
			newCircle->Init(iRand % MAIN_W, iRand % 30, iRand % SHAPE_MAX_SIZE);
			m_CircleList.push_back(newCircle);

			/////////////////////////////////////////

			iRand = rand();
			Circle* newCircle2 = new Circle();
			newCircle2->Init(iRand % MAIN_W, iRand % 30, iRand % SHAPE_MAX_SIZE);
			m_CircleList.push_back(newCircle2);
			break;
		}
		case SHAPE_BOX:
		{
			m_CreateType = SHAPE_CIRCLE;
			break;
		}
		}
	}
		m_CreateTime += deltaTime;
}


void GameManager::Update(float deltaTime)
{
	//도형 추가
	RandCreateShaoe(deltaTime);
	//Circle* newCircle = new Circle();
	//newCircle->Init(50, 50, 30);
	//m_CircleList.push_back(newCircle);

	//중력 가속도
	Vector2 _Gravity = Gravity * deltaTime;

	for (auto cList : m_CircleList)
	{
		cList->Set_GravityVelocity(_Gravity);
		cList->Update(deltaTime);
	}
	//m_circle.Set_GravityVelocity(_Gravity);
	//m_Box.Set_GravityVelocity(_Gravity);


	//m_circle.Update(deltaTime);
	//m_Box.Update(deltaTime);

	//원 vs 원 충돌
	for (int i = 0; i < m_CircleList.size() - 1; i++)
	{
		for (int j = i + 1; j < m_CircleList.size(); j++)
		{
			//충돌이 발생하면 true (부딪힌 상태에서 다시 체크하러 와서 부딪혔다라고 뜰 수 있다. 해당 건은 아래 if에서 걸러질것)
			if (CirclevsCircle(m_CircleList[i], m_CircleList[j]))
			{
				//penetration과 nomal의 값을 CirclevsCircle 함수 안에서 결정했다.

				//A가 B로 향하는 상대속도(rv) = B의 속도(bv) - A의 속도(av)
				//m_CircleList[i + 1]->m_Velocity - m_CircleList[i]->m_Velocity;

				//두 물체가 멀어지는 중, 충돌 처리를 하지 않는다.(내적(dot)이 > 0 이면 멀어지는 중, 충돌 처리 안함) ( dot < 0 이면 가까워지는 중, 충돌처리 함)
				dot = Dot_(m_CircleList[j]->m_Velocity - m_CircleList[i]->m_Velocity, normal);
				if (dot > 0)
				{
					//충돌
					//float ImpluseMagnitude = -(1.0f + 0.02f) * dot / (m_CircleList[i]->m_InvMass + m_CircleList[j]->m_InvMass);
					//충돌에 의해 발생한 속도
					Vector2 Impulse = normal * -(1.0f + 0.02f) * dot / (m_CircleList[i]->m_InvMass + m_CircleList[j]->m_InvMass);


					//TODO::테스트
					m_CircleList[i]->m_Velocity + Impulse;
					m_CircleList[j]->m_Velocity - Impulse;
				}
			}
		}
	}


	//원 vs 장애물 충돌
	for (int i = 0; i < m_CircleList.size(); i++)
	{
		//충돌이 발생하면 true (부딪힌 상태에서 다시 체크하러 와서 부딪혔다라고 뜰 수 있다. 해당 건은 아래 if에서 걸러질것)
		if (AABBvsCircle(&m_Obstacle_B, m_CircleList[i]))
		{
			//penetration과 nomal의 값을 CirclevsCircle 함수 안에서 결정했다.

			//A가 B로 향하는 상대속도(rv) = B의 속도(bv) - A의 속도(av)
			//m_CircleList[i + 1]->m_Velocity - m_CircleList[i]->m_Velocity;

			//두 물체가 멀어지는 중, 충돌 처리를 하지 않는다.(내적(dot)이 > 0 이면 멀어지는 중, 충돌 처리 안함) ( dot < 0 이면 가까워지는 중, 충돌처리 함)
			dot = Dot_(m_Obstacle_B.m_Velocity - m_CircleList[i]->m_Velocity, normal);
			if (dot > 0)
			{
				//충돌
				//float ImpluseMagnitude = -(1.0f + 0.02f) * dot / (m_CircleList[i]->m_InvMass + m_CircleList[j]->m_InvMass);
				//충돌에 의해 발생한 속도
				Vector2 Impulse = normal * -(1.0f + 0.02f) * dot / (m_CircleList[i]->m_InvMass + m_Obstacle_B.m_InvMass);


				//TODO::테스트
				m_CircleList[i]->m_Velocity = { 0, 0 };
				//m_CircleList[i]->m_Velocity + Impulse;
			}

			//TODO::테스트
			m_CircleList[i]->m_Velocity = { 0, 0 };
		}
	}
	
	//장애물 제한

}

void GameManager::Draw(HDC m_frontDC)
{
	//더블 버퍼링
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Window_WH.x, m_Window_WH.y); //TODO::임시 W H
	SelectObject(m_backDC, backBitmap);

	//장애물 그리기
	m_Obstacle_B.Draw(m_backDC);

	//도형 그리기
	for (auto cList : m_CircleList)
	{
		cList->Draw(m_backDC);
	}
	//m_circle.Draw(m_backDC);
	//m_Box.Draw(m_backDC);


	//더블 버퍼링
	BitBlt(m_frontDC, 0, 0, m_Window_WH.x, m_Window_WH.y, m_backDC, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}



//더블 버퍼링
HBITMAP GameManager::MyCreateDIBSection(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//color bits : 1, 4, 8, 16, 24, 32
	//1:흑백, 4:16색, 8:256색, 16:2^15색, 24,31:2^24색
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; //너비, 비트맵의 가로 픽셀 수
	bm_info.bmiHeader.biHeight = height; //높이, 비트맵의 세로 픽셀 수
	bm_info.bmiHeader.biPlanes = 1; //1로 고정, 반드시 1이어야 한다

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}



bool GameManager::CirclevsCircle(Circle* lhs, Circle* rhs)
{
	//lhs를 중심으로 하는 rhs의 상대 위치
	const Vector2 incident = rhs->m_Position - rhs->m_Position;
	float radiusSum = lhs->m_Radius + rhs->m_Radius;

	//두 원의 반지름으리 합보다 두원 사이의 거리가 크면 충돌하지 않은 상태
	if (incident.SqrMagnitude() > (radiusSum * radiusSum))
		return false;

	float dist = incident.Magitude();
	if (0 != dist)
	{
		penetration = radiusSum - dist;
		normal = incident;
	}
	else
	{
		//두 원은 같은 위치에 있다. 겹쳐있다.
		penetration = lhs->m_Radius;
		normal = Vector2(1, 0);
	}
	normal.Normalize();

	return true;
}

bool GameManager::AABBvsCircle(Box* lhs, Circle* rhs)
{
	const Vector2 incident = rhs->m_Position - lhs->m_Position; // Box를 중심으로 하는 Circle의 상대 위치
	//Box의 너비(width)와 높이(height)의 반(half width, half height)를 구한다.
	float extentX = (lhs->m_Half_W);
	float extentY = (lhs->m_Half_H);

	Vector2 closet;
	closet.x = clamp(incident.x, -extentX, extentX);
	closet.y = clamp(incident.y, -extentY, extentY);

	bool inside = false;
	if (incident == closet) //Box와 Circle이 반 이상 침투했다.
	{
		inside = true;
		if (std::abs(incident.x) > std::abs(incident.y))
		{
			closet.x = (0 < closet.x) ? extentX : -extentX;
		}
		else
			closet.y = (0 < closet.y) ? extentY : -extentY;
	}

	normal = incident - closet;
	float dist = normal.SqrMagnitude();
	float radius = rhs->m_Radius;
	if ((radius * radius) < dist && !inside)
		return false;

	penetration - radius - std::sqrt(dist);
	if (inside)
		normal = -normal; //반 이상으로 침투하면 침투 방향이 뒤집히기 때문에 다시 방향을 되돌려 준다

	normal.Normalize();

	return false;
}