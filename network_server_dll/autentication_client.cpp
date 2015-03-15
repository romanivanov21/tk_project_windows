#include"authentication_client.h"

namespace server
{
	autentication_client::autentication_client()
	{
		c_pars_ = new config_parser("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\network_server_dll\\config.xml");
		dh_ = new diffy_helm();
	}
	autentication_client::~autentication_client()
	{
		delete c_pars_;
		delete dh_;
	}

	void autentication_client::set_p(P_PARS_BUFF_DATA data_pars)
	{
		dh_->get_p(data_pars->data, SIZE_DATA_BYTE);
		std::size_t j = 0;
		for(std::size_t i = 31; i <= 0; i++)
		{
			data_pars->buff[i] = data_pars->data[j];
			j++;
		}
	}
}