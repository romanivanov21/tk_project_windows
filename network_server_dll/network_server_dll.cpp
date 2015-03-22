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
#include "server_types.h"
#include <iostream>
#include <thread>

#ifndef WIN32

#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#define DEBUG_VERSION 1

namespace server
{
	server_network::server_network(const std::uint32_t port) :
		port_(port),
		socket_(io_service_), 
		acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_)) 
	{
		assert(port != 0);

		data_parser_ = new data_parser();

		net_data_ = new SERVER_NET_BUF();
		memset(&net_data_->data_buff[0], 0x00, 38);
		net_data_->comand = 0x0000;
		net_data_->data_length = 0x00;
		net_data_->info_byte = 0x00;
		net_data_->id_client = 0x0000;
		net_data_->data.clear();
		pars_data_ = new SERVER_DATA_BUFF();
		memset(&pars_data_->data_buff[0], 0x00, 38);
		pars_data_->comand = 0x00000;
		pars_data_->data_length = 0x00;
		pars_data_->id_client = 0x0000;
		pars_data_->info_byte = 0x00;
		pars_data_->data.clear();
		server_info_.is_client_connect_ = false;
	}

	void server_network::start()
	{
		if(server_info_.is_client_connect_)
		{
			throw server::server_network_exception("Server is start");
		}
		try
		{
			acceptor_.accept(socket_);
			client_connect_time_ = time_.current_date_time_string();
			server_info_.is_client_connect_ = true;
#if _DEBUG
			std::cout<<"connect client"<<std::endl;
#endif
		}
		catch(...)
		{
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
			throw server::server_network_exception("Soket read_bytes error");
		}
		return bytes;
	}

	server_network::~server_network()
	{
		disable_connect();
		delete data_parser_;
		delete net_data_;
		delete pars_data_;
	}
	std::uint32_t server_network::current_port()const { return port_; }
	std::string server_network::client_connect_data_time()const { return client_connect_time_; }
	bool server_network::get_is_client_connect()const
	{
		return true;//server_info_.is_client_connect_;
	}
	void server_network::disable_connect()
	{
		acceptor_.close();
		socket_.close();
	}
	void server_network::send_bytes()
	{
		try
		{
			pars_data_->comand = 0x00000;
			pars_data_->data_length = 0x00;
			pars_data_->id_client = 0x0000;
			pars_data_->info_byte = 0x00;
			pars_data_->data.clear();
			data_parser_->parse_send_data(net_data_,pars_data_);
			socket_.write_some(boost::asio::buffer(pars_data_->data_buff,SIZE_NET_BUFF_BYTE));
#if _DEBUG
			std::cout<<"Send: ";
			for(std::size_t i = 0; i < 38; i++)
			{
				std::cout<<std::setw(2)<<std::setfill('0') <<std::hex <<(unsigned int) pars_data_->data_buff[i]<<" ";
			}
			std::cout<<std::endl;
#endif
		}
		catch(...)
		{
			throw server::server_network_exception("Siket write_some error");
		}
	}
	boost::int32_t server_network::read_bytes()
	{
		boost::int32_t bytes = -1;
		try
		{
			bytes = socket_.read_some(boost::asio::buffer(net_data_->data_buff, SIZE_NET_BUFF_BYTE));
			net_data_->comand = 0x0000;
			net_data_->data_length = 0x00;
			net_data_->info_byte = 0x00;
			net_data_->id_client = 0x0000;
			net_data_->data.clear();
			//считываем данные в net_buff_ и парсим
			data_parser_->parse_read_data(net_data_);
#if _DEBUG
			std::cout<<"Adopt: ";
			for(std::size_t i = 0; i < 38; i++)
			{
				std::cout<<std::setw(2)<<std::setfill('0') <<std::hex <<(unsigned int)net_data_->data_buff[i]<<" ";
			}
			std::cout<<std::endl;
#endif
		}
		catch(...)
		{
			throw server::server_network_exception("Soket read_bytes error");
		}
		return bytes;
	}
	server_network* server_network::get_instanse(const std::uint32_t &port)
	{
		std::atomic<server_network*> m_instance_(nullptr);
		std::mutex m_mutex_;

		server_network* tmp = m_instance_.load(std::memory_order_relaxed);
		std::atomic_thread_fence(std::memory_order_acquire);
		
		if (tmp == nullptr) 
		{
			std::lock_guard<std::mutex> lock(m_mutex_);
			tmp = m_instance_.load(std::memory_order_relaxed);
			if (tmp == nullptr) 
			{
				tmp = new server_network(port);
				std::atomic_thread_fence(std::memory_order_release);
				m_instance_.store(tmp, std::memory_order_relaxed);
			}
		}
		return tmp;
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