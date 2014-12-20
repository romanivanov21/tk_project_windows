#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#include "..\shared_code\gost_include.h"
#include "..\shared_code\gost_types_convert.h"

#include <iostream>
#include <boost/asio.hpp>
using namespace boost::asio;
using boost::system::error_code;
io_service service;

ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);

void sync_echo() {
    ip::tcp::socket sock(service);
    sock.connect(ep);
	char buf[1024];
	strcpy_s(buf,"I is client");
	sock.write_some(buffer(buf,1024));
	char destBuff[8];
	memset(destBuff,0,8);

	boost::uint32_t bytes_recived = sock.read_some(buffer(destBuff,8));
	sock.close();
	for(std::size_t i = 0; i < 8; i++)
	{
		std::cout<<destBuff[i];
	}
	std::cout<<std::endl;
	word32 key_word32[8];
	word32 crypt_data[2];
	word32 decrypt_data_word32[2];
	byte decrypt_data_byte[8];

	key_word32[0] = 5; 
	key_word32[1] = 4; 
	key_word32[2] = 3; 
	key_word32[3] = 2; 
	key_word32[4] = 1; 
	key_word32[5] = 0; 
	key_word32[6] = 1; 
	key_word32[7] = 5;
	key_box_init();
	byte_to_word32_data((byte*)destBuff,crypt_data);
	gostdecrypt(crypt_data,decrypt_data_word32,key_word32);
	word32_to_byte_data(decrypt_data_word32,decrypt_data_byte);
	for(std::size_t i = 0 ; i < 8; i++)
	{
		std::cout<<decrypt_data_byte[i];
	}
	std::cout<<std::endl;

}

int main() 
{
	try{
	sync_echo();
	}
	catch(...)
	{
		std::cout<<"Eroor"<<std::endl;
	}
	getchar();
	return 0;
}