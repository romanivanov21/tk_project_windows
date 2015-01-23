/*******************************************************************
* Файл: main.cpp												   *
* Описание: тест функций crypt_gost_28147-89.dll				   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include "..\crypt_gost_28147-89\diffy_helman.h"
#include "..\shared_code\gost_include.h"

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

/*void gost_crypt_data(byte *data, std::size_t size)
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
*/
int main(void)
{
	diffy_helm *dh = new diffy_helm();
	/*byte p[32];
	byte q[32];
	byte g;
	*/
	byte A[32];
	/*dh->get_p(p, (sizeof(byte) * 32));
	dh->get_q(q, (sizeof(byte) * 32));
	dh->get_g(g);
	*/
	std::size_t time_1 = clock();
	dh->generate_A(A, 32);
	delete dh;
	
	key_box_init();

	unsigned char hash[64];
	unsigned int i = 0;
	byte tests[6];
	memcpy(tests, "Roman", sizeof(byte) * 5);
	hash_512(tests, 5,hash);
	for(i = 0; i < 64; i++)
	{
		printf("%x",hash[i]);
	}
	printf("\n");
	char k1[key_size16] = {0x0, 0x0,  0x0,  0x0,  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	const std::size_t s1 = strlen("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\Debug\\ginit.bin");
	read_vector_init("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\Debug\\ginit.bin",&s1);
	/*for(std::size_t i = 0; i < 32; i++)
	{
		std::cout<<std::hex<<(int)p[i];
	}
	std::cout<<std::endl;
	for(std::size_t i = 0; i < 32; i++)
	{
		std::cout<<std::hex<<(int)q[i];
	}
	std::cout<<std::endl;
	std::cout<<std::hex<<(int)g<<std::endl; */

/*	char data[15];
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
	*/
	printf("\nAll tests passed.\n");
	getchar();
	return 0;
}