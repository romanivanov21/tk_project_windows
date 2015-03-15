#ifndef _NETWORK_CLIENT_H_
#define _NETWORK_CLIENT_H_

#include"inc_boost_heders.h"
#include"crypt_gost_types.h"
#include"client_types.h"
#include"..\crypt_gost_28147-89\diffy_helman.h"
#include"client_authentication_win.h"
#include"client_data_parser_win.h"

namespace client
{
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
	
	class authentication;
	class client_data_parser;

	class client_network_windows
	{
	public:
		client_network_windows(const std::size_t &port_, const std::string ip_address);
		~client_network_windows();
		void client_connect();
		void client_authentication();
		void send_data();
		void send_data(byte *dest_buff, const std::size_t &size);
		boost::int32_t read_data(byte *dest_buff, const std::size_t &size);
		boost::int32_t read_data();
	private:
		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::endpoint ep_;
		boost::asio::ip::tcp::socket socket_;
		std::size_t port_;
		std::string ip_address_;

		authentication *authentication_client_;
		client_data_parser *data_parser_;

		CLIENT_DATA_BUFF data_buff_;
		CLIENT_NET_BUF net_buff_;

		GOST_TYPE gtype_;
		DH_TYPE dh_type;
		diffy_helm dh_;
	};
}
#endif