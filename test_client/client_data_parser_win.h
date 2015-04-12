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
		
		void send_data_parser(PCLIENT_DATA_BUFF data_buff, PCLIENT_NET_BUF net_buf);
		void read_data_parser(PCLIENT_NET_BUF net_buf, PCLIENT_DATA_BUFF data_buff);
	private:

		bool is_crypt(const byte &data)const;

		void set_client_id(PCLIENT_DATA_BUFF data);
		void set_byte_info(PCLIENT_DATA_BUFF data);
		void set_comand(PCLIENT_DATA_BUFF data);
		void set_data_and_length(PCLIENT_DATA_BUFF data);

		void get_client_id(PCLIENT_NET_BUF data);
		void get_info_byte(PCLIENT_NET_BUF data);
		void get_comand(PCLIENT_NET_BUF data);
		void get_data_and_length(PCLIENT_NET_BUF data);

		void send_hello(PCLIENT_DATA_BUFF data);
		void send_p_hash(PCLIENT_DATA_BUFF data);
		void send_q_hash(PCLIENT_DATA_BUFF data);
		void send_spublic_key_hash(PCLIENT_DATA_BUFF data);
		void send_spublic_key_ok(PCLIENT_DATA_BUFF data);
		void send_cpublic_key_hash(PCLIENT_DATA_BUFF data, PCLIENT_NET_BUF net_buff);
	
	private:
		diffy_helm *dh_;
		PTR_DH_TYPE dh_type_;
		PTR_GOST_TYPE crypt_g_;
		PTR_HASH_TYPE hash_;
	};
}
#endif