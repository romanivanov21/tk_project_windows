/*******************************************************************
* Файл: diffy_helman.h											   *
* Описание:содержит обяъявление функций протокола обмена ключами   *
* Диффи-Хелмана													   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/
#ifndef _DIFFY_HELMAN_H_
#define _DIFFY_HELMAN_H_


#define DIFFY_HELMAN_API __declspec(dllexport)


#define DEBUG_INFO_PRINT 1

#include "inc_crypt_pp.h"

const std::size_t gost_key_size = 256;

class diffy_helm
{
public:
	DIFFY_HELMAN_API explicit diffy_helm();
	DIFFY_HELMAN_API ~diffy_helm();

	DIFFY_HELMAN_API void get_p(byte *p, const std::size_t &p_size)const;
	DIFFY_HELMAN_API void get_q(byte *q, const std::size_t &q_size)const;
	DIFFY_HELMAN_API void get_g(byte &g);

	DIFFY_HELMAN_API void generate_A(byte *A, const std::size_t &A_size);
	DIFFY_HELMAN_API void generate_K(byte *B, const std::size_t &B_size, byte *gost_K, const std::size_t &gost_K_size);

private:

	diffy_helm(diffy_helm &);
	diffy_helm& operator=(diffy_helm &);

private:

	CryptoPP::AutoSeededRandomPool rnd_;
	CryptoPP::AutoSeededRandomPool rnd_A_;
	CryptoPP::DH dh_;
	CryptoPP::DH dhA_;

	CryptoPP::Integer p_;
	CryptoPP::Integer g_;
	CryptoPP::Integer q_;
	
	CryptoPP::SecByteBlock *priv_A_;
	CryptoPP::SecByteBlock *pub_A_;
	
	CryptoPP::Integer key_;

	bool is_generateA_;
};

#endif