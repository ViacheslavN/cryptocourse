#pragma once
#include "BigNum.h"
#include "PublicKey.h"
#include "PrivateKey.h"

class CRSA
{
public:
	CRSA(uint32_t nKeyBits);
	~CRSA();

	bool Init();
	const CPrivateKey& GetPublicKey();
	void SetPublicKeyForEncrypt(CPublicKey& pubKey);


	bool Decrypt(const byte_t* plaintext, byte_t* ciphertext, size_t nSize) const;
	void Encrypt(const byte_t* ciphertext, byte_t* plaintext, size_t nSize) const;

private:

	CPrivateKey m_prKey;
	CPublicKey  m_pubKey;

	CPublicKey  m_pubKeyForEnc;
};