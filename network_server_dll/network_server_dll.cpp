/*******************************************************************
* Файл: server_network_dll.cpp									   *
* Описание:содержит реализацию функций для работы сервреа с сетью  *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include"network_server_dll.h"
#include"inc_boost_heders.h"
#include"..\shared_code\gost_include.h"
#include"..\shared_code\gost_types_convert.h"
#include "..\crypt_gost_28147-89\crypt_gost_types.h"

#include <iostream>

#ifndef WIN32

#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#define DEBUG_VERSION 1

server::server(const std::uint32_t port) : 
	port_(port),
	socket_(io_service_), 
	socket_icmp_(io_service_),
	acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_)){ }

void server::start()
{
	acceptor_.accept(socket_); 
	socket_.close();
	//socket_icmp_.open(boost::asio::ip::icmp::v4());
}

void server::send_bytes(byte *data, std::size_t &size)
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

	gost_crypt_data(data,size,key);
	
	socket_.write_some(boost::asio::buffer(data,size));
}
boost::int32_t server::read_bytes(byte *data, std::size_t &size)
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

	boost::int32_t bytes = socket_.read_some(boost::asio::buffer(data, size));
	gost_decrypt_data(data, size, key);
	return bytes;
}

void server::gost_decrypt_data(byte *data, std::size_t &size, const word32 *key)
{
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
void server::gost_crypt_data(byte *data, std::size_t &size, const word32 *key)
{
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

server::~server()
{
	acceptor_.close();
	socket_.close();
}

NETWORK_SERVER_API void server_start()
{
	server s(8001);
	s.start();
}
/*boost::asio::io_service service;
NETWORK_SERVER_API void server_start()
{
	boost::asio::ip::tcp::acceptor acceptor(service, 
											boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
											8001));
	enum { buffer_size = 1024 };
	boost::asio::ip::tcp::socket sock(service);
	acceptor.accept(sock);

	char destBuff[buffer_size];
	boost::int32_t bytes = sock.read_some(boost::asio::buffer(destBuff,buffer_size));
    std::string msg(destBuff);
    if(DEBUG_VERSION)
	{
		std::cout<<msg<<std::endl;
	}
	word32 key[8];
	key[0] = 5; 
	key[1] = 4; 
	key[2] = 3; 
	key[3] = 2; 
	key[4] = 1; 
	key[5] = 0; 
	key[6] = 1; 
	key[7] = 5;
	char buff_byte[8];
	word32 buff_word32[2];

	byte crypt_buff_byte[8];
	word32 crypt_buff_word32[2];

	strcpy_s(buff_byte,"Roman21");
	byte_to_word32_data((byte*)buff_byte,buff_word32);
	key_box_init();
	gostcrypt(buff_word32,crypt_buff_word32,key);
	word32_to_byte_data(crypt_buff_word32,crypt_buff_byte);
	for(std::size_t i = 0; i < 8; i++)
	{
		std::cout<<crypt_buff_byte[i];
	}
	std::cout<<std::endl;
	sock.write_some(boost::asio::buffer(crypt_buff_byte,8));
	sock.close();
}
*/
BOOL WINAPI DllMain(HANDLE hInst, 
					ULONG ul_reason_for_call, 
					LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
	case(DLL_PROCESS_ATTACH):
		break;
	case(DLL_THREAD_ATTACH):
		break;
	case(DLL_THREAD_DETACH):
		break;
	case(DLL_PROCESS_DETACH):
		break;
	}
	return TRUE;
}