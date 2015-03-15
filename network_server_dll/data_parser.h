#ifndef _DATA_PARSER_H_
#define _DATA_PARSER_H_

#include"crypt_gost_types.h"
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

		void parse_send_data(PNET_BUFF_DATA data_net, P_PARS_BUFF_DATA data_pars);
		void parse_read_data(PNET_BUFF_DATA data_net, P_PARS_BUFF_DATA data_pars);

	private:
		void get_client_id(PNET_BUFF_DATA data_net);
		void get_comand(PNET_BUFF_DATA data_net);
		void parse_comand(PNET_BUFF_DATA data_net, P_PARS_BUFF_DATA data_pars);
		void set_client_id(P_PARS_BUFF_DATA data_pars, const word16 &client_id);
		void set_comand(P_PARS_BUFF_DATA data_pars, const word16 &comand);
		/************************************************************************
		* Проверка, установлен ли флаг шифрования								*
		*************************************************************************/
		bool is_crypt(const PNET_BUFF_DATA data)const;
	
	private:
		autentication_client *autentication_client_;
	};
}
#endif