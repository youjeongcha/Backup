#pragma once
typedef unsigned char BYTE;
class Color
{
private:
	union
	{
		BYTE  rgba[4];
		unsigned int color;
	};
public:
	Color();
	Color(unsigned int val);
	Color(BYTE r, BYTE g, BYTE b);
	Color(BYTE r, BYTE g, BYTE b, BYTE a);
	Color(const Color& src);

	Color& operator=(const Color& rhs);
	bool operator==(const Color& rhs) const;
	bool operator!=(const Color& rhs) const;

	
	constexpr BYTE GetR() const; // constexpr : const 보다 훨씬 더 상수성에 충실.
	void SetR(BYTE r);			 // const 변수의 초기화를 런타임까지 지연시킬 수 있는 반면,
								 // constexpr 변수는 반드시 컴파일 타임에 초기화가 되어 있어야 한다.
								 // 변수 또는 함수의 반환값은 반드시 LiteralType이어야 한다.
								 // LiteralType : 컴파일 타임에 해당 레이아웃이 결정될 수 있는 타입을 의미. 
	constexpr BYTE GetG() const;
	void SetG(BYTE g);
	constexpr BYTE GetB() const;
	void SetB(BYTE b);
	constexpr BYTE GetA() const;
	void SetA(BYTE a);
};

namespace Colors
{
	const Color UnloadedTextureColor(255, 255, 255); // 흰색(로드할 텍스처가 없을 경우 사용)
	const Color UnhandledTextureColor(255, 0, 255); // 분홍색(로드할 텍스처를 찾을 수 없을 경우 사용)
}