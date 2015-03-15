#ifndef CLIENT_AUTHENTICATION_WIN_H_
#define CLIENT_AUTHENTICATION_WIN_H_
#include "crypt_gost_types.h"
#include "gost_include.h"
#include "..\crypt_gost_28147-89\diffy_helman.h"
#include "client_data_parser_win.h"

namespace client
{
	class client_data_parser;
	class authentication
	{
	public:
		authentication();
		~authentication();
		
		void send_hello(PCLIENT_DATA_BUFF data);
	private:
		client_data_parser *pars_;
	};
}
#endif