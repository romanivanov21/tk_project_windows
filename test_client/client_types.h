#ifndef _CLIENT_TYPES_H_
#define _CLIENT_TYPES_H_
#define CLIENT_ID 0x01

#include "crypt_gost_types.h"
namespace client
{
	enum 
	{
		SIZE_NET_BUFF=37,
		SIZE_DATA_BUFF=37,
		SIZE_CLIENT_ID=2,
		CLIENT_ID_NUM = 36,
		SERVICR_INFO_BYTE_NUM=34,
		DATA_BYTE_NUM=31,
		HCMD_NUM=33
	};
	enum
	{
		HCMD = 0x01
	};
#pragma pack(push,1)
	typedef struct
	{
		byte net_buff_data[SIZE_NET_BUFF];
	}CLIENT_NET_BUF, *PCLIENT_NET_BUF;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct
	{
		byte data_buff[SIZE_DATA_BUFF];
	}CLIENT_DATA_BUFF, *PCLIENT_DATA_BUFF;
#pragma pack(pop)
}
#endif