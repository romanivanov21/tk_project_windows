/*******************************************************************
* Файл: server_network_dll.h									   *
* Описание:содержит обяъявление функций для работы сервреа с сетью *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014														   *
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
#include "..\crypt_gost_28147-89\crypt_gost_types.h"
#include <string>
#include "server_timer.h"

NETWORK_SERVER_API void server_start(byte *data, std::size_t size);

/*********************************************************
* Класс, инкапсулирующий работу сервреа					 *
**********************************************************/
namespace server
{
	class server_network : private boost::noncopyable
	{
	public:
		/*************************************************
		* Коструктор класса server						 *
		* Параметры конструктора:						 *
		* 1. Логический порт сервреа					 *
		**************************************************/
		NETWORK_SERVER_API explicit server_network(const std::uint32_t port);

		/*************************************************
		* Деструктор класса server						 *
		**************************************************/
		NETWORK_SERVER_API ~server_network();

		/*************************************************
		* Функция для начала работы сервреа				 *
		**************************************************/
		NETWORK_SERVER_API void start();

		/*************************************************
		*  Функция для передачи данных клиенту			 *
		* Параметры функции:							 *
		* 1. массив данных								 *
		* 2. размер массива								 *
		**************************************************/
		NETWORK_SERVER_API void send_bytes(byte *data, const std::size_t &size);

		/*************************************************
		* Функция для приёма данных отклиента			 *
		* Параметры функции:							 *
		* 1. массив данных								 *
		* 2. размер массива								 *
		* Возвращаемое значение: число принятых байтов	 *
		**************************************************/
		NETWORK_SERVER_API boost::int32_t read_bytes(byte *data, const std::size_t &size);

		/*************************************************
		* Функция возвращает текущий логический порт	 *
		* сервера										 *
		* Возвращаемое значение: текущий логический порт *
		**************************************************/
		NETWORK_SERVER_API std::uint32_t current_port()const { return port_; }

		/*************************************************
		* Функция возвращает дата время соединения 		 *
		* клиента										 *
		* Возвращаемое значение: строка дата и время	 *
		**************************************************/
		NETWORK_SERVER_API std::string client_connect_data_time() { return client_connect_time_; }
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