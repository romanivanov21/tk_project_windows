#include "server_API.h"
#include "network_server_dll.h"
#include "server_timer.h"

server::server_network* s = 0;

SERVER_API void server_start(const std::size_t &port)
{
	s->instance(port);
	s->start();
}
SERVER_API void server_shut_dwon()
{

}
SERVER_API boost::int32_t read_command()
{
	boost::int32_t result = -1;
	return -1;
}
SERVER_API void write_command()
{

}