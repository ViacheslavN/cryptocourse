#pragma once

#include "BigNum.h"

class CPublicKey
{
public:
	CPublicKey();
	~CPublicKey();

	CBigNum& GetModulus();
	CBigNum& GetPublicExponent();

	const CBigNum& GetModulus() const;
	const CBigNum& GetPublicExponent() const;

private:
	CBigNum m_n; /* Modulus */
	CBigNum m_e; /* Public Exponent */
};