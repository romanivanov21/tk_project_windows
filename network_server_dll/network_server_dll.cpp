/*******************************************************************
* Файл: server_network_dll.cpp									   *
* Описание:содержит реализацию класса server, server_timer		   *
* для работы сервреа с сетью, и использования времени			   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include"network_server_dll.h"
#include"network_server_exception.h"
#include"inc_boost_heders.h"
#include"gost_include.h"
#include"gost_types_convert.h"
#include "crypt_gost_types.h"
#include "server_timer.h"

#include <iostream>

#ifndef WIN32

#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#define DEBUG_VERSION 1

namespace server
{
	server_network* server_network::s_ = 0;
	server_network::server_network(const std::uint32_t port) : 
		port_(port),
		socket_(io_service_), 
		acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_)) 
	{
		assert(port != 0);

	}

	server::server_network* server_network::instance(const std::size_t &port)
	{
		try
		{
			if(s_ == 0)
			{
				s_ = new server::server_network(port);
			}
		}
		catch(server_network_exception &ex)
		{
			throw server_network_exception(ex.what());
		}
		return s_;
	}

	void server_network::start()
	{
		try
		{
			acceptor_.accept(socket_);
			client_connect_time_ = time_.current_date_time_string();
		}
		catch(...)
		{
			acceptor_.close();
			socket_.close();
			throw server::server_network_exception("Socket accept error");
		}
	}
	
	void server_network::send_bytes(byte *data, const std::size_t &size)
	{
		assert(data != NULL || size != 0);
		try
		{
			socket_.write_some(boost::asio::buffer(data,size));
		}
		catch(...)
		{
			acceptor_.close();
			socket_.close();
			throw server::server_network_exception("Siket write_some error");
		}
	}
	
	boost::int32_t server_network::read_bytes(byte *data, const std::size_t &size)
	{
		assert(data != NULL || size != 0);
		boost::int32_t bytes = -1;
		try
		{
			bytes = socket_.read_some(boost::asio::buffer(data, size));
		}
		catch(...)
		{
			acceptor_.close();
			socket_.close();
			throw server::server_network_exception("Soket read_bytes error");
		}
		return bytes;
	}

	server_network::~server_network()
	{
		acceptor_.close();
		socket_.close();
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