#include"data_parser.h"
#include"gost_include.h"
#include"gost_types_convert.h"
#include<string>
#include<assert.h>
namespace server
{
	data_parser::data_parser() { }
	data_parser::~data_parser() { }

	void data_parser::parse_send_data(PNET_BUFF_DATA data_net, P_PARS_BUFF_DATA data_pars)
	{
		assert((data_net != NULL) || (data_pars != NULL));
		throw;
	}
	void data_parser::parse_read_data(P_PARS_BUFF_DATA data_pars, PNET_BUFF_DATA data_net)
	{
		assert((data_pars != NULL) || (data_pars != NULL));

	}
	bool data_parser::is_crypt(const byte *buff, const std::size_t &length)const
	{
		assert((buff != NULL) || (length != SIZE_NET_BUFF_BYTE));
		byte temp = 0;
		temp = buff[30];
		return ((temp << 7) || 0x00) ? true : false;
	}
}