#include"parse_const.h"
#include"data_parser.h"
#include"gost_include.h"
#include"gost_types_convert.h"
#include<string>
#include<assert.h>
namespace server
{
	data_parser::data_parser() 
	{
		autentication_client_ = new autentication_client();
	}
	data_parser::~data_parser() 
	{
		delete autentication_client_;
	}

	void data_parser::parse_send_data(PNET_BUFF_DATA data_net, P_PARS_BUFF_DATA data_pars)
	{
		assert((data_net != nullptr) || (data_pars != nullptr));
		throw;
	}
	void data_parser::parse_read_data(PNET_BUFF_DATA data_net, P_PARS_BUFF_DATA data_pars)
	{
		assert(data_net != nullptr);
		get_client_id(data_net);
		// Здесь должна быть проверка id клиента
		if(is_crypt(data_net))
		{
			//Здесь должна быть расшифровка данных
		}
		get_comand(data_net);
		parse_comand(data_net, data_pars);
	}
	bool data_parser::is_crypt(const PNET_BUFF_DATA data)const
	{
		((data->net_buff[SERVICR_INFO_BYTE_NUM] << 7) & 0x01) ? (data->is_crypt = true) : (data->is_crypt=false);
		return data->is_crypt ? true : false;
	}
	void data_parser::get_client_id(PNET_BUFF_DATA data_net)
	{
		assert(data_net != nullptr);
		data_net->client_id = 0;
		data_net->client_id |= data_net->net_buff[35];
		data_net->client_id = data_net->client_id<< 8;
		data_net->client_id |= data_net->net_buff[34];
	}
	void data_parser::get_comand(PNET_BUFF_DATA data_net)
	{
		assert(data_net != nullptr);
		data_net->comand = 0;
		data_net->comand |= data_net->net_buff[33];
		data_net->comand = data_net->comand << 8;
		data_net->comand |= data_net->net_buff[32];
	}

	void data_parser::set_client_id(P_PARS_BUFF_DATA data_pars, const word16 &client_id)
	{
		assert(data_pars != nullptr || client_id != 0);
		data_pars->buff[36] = 0x00;
		data_pars->buff[35] = 0x00;
		data_pars->buff[35] |= client_id;
		const_cast<word16 &>(client_id) = client_id >>8;
		data_pars->buff[36];
	}
	void data_parser::set_comand(P_PARS_BUFF_DATA data_pars, const word16 &comand)
	{
		assert(data_pars != nullptr || comand != 0);
		data_pars->buff[33] = 0x00;
		data_pars->buff[32] = 0x00;
		data_pars->buff[32] |= comand;
		const_cast<word16 &>(comand) = comand >> 8;
		data_pars->buff[33] |= comand;
	}
	void data_parser::parse_comand(PNET_BUFF_DATA data_net, P_PARS_BUFF_DATA data_pars)
	{
		assert(data_net != nullptr || data_net->comand != 0);
		switch(data_net->comand)
		{
			case HCMD:
				set_client_id(data_pars, data_net->client_id);
				set_comand(data_pars, PSETCMD);
				autentication_client_->set_p(data_pars);
			break;
		}
	}
}