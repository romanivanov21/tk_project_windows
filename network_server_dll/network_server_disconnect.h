#ifndef _NETWORK_SERVER_DISCONNECT_H
#define _NETWORK_SERVER_DISCONNECT_H_
#include "crypt_gost_types.h"
#include "inc_boost_heders.h"

#define PORT 8001
class server_disconnect : private boost::noncopyable
{
public:
	explicit server_disconnect();
	~server_disconnect();

	void send_disconnect_msg();
private:
	void send_bytes(byte *data, const std::size_t &size);
	boost::int32_t read_bytes(byte *data, const std::size_t &size);
private:
	std::uint32_t port_;
	
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::endpoint ep_;
	boost::asio::ip::tcp::socket socket_;
};
#endif