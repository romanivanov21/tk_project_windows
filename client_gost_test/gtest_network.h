#ifndef _GTEST_NETWORK_H_
#define _GTEST_NETWORK_H_
#include"inc_boost_heders.h"
#include"crypt_gost_types.h"

#define SIZE_DH_BYTE_BUFF 32

class client_exception : std::exception
{
public:
	client_exception(const std::string &str)
	{
		str_ = str;
	}
	std::string wath() { return str_; }
private:
	std::string str_;
};
#pragma pack(push, 1)
typedef struct
{
	byte p_destBuff[SIZE_DH_BYTE_BUFF];
	byte q_destBuff[SIZE_DH_BYTE_BUFF];
	byte g;

	byte A_destBuff[SIZE_DH_BYTE_BUFF];
	byte B_destBuff[SIZE_DH_BYTE_BUFF];

	byte key_destBuff[SIZE_DH_BYTE_BUFF];

}CLIENT_DH_TYPE, *PTR_CLIENT_DH_TYPE;
#pragma pack(pop)

class client : private boost::noncopyable
{
public:
	client(const std::size_t port_);
	~client();
	void client_connect();
	void send_data(byte *dest_buff, const std::size_t &size);
	boost::int32_t read_data(byte *dest_buff, const std::size_t &size);
	void print_result(byte *msg, const std::size_t &length)const;
private:
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::endpoint ep_;
	boost::asio::ip::tcp::socket socket_;
	const std::size_t port_;
};
#endif