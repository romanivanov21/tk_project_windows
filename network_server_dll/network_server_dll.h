/*******************************************************************
* Файл: server_network_dll.h									   *
* Описание:содержит обяъявление функций для работы сервреа с сетью *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014														   *
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
* Функция server_start запускает сервер					 *
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