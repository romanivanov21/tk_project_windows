#include"network_client_win.h"
#include"crypt_gost_types.h"
#include"client_authentication_win.h"
#include"client_data_parser_win.h"
#include"client_types.h"

namespace client
{
	client_network_windows::client_network_windows(const std::size_t &port, const std::string ip_addres) : port_(port),
		ep_(boost::asio::ip::address::from_string("127.0.0.1"), 8001),
		socket_(io_service_)
	{
		assert((port != 0) || !(ip_addres.empty()));

		ip_address_ = ip_addres;

		authentication_client_ = new authentication();
		data_parser_ = new client::client_data_parser();

		memset(data_buff_.data_buff, 0, SIZE_DATA_BUFF);
		memset(net_buff_.net_buff_data, 0, SIZE_NET_BUFF);

		memset(gtype_.byte_decryption_data, 0, sizeof(byte) * SIZE_CRYPT_BUFF_BYTE);
		memset(gtype_.byte_encryption_data, 0, sizeof(byte) * SIZE_CRYPT_BUFF_BYTE);
		memset(gtype_.byte_key, 0, sizeof(byte) * SIZE_CRYPT_KEY_BYTE);
		memset(gtype_.word_decryption_data, 0, sizeof(word32) * SIZE_CRYPT_BUFF_WORD);
		memset(gtype_.word_encryption_data, 0, sizeof(word32) * SIZE_CRYPT_BUFF_WORD);
		memset(gtype_.word_key, 0, sizeof(word32) * SIZE_CRYPT_KEY_WORD);

	}
	client_network_windows::~client_network_windows()
	{
		socket_.close();
		delete authentication_client_;
		delete data_parser_;
	}
	void client_network_windows::client_connect()
	{
		try
		{
			socket_.connect(ep_);
		}
		catch(...)
		{
			throw client_exception("Can not connect to the server");
		}
	}
	
	void client_network_windows::send_data()
	{
		try
		{
			socket_.write_some(boost::asio::buffer(data_buff_.data_buff,SIZE_DATA_BUFF));
		}
		catch(...)
		{
			socket_.close();
			throw client_exception("Error write_data");
		}
	}
	void client_network_windows::send_data(byte *dest_buff, const std::size_t &size)
	{
		assert((dest_buff != 0) || (size != 0));
		try
		{
			socket_.write_some(boost::asio::buffer(&dest_buff,size));
		}
		catch(...)
		{
			socket_.close();
			throw client_exception("Error write_data");
		}
	}
	boost::int32_t client_network_windows::read_data()
	{
		boost::int32_t bytes_recived = 0;
		try
		{
			bytes_recived = socket_.read_some(boost::asio::buffer(net_buff_.net_buff_data,SIZE_NET_BUFF));
			for(boost::int32_t i = 0; i < bytes_recived; i++)
			{
				std::cout<<(unsigned int)net_buff_.net_buff_data[i];
			}
			std::cout<<std::endl;
		}
		catch(...)
		{
			socket_.close();
			throw client_exception("Error read_data");
		}
		return bytes_recived;
	}
	boost::int32_t client_network_windows::read_data(byte *dest_buff, const std::size_t &size)
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
	void client_network_windows::client_authentication()
	{
		authentication_client_->send_hello(&data_buff_);
		send_data();
	}
}