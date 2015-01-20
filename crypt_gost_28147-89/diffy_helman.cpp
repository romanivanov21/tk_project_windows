/*******************************************************************
* Файл: diffy_helman.cpp										   *
* Описание:содержит реализация функций							   *
* протокола обмена ключами Диифи - Хелмана						   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include "diffy_helman.h"
#include "inc_crypt_pp.h"

#include <iostream>

DIFFY_HELMAN_API diffy_helm::diffy_helm()
{
	dh_.AccessGroupParameters().GenerateRandomWithKeySize(rnd_,gost_key_size);
	p_ = dh_.GetGroupParameters().GetModulus();
	q_ = dh_.GetGroupParameters().GetSubgroupOrder();
	g_ = dh_.GetGroupParameters().GetGenerator();
	dhA_.AccessGroupParameters().Initialize(p_,q_, g_);

#if PRINT
	std::size_t count = p_.ByteCount();
	std::cout << "P (" << std::dec << count << "): " << std::hex << p_ << std::endl;

	count = q_.ByteCount();
	std::cout << "Q (" << std::dec << count << "): " << std::hex << q_ << std::endl;
	bool is_generateA_ = false;
#endif

}

DIFFY_HELMAN_API diffy_helm::~diffy_helm()
{
	if(is_generateA_ == true)
	{
		delete priv_A_; delete pub_A_;
	}
}

DIFFY_HELMAN_API void diffy_helm::get_p(byte *p, const std::size_t &p_size)
{
	assert(p_size == p_.ByteCount());
	memset(p, 0, p_size);
	p_.Encode(p, p_size);

}

DIFFY_HELMAN_API void diffy_helm::get_q(byte *q, const std::size_t &q_size)
{
	assert(q_size == q_.ByteCount());
	memset(q, 0, q_size);
	std::size_t count = q_.ByteCount();
	q_.Encode(q, q_size);
}
DIFFY_HELMAN_API void diffy_helm::get_g(byte &g)
{
	for(std::size_t i = 0; i < g_.ByteCount(); i++)
	{
		g = g_.GetByte(i);
	}
}

DIFFY_HELMAN_API void diffy_helm::generate_A(byte *A, const std::size_t &size_A)
{
	dhA_.AccessGroupParameters().Initialize(p_, q_, g_);

	priv_A_ = new CryptoPP::SecByteBlock(dhA_.PrivateKeyLength());
	pub_A_ = new CryptoPP::SecByteBlock(dhA_.PublicKeyLength());

	is_generateA_ = true;

	assert(size_A == pub_A_->size());
	memset(A, 0 ,size_A);
	dhA_.GenerateKeyPair(rnd_A_, *priv_A_, *pub_A_);

	CryptoPP::Integer temp;
	temp.Decode(pub_A_->BytePtr(), pub_A_->SizeInBytes());

#if PRINT
	std::cout<<"A = ";
#endif

	for(std::size_t i = 0; i < temp.ByteCount(); i++)
	{
		A[i] = temp.GetByte(i);

#if PRINT
		std::cout<<std::hex<<(int)A[i];
#endif

	}
	std::cout<<std::endl;
}
DIFFY_HELMAN_API void diffy_helm::generate_K(byte *B, const std::size_t &size_B, byte *gost_K, const std::size_t &size_gost_K)
{
	CryptoPP::SecByteBlock key(dhA_.AgreedValueLength());
	dhA_.Agree(key, *priv_A_, B);

	key_.Decode(key.BytePtr(), key.SizeInBytes());

	for(std::size_t i = 0; i < key_.ByteCount(); i++)
	{
		gost_K[i] = key_.GetByte(i);
	}
}