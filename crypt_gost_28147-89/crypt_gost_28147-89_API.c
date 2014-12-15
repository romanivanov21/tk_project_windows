/*******************************************************************
* Файл: crypt_gost_28147-89_API.c								   *
* Описание:содержит реализацию функций							   *
* криптографического алгоритма ГОСТ 28247-89					   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015 												   *
*																   *
********************************************************************/
#include "crypt_gost_types.h"
#include "crypt_gost_28147-89_API.h"

CRYPT_GOST_API void key_box_init()
{
	unsigned int i;
	for(i = 0; i < key_size256; i++)
	{
		k87[i] = k8[i >> 4] << 4 | k7[i & 15];
		k65[i] = k6[i >> 4] << 4 | k5[i & 15];
		k43[i] = k4[i >> 4] << 4 | k3[i & 15];
		k21[i] = k2[i >> 4] << 4 | k1[i & 15];
	}
}

CRYPT_GOST_API void gostcrypt( word32 const *in_data, word32  *out_data, word32 const *gost_key)
{
	register word32 n1, n2;
	
	n1 = in_data[0];
	n2 = in_data[1];
	
	n2 ^= f(n1 + gost_key[0]);
	n1 ^= f(n2 + gost_key[1]);
	n2 ^= f(n1 + gost_key[2]);
	n1 ^= f(n2 + gost_key[3]);
	n2 ^= f(n1 + gost_key[4]);
	n1 ^= f(n2 + gost_key[5]);
	n2 ^= f(n1 + gost_key[6]);
	n1 ^= f(n2 + gost_key[7]);

	n2 ^= f(n1 + gost_key[0]);
	n1 ^= f(n2 + gost_key[1]);
	n2 ^= f(n1 + gost_key[2]);
	n1 ^= f(n2 + gost_key[3]);
	n2 ^= f(n1 + gost_key[4]);
	n1 ^= f(n2 + gost_key[5]);
	n2 ^= f(n1 + gost_key[6]);
	n1 ^= f(n2 + gost_key[7]);

	n2 ^= f(n1 + gost_key[0]);
	n1 ^= f(n2 + gost_key[1]);
	n2 ^= f(n1 + gost_key[2]);
	n1 ^= f(n2 + gost_key[3]);
	n2 ^= f(n1 + gost_key[4]);
	n1 ^= f(n2 + gost_key[5]);
	n2 ^= f(n1 + gost_key[6]);
	n1 ^= f(n2 + gost_key[7]);

	n2 ^= f(n1 + gost_key[7]);
	n1 ^= f(n2 + gost_key[6]);
	n2 ^= f(n1 + gost_key[5]);
	n1 ^= f(n2 + gost_key[4]);
	n2 ^= f(n1 + gost_key[3]);
	n1 ^= f(n2 + gost_key[2]);
	n2 ^= f(n1 + gost_key[1]);
	n1 ^= f(n2 + gost_key[0]);

	out_data[0] = n2;
	out_data[1] = n1;
} 

CRYPT_GOST_API void gostdecrypt( word32 const *in_data, word32 *out_data, word32 const *gost_key)
{
	register word32 n1, n2;
	n1 = in_data[0];
	n2 = in_data[1];
	n2 ^= f(n1 + gost_key[0]);
	n1 ^= f(n2 + gost_key[1]);
	n2 ^= f(n1 + gost_key[2]);
	n1 ^= f(n2 + gost_key[3]);
	n2 ^= f(n1 + gost_key[4]);
	n1 ^= f(n2 + gost_key[5]);
	n2 ^= f(n1 + gost_key[6]);
	n1 ^= f(n2 + gost_key[7]);

	n2 ^= f(n1 + gost_key[7]);
	n1 ^= f(n2 + gost_key[6]);
	n2 ^= f(n1 + gost_key[5]);
	n1 ^= f(n2 + gost_key[4]);
	n2 ^= f(n1 + gost_key[3]);
	n1 ^= f(n2 + gost_key[2]);
	n2 ^= f(n1 + gost_key[1]);
	n1 ^= f(n2 + gost_key[0]);

	n2 ^= f(n1 + gost_key[7]);
	n1 ^= f(n2 + gost_key[6]);
	n2 ^= f(n1 + gost_key[5]);
	n1 ^= f(n2 + gost_key[4]);
	n2 ^= f(n1 + gost_key[3]);
	n1 ^= f(n2 + gost_key[2]);
	n2 ^= f(n1 + gost_key[1]);
	n1 ^= f(n2 + gost_key[0]);

	n2 ^= f(n1 + gost_key[7]);
	n1 ^= f(n2 + gost_key[6]);
	n2 ^= f(n1 + gost_key[5]);
	n1 ^= f(n2 + gost_key[4]);
	n2 ^= f(n1 + gost_key[3]);
	n1 ^= f(n2 + gost_key[2]);
	n2 ^= f(n1 + gost_key[1]);
	n1 ^= f(n2 + gost_key[0]);

	out_data[0] = n2;
	out_data[1] = n1;
}

word32 f(word32 x)
{
	x = k87[x >> 24 & 255] << 24 | k65[x >> 16 & 255] << 16 |
	    k43[x >>  8 & 255] <<  8 | k21[x & 255];
	return x << 11 | x >> (32-11);
}
