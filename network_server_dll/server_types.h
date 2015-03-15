#ifndef _DATA_FORMAT_H_
#define _DATA_FORMAT_H_

#include "crypt_gost_types.h"
#include <string>
namespace server
{
	enum
	{
		SIZE_DATA_BUFF_BYTE = 36,
		SIZE_CLIENT_ID_BYTE = 2,
		SIZE_DATA_BYTE = 32,
		SIZE_NET_BUFF_BYTE = 37
	};
#pragma pack(push, 1)
	typedef struct
	{
		/****************************************************
		*	Буффер расшифрованных данных в одном массиве	*
		*****************************************************/
		byte buff[SIZE_DATA_BUFF_BYTE];
		/****************************************************
		*   Идентификатор клиента 2 байта					*
		*****************************************************/
		byte id_client[SIZE_CLIENT_ID_BYTE];
		/****************************************************
		* Байт содержит дополнительные флаги				*
		*****************************************************/
		byte fl_info;
		/****************************************************
		*   Остальные данные								*
		*****************************************************/
		byte data[SIZE_DATA_BYTE];

	}PARS_BUFF_DATA, *P_PARS_BUFF_DATA;
#pragma pack(pop)
#pragma pack(push,1)
	typedef struct
	{
		/****************************************************
		*   Идентификатор клиента 2 байта					*
		*****************************************************/
		word16 client_id;
		/****************************************************
		*  Время, когда подключился клиент 					*
		*****************************************************/
		std::string time_connect;
		/****************************************************
		*  Время, когда отключился клиент					*
		*****************************************************/
		std::string time_disconnect;
	}CLIENT_INFO, *PCLIENT_INFO;
#pragma pack(pop)
#pragma pack(push, 1)
	typedef struct 
	{
		byte net_buff[SIZE_NET_BUFF_BYTE];
		word16 client_id;
		bool is_crypt;
		byte fl_info;
		word16 comand;
		byte data[32];

	}NET_BUFF_DATA, *PNET_BUFF_DATA;

#pragma pack(pop)
}
#pragma pack(push, 1)
	typedef struct
	{
		bool is_client_connect_;
		server::CLIENT_INFO client_info_;
	}SERVER_INFO, *PSERVER_INFO;
#pragma pack(pop)
#endif