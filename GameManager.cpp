#include "GameManager.h"

/*-�簢���� ȸ�� ���� �ʴ´�.
-�ٴڿ��� ƨ��� ���� ����(�ٴ��� �İ�縸ŭ �ٽ� ���� ƨ�ܳ��� �־)
-���� ������ �������� ���� ���� �İ� ��� ��. �̰� ���� �������� �ؾ� �ذ� �Ǵ� ��. ���� �ڵ� ���������� ���� �۵��� �Ǵ� ���̴�.
-���� ������ ��ġ�� ���ܳ� ������ �浹 üũ�� ���� �ʴ´�. ó������ �İ�� ���·� ���ܳ���. ������ ����*/

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
	//CreateCompatibleDC �Լ��� ����ؼ� DC�� �����ϸ� �� DC�� ����� ��Ʈ�� ��ü���� �׸��� �׷������� ȭ�鿡�� ����� ���� �ʴ´�.
	//CreateCompatibleDC �Լ��� ������� DC�� 'Memory DC'��� �θ���.
	GetClientRect(m_HWND, &clientRect); //�������� Ŭ���̾�Ʈ�� ������ �˷��ش�.
	m_Window_WH.x = clientRect.right - clientRect.left;
	m_Window_WH.y = clientRect.bottom - clientRect.top;

	//Circle* m_Obstacle_B = new Circle();
	//m_Obstacle_B->Init(OBSTACLE_X, OBSTACLE_Y + 30, 100);
	//m_Obstacle_B->Set_Static();
	//m_ShapeList.push_back(m_Obstacle_B);

	//��ֹ� ���� 
	Box* m_Obstacle_B = new Box();
	//newBox->Init(iRand % MAIN_W, iRand % 30, sizeWH, sizeWH);
	m_Obstacle_B->Init(OBSTACLE_X, OBSTACLE_Y, OBSTACLE_W, OBSTACLE_H);
	m_Obstacle_B->Set_Static();
	m_ShapeList.push_back(m_Obstacle_B);

	Box* m_Obstacle_S = new Box();
	m_Obstacle_S->Init(OBSTACLE_X + 60, OBSTACLE_Y - 200, 50, OBSTACLE_H);
	m_Obstacle_S->Set_Static();
	m_ShapeList.push_back(m_Obstacle_S);

	//�߷�(�Ʒ��θ� �������� �ֱ� ����)
	Gravity.y = GRAVITY_VALUE;

	//______test_____________
		//���� �߰�
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
	//�߷� ���ӵ�
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
			
			//-----------�� vs �� �浹---------------
			if ((m_ShapeList[i]->Get_ShapeType() == SHAPE_CIRCLE) && (m_ShapeList[j]->Get_ShapeType() == SHAPE_CIRCLE))
			{
				//�浹�� �߻��ϸ� true (�ε��� ���¿��� �ٽ� üũ�Ϸ� �ͼ� �ε����ٶ�� �� �� �ִ�. �ش� ���� �Ʒ� if���� �ɷ�����)
				if (CirclevsCircle((Circle*)m_ShapeList[i], (Circle*)m_ShapeList[j]))
				{
					bBump = true;
				}
			}
			//-----------�� vs �簢�� �浹---------------	
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
			//-----------�簢�� vs �簢�� �浹---------------
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
					//penetration�� nomal�� ���� CirclevsCircle �Լ� �ȿ��� �����ߴ�.

					//A�� B�� ���ϴ� ���ӵ�(rv) = B�� �ӵ�(bv) - A�� �ӵ�(av)
					Vector2 rv = m_ShapeList[j]->m_Velocity - m_ShapeList[i]->m_Velocity;

					//�� ��ü�� �ε���.(����(dot)�� > 0 �̸� �־����� ��, �浹 ó�� ����) ( dot < 0 �̸� ��������� ��, �浹ó�� ��)
					dot = Dot_(rv, normal);

					if (dot < 0)
					{
						//�浹
						//float ImpluseMagnitude = -(1.0f + 0.02f) * dot / (m_CircleList[i]->m_InvMass + m_CircleList[j]->m_InvMass);

						//�浹�� ���� �߻��� �ӵ�
						/*n * 2 * DotProduct(-P, n)
							normal * (1.0f + e) * dot
								�ݻ� ���͸� ����� ��*/
						float Impulse = (-(1.0f + 2) * dot / (m_ShapeList[i]->m_InvMass + m_ShapeList[j]->m_InvMass));

						//ƨ�ܳ��� ó��
						/*normal ���� ���� ������ �����ϴ� ��ü�� ƨ�ܳ��� �����̴�.
							�׷��Ƿ� ���� ������ ƨ�� ���� ���� -�� �ʿ�*/
						m_ShapeList[i]->AddForce(-normal * Impulse * deltaTime * 0.01f);
						m_ShapeList[j]->AddForce(normal * Impulse * deltaTime * 0.01f);

						continue; //�ش� if���� �ش�Ǹ� for���� ����ؼ� ����
					}
					break;
				}
			bBump = false;
			}
		}
	}


	//��ǥ �̵��� ������ �� �������� ����Ǿ�� �Ѵ�.
	for (auto cList : m_ShapeList)
	{
		cList->Update(deltaTime);
	}
}

void GameManager::Draw(HDC m_frontDC)
{
	//���� ���۸�
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Window_WH.x, m_Window_WH.y); //TODO::�ӽ� W H
	SelectObject(m_backDC, backBitmap);

	//���� �׸���
	for (auto cList : m_ShapeList)
	{
		cList->Draw(m_backDC);
	}

	//���� ���۸�
	BitBlt(m_frontDC, 0, 0, m_Window_WH.x, m_Window_WH.y, m_backDC, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}



//���� ���۸�
HBITMAP GameManager::MyCreateDIBSection(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//color bits : 1, 4, 8, 16, 24, 32
	//1:���, 4:16��, 8:256��, 16:2^15��, 24,31:2^24��
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; //�ʺ�, ��Ʈ���� ���� �ȼ� ��
	bm_info.bmiHeader.biHeight = height; //����, ��Ʈ���� ���� �ȼ� ��
	bm_info.bmiHeader.biPlanes = 1; //1�� ����, �ݵ�� 1�̾�� �Ѵ�

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}



bool GameManager::CirclevsCircle(Circle* lhs, Circle* rhs)
{
	//lhs�� �߽����� �ϴ� rhs�� ��� ��ġ
	const Vector2 incident = rhs->m_Position - lhs->m_Position;
	float radiusSum = lhs->m_Radius + rhs->m_Radius;

	//�� ���� ���������� �պ��� �ο� ������ �Ÿ��� ũ�� �浹���� ���� ����
	if (incident.SqrMagnitude() > (radiusSum * radiusSum))
		return false;

	float dist = incident.Magitude();
	if (0 != dist)
	{
		//���� ħ�����̴� ���� �ʰ� �־ ������ ����� ����.
		//ħ������
		penetration = radiusSum - dist;
		//�浹 ����
		normal = incident;
	}
	else
	{
		//�� ���� ���� ��ġ�� �ִ�. �����ִ�.
		penetration = lhs->m_Radius; //���� �߽����� ��ġ��(������ ũ�� ���X) ��ü�� ���� ������ ��ŭ ƨ�ܳ���.
		normal = Vector2(1, 0); //�߽� ��ģ ����� ���� ���������� ƨ�ܳ� ��
	}
	normal.Normalize();

	return true;
}

bool GameManager::AABBvsCircle(Box* lhs, Circle* rhs)
{
	const Vector2 incident = rhs->m_Position - lhs->m_Position; // Box�� �߽����� �ϴ� Circle�� ��� ��ġ
	//Box�� �ʺ�(width)�� ����(height)�� ��(half width, half height)�� ���Ѵ�.
	float extentX = (lhs->m_Half_W);
	float extentY = (lhs->m_Half_H);

	Vector2 closet;
	closet.x = clamp(incident.x, -extentX, extentX);
	closet.y = clamp(incident.y, -extentY, extentY);

	bool inside = false;
	if (incident == closet) //Box�� Circle�� �� �̻� ħ���ߴ�.
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
		normal = -normal; //�� �̻����� ħ���ϸ� ħ�� ������ �������� ������ �ٽ� ������ �ǵ��� �ش�

	normal.Normalize();

	return true;
}

bool GameManager::AABBvsAABB(Box* lhs, Box* rhs)
{
	//�浹 ���� ����, ��� ��ġ(lhs�� �������� rhs�� ��ġ)
	const Vector2 incident = rhs->m_Position - lhs->m_Position;
	//�� Box�� �ʺ�(Width)�� ��(half width)�� ���Ѵ�.
	float lhs_extent = lhs->m_Half_W;
	float rhs_extent = rhs->m_Half_W;
	float overlapX = lhs_extent + rhs_extent - std::abs(incident.x);

	//x�� y�� ��� ���� �ȿ� ���ľ����� �簢���� ��ģ ��
	if (0 < overlapX) //x������ ��ġ�� ��ġ�� �ִ�.
	{
		Vector2 closet;
		float offset = max(lhs_extent, rhs_extent);
		closet.x = clamp(incident.x, -offset, offset);

		//�� Box�� ����(height)�� ��(half height)�� ���Ѵ�.
		lhs_extent = lhs->m_Half_H;
		rhs_extent = rhs->m_Half_H;

		float overlapY = lhs_extent + rhs_extent - std::abs(incident.y);
		if (0 < overlapY) //y������ ��ġ�� ��ġ�� �ִ�.
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
