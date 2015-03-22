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
		dh_type_ = new DH_TYPE();
		memset(dh_type_->gkey, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		memset(dh_type_->keyA, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		memset(dh_type_->keyB, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		memset(dh_type_->p_byte, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		memset(dh_type_->q_byte, 0x00, sizeof(byte)*SIZE_DH_BUFF_BYTE);
		dh_type_->g_byte = 0x00;
		hash_ = new HASH_TYPE();
		crypt_g_ = new GOST_TYPE();
		dh_ = new diffy_helm();
	}
	client_data_parser::~client_data_parser()
	{
		delete dh_type_;
		delete crypt_g_;
		delete dh_;
	}
	
	void client_data_parser::send_data_parser(PCLIENT_DATA_BUFF data_buff, PCLIENT_NET_BUF net_buff )
	{
		switch(net_buff->comand)
		{
		case INICMD:
			send_hello(data_buff);
			if(is_crypt(data_buff->info_byte))
			{
				//надо зашифровать данные
			}
			break;
		case PSETCMD:
			memcpy(&dh_type_->p_byte[0],&net_buff->data[0],net_buff->data.size()*sizeof(byte));
			send_p_hash(data_buff);
		}
	}
	void client_data_parser::read_data_parser(PCLIENT_NET_BUF net_buff, PCLIENT_DATA_BUFF data_buff)
	{
		get_info_byte(net_buff);
		if(is_crypt(net_buff->info_byte))
		{
			//должно быть расшифрование данных
		}
		get_client_id(net_buff);
		if(net_buff->id_client != CLIENT_ID) { throw; }
		get_comand(net_buff);
		get_data_and_length(net_buff);
	}
	void client_data_parser::set_client_id(PCLIENT_DATA_BUFF data)
	{
		assert(data != nullptr || data->id_client != 0x00);
		memcpy(&data->data_buff[1], &data->id_client, 2);
	}
	void client_data_parser::set_byte_info(PCLIENT_DATA_BUFF data) 
	{ 
		assert(data != nullptr); 
		data->data_buff[2] = data->info_byte; 
	}

	void client_data_parser::set_comand(PCLIENT_DATA_BUFF data)
	{
		assert(data != nullptr);
		memcpy(&data->data_buff[4], &data->comand, 2);
	}
	void client_data_parser::set_data_and_length(PCLIENT_DATA_BUFF data)
	{
		assert(data != nullptr);
		data->data_buff[5] = data->data_length;
		memset(&data->data_buff[6], 0x00, sizeof(byte)*32);
		if(data->data_length)
		{
			memcpy(&data->data_buff[6],&data->data[0],data->data_length);
		}
	}
	void client_data_parser::get_client_id(PCLIENT_NET_BUF data)
	{
		assert(data != nullptr);
		memcpy(&data->id_client, &data->data_buff[1], 2);
	}
	void client_data_parser::get_info_byte(PCLIENT_NET_BUF data) 
	{ 
		assert(data != nullptr);
		data ->info_byte = data->data_buff[2]; 
	}

	void client_data_parser::get_comand(PCLIENT_NET_BUF data)
	{
		assert(data != nullptr);
		//memcpy(&data->comand, &data->data_buff[4], sizeof(word16));
		data->comand |= data->data_buff[3];
		data->comand = data->comand<<8 | data->data_buff[4];
	}

	void client_data_parser::get_data_and_length(PCLIENT_NET_BUF data) 
	{ 
		assert (data != nullptr);
		data->data_length = data->data_buff[5];
		if(data->data_length > 32)
		{
			//exception
		}
		data->data.clear();
		const std::size_t size = data->data_length;
		for(std::size_t i = 6; i < 6 + size; i++)
		{
			data->data.push_back(data->data_buff[i]);
		}
	}

	void client_data_parser::send_hello(PCLIENT_DATA_BUFF data)
	{
		data->id_client = CLIENT_ID;
		set_client_id(data);
		data->info_byte = 0x00;
		set_byte_info(data);
		data->comand = HCMD;
		set_comand(data);
		data->data_length = 0;
		if(data->data.size())
		{
			memset(&data->data[0], 0x00, data->data.size());
		}
		set_data_and_length(data);
	}
	void client_data_parser::send_p_hash(PCLIENT_DATA_BUFF data_buff)
	{
		data_buff->id_client = CLIENT_ID;
		set_client_id(data_buff);
		data_buff->info_byte = 0x00;
		set_byte_info(data_buff);
		data_buff->comand = PHASHCMD;
		set_comand(data_buff);
		data_buff->data.clear();
		hash_256(dh_type_->p_byte,SIZE_DH_BUFF_BYTE*sizeof(byte),hash_->hash256);
		for(std::size_t i = 0; i < SIZE_HASH256_BYTE; i++)
		{
			data_buff->data.push_back(hash_->hash256[i]);
		}
		data_buff->data_length = SIZE_HASH256_BYTE * sizeof(byte);
		set_data_and_length(data_buff);
	}
	bool client_data_parser::is_crypt(const byte &data)const
	{
		return (data & 0x01) ? true : false;
	}
}