#include"parse_const.h"
#include"data_parser.h"
#include"gost_include.h"
#include"gost_types_convert.h"
#include <iomanip>
#include <iostream>
#include<string>
#include<assert.h>
namespace server
{
	data_parser::data_parser() 
	{
		autentication_client_ = new autentication_client();
		dh_type_ = new DH_TYPE();
		memset(dh_type_->gkey, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		memset(dh_type_->q_byte, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		memset(dh_type_->p_byte, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		memset(dh_type_->keyA, 0x0, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		memset(dh_type_->keyB, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		dh_ = new diffy_helm();
		crypt_g_ = new GOST_TYPE();
		memset(crypt_g_->byte_decryption_data, 0x00, sizeof(byte)*SIZE_CRYPT_BUFF_BYTE);
		memset(crypt_g_->byte_encryption_data, 0x00, sizeof(byte)*SIZE_CRYPT_BUFF_BYTE);
		memset(crypt_g_->byte_key, 0x00, sizeof(byte)*SIZE_CRYPT_BUFF_BYTE);
		memset(crypt_g_->word_decryption_data, 0x00, sizeof(word32)*SIZE_CRYPT_BUFF_WORD);
		memset(crypt_g_->word_encryption_data, 0x00, sizeof(word32)*SIZE_CRYPT_BUFF_WORD);
		hash_g_ = new HASH_TYPE();
		memset(hash_g_->data256, 0x00, sizeof(byte)*SIZE_HASH256_BYTE);
		memset(hash_g_->data512, 0x00, sizeof(byte)*SIZE_HASH512_BYTE);
		memset(hash_g_->hash256, 0x00, sizeof(byte)*SIZE_HASH256_BYTE);
		memset(hash_g_->hash512, 0x00, sizeof(byte)*SIZE_HASH512_BYTE);
	}
	data_parser::~data_parser() 
	{
		delete dh_;
		delete dh_type_;
		delete crypt_g_;
		delete hash_g_;
		delete autentication_client_;
	}

	void data_parser::parse_send_data(PSERVER_NET_BUF data_net, PSERVER_DATA_BUFF data_pars)
	{
		assert((data_net != nullptr) || (data_pars != nullptr));
		switch (data_net->comand)
		{
		case HCMD:
			send_p_dh(data_pars, data_net);
			break;
		case PHASHCMD:
			send_phashcmd(data_pars, data_net);
			break;
		case QHASHCMD:
			send_qhashcmd(data_pars, data_net);
			break;
		case SPUBLICKEYHASHCMD:
			send_spublic_key_hash(data_pars, data_net);
			break;
		case CPUBLICKEYCMD:
			send_cpublic_key(data_pars, data_net);
			break;
		case CPUBLICKEYOK:
			dh_->generate_K(dh_type_->keyB, SIZE_DH_BUFF_BYTE, dh_type_->gkey, SIZE_DH_BUFF_BYTE);
			std::cout<<"gkey :";
			for(std::size_t i = 0; i < SIZE_DH_BUFF_BYTE; i++)
			{
				std::cout<<std::setw(2)<<std::setfill('0') <<std::hex <<(unsigned int)dh_type_->gkey[i]<<" ";
			}
			std::cout<<std::endl;
			break;
		}
	}
	void data_parser::parse_read_data(PSERVER_NET_BUF data_net)
	{
		assert(data_net != nullptr);
		get_info_byte(data_net);
		// Здесь должна быть проверка id клиента
		if(is_crypt(data_net->info_byte))
		{
			//Здесь должна быть расшифровка данных
		}
		get_client_id(data_net);
		get_comand(data_net);
		get_data_and_length(data_net);
	}
	bool data_parser::is_crypt(const byte &data)const
	{
		return (data & 0x01) ? true : false;
	}
	void data_parser::get_info_byte(PSERVER_NET_BUF data)
	{
		assert(data != nullptr);
		data ->info_byte = data->data_buff[2]; 
	}
	void data_parser::get_data_and_length(PSERVER_NET_BUF data)
	{
		assert(data != nullptr);
		data->data_length = data->data_buff[5];
		if(data->data_length > 32)
		{
			//exception
		}
		if(data->data_length == 0)
		{
			data->data.clear();
			return;
		}
		data->data.clear();
		data->data.resize(data->data_length);
		memcpy(&data->data[0], &data->data_buff[6], data->data_length);
		/*std::size_t j = 7;
		for(std::size_t i = 0; i < size; i++)
		{
			data->data.push_back(data->data_buff[7]);
			j++;
		}*/
	}

	void data_parser::get_client_id(PSERVER_NET_BUF data)
	{
		assert(data != nullptr);
		memcpy(&data->id_client, &data->data_buff[1], 2);
	}
	void data_parser::get_comand(PSERVER_NET_BUF data)
	{
		assert(data != nullptr);
		//memcpy(&data->comand, &data->data_buff[4], 2);
		data->comand |= data->data_buff[3];
		data->comand = (data->comand<<8); 
		data->comand |= data->data_buff[4];
	}

	void data_parser::set_client_id(PSERVER_DATA_BUFF data)
	{
		assert(data != nullptr);
		data->data_buff[1] |= data->id_client;
		data->id_client = data->id_client<<8;
		data->data_buff[0] |= data->id_client;
		//memcpy(&data->data_buff[1], &data->id_client, sizeof(word16));
	}
	void data_parser::set_data_and_length(PSERVER_DATA_BUFF data)
	{
		assert(data != nullptr);
		assert(data->data.size() <= 32);
		data->data_buff[5] = data->data_length;
		memset(&data->data_buff[6], 0x00, sizeof(byte)*32);
		if(data->data_length)
		{
			memcpy(&data->data_buff[6],&data->data[0],data->data_length);
		}
	}
	void data_parser::set_info_byte(PSERVER_DATA_BUFF data)
	{
		assert(data != nullptr);
		data->data_buff[2] = data->info_byte; 
	}
	void data_parser::set_comand(PSERVER_DATA_BUFF data)
	{
		assert(data != nullptr);
		memcpy(&data->data_buff[4], &data->comand, 2);
	}
	
	void data_parser::send_p_dh(PSERVER_DATA_BUFF data_pars, PSERVER_NET_BUF data_net)
	{
		data_pars->info_byte = 0x00;
		set_info_byte(data_pars);
		data_pars->id_client = data_net->id_client;
		set_client_id(data_pars);
		data_pars->comand = PSETCMD;
		set_comand(data_pars);
		data_pars->data.clear();
		data_pars->data.resize(SIZE_DH_BUFF_BYTE);
		dh_->get_p(dh_type_->p_byte,SIZE_DH_BUFF_BYTE);
		memcpy(&data_pars->data[0], &dh_type_->p_byte[0],SIZE_DH_BUFF_BYTE);
		data_pars->data_length = data_pars->data.size();
		set_data_and_length(data_pars);
	}
	void data_parser::send_phashcmd(PSERVER_DATA_BUFF data_pars, PSERVER_NET_BUF data_net)
	{
		memcpy(hash_g_->data256, dh_type_->p_byte, SIZE_DH_BUFF_BYTE);
		hash_256(hash_g_->data256, SIZE_DH_BUFF_BYTE, hash_g_->hash256);
		if(!memcmp(&data_net->data[0], hash_g_->hash256, SIZE_DH_BUFF_BYTE))
		{
			send_q_dh(data_pars, data_net);
		}
		else
		{
			send_p_dh(data_pars,data_net);
		}
	}
	void data_parser::send_q_dh(PSERVER_DATA_BUFF data_pars, PSERVER_NET_BUF data_net)
	{
		data_pars->comand = QSETCMD;
		set_comand(data_pars);
		dh_->get_g(data_pars->info_byte);
		set_info_byte(data_pars);
		data_pars->id_client = data_net->id_client;
		set_client_id(data_pars);
		dh_->get_q(dh_type_->q_byte,SIZE_DH_BUFF_BYTE);
		data_pars->data.clear();
		data_pars->data.resize(SIZE_DH_BUFF_BYTE);
		memcpy(&data_pars->data[0],dh_type_->q_byte, SIZE_DH_BUFF_BYTE);
		data_pars->data_length = SIZE_DH_BUFF_BYTE;
		set_data_and_length(data_pars);
	}
	void data_parser::send_spublic_key(PSERVER_DATA_BUFF data_buff, PSERVER_NET_BUF net_buff)
	{
		data_buff->info_byte = 0x00;
		set_info_byte(data_buff);
		data_buff->id_client = net_buff->id_client;
		set_client_id(data_buff);
		data_buff->comand = SPUBLICKEYCMD;
		set_comand(data_buff);
		data_buff->data.clear();
		data_buff->data.resize(SIZE_DH_BUFF_BYTE);
		data_buff->data.reserve(0);
		std::vector<byte>::iterator it = data_buff->data.begin();
		dh_->generate_A(dh_type_->keyA, SIZE_DH_BUFF_BYTE*sizeof(byte));
		memcpy(&(*it),dh_type_->keyA,SIZE_DH_BUFF_BYTE*sizeof(byte));
		data_buff->data_length = data_buff->data.size();
		set_data_and_length(data_buff);
	}
	void data_parser::send_qhashcmd(PSERVER_DATA_BUFF data_buff, PSERVER_NET_BUF net_buff)
	{
		memset(hash_g_->hash256, 0x00, SIZE_HASH256_BYTE);
		hash_256(dh_type_->q_byte,SIZE_DH_BUFF_BYTE, hash_g_->hash256);
		if(!memcmp(hash_g_->hash256, &net_buff->data[0], SIZE_HASH256_BYTE))
		{
			send_spublic_key(data_buff, net_buff);
		}
		else
		{
			send_q_dh(data_buff, net_buff);
		}
	}
	void data_parser::send_spublic_key_hash(PSERVER_DATA_BUFF data_buff, PSERVER_NET_BUF net_buff)
	{
		memset(hash_g_->hash256, 0x00, SIZE_HASH256_BYTE*sizeof(byte));
		hash_256(dh_type_->keyA, SIZE_DH_BUFF_BYTE*sizeof(byte),hash_g_->hash256);
		if(!memcmp(hash_g_->hash256, &(*net_buff->data.begin()),net_buff->data.size()))
		{
			send_is_spublic_key_valid(data_buff, net_buff);
		}
		else
		{
			send_spublic_key(data_buff, net_buff);
		}
	}
	void data_parser::send_cpublic_key(PSERVER_DATA_BUFF data_buff, PSERVER_NET_BUF net_buff)
	{
		data_buff->id_client = net_buff->id_client;
		set_client_id(data_buff);
		data_buff->comand = CPUBLICKEYHASHCMD;
		set_comand(data_buff);
		data_buff->info_byte = 0x00;
		set_info_byte(data_buff);
		memcpy(dh_type_->keyB,&(*net_buff->data.begin()), net_buff->data.size());
		memset(hash_g_->hash256, 0x00, SIZE_HASH256_BYTE*sizeof(byte));
		hash_256(dh_type_->keyB, SIZE_DH_BUFF_BYTE*sizeof(byte),hash_g_->hash256);
		data_buff->data.clear();
		data_buff->data.resize(SIZE_HASH256_BYTE);
		data_buff->data.reserve(0);
		memcpy(&(*data_buff->data.begin()),hash_g_->hash256, data_buff->data.size());
		data_buff->data_length = data_buff->data.size();
		set_data_and_length(data_buff);
	}
	void data_parser::send_is_spublic_key_valid(PSERVER_DATA_BUFF data_buff, PSERVER_NET_BUF net_buff)
	{
		data_buff->id_client = net_buff->id_client;
		set_client_id(data_buff);
		data_buff->comand = SPUBLICKEYOK;
		set_comand(data_buff);
		data_buff->info_byte = 0x00;
		set_info_byte(data_buff);
		data_buff->data_length = 0x00;
		set_data_and_length(data_buff);
	}
}