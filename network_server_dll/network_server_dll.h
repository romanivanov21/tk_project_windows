/*******************************************************************
* ����: server_network_dll.h									   *
* ��������:�������� ����������� ������� ��� ������ ������� � ����� *
* �����: ������ ����� ���������� (c)							   *
* ���: 2014														   *
*																   *
********************************************************************/

#ifndef _NETWORK_SERVER_DLL_H_
#define _NETWORK_SERVER_DLL_H_

#define NETWORK_SERVER_API __declspec(dllexport)

/*********************************************************
* define ServerNetworkDll version						 *
**********************************************************/
#define NETWORK_SERVER_DLL_VERSION 0x01

#include "inc_boost_heders.h"
#include "authentication_client.h"
#include "data_parser.h"
#include "crypt_gost_types.h"
#include <cstring>
#include <mutex>
#include <atomic>
#include "server_timer.h"
#include "server_types.h"
/*********************************************************
* �����, ��������������� ������� ����� �������			 *
**********************************************************/
namespace server
{
	class data_parser;
	class server_network : private boost::noncopyable
	{
	private:
		/*************************************************
		* ���������� ������ server						 *
		* ��������� ������������:						 *
		* 1. ���������� ���� �������					 *
		**************************************************/
		explicit server_network(const std::uint32_t port);
	public:
		/*************************************************
		* ���������� ������ server						 *
		**************************************************/
		~server_network();

		/*************************************************
		* ������� ��� ������ ������ �������				 *
		**************************************************/
		
		void start();

		/*************************************************
		*  ������� ��� �������� ������ �������			 *
		* ��������� �������:							 *
		* 1. ������ ������								 *
		* 2. ������ �������								 *
		**************************************************/
		void send_bytes(byte *data, const std::size_t &size);
		void send_bytes();

		/*************************************************
		* ������� ��� ����� ������ ���������			 *
		* ��������� �������:							 *
		* 1. ������ ������								 *
		* 2. ������ �������								 *
		* ������������ ��������: ����� �������� ������	 *
		**************************************************/
		boost::int32_t read_bytes(byte *data, const std::size_t &size);
		boost::int32_t read_bytes();

		/*************************************************
		* ������� ���������� ������� ���������� ����	 *
		* �������										 *
		* ������������ ��������: ������� ���������� ���� *
		**************************************************/
		std::uint32_t current_port()const;

		/*************************************************
		* ������� ���������� ���� ����� ���������� 		 *
		* �������										 *
		* ������������ ��������: ������ ���� � �����	 *
		**************************************************/
		std::string client_connect_data_time()const;
		bool get_is_client_connect()const;
		server_network *get_instanse(const std::uint32_t &port); 
		
	private:

		void disable_connect();
	private:
		SERVER_INFO server_info_;

		server_time time_;
		std::string client_connect_time_;
		std::uint32_t port_;
		
		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::acceptor acceptor_;
		boost::asio::ip::tcp::socket socket_;

		data_parser *data_parser_;

		PSERVER_NET_BUF net_data_;
		PSERVER_DATA_BUFF pars_data_;
	};
}
#endif