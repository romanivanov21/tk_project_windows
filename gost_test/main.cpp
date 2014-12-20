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

	word32 key_word32[8];
	byte key_byte[32];

	memset(key_byte, 5, 32);

	byte_to_word32_key(key_byte, key_word32);
	word32_to_byte_key(key_word32, key_byte);

	for(int i = 0; i < 32; i++)
	{
		printf("%x",key_byte[i]);
	}
	/*byte_to_word32_data(byte_,word32_);
	word32_to_byte_data(word32_,byte_);
	printf("\n");
	for(int i = 0; i < 8; i++)
	{
		printf("%d",byte_[i]);
	}
	*/
	printf("\nAll tests passed.\n");
	getchar();
	return 0;
}