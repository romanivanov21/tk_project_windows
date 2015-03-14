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
#include "crypt_gost_types.h"
#include <cstring>
#include <mutex>
#include <atomic>
#include "server_timer.h"
#include "server_types.h"
/*********************************************************
* Класс, инкапсулирующий сетевую часть сервера			 *
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
		explicit server_network(const std::uint32_t port);

		/*************************************************
		* Деструктор класса server						 *
		**************************************************/
		~server_network();

		/*************************************************
		* Функция для начала работы сервреа				 *
		**************************************************/
		
		void start();

		/*************************************************
		*  Функция для передачи данных клиенту			 *
		* Параметры функции:							 *
		* 1. массив данных								 *
		* 2. размер массива								 *
		**************************************************/
		void send_bytes(byte *data, const std::size_t &size);
		void send_bytes(PNET_BUFF_DATA net_data);

		/*************************************************
		* Функция для приёма данных отклиента			 *
		* Параметры функции:							 *
		* 1. массив данных								 *
		* 2. размер массива								 *
		* Возвращаемое значение: число принятых байтов	 *
		**************************************************/
		boost::int32_t read_bytes(byte *data, const std::size_t &size);
		boost::int32_t read_bytes(PNET_BUFF_DATA net_data);

		/*************************************************
		* Функция возвращает текущий логический порт	 *
		* сервера										 *
		* Возвращаемое значение: текущий логический порт *
		**************************************************/
		std::uint32_t current_port()const;

		/*************************************************
		* Функция возвращает дата время соединения 		 *
		* клиента										 *
		* Возвращаемое значение: строка дата и время	 *
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
	};
}
#endif