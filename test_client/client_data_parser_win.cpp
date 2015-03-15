#include"client_types.h"
#include"client_data_parser_win.h"
#include"gost_include.h"
#include"crypt_gost_types.h"
#include"network_client_win.h"
#include<iostream>
namespace client
{
	client_data_parser::client_data_parser()
	{

	}
	client_data_parser::~client_data_parser()
	{
	}
	
	void client_data_parser::send_data_parser(PCLIENT_NET_BUF net_buff, PCLIENT_DATA_BUFF data_buff)
	{
	}
	void client_data_parser::send_data_parser(PCLIENT_DATA_BUFF net_buff)
	{
	}
	void client_data_parser::read_data_parser(PCLIENT_NET_BUF net_buff, PCLIENT_DATA_BUFF data_buff)
	{
	}
	void client_data_parser::set_client_id(PCLIENT_DATA_BUFF data)
	{
		word16 client_id = CLIENT_ID;
		data->data_buff[35] |= client_id;
		client_id = client_id << 8;
		data->data_buff[34] |= client_id;
	}
	void client_data_parser::set_byte_autch(PCLIENT_DATA_BUFF data)
	{
		/***************************************************************
		* установлены биты нет шифрования и бит аутентификации клиента *
		****************************************************************/
		data->data_buff[SERVICR_INFO_BYTE_NUM] |= 0x03;
	}
	void client_data_parser::set_hello_comand(PCLIENT_DATA_BUFF data)
	{
		word16 cmd = HCMD;
		data->data_buff[HCMD_NUM - 1] |= cmd;
		cmd = cmd>>8;
		data->data_buff[HCMD_NUM] |= cmd;
	}
}