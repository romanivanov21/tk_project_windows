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

		data_parser_ = new client_data_parser();
		data_buff_ = new CLIENT_DATA_BUFF();
		data_buff_->comand = INICMD;
		data_buff_->data_length = 0;
		data_buff_->id_client = 0;
		data_buff_->info_byte = 0;
		memset(data_buff_->data_buff, 0x00, 38);

		net_buff_ = new CLIENT_NET_BUF();
		net_buff_->comand = 0;
		net_buff_->data_length = 0;
		net_buff_->id_client = 0;
		net_buff_->info_byte = 0;
		memset(net_buff_->data_buff, 0x00, 38);
	}
	client_network_windows::~client_network_windows()
	{
		socket_.close();
		delete data_parser_;
		delete data_buff_;
		delete net_buff_;
	}
	void client_network_windows::client_connect()
	{
		try
		{
			socket_.connect(ep_);
#if _DEBUG
			std::cout<<"connect to server"<<std::endl;
#endif
		}
		catch(...)
		{
			throw client_exception("Can not connect to the server");
		}
	}
	
	void client_network_windows::send_data()
	{
		//берём данные из net_buff и парсим data_buff_
		data_parser_->send_data_parser(data_buff_,net_buff_);
		try
		{
			//отправляем данные из data_buff_
			socket_.write_some(boost::asio::buffer(data_buff_->data_buff, 38));
#if _DEBUG
			std::cout<<"Send :";
			for(std::size_t i = 0; i < 38; i++)
			{
				std::cout<<std::setw(2)<<std::setfill('0') <<std::hex <<(unsigned int)data_buff_->data_buff[i]<<" ";
			}
			std::cout<<std::endl;
#endif
		}
		catch(...)
		{
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
			throw client_exception("Error write_data");
		}
	}
	boost::int32_t client_network_windows::read_data()
	{
		boost::int32_t bytes_recived = 0;
		try
		{
			//получамем данные и заполняем net_buff_
			bytes_recived = socket_.read_some(boost::asio::buffer(net_buff_->data_buff, 38));

			//парсим из net_buff
			data_parser_->read_data_parser(net_buff_,data_buff_);
#if _DEBUG
			std::cout<<"Adopt: ";
			for(std::size_t i = 0; i < 38; i++)
			{
				std::cout<<std::setw(2)<<std::setfill('0') <<std::hex <<(unsigned int)net_buff_->data_buff[i]<<" ";
			}
			std::cout<<std::endl;
#endif
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
}