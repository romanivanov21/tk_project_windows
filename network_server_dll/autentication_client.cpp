#include"authentication_client.h"

namespace server
{
	autentication_client::autentication_client(const word16 &id_client) : id_client_(id_client)
	{
		pars_ = new config_parser("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\network_server_dll\\config.xml");
	}
	autentication_client::~autentication_client()
	{
		delete pars_;
	}
	bool autentication_client::autentication()const
	{
		return false;
	}
}