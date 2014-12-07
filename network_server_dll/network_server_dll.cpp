/*******************************************************************
* Файл: server_network_dll.cpp									   *
* Описание:содержит реализацию функций для работы сервреа с сетью  *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014														   *
*																   *
********************************************************************/
#include"network_server_dll.h"
#include"inc_boost_heders.h"

#include <Windows.h>
#include <iostream>

#ifndef WIN32

#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#define DEBUG_VERSION 1

boost::asio::io_service service;

SERVER_NETWORK_API void WINAPI read_message()
{

}

SERVER_NETWORK_API void WINAPI server_start()
{
	boost::asio::ip::tcp::acceptor acceptor(service, 
											boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
											8001));
	enum { buffer_size = 1024 };
	char buff[buffer_size];
	boost::asio::ip::tcp::socket sock(service);
	acceptor.accept(sock);
	char destBuff[1024];
	int bytes = sock.read_some(boost::asio::buffer(destBuff,1024));
    std::string msg(destBuff);
    if(DEBUG_VERSION)
	{
		std::cout<<msg<<std::endl;
	}
	strcpy_s(buff,"I is server");
	sock.write_some(boost::asio::buffer(buff,1024));
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