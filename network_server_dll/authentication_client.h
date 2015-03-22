#ifndef _AUTHENTICATION_CLIENT_H_
#define _AUTHENTICATION_CLIENT_H_
#include"crypt_gost_types.h"
#include"server_types.h"
#include"config_parser.h"
#include"data_parser.h"
#include<boost\noncopyable.hpp>
#include"..\crypt_gost_28147-89\diffy_helman.h"
namespace server 
{
	class autentication_client : private boost::noncopyable
	{
	public:
		autentication_client();
		~autentication_client();

	private:
		config_parser *c_pars_;
	};
}
#endif