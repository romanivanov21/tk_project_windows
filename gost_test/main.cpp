/*******************************************************************
* Файл: main.cpp												   *
* Описание: тест функций crypt_gost_28147-89.dll				   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include "gost_API_test.h"
#include <iostream>

void gost_crypt_data(byte *data, std::size_t size)
{
	word32 key[8];
	key[0] = 5; 
	key[1] = 4; 
	key[2] = 3; 
	key[3] = 2; 
	key[4] = 1; 
	key[5] = 0; 
	key[6] = 1; 
	key[7] = 5;
	word32 word32_data[2];
	byte byte_data[8];
	memset(word32_data,0,8);
	memset(byte_data,0,8);
	word32 crypt_word32_data[2];
	byte crypt_byte_data[8];
	memset(crypt_word32_data, 0, 8);
	memset(crypt_byte_data, 0, 8);
	std::size_t number_blocks = 0; //количество блоков для шифрования
	if(size % 8 != 0)
	{
		number_blocks = (size / 8) + 1;
	}
	else
	{
		number_blocks = (size / 8);
	}
	
	std::size_t i = 0;
	std::size_t i_blocks = 1;
	while(i_blocks <= number_blocks)
	{
		std::size_t i_data = 0;
		for(std::size_t n_byte = i; (n_byte < (i + 8)); n_byte++)
		{
			byte_data[i_data] = data[n_byte];
			i_data++;
		}
		key_box_init();
		byte_to_word32_data(byte_data, word32_data);
		gostcrypt(word32_data,crypt_word32_data, key);
		word32_to_byte_data(crypt_word32_data, crypt_byte_data);

		i_data = 0;
		for(std::size_t n_byte = i; (n_byte < (i + 8)); n_byte++)
		{
			data[n_byte] = crypt_byte_data[i_data];
			i_data++;
		}
		i+=8;
		i_blocks++;
	}
}
void gost_decrypt_data(byte *data, std::size_t size)
{
	word32 key[8];
	key[0] = 5; 
	key[1] = 4; 
	key[2] = 3; 
	key[3] = 2; 
	key[4] = 1; 
	key[5] = 0; 
	key[6] = 1; 
	key[7] = 5;
	word32 word32_data[2];
	byte byte_data[8];
	memset(word32_data,0,8);
	memset(byte_data,0,8);
	word32 crypt_word32_data[2];
	byte crypt_byte_data[8];
	memset(crypt_word32_data, 0, 8);
	memset(crypt_byte_data, 0, 8);
	std::size_t number_blocks = 0; //количество блоков для шифрования
	if(size % 8 != 0)
	{
		number_blocks = (size / 8) + 1;
	}
	else
	{
		number_blocks = (size / 8);
	}
	
	std::size_t i = 0;
	std::size_t i_blocks = 1;
	while(i_blocks <= number_blocks)
	{
		std::size_t i_data = 0;
		for(std::size_t n_byte = i; (n_byte < (i + 8)); n_byte++)
		{
			byte_data[i_data] = data[n_byte];
			i_data++;
		}
		key_box_init();
		byte_to_word32_data(byte_data, word32_data);
		gostdecrypt(word32_data,crypt_word32_data, key);
		word32_to_byte_data(crypt_word32_data, crypt_byte_data);

		i_data = 0;
		for(std::size_t n_byte = i; (n_byte < (i + 8)); n_byte++)
		{
			data[n_byte] = crypt_byte_data[i_data];
			i_data++;
		}
		i+=8;
		i_blocks++;
	}
}
int main(void)
{
	char data[15];
	strcpy_s(data,"IvanovRoman021");
	gost_crypt_data((byte*)data,9);
	//init_gost(data);
	for(int i = 0; i < 9; i++)
	{
		std::cout<<data[i];
	}
	std::cout<<std::endl;
	gost_decrypt_data((byte*)data,9);
	for(int i = 0; i < 9; i++)
	{
		std::cout<<data[i];
	}
	std::cout<<std::endl;
	printf("\nAll tests passed.\n");
	getchar();
	return 0;
}