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
		memcpy(&data->data_buff[1], &data->id_client, 2);
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
			data_pars->comand = QSETCMD;
			set_comand(data_pars);
			data_pars->info_byte = 0x00;
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
		else
		{
			send_p_dh(data_pars,data_net);
		}
	}
}