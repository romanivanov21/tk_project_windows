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

#include <boost/asio.hpp>
#include "..\crypt_gost_28147-89\crypt_gost_types.h"
#include <string>

class server : private boost::noncopyable
{
public:
	explicit server(const std::uint32_t port);
	~server();

	void start();
	void send_bytes(byte *data, std::size_t &size);
	boost::int32_t read_bytes(byte *data, std::size_t &size);
	std::uint32_t current_port() { return port_; }

private:
	void gost_crypt_data(byte *data, std::size_t &size, const word32 *key);
	void gost_decrypt_data(byte *data, std::size_t &size, const word32 *key);
private:

	std::uint32_t port_;

	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::icmp::socket socket_icmp_;
};
#endif