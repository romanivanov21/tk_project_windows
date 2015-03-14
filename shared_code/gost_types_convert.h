/*******************************************************************
* Файл: gost_types_convert.h									   *
* Описание:содержит обяъявление функций, преобразующие данные	   *
* для шифрования из массива word32[2] в массив byte[8] и обратно   *
* для передачи в функции штфрования и дешифрования				   *
* криптографическим алгоритмом ГОСТ 28147-89					   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/


#ifndef _GOST_TYPES_CONVERT_H_
#define _GOST_TYPES_CONCERT_H_

#include "crypt_gost_types.h"
#include <string.h>
	
static void word32_to_byte_data(word32 *word32_, byte *byte_)
{
	memset(byte_, 0, 8);
	word32 temp = word32_[0];
	int s = 24;
	for(unsigned int i = 0; i < 4; i++)
	{
		word32_[0] = temp;
		word32_[0] = word32_[0] >> s;
		byte_[i] |= word32_[0];
		s = s - 8;
	}
	temp = word32_[1];
	for(unsigned int i = 4; i < 8; i++)
	{
		word32_[1] = temp;
		word32_[1] = word32_[1] >> s;
		byte_[i] |= word32_[1];
		s = s - 8;
	}
}

static void byte_to_word32_data( byte *byte_, word32 *word32_)
{
	memset(word32_, 0, 8);

	for(unsigned int i = 0; i < 4; i++)
	{
		word32_[0] = word32_[0] << 8;
		word32_[0] |= byte_[i];
	}
	for(unsigned int i = 4; i < 8; i++)
	{
		word32_[1] = word32_[1] << 8;
		word32_[1] |= byte_[i];
	}
}

static void word32_to_byte_key(word32 *word32_, byte *byte_)
{
	memset(byte_, 0, 32);
	word32 temp = word32_[0];
	int s = 24;
	for(unsigned int i = 0; i < 4; i++)
	{
		word32_[0] = temp;
		word32_[0] = word32_[0] >> s;
		byte_[i] |= word32_[0];
		s = s - 8;
	}
	temp = word32_[1];
	for(unsigned int i = 4; i < 8; i++)
	{
		word32_[1] = temp;
		word32_[1] = word32_[1] >> s;
		byte_[i] |= word32_[1];
		s = s - 8;
	}
	temp = word32_[2];
	for(unsigned int i = 8; i < 12; i++)
	{
		word32_[2] = temp;
		word32_[2] = word32_[2] >> s;
		byte_[i] |= word32_[2];
		s = s - 8;
	}
	temp = word32_[3];
	for(unsigned int i = 12; i < 16; i++)
	{
		word32_[3] = temp;
		word32_[3] = word32_[3] >> s;
		byte_[i] |= word32_[3];
		s = s - 8;
	}
	temp = word32_[4];
	for(unsigned int i = 16; i < 20; i++)
	{
		word32_[4] = temp;
		word32_[4] = word32_[4] >> s;
		byte_[i] |= word32_[4];
		s = s - 8;
	}
	temp = word32_[5];
	for(unsigned int i = 20; i < 24; i++)
	{
		word32_[5] = temp;
		word32_[5] = word32_[5] >> s;
		byte_[i] |= word32_[5];
		s = s - 8;
	}
	temp = word32_[6];
	for(unsigned int i = 24; i < 28; i++)
	{
		word32_[6] = temp;
		word32_[6] = word32_[6] >> s;
		byte_[i] |= word32_[6];
		s = s - 8;
	}
	temp = word32_[7];
	for(unsigned int i = 28; i < 32; i++)
	{
		word32_[7] = temp;
		word32_[7] = word32_[7] >> s;
		byte_[i] |= word32_[7];
		s = s - 8;
	}
}
static void byte_to_word32_key(byte *byte_, word32 *word32_)
{
	memset(word32_, 0, 32);

	for(unsigned int i = 0; i < 4; i++)
	{
		word32_[0] = word32_[0] << 8;
		word32_[0] |= byte_[i];
	}
	for(unsigned int i = 4; i < 8; i++)
	{
		word32_[1] = word32_[1] << 8;
		word32_[1] |= byte_[i];
	}
	for(unsigned int i = 8; i < 12; i++)
	{
		word32_[2] = word32_[2] << 8;
		word32_[2] |= byte_[i];
	}
	for(unsigned int i = 12; i < 16; i++)
	{
		word32_[3] = word32_[3] << 8;
		word32_[3] |= byte_[i];
	}
	for(unsigned int i = 16; i < 20; i++)
	{
		word32_[4] = word32_[4] << 8;
		word32_[4] |= byte_[i];
	}
	for(unsigned int i = 20; i < 24; i++)
	{
		word32_[5] = word32_[5] << 8;
		word32_[5] |= byte_[i];
	}
	for(unsigned int i = 24; i < 28; i++)
	{
		word32_[6] = word32_[6] << 8;
		word32_[6] |= byte_[i];
	}
	for(unsigned int i = 28; i < 32; i++)
	{
		word32_[7] = word32_[7] << 8;
		word32_[7] |= byte_[i];
	}
}
#endif