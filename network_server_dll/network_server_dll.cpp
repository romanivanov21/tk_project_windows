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

#include <iostream>

#ifndef WIN32

#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#define DEBUG_VERSION 1

/*server::server(const std::string &ip_addres, const std::string &port): ip_address_(ip_addres), port_(port), 
	acceptor_(io_service_),
	socket_(io_service_), 
	socket_icmp_(io_service_)
{
	boost::asio::ip::tcp::resolver resolver(io_service_);
	boost::asio::ip::tcp::resolver::query query(ip_address_,port_);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	acceptor_.open(endpoint.protocol());
	acceptor_.bind(endpoint);
}

void server::server_start()
{
	acceptor_.accept(socket_);

	acceptor_.listen();
	boost::uint32_t bytes = socket_.read_some(boost::asio::buffer(buff_in_,buffer_size));
	std::string msg(buff_out_);
	strcpy_s(buff_out_, "I is server");
	socket_.write_some(boost::asio::buffer(buff_out_,buffer_size));
}

server::~server()
{
	acceptor_.close();
	socket_.close();
}*/

boost::asio::io_service service;
NETWORK_SERVER_API void server_start()
{
	boost::asio::ip::tcp::acceptor acceptor(service, 
											boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
											8001));
	enum { buffer_size = 1024 };
	boost::asio::ip::tcp::socket sock(service);
	acceptor.accept(sock);

	char destBuff[buffer_size];
	int bytes = sock.read_some(boost::asio::buffer(destBuff,buffer_size));
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