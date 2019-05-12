#pragma once

class CNumImp;

class CBigNum
{
public:
	CBigNum(byte_t *pData = NULL, size_t size = 0);

	CBigNum(const CBigNum& bigNum);
	CBigNum& operator = (CBigNum& bigNum);


	~CBigNum();


	void Import(byte_t *pData, size_t size);

	void SetUI(uint64_t n);
	void NextPrime();

	int CmpUi(uint64_t n) const;
	void SubUI(uint64_t n); //mpz_sizeinbase 

	bool operator == (const CBigNum& num) const;
	bool operator == (uint64_t num) const;

	static void NextPrime(CBigNum& rop, const CBigNum& op);
	static int Compare(const CBigNum& left, const CBigNum& right);
	static void Mod(CBigNum& r, const CBigNum& n, const CBigNum& d);
	static void Mul(CBigNum& rop, const CBigNum& op1, const CBigNum& op2);
	/* Calculate d (multiplicative inverse of e mod m) */
	static bool	Invert(CBigNum& rop, const CBigNum& e, const CBigNum& m);

	
private:
	std::unique_ptr<CNumImp>  m_num;
	//mpz_t m_num;
};