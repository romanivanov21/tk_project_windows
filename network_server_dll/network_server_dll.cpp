/*******************************************************************
* ����: server_network_dll.cpp									   *
* ��������:�������� ���������� ������� ��� ������ ������� � �����  *
* �����: ������ ����� ���������� (c)							   *
* ���: 2014 - 2015												   *
*																   *
********************************************************************/

//#include"..\crypt_gost_28147-89\crypt_gost_28147-89_API.h"
#include"network_server_dll.h"
#include"inc_boost_heders.h"

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
	//char buff[buffer_size];
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

	strcpy_s(buff_byte,"I is se");
	byte_to_word32((byte*)buff_byte,buff_word32);
	key_box_init();
	gostcrypt(buff_word32,crypt_buff_word32,key);
	word32_to_byte(crypt_buff_word32,crypt_buff_byte);
	//strcpy_s(buff,"I is server");
	sock.write_some(boost::asio::buffer(crypt_buff_byte,8));
	sock.close();
}

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