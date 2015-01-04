/*******************************************************************
* ����: server_network_dll.h									   *
* ��������:�������� ����������� ������� ��� ������ ������� � ����� *
* �����: ������ ����� ���������� (c)							   *
* ���: 2014														   *
*																   *
********************************************************************/

#ifndef _NETWORK_SERVER_DLL_H_
#define _NETWORK_SERVER_DLL_H_

#define NETWORK_SERVER_API extern __declspec(dllexport)
/*#else
#define NETWORK_SERVER_API extern __declspec(dllimport)
*/
/*********************************************************
* define ServerNetworkDll version						 *
**********************************************************/
#define NETWORK_SERVER_DLL_VERSION 0x01

#include "inc_boost_heders.h"
#include "..\crypt_gost_28147-89\crypt_gost_types.h"
#include <string>
#include "server_timer.h"

NETWORK_SERVER_API void server_start(byte *data, std::size_t size);

/*********************************************************
* �����, ��������������� ������ �������					 *
**********************************************************/
namespace server_netw
{
	class server : private boost::noncopyable
	{
	public:
		/*************************************************
		* ���������� ������ server						 *
		* ��������� ������������:						 *
		* 1. ���������� ���� �������					 *
		**************************************************/
		explicit server(const std::uint32_t port);

		/*************************************************
		* ���������� ������ server						 *
		**************************************************/
		~server();

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
		void send_bytes(byte *data, std::size_t &size);

		/*************************************************
		* ������� ��� ����� ������ ���������			 *
		* ��������� �������:							 *
		* 1. ������ ������								 *
		* 2. ������ �������								 *
		* ������������ ��������: ����� �������� ������	 *
		**************************************************/
		boost::int32_t read_bytes(byte *data, std::size_t &size);

		/*************************************************
		* ������� ���������� ������� ���������� ����	 *
		* �������										 *
		* ������������ ��������: ������� ���������� ���� *
		**************************************************/
		std::uint32_t current_port()const { return port_; }

		/*************************************************
		* ������� ���������� ���� ����� ���������� 		 *
		* �������										 *
		* ������������ ��������: ������ ���� � �����	 *
		**************************************************/
		std::string client_connect_data_time() { return client_connect_time_; }
	private:
		void gost_crypt_data(byte *data, std::size_t &size, const word32 *key);
		void gost_decrypt_data(byte *data, std::size_t &size, const word32 *key);
	private:
		server_time time_;
		std::string client_connect_time_;
		std::uint32_t port_;
		
		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::acceptor acceptor_;
		boost::asio::ip::tcp::socket socket_;
		boost::asio::ip::icmp::socket socket_icmp_;
	};
}
#endif