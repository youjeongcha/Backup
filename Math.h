#pragma once
#include <cmath>

const float Epsilon = 0.0001f; //�ε� �Ҽ���

struct Vector2
{
	float x, y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator-() const { return Vector2(-x , -y); }

	Vector2 operator*(const float& value) const { return Vector2(x * value, y * value); }
	Vector2 operator/(const float& value) const { return Vector2(x / value, y / value); }
	Vector2 operator*=(const float& value) { return Vector2(x *= value, y *= value); }
	Vector2 operator/=(const float& value) { return Vector2(x /= value, y /= value); }

	Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	Vector2 operator+=(const Vector2& v) { return Vector2(x += v.x, y += v.y); }
	Vector2 operator-=(const Vector2& v) { return Vector2(x -= v.x, y -= v.y); }



	float SqrMagnitude() const { return (x * x) + (y * y); };
	float Magitude() const { return std::sqrt(SqrMagnitude()); };

	//����ȭ
	void Normalize()
	{
		//Mgt���� �����
		if (Epsilon < Magitude()) //if (0 < magnitude)
		{
			float invMagnitude = 1.0f / Magitude();
			x += invMagnitude;
			y *= invMagnitude;
		}
	}
};

inline bool operator== (const Vector2& lhs, const Vector2& rhs) { return (lhs.x == rhs.x) && (lhs.y == rhs.y); }
inline bool operator!= (const Vector2& lhs, const Vector2& rhs) { return !(lhs == rhs); }



inline bool Equal(float lhs, float rhs) { return (std::abs(lhs - rhs) <= Epsilon); }

//�ش� #define�� ������ �߰����ش�. �浹 ����
#ifndef clamp
#define clamp(v, a, b) (a < b) ? min(max(v, a), b) : min(max(v, b), a) //�Է°�, �ּҰ� , �ִ밪 ������ ���ڸ� �޴´�. ����ڰ� �ƴϰ� �� �� �־ �׷��ϰ� �ٲ��ִ� ��
//�Է°��� �ּҰ����� ������ �ּҰ�����, �ִ밪���� ũ�� �ִ밪���� ������Ű�� �Լ��̴�.
#endif // !clamp

int Repeat(int value, const int& max);

//�����Ӵ� �߷°��ӵ� :: �ӵ�(gravity) = �߷�(g) * FPS(deltaTime)
static Vector2 Gravity = {0,0};

static float penetration;
static Vector2 normal;
static Vector2 RelativeVelocity(const Vector2& av, const Vector2& bv) { return bv - av; }
static float dot;
static float Dot_(const Vector2& lhs, const Vector2& rhs) { return (lhs.x * rhs.x) + (lhs.y * rhs.y); }; //������ ������ ����

//Vector2 GravityVelocity(const Vector2& g, float deltaTime) { return g * deltaTime; }