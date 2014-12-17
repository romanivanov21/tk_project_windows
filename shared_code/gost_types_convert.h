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
#include "..\crypt_gost_28147-89\crypt_gost_types.h"
#include "string.h"

void word32_to_byte(word32 *word32_, byte *byte_)
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

void byte_to_word32( byte *byte_, word32 *word32_)
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

#endif