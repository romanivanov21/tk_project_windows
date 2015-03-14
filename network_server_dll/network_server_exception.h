#ifndef _NETOWORK_SERVER_EXCEPTION_H_
#define _NETOWORK_SERVER_EXCEPTION_H_

#include <string>
#include <exception>

namespace server
{
	class server_network_exception : std::exception
	{
	public:
		server_network_exception(const std::string &msg) : msg_(msg) { }
		inline std::string what() { return msg_; }
	private:
		const std::string msg_;
	};
}
class server_disconnect_exception : std::exception
{
public:
	server_disconnect_exception(const std::string &msg) : msg_(msg) { }
	inline std::string what() { return msg_; }
private:
	const std::string msg_;
};
class config_parser_exception
{
public:
	config_parser_exception(const std::string &msg) : msg_(msg) { }
	__inline std::string wath() { return msg_; }
private:
	const std::string msg_;
};
#endif