#ifndef _DATA_PARSER_H_
#define _DATA_PARSER_H_

#include"crypt_gost_types.h"
#include"..\crypt_gost_28147-89\diffy_helman.h"
#include"server_types.h"
#include"authentication_client.h"

#include<boost\noncopyable.hpp>
#include<iostream>

namespace server
{
	class autentication_client;
	class data_parser : private boost::noncopyable
	{
	public:
		data_parser();
		~data_parser();

		void parse_send_data(PSERVER_NET_BUF data_net, PSERVER_DATA_BUFF data_pars);
		void parse_read_data(PSERVER_NET_BUF data_net);

	private:
		void get_client_id(PSERVER_NET_BUF data_net);
		void get_info_byte(PSERVER_NET_BUF data_net);
		void get_comand(PSERVER_NET_BUF data_net);
		void get_data_and_length(PSERVER_NET_BUF data_net);

		void set_client_id(PSERVER_DATA_BUFF data_pars);
		void set_comand(PSERVER_DATA_BUFF data_pars);
		void set_info_byte(PSERVER_DATA_BUFF data_pars);
		void set_data_and_length(PSERVER_DATA_BUFF);
		/************************************************************************
		* Проверка, установлен ли флаг шифрования								*
		*************************************************************************/
		bool is_crypt(const byte &data)const;
		void send_p_dh(PSERVER_DATA_BUFF data_pars, PSERVER_NET_BUF net_data);
		void send_phashcmd(PSERVER_DATA_BUFF data_pars, PSERVER_NET_BUF net_data);
	
	private:
		autentication_client *autentication_client_;
		PTR_DH_TYPE dh_type_;
		diffy_helm *dh_;
		PTR_GOST_TYPE crypt_g_;
		PTR_HASH_TYPE hash_g_;
	};
}
#endif