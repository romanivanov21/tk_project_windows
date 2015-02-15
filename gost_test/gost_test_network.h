#ifndef _GOST_TEST_NETWORK_H_
#define _GOST_TEST_NETWORK_H_

#include"crypt_gost_types.h"
#include"inc_boost_heders.h"
#include <string>

class gost_test_network : private boost::noncopyable
{
public:
	explicit gost_test_network(const std::uint32_t port);
	~gost_test_network();
	
	void send_bytes(byte *data, const std::size_t &size);
	boost::int32_t read_bytes(byte *data, const std::size_t &size);

	void start();

private:
	std::string client_connect_time_;
	std::uint32_t port_;
	
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
};
#endif