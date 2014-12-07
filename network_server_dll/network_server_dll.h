/*******************************************************************
* Файл: server_network_dll.h									   *
* Описание:содержит обяъявление функций для работы сервреа с сетью *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014														   *
*																   *
********************************************************************/

#ifndef _SERVER_NETWORK_DLL_H_

#define SERVER_NETWORK_API extern __declspec(dllexport)
#else
#define SERVER_NETWORK_API extern __declspec(dllimport)

/*********************************************************
* define ServerNetworkDll version						 *
**********************************************************/
#define SERVER_NETWORK_DLL_VERSION 0x01

std::size_t read_complete(char *buff,
						  const boost::system::error_code &err, 
						  std::size_t bytes);

/*********************************************************
* Функция server_start запускает сервер					 *
**********************************************************/
SERVER_NETWORK_API void WINAPI server_start();

/*class server_network
{
public:
	server_network();
	~server_network();

	SERVER_NETWORK_API void WINAPI server_start();
	SERVER_NETWORK_API void WINAPI read_message();
	SERVER_NETWORK_API void WINAPI write_message();

private:
	boost::asio::io_service service;

};
*/
#endif