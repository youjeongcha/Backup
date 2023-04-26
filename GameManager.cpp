#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_CreateType = SHAPE_CIRCLE;
	m_CreateTime = CREATE_SEC;
	srand(time(NULL));

	//m_Obstacle_B.Init(OBSTACLE_X, OBSTACLE_Y, OBSTACLE_W, OBSTACLE_H);
	/*m_Obstacle_B.Init(OBSTACLE_X, OBSTACLE_Y, 80);*/
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
	//CreateCompatibleDC �Լ��� ����ؼ� DC�� �����ϸ� �� DC�� ����� ��Ʈ�� ��ü���� �׸��� �׷������� ȭ�鿡�� ����� ���� �ʴ´�.
	//CreateCompatibleDC �Լ��� ������� DC�� 'Memory DC'��� �θ���.
	GetClientRect(m_HWND, &clientRect); //�������� Ŭ���̾�Ʈ�� ������ �˷��ش�.
	m_Window_WH.x = clientRect.right - clientRect.left;
	m_Window_WH.y = clientRect.bottom - clientRect.top;


	Circle* m_Obstacle_B = new Circle();
	m_Obstacle_B->Init(OBSTACLE_X, OBSTACLE_Y, 80);
	m_Obstacle_B->Set_Static();
	m_CircleList.push_back(m_Obstacle_B);

	//�߷�(�Ʒ��θ� �������� �ֱ� ����)
	Gravity.y = GRAVITY_VALUE;
}

void GameManager::RandCreateShaoe(float deltaTime)
{
	//5�ʸ��� �����ư��� ���� ����
	if (m_CreateTime >= CREATE_SEC)
	{
		m_CreateTime = 0;
		int iRand = rand();

		switch (m_CreateType)
		{
		case SHAPE_CIRCLE:
		{
			//m_CreateType = SHAPE_BOX;

			Circle* newCircle = new Circle();
			newCircle->Init(iRand % MAIN_W, iRand % 30, iRand % SHAPE_PLUS_SIZE + SHAPE_MIN_SIZE);
			//newCircle->Init(MAIN_W * 0.5f, iRand % 30, iRand % SHAPE_MAX_SIZE);
			m_CircleList.push_back(newCircle);

			/////////////////////////////////////////

			iRand = rand();
			Circle* newCircle2 = new Circle();
			newCircle2->Init(iRand % MAIN_W, iRand % 30, iRand % SHAPE_PLUS_SIZE + SHAPE_MIN_SIZE);
			m_CircleList.push_back(newCircle2);

			///////////////////////////////////////////

			//iRand = rand();
			//Circle* newCircle3 = new Circle();
			//newCircle3->Init(iRand % MAIN_W, iRand % 30, iRand % SHAPE_MAX_SIZE);
			//m_CircleList.push_back(newCircle3);
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
	//���� �߰�
	RandCreateShaoe(deltaTime);

	//�߷� ���ӵ�
	Vector2 _Gravity = Gravity * deltaTime;

	for (auto cList : m_CircleList)
	{
		cList->Set_GravityVelocity(_Gravity);
	}
	//m_circle.Set_GravityVelocity(_Gravity);
	//m_Box.Set_GravityVelocity(_Gravity);


	//m_circle.Update(deltaTime);
	//m_Box.Update(deltaTime);

	//�� vs �� �浹

	for (int i = 0; i < m_CircleList.size() - 1; i++)
	{
		for (int j = i + 1; j < m_CircleList.size(); j++)
		{
			//�浹�� �߻��ϸ� true (�ε��� ���¿��� �ٽ� üũ�Ϸ� �ͼ� �ε����ٶ�� �� �� �ִ�. �ش� ���� �Ʒ� if���� �ɷ�����)
			if (CirclevsCircle(m_CircleList[i], m_CircleList[j]))
			{
				for (int i = 0; i < 40; i++)
				{
					//penetration�� nomal�� ���� CirclevsCircle �Լ� �ȿ��� �����ߴ�.

					//A�� B�� ���ϴ� ���ӵ�(rv) = B�� �ӵ�(bv) - A�� �ӵ�(av)
					Vector2 rv = m_CircleList[j]->m_Velocity - m_CircleList[i]->m_Velocity;

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
						float Impulse = (-(1.0f + 0.02f) * dot / (m_CircleList[i]->m_InvMass + m_CircleList[j]->m_InvMass));

						//ƨ�ܳ��� ó��
						/*normal ���� ���� ������ �����ϴ� ��ü�� ƨ�ܳ��� �����̴�.
							�׷��Ƿ� ���� ������ ƨ�� ���� ���� -�� �ʿ�*/
						m_CircleList[i]->AddForce(-normal * Impulse * deltaTime * 0.01f);
						m_CircleList[j]->AddForce(normal * Impulse * deltaTime * 0.01f);

						continue; //�ش� if���� �ش�Ǹ� for���� ����ؼ� ����
					}

					break;
				}
			}
		}
	}


	//��ǥ �̵��� ������ �� �������� ����Ǿ�� �Ѵ�.
	for (auto cList : m_CircleList)
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
	for (auto cList : m_CircleList)
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

	return false;
}