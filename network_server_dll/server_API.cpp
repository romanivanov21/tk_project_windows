#include "server_API.h"
#include "network_server_dll.h"
#include "network_server_exception.h"
#include "network_server_disconnect.h"
#include "server_timer.h"
#include <boost/smart_ptr.hpp>

static server::server_network* s = 0;

SERVER_API void server_start(const std::size_t &port)
{
	assert(port != 0);
	if(s == 0)
	{
		s = s->get_instanse(port);
	}
	try
	{
		s->start();
	}
	catch(server::server_network_exception &ex)
	{
		throw server::server_network_exception(ex.what());
	}
}
SERVER_API void server_shut_dwon()
{
	if(!s->get_is_client_connect())
	{
		boost::shared_ptr<server_disconnect> s_disconnect(new server_disconnect());
		try
		{
			s_disconnect->send_disconnect_msg();
		}
		catch(server_disconnect_exception &ex)
		{
			throw server::server_network_exception(ex.what());
		}
	}
	else
	{
		// здесь должен быть команда завершени€ сервреа
	}
}
SERVER_API void read_command()
{
	try
	{
		s->read_bytes();
	}
	catch(server::server_network_exception &ex)
	{
		throw server::server_network_exception(ex.what());
	}
}
SERVER_API void write_command()
{
	try
	{
		s->send_bytes();
	}
	catch(server::server_network_exception &ex)
	{
		throw server::server_network_exception(ex.what());
	}
}