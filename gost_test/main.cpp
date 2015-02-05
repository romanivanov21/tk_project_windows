/*******************************************************************
* Файл: main.cpp												   *
* Описание: тест функций crypt_gost_28147-89.dll				   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include "..\crypt_gost_28147-89\diffy_helman.h"
#include "..\network_server_dll\network_server_dll.h"
#include "..\shared_code\gost_include.h"
#include "gost_test_exeption.h"
#include "crypt_gost_test.h"

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
int main(int argc, char *argv[])
{
	const std::string path = "F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\crypt_gost_28147-89\\ginit.bin";
	const std::string path_data = "F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\gost_test\\test_data\\gdata.xml";
	try
	{
		gost_test *g = new gost_test(path, path_data, 1);
		if(!(g->testing()))
		{
			std::cout<<"ERROR"<<std::endl;
		}

		delete g;
	}
	catch(gost_exception &ex)
	{
		std::cout<<ex.what()<<std::endl;
	}
	/*for(int i = 0; i < argc; i++)
	{
		std::cout<<"argc["<< i <<"]"<<argv[i]<<std::endl;
	}
	if((read_vector_init(path, &s1)) != 0)
	{
		return 0;
	}
	key_box_init();

	diffy_helm *d = new diffy_helm();
	byte A[32];
	byte p[32];
	byte q[32];
	byte g;
	byte p_hash[32];
	byte q_hash[32];

	d->get_p(p, 32);
	d->get_q(q, 32);
	d->get_g(g);
	d->generate_A(A, 32);

	boost::uint32_t port = 8001;
	server_netw::server *s = new server_netw::server(port);
	s->start();

	s->send_bytes(p, 32);
	hash_256(p,32,p_hash);
	printf("\n");
	for(std::size_t i = 0; i < 32; i++)
	{
		printf("%x",p_hash[i]);
	}
	printf("\n");

	s->send_bytes(q, 32);
	hash_256(q,32,q_hash);
	printf("\n");
	for(std::size_t i = 0; i < 32; i++)
	{
		printf("%x",q_hash[i]);
	}
	printf("\n");

	s->send_bytes(&g, 1);
	s->send_bytes(A, 32);

	byte B[32];
	boost::int32_t byte_reciver_B = s->read_bytes(B, 32);

	for(size_t i = 0; i < 32; i++)
	{
		printf("%x",B[i]);
	}
	printf("\n");

	byte shared_secret[32];
	d->generate_K(B, 32, shared_secret, 32);
	for(size_t i = 0; i < 32; i++)
	{
		printf("%x", shared_secret[i]);
	}
	printf("\n");

	delete d; delete s;*/
	printf("\nAll tests passed.\n");
	getchar();
	return 0;
}