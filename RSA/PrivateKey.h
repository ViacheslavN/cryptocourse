#pragma once
#include "BigNum.h"

class CPrivateKey
{
public:
	CPrivateKey();
	~CPrivateKey();

	CBigNum& GetModulus();
	CBigNum& GetPrivateExponent();

	const CBigNum& GetModulus() const;
	const CBigNum& GetPrivateExponent() const;

private:

	CBigNum m_n; /* Modulus */
	//CBigNum m_e; /* Public Exponent */
	CBigNum m_d; /* Private Exponent */
	//CBigNum m_p; /* Starting prime p */
	//CBigNum m_q; /* Starting prime q */
};