#include "pch.h"
#include "mpir.h"
#include "BigNum.h"




class CNumImp
{
public:
	CNumImp()
	{
		mpz_init(m_num);
	}
	~CNumImp()
	{
		mpz_clear(m_num);
	}
private:
	friend class CBigNum;
	mpz_t m_num;
};

CBigNum::CBigNum(byte_t *pData, size_t size)
{
	m_num.reset(new CNumImp());

	if(pData != NULL && size != 0)
		mpz_import(m_num->m_num, size, 1, sizeof(byte_t), 0, 0, pData);
}

CBigNum::CBigNum(const CBigNum& bigNum)
{
	mpz_set(m_num->m_num, bigNum.m_num->m_num);
}

CBigNum::~CBigNum()
{
	mpz_clear(m_num->m_num);
}

void CBigNum::Import(byte_t *pData, size_t size)
{
	if (pData != NULL && size != 0)
		mpz_import(m_num->m_num, size, 1, sizeof(byte_t), 0, 0, pData);
}

void CBigNum::SetUI(uint64_t n)
{
	mpz_set_ui(m_num->m_num, n);
}

int CBigNum::CmpUi(uint64_t n) const
{
	return mpz_cmp_ui(m_num->m_num, n);
}

void CBigNum::SubUI(uint64_t n)
{
	mpz_sub_ui(m_num->m_num, m_num->m_num, n);
}

void CBigNum::NextPrime()
{
	NextPrime(*this, *this);
}


CBigNum& CBigNum::operator = (CBigNum& bigNum)
{
	mpz_set(m_num->m_num, bigNum.m_num->m_num);
	return *this;
}


bool CBigNum::operator == (const CBigNum& num) const
{
	return Compare(*this, num) == 0;
}

bool CBigNum::operator == (uint64_t num) const
{
	return CmpUi(num) == 0;
}

//////////////////////////////////


void CBigNum::NextPrime(CBigNum& rop, const CBigNum& op)
{
	mpz_nextprime(rop.m_num->m_num, op.m_num->m_num);
}

int CBigNum::Compare(const CBigNum& left, const CBigNum& right)
{
	return mpz_cmp(left.m_num->m_num, right.m_num->m_num);
}

void CBigNum::Mod(CBigNum& r, const CBigNum& n, const CBigNum& d)
{
	return mpz_mod(r.m_num->m_num, n.m_num->m_num, d.m_num->m_num);
}

void CBigNum::Mul(CBigNum& rop, const CBigNum& op1, const CBigNum& op2)
{
	mpz_mul(rop.m_num->m_num, op1.m_num->m_num, op2.m_num->m_num);
}

bool CBigNum::Invert(CBigNum& rop, const CBigNum& e, const CBigNum& m)
{
	if (m == 0)
		return false;

	return mpz_invert(rop.m_num->m_num, e.m_num->m_num, m.m_num->m_num) != 0;
}