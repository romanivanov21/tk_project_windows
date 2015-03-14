#include"network_server_disconnect.h"
#include"network_server_exception.h"
#include"gost_include.h"
#include"config_parser.h"
#include"inc_boost_heders.h"
#include"gost_types_convert.h"

server_disconnect::server_disconnect() :
	port_(PORT),
	ep_(boost::asio::ip::address::from_string("127.0.0.1"), port_),
	socket_(io_service_)
{

}
server_disconnect::~server_disconnect()
{
	socket_.close();
}
void server_disconnect::send_bytes(byte *data, const std::size_t &size)
{
	assert(data != NULL || size != 0);
	try
	{
		socket_.write_some(boost::asio::buffer(data,size));
	}
	catch(...)
	{
		throw server_disconnect_exception("Siket write_some error");
	}
}
void server_disconnect::send_disconnect_msg()
{
	try
	{
		socket_.connect(ep_);
	}
	catch(...)
	{
		throw server_disconnect_exception("Socket connect error");
	}
	GOST_TYPE send_data;
	boost::shared_ptr<config_parser> conf_key(new config_parser("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\network_server_dll\\config.xml"));
	conf_key->get_disconnect_key(send_data.byte_key, SIZE_CRYPT_KEY_BYTE);
	byte_to_word32_key(send_data.byte_key,send_data.word_key);

}
boost::int32_t server_disconnect::read_bytes(byte *data, const std::size_t &size)
{
	assert(data != NULL || size != 0);
	boost::int32_t bytes = -1;
	try
	{
		bytes = socket_.read_some(boost::asio::buffer(data, size));
	}
	catch(...)
	{
		throw server_disconnect_exception("Soket read_bytes error");
	}
	return bytes;
}
