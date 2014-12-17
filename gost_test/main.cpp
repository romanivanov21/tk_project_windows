/*******************************************************************
* Файл: main.cpp												   *
* Описание: тест функций crypt_gost_28147-89.dll				   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include <iostream>
#include "..\shared_code\gost_include.h"
#include "..\shared_code\gost_types_convert.h"

int main(void)
{
	word32 word32_[2];
	byte byte_[8];
	byte_[0] = 1;
	byte_[1] = 2;
	byte_[2] = 3;
	byte_[3] = 4;
	byte_[4] = 5;
	byte_[5] = 6;
	byte_[6] = 7;
	byte_[7] = 8;

	for(int i = 0; i < 8; i++)
	{
		printf("%x",byte_[i]);
	}
	byte_to_word32(byte_,word32_);
	word32_to_byte(word32_,byte_);
	printf("\n");
	for(int i = 0; i < 8; i++)
	{
		printf("%d",byte_[i]);
	}
	printf("\nAll tests passed.\n");
	getchar();
	return 0;
}