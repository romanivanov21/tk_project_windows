/*******************************************************************
* Файл: gots_API_test.h											   *
* Описание: содержит объявление функций тестирования библиотеки	   *
* crypt_gost_28147-89.dll										   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#ifndef _GOST_API_TEST_H_
#define _GOST_API_TEST_H_

#include "..\shared_code\gost_include.h"
#include "..\shared_code\gost_types_convert.h"
#include <stdlib.h>
#include <iostream>

#pragma pack(push,1)
typedef struct 
{
	char key_byte[32];
	char data_crypt_byte[8];
	char data_decrypt_byte[8];

} gost_crypt_byte, *ptr_gost_crypt_byte;

typedef struct 
{
	word32 key_word32[8];
	word32 data_crypt_word32[2];
	word32 data_decrypt_word32[2];
} gost_crypt_word32, *ptr_gost_crypt_word32;
#pragma pack(pop)

void init_gost(char *data)
{
	gost_crypt_word32 word32_ = { 0 };
	gost_crypt_byte byte_ = { 0 };
	for(unsigned int i = 0; i < 32; i++)
	{
		byte_.key_byte[i] = (byte)(rand() % 7);
	}
	strcpy_s(byte_.data_crypt_byte, data);
	byte_to_word32_key((byte*)byte_.key_byte, word32_.key_word32);
	byte_to_word32_data((byte*)byte_.data_crypt_byte, word32_.data_crypt_word32);
	gostcrypt(word32_.data_crypt_word32, word32_.data_decrypt_word32,word32_.key_word32);
	gostdecrypt(word32_.data_decrypt_word32, word32_.data_crypt_word32, word32_.key_word32);
	word32_to_byte_data(word32_.data_crypt_word32, (byte*)byte_.data_crypt_byte);
	for(std::size_t i = 0 ; i < 8; i++)
	{
		std::cout<<byte_.data_crypt_byte[i];
	}
}

#endif