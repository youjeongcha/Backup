#pragma once
#include <cmath>

const float Epsilon = 0.0001f; //부동 소수점

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

	//정규화
	void Normalize()
	{
		//Mgt변수 만들기
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

//해당 #define이 없으면 추가해준다. 충돌 방지
#ifndef clamp
#define clamp(v, a, b) (a < b) ? min(max(v, a), b) : min(max(v, b), a) //입력값, 최소값 , 최대값 순으로 인자를 받는다. 사용자가 아니게 쓸 수 있어서 그러하게 바꿔주는 것
//입력값이 최소값보다 작으면 최소값으로, 최대값보다 크면 최대값으로 고정시키는 함수이다.
#endif // !clamp

int Repeat(int value, const int& max);

//프레임당 중력가속도 :: 속도(gravity) = 중력(g) * FPS(deltaTime)
static Vector2 Gravity = {0,0};

static float penetration;
static Vector2 normal;
static Vector2 RelativeVelocity(const Vector2& av, const Vector2& bv) { return bv - av; }
static float dot;
static float Dot_(const Vector2& lhs, const Vector2& rhs) { return (lhs.x * rhs.x) + (lhs.y * rhs.y); }; //이차원 벡터의 내적

//Vector2 GravityVelocity(const Vector2& g, float deltaTime) { return g * deltaTime; }