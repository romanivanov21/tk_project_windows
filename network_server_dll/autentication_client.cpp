#include"authentication_client.h"

namespace server
{
	autentication_client::autentication_client()
	{
		c_pars_ = new config_parser("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\network_server_dll\\config.xml");
	}
	autentication_client::~autentication_client()
	{
		delete c_pars_;
	}

}