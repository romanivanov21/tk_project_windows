#include"gtest_network.h"
#include"..\crypt_gost_28147-89\crypt_gost_types.h"

client::client(const std::size_t port) : port_(port),
	ep_(boost::asio::ip::address::from_string("127.0.0.1"), 8001),
	socket_(io_service_)
{
	assert(port != 0);
}
client::~client()
{
	socket_.close();
}
void client::client_connect()
{
	socket_.connect(ep_);

}
void client::print_result(byte *msg, const std::size_t &length)const
{
	assert((msg != NULL) || (length != 0));
	for(std::size_t i = 0; i < length; i++)
	{
		printf("%x",msg[i]);
	}
	printf("\n");
}
void client::send_data(byte *dest_buff, const std::size_t &size)
{
	assert((dest_buff != 0) || (size != 0));
	try
	{
		socket_.write_some(boost::asio::buffer(dest_buff,size));
	}
	catch(...)
	{
		socket_.close();
		throw client_exception("Error write_data");
	}
}

boost::int32_t client::read_data(byte *dest_buff, const std::size_t &size)
{
	assert(dest_buff != 0 || size != 0);
	boost::int32_t bytes_recived = 0;
	try
	{
		bytes_recived = socket_.read_some(boost::asio::buffer(dest_buff,size));
	}
	catch(...)
	{
		socket_.close();
		throw client_exception("Error read_data");
	}
	return bytes_recived;
}
