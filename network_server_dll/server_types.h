#ifndef _DATA_FORMAT_H_
#define _DATA_FORMAT_H_

#include "crypt_gost_types.h"
#include <string>
#include <vector>
namespace server
{
	enum
	{
		SIZE_DATA_BUFF_BYTE = 37,
		SIZE_CLIENT_ID_BYTE = 2,
		SIZE_DATA_BYTE = 32,
		SIZE_NET_BUFF_BYTE = 38
	};
	#pragma pack(push,1)
	typedef struct
	{
		byte data_buff[38];
		std::vector<byte> data;
		word16 id_client;
		byte info_byte;
		word16 comand;
		byte data_length;
	}SERVER_NET_BUF, *PSERVER_NET_BUF;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct
	{
		byte data_buff[38];
		std::vector<byte> data;
		word16 id_client;
		byte info_byte;
		word16 comand;
		byte data_length;
	}SERVER_DATA_BUFF, *PSERVER_DATA_BUFF;
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
}
#pragma pack(push, 1)
	typedef struct
	{
		bool is_client_connect_;
	}SERVER_INFO, *PSERVER_INFO;
#pragma pack(pop)
#endif