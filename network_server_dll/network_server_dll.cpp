/*******************************************************************
* Файл: server_network_dll.cpp									   *
* Описание:содержит реализацию класса server, server_timer		   *
* для работы сервреа с сетью, и использования времени			   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include"network_server_dll.h"
#include"inc_boost_heders.h"
#include"..\shared_code\gost_include.h"
#include"..\shared_code\gost_types_convert.h"
#include "..\crypt_gost_28147-89\crypt_gost_types.h"
#include "server_timer.h"

#include <iostream>

#ifndef WIN32

#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#define DEBUG_VERSION 1

namespace server_netw
{
	NETWORK_SERVER_API  server::server(const std::uint32_t port) : 
		port_(port),
		socket_(io_service_), 
		socket_icmp_(io_service_),
		acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_)) 
	{

	}
	
	NETWORK_SERVER_API	void server::start()
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
			throw new std::string("Socket accept error");
		}
	}
	
	NETWORK_SERVER_API	void server::send_bytes(byte *data, const std::size_t &size)
	{
		try
		{
			socket_.write_some(boost::asio::buffer(data,size));
		}
		catch(...)
		{
			acceptor_.close();
			socket_.close();
			throw new std::string("Siket write_some error");
		}
	}
	
	NETWORK_SERVER_API	boost::int32_t server::read_bytes(byte *data, const std::size_t &size)
	{
		boost::int32_t bytes = -1;
		try
		{
			bytes = socket_.read_some(boost::asio::buffer(data, size));
		}
		catch(...)
		{
			acceptor_.close();
			socket_.close();
			throw new std::string("Soket read_bytes error");
		}
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
	NETWORK_SERVER_API	server::~server()
	{
		acceptor_.close();
		socket_.close();
	}
	std::string server_time::current_date_time_string()
	{
		return boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time());
	}

	void server_time::timer_start()
	{
		start_time_ = boost::posix_time::microsec_clock::local_time();
	}

	boost::int64_t server_time::timer_stop()
	{
		stop_time_ = boost::posix_time::microsec_clock::local_time();
		return (start_time_ - stop_time_).total_microseconds();
	}
}
NETWORK_SERVER_API void server_start(byte *data, std::size_t size)
{
	server_netw::server s(8001);
	server_netw::server_time time;
	try
	{
		std::cout<<time.current_date_time_string()<<std::endl;
		s.start();
		byte data_[8];
		std::size_t size_;
		if(s.read_bytes(data_,size_) == -1)
		{
			std::cout<<"Не удалось принять данные"<<std::endl;
		}
		s.send_bytes(data,size);
		for(std::size_t i = 0; i < 8; i++)
		{
			std::cout<<data_[i];
		}
		std::cout<<std::endl;
		for(int i = 0; i < 8; i++)
		{
			std::cout<<data[i];
		}
		std::cout<<std::endl;
	}
	catch(std::string s)
	{
		std::cout<<s<<std::endl;
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