#ifndef _CLIENT_TYPES_H_
#define _CLIENT_TYPES_H_
#define CLIENT_ID 0x01

#include "comand_pars.h"
#include "crypt_gost_types.h"
#include <vector>
namespace client
{
#pragma pack(push,1)
	typedef struct
	{
		byte data_buff[38];
		std::vector<byte> data;
		word16 id_client;
		byte info_byte;
		word16 comand;
		byte data_length;
	}CLIENT_NET_BUF, *PCLIENT_NET_BUF;
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
	}CLIENT_DATA_BUFF, *PCLIENT_DATA_BUFF;
#pragma pack(pop)
}
#endif