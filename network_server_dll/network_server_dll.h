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

/*********************************************************
* ������� server_start ��������� ������					 *
**********************************************************/
NETWORK_SERVER_API void server_start();
/*
#include <boost/asio.hpp>
#include <string>

class server : private boost::noncopyable
{
public:
	explicit server(const std::string &ip_address, const std::string &port);
	~server();

	void server_start();
private:

	std::string port_;

	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::icmp::socket socket_icmp_;

	std::string ip_address_;

	enum { buffer_size = 1024 };
	char buff_in_[buffer_size];
	char buff_out_[buffer_size];
};*/
#endif