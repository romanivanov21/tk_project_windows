#include "gost_test_network.h"
#include "gost_test_exeption.h"
#include <iostream>

gost_test_network::gost_test_network(const std::uint32_t port) : port_(port),
		socket_(io_service_), 
		acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_)) 
{

}

gost_test_network::~gost_test_network()
{
	socket_.close();
}
void gost_test_network::send_bytes(byte *data, const std::size_t &size)
{
	assert(data != NULL || size != 0);
	try
	{
		socket_.write_some(boost::asio::buffer(data,size));
	}
	catch(...)
	{
		acceptor_.close();
		socket_.close();
		throw gost_exception("Siket write_some error");
	}
}
void gost_test_network::start()
{
	try
	{
		acceptor_.accept(socket_);
	}
	catch(...)
	{
		acceptor_.close();
		socket_.close();
		throw gost_exception("Socket accept error");
	}
}
boost::int32_t gost_test_network::read_bytes(byte *data, const std::size_t &size)
{
	assert(data != NULL || size != 0);
	boost::int32_t bytes = -1;
	try
	{
		bytes = socket_.read_some(boost::asio::buffer(data, size));
	}
	catch(...)
	{
		acceptor_.close();
		socket_.close();
		throw gost_exception("Soket read_bytes error");
	}
	return bytes;
}
