#ifndef _DATA_FORMAT_H_
#define _DATA_FORMAT_H_

#include "crypt_gost_types.h"
#include <string>
namespace server
{
	enum
	{
		SIZE_DATA_BUFF_BYTE = 34,
		SIZE_CLIENT_ID_BYTE = 2,
		SIZE_DATA_BYTE = 22,
		SIZE_NET_BUFF_BYTE = 36
	};
#pragma pack(push, 1)
	typedef struct
	{
		/****************************************************
		*	������ �������������� ������ � ����� �������	*
		*****************************************************/
		byte buff[SIZE_DATA_BUFF_BYTE];
		/****************************************************
		*   ������������� ������� 2 �����					*
		*****************************************************/
		byte id_client[SIZE_CLIENT_ID_BYTE];
		/****************************************************
		* ���� �������� �������������� �����				*
		*****************************************************/
		byte fl_info;
		/****************************************************
		*   ��������� ������								*
		*****************************************************/
		byte data[SIZE_DATA_BYTE];

	}PARS_BUFF_DATA, *P_PARS_BUFF_DATA;
#pragma pack(pop)
#pragma pack(push,1)
	typedef struct
	{
		/****************************************************
		*   ������������� ������� 2 �����					*
		*****************************************************/
		word16 client_id;
		/****************************************************
		*  �����, ����� ����������� ������ 					*
		*****************************************************/
		std::string time_connect;
		/****************************************************
		*  �����, ����� ���������� ������					*
		*****************************************************/
		std::string time_disconnect;
	}CLIENT_INFO, *PCLIENT_INFO;
#pragma pack(pop)
#pragma pack(push, 1)
	typedef struct 
	{
		byte net_buff[SIZE_NET_BUFF_BYTE];

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