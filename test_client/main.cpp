#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#include <iostream>
#include <boost/asio.hpp>
using namespace boost::asio;
using boost::system::error_code;
io_service service;

ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
void sync_echo(std::string msg) {
    msg += "\n";
    ip::tcp::socket sock(service);
    sock.connect(ep);
	char buf[1024];
	strcpy_s(buf,"I is client");
	sock.write_some(buffer(buf,1024));
	char destBuff[1024];
	memset(destBuff,0,1024);

	int bytes_recived = sock.read_some(buffer(destBuff,1024));
	std::string server_message(destBuff);
	std::cout<<server_message<<std::endl;
    sock.close();
}

int main() 
{
	try{
	sync_echo("I is client");
	}
	catch(...)
	{
		std::cout<<"Eroor"<<std::endl;
	}
	getchar();
	return 0;
}