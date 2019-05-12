#pragma once

class CSimpleBigNum
{
public:
	CSimpleBigNum(byte_t *pData = NULL, size_t size = 0, bool sign = false);
	~CSimpleBigNum();

	CSimpleBigNum(const CSimpleBigNum& num);
	CSimpleBigNum& operator=(const CSimpleBigNum& num);
	CSimpleBigNum& operator=(uint32_t num);
	
	void Init(size_t size, bool sign);

	size_t Size() const;
	bool Sign() const;

	static int CompareABS(const CSimpleBigNum& h1, const CSimpleBigNum& h2);
	static int Compare(const CSimpleBigNum& h1, const CSimpleBigNum& h2);
	static void Add(CSimpleBigNum& h1, const CSimpleBigNum& h2);
	static void Subtract(CSimpleBigNum& h1, const CSimpleBigNum& h2);
	static void Multiply(CSimpleBigNum& h1, const CSimpleBigNum& h2);
	static void Divide(CSimpleBigNum& dividend, CSimpleBigNum& divisor, CSimpleBigNum* quotient);
	static void ModPow(CSimpleBigNum& h1, CSimpleBigNum& exp, CSimpleBigNum& n, CSimpleBigNum& h2);
	static void Inv(CSimpleBigNum&  z, CSimpleBigNum& a);
private:

	void Expand();
	void Contract();
	void Clear();
	void LeftShift();
	void RightShift();

	static void AddMagnitude( CSimpleBigNum& left, const CSimpleBigNum& right);
	static void SubtractMagnitude(CSimpleBigNum& left, const CSimpleBigNum& right);
private:
	byte_t* m_pData{ nullptr };
	bool m_sign{ false };
	size_t m_size{ 0 };
};