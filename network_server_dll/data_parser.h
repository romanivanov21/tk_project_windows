#ifndef _DATA_PARSER_H_
#define _DATA_PARSER_H_

#include"crypt_gost_types.h"
#include"server_types.h"

#include<boost\noncopyable.hpp>
#include<iostream>

namespace server
{
	class data_parser : private boost::noncopyable
	{
	public:
		data_parser();
		~data_parser();

		void parse_send_data(PNET_BUFF_DATA data_net, P_PARS_BUFF_DATA data_pars);
		void parse_read_data(P_PARS_BUFF_DATA data_pars, PNET_BUFF_DATA data_net);
	private:
		/************************************************************************
		* Проверка, установлен ли флаг шифрования								*
		*************************************************************************/
		bool is_crypt(const byte *buff, const std::size_t &length)const;
	};
}
#endif