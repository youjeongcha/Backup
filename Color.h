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

	
	constexpr BYTE GetR() const; // constexpr : const ���� �ξ� �� ������� ���.
	void SetR(BYTE r);			 // const ������ �ʱ�ȭ�� ��Ÿ�ӱ��� ������ų �� �ִ� �ݸ�,
								 // constexpr ������ �ݵ�� ������ Ÿ�ӿ� �ʱ�ȭ�� �Ǿ� �־�� �Ѵ�.
								 // ���� �Ǵ� �Լ��� ��ȯ���� �ݵ�� LiteralType�̾�� �Ѵ�.
								 // LiteralType : ������ Ÿ�ӿ� �ش� ���̾ƿ��� ������ �� �ִ� Ÿ���� �ǹ�. 
	constexpr BYTE GetG() const;
	void SetG(BYTE g);
	constexpr BYTE GetB() const;
	void SetB(BYTE b);
	constexpr BYTE GetA() const;
	void SetA(BYTE a);
};

namespace Colors
{
	const Color UnloadedTextureColor(255, 255, 255); // ���(�ε��� �ؽ�ó�� ���� ��� ���)
	const Color UnhandledTextureColor(255, 0, 255); // ��ȫ��(�ε��� �ؽ�ó�� ã�� �� ���� ��� ���)
}