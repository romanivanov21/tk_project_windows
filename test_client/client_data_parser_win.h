#ifndef _CLIENT_DATA_PARSER_WIN_H_
#define _CLIENT_DATA_PARSER_WIN_H_
#include"client_types.h"
#include"network_client_win.h"
#include"client_authentication_win.h"
namespace client
{
	class client_network_windows;
	class client_data_parser
	{
	public:
		client_data_parser();
		~client_data_parser();
		
		void send_data_parser(PCLIENT_NET_BUF net_buf, PCLIENT_DATA_BUFF data_buff);
		void send_data_parser(PCLIENT_DATA_BUFF net_buf);
		void read_data_parser(PCLIENT_NET_BUF net_buf, PCLIENT_DATA_BUFF data_buff);
		
		void set_client_id(PCLIENT_DATA_BUFF data);
		void set_byte_autch(PCLIENT_DATA_BUFF data);
		void set_hello_comand(PCLIENT_DATA_BUFF data);
	
	private:
		client_network_windows *netw_;
	};
}
#endif