#include "pch.h"
#include "PublicKey.h"


CPublicKey::CPublicKey()
{

}

CPublicKey::~CPublicKey()
{

}


CBigNum& CPublicKey::GetModulus()
{
	return m_n;
}

CBigNum& CPublicKey::GetPublicExponent()
{
	return m_e;
}

const CBigNum& CPublicKey::GetModulus() const
{
	return m_n;
}

const CBigNum& CPublicKey::GetPublicExponent() const
{
	return m_e;
}