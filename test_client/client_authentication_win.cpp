#include"client_authentication_win.h"
#include"client_types.h"
#include"client_data_parser_win.h"
#include"gost_include.h"
#include"crypt_gost_types.h"
#include"..\crypt_gost_28147-89\diffy_helman.h"
#include<cstring>

namespace client
{
	authentication::authentication()
	{
		pars_ = new client_data_parser();
	}
	authentication::~authentication()
	{
		delete pars_;
	}
	
	void authentication::send_hello(PCLIENT_DATA_BUFF data)
	{
		pars_->set_client_id(data);
		pars_->set_byte_autch(data);
		pars_->set_hello_comand(data);
		for(std::size_t i = 0; i < SIZE_DATA_BUFF; i++)
		{
			std::cout<<std::hex<<(unsigned int)data->data_buff[i];
		}
		std::cout<<std::endl;
	}
}