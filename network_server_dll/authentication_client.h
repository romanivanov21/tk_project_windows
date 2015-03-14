#ifndef _AUTHENTICATION_CLIENT_H_
#define _AUTHENTICATION_CLIENT_H_
#include"crypt_gost_types.h"
#include"config_parser.h"
#include<boost\noncopyable.hpp>
namespace server 
{
	class autentication_client : private boost::noncopyable
	{
	public:
		autentication_client(const word16 &id_client);
		~autentication_client();
		bool autentication()const;
	private:
		config_parser *pars_;
		word16 id_client_;
};
}
#endif