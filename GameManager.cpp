#include "GameManager.h"

/*-사각형은 회전 되지 않는다.
-바닥에서 튕기는 듯한 현상(바닥을 파고든만큼 다시 위로 튕겨내고 있어서)
-높은 곳에서 떨어지면 가끔 땅을 파고 드는 것. 이건 떨림 보정까지 해야 해결 되는 것. 현재 코드 구조에서는 정상 작동이 되는 것이다.
-시작 점에서 겹치게 생겨난 도형은 충돌 체크가 되지 않는다. 처음부터 파고든 상태로 생겨나서. 인지를 못함*/

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_CreateType = SHAPE_CIRCLE;
	m_CreateTime = CREATE_SEC;
	srand(time(NULL));
}

GameManager::~GameManager()
{
	for (auto cList : m_ShapeList)
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

	//Circle* m_Obstacle_B = new Circle();
	//m_Obstacle_B->Init(OBSTACLE_X, OBSTACLE_Y + 30, 100);
	//m_Obstacle_B->Set_Static();
	//m_ShapeList.push_back(m_Obstacle_B);

	//장애물 생성 
	Box* m_Obstacle_B = new Box();
	//newBox->Init(iRand % MAIN_W, iRand % 30, sizeWH, sizeWH);
	m_Obstacle_B->Init(OBSTACLE_X, OBSTACLE_Y, OBSTACLE_W, OBSTACLE_H);
	m_Obstacle_B->Set_Static();
	m_ShapeList.push_back(m_Obstacle_B);

	Box* m_Obstacle_S = new Box();
	m_Obstacle_S->Init(OBSTACLE_X + 60, OBSTACLE_Y - 200, 50, OBSTACLE_H);
	m_Obstacle_S->Set_Static();
	m_ShapeList.push_back(m_Obstacle_S);

	//중력(아래로만 떨어지고 있기 때문)
	Gravity.y = GRAVITY_VALUE;

	//______test_____________
		//도형 추가
	CreateShaoe(CREATE_SEC);
}

void GameManager::CreateShaoe(float deltaTime)
{

	Box* newBox = new Box();
	newBox->Init(MAIN_W * 0.5f - 50, 20, 80, 80);
	m_ShapeList.push_back(newBox);

	Box* newBox2 = new Box();
	newBox2->Init(MAIN_W * 0.5f + 10, -50, 60, 60);
	m_ShapeList.push_back(newBox2);

	Circle* newCircle = new Circle();
	newCircle->Init(MAIN_W * 0.5f + 30, 20, 30);
	m_ShapeList.push_back(newCircle);

	Circle* newCircle2 = new Circle();
	newCircle2->Init(MAIN_W * 0.5f + 50, 70, 20);
	m_ShapeList.push_back(newCircle2);

}


void GameManager::Update(float deltaTime)
{
	//중력 가속도
	Vector2 _Gravity = Gravity * deltaTime;

	for (auto cList : m_ShapeList)
	{
		cList->Set_GravityVelocity(_Gravity);
	}

	bool bBump = false;
	int iMainIndex, iCompareIndex;

	for (int i = 0; i < m_ShapeList.size() - 1; i++)
	{
		for (int j = i + 1; j < m_ShapeList.size(); j++)
		{
			
			//-----------원 vs 원 충돌---------------
			if ((m_ShapeList[i]->Get_ShapeType() == SHAPE_CIRCLE) && (m_ShapeList[j]->Get_ShapeType() == SHAPE_CIRCLE))
			{
				//충돌이 발생하면 true (부딪힌 상태에서 다시 체크하러 와서 부딪혔다라고 뜰 수 있다. 해당 건은 아래 if에서 걸러질것)
				if (CirclevsCircle((Circle*)m_ShapeList[i], (Circle*)m_ShapeList[j]))
				{
					bBump = true;
				}
			}
			//-----------원 vs 사각형 충돌---------------	
			else if ((m_ShapeList[i]->Get_ShapeType() == SHAPE_CIRCLE) && (m_ShapeList[j]->Get_ShapeType() == SHAPE_BOX))
			{
				if (AABBvsCircle((Box*)m_ShapeList[j], (Circle*)m_ShapeList[i]))
				{
					bBump = true;
					normal = -normal;
				}
			}
			else if ((m_ShapeList[i]->Get_ShapeType() == SHAPE_BOX) && (m_ShapeList[j]->Get_ShapeType() == SHAPE_CIRCLE))
			{
				if (AABBvsCircle((Box*)m_ShapeList[i], (Circle*)m_ShapeList[j]))
				{
					bBump = true;
				}
			}
			//-----------사각형 vs 사각형 충돌---------------
			else if ((m_ShapeList[i]->Get_ShapeType() == SHAPE_BOX) && (m_ShapeList[j]->Get_ShapeType() == SHAPE_BOX))
			{
				if (AABBvsAABB((Box*)m_ShapeList[i], (Box*)m_ShapeList[j]))
				{
					bBump = true;
				}
			}

			if (bBump)
			{
				for (int k = 0; k < 40; k++)
				{
					//penetration과 nomal의 값을 CirclevsCircle 함수 안에서 결정했다.

					//A가 B로 향하는 상대속도(rv) = B의 속도(bv) - A의 속도(av)
					Vector2 rv = m_ShapeList[j]->m_Velocity - m_ShapeList[i]->m_Velocity;

					//두 물체가 부딪힘.(내적(dot)이 > 0 이면 멀어지는 중, 충돌 처리 안함) ( dot < 0 이면 가까워지는 중, 충돌처리 함)
					dot = Dot_(rv, normal);

					if (dot < 0)
					{
						//충돌
						//float ImpluseMagnitude = -(1.0f + 0.02f) * dot / (m_CircleList[i]->m_InvMass + m_CircleList[j]->m_InvMass);

						//충돌에 의해 발생한 속도
						/*n * 2 * DotProduct(-P, n)
							normal * (1.0f + e) * dot
								반사 백터를 사용한 것*/
						float Impulse = (-(1.0f + 2) * dot / (m_ShapeList[i]->m_InvMass + m_ShapeList[j]->m_InvMass));

						//튕겨나옴 처리
						/*normal 값은 기준 도형에 접근하는 물체가 튕겨나갈 방향이다.
							그러므로 기준 도형이 튕겨 나갈 것은 -가 필요*/
						m_ShapeList[i]->AddForce(-normal * Impulse * deltaTime * 0.01f);
						m_ShapeList[j]->AddForce(normal * Impulse * deltaTime * 0.01f);

						continue; //해당 if문에 해당되면 for문을 계속해서 돈다
					}
					break;
				}
			bBump = false;
			}
		}
	}


	//좌표 이동은 무조건 맨 마지막에 실행되어야 한다.
	for (auto cList : m_ShapeList)
	{
		cList->Update(deltaTime);
	}
}

void GameManager::Draw(HDC m_frontDC)
{
	//더블 버퍼링
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Window_WH.x, m_Window_WH.y); //TODO::임시 W H
	SelectObject(m_backDC, backBitmap);

	//도형 그리기
	for (auto cList : m_ShapeList)
	{
		cList->Draw(m_backDC);
	}

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
	const Vector2 incident = rhs->m_Position - lhs->m_Position;
	float radiusSum = lhs->m_Radius + rhs->m_Radius;

	//두 원의 반지름으리 합보다 두원 사이의 거리가 크면 충돌하지 않은 상태
	if (incident.SqrMagnitude() > (radiusSum * radiusSum))
		return false;

	float dist = incident.Magitude();
	if (0 != dist)
	{
		//현재 침투깊이는 쓰지 않고 있어서 지워도 상관이 없다.
		//침투깊이
		penetration = radiusSum - dist;
		//충돌 방향
		normal = incident;
	}
	else
	{
		//두 원은 같은 위치에 있다. 겹쳐있다.
		penetration = lhs->m_Radius; //원의 중심점이 겹치면(반지름 크기 상관X) 주체인 원의 반지를 만큼 튕겨낸다.
		normal = Vector2(1, 0); //중심 겹친 상대의 원을 오른쪽으로 튕겨낼 것
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

	return true;
}

bool GameManager::AABBvsAABB(Box* lhs, Box* rhs)
{
	//충돌 방향 벡터, 상대 위치(lhs를 원점으로 rhs의 위치)
	const Vector2 incident = rhs->m_Position - lhs->m_Position;
	//각 Box의 너비(Width)의 반(half width)을 구한다.
	float lhs_extent = lhs->m_Half_W;
	float rhs_extent = rhs->m_Half_W;
	float overlapX = lhs_extent + rhs_extent - std::abs(incident.x);

	//x와 y축 모두 범위 안에 겸쳐야지만 사각형이 겹친 것
	if (0 < overlapX) //x축으로 겹치는 위치에 있다.
	{
		Vector2 closet;
		float offset = max(lhs_extent, rhs_extent);
		closet.x = clamp(incident.x, -offset, offset);

		//각 Box의 높이(height)의 반(half height)을 구한다.
		lhs_extent = lhs->m_Half_H;
		rhs_extent = rhs->m_Half_H;

		float overlapY = lhs_extent + rhs_extent - std::abs(incident.y);
		if (0 < overlapY) //y축으로 겹치는 위치에 있다.
		{
			closet.y = clamp(incident.y, -lhs_extent, lhs_extent);
			normal = incident - closet;
			normal.Normalize();

			penetration = (std::abs(normal.x) > std::abs(normal.y)) ? overlapX : overlapY;
			return true;
		}
	}
	return false;
}
