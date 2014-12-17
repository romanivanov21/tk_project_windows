#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#include <iostream>
#include <boost/asio.hpp>
using namespace boost::asio;
using boost::system::error_code;
io_service service;
extern "C" void key_box_init();
extern "C" void gostdecrypt( unsigned long const *in_data, unsigned long *out_data, unsigned long const *gost_key);
extern "C" void gostcrypt( unsigned long const *in_data, unsigned long *out_data, unsigned long const *gost_key);
typedef unsigned long word32;

typedef unsigned char byte;
ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
void word32_to_byte(word32 *word32_, byte *byte_)
{
	memset(byte_, 0, 8);
	word32 temp = word32_[0];
	int s = 24;
	for(unsigned int i = 0; i < 4; i++)
	{
		word32_[0] = temp;
		word32_[0] = word32_[0] >> s;
		byte_[i] |= word32_[0];
		s = s - 8;
	}
	temp = word32_[1];
	for(unsigned int i = 4; i < 8; i++)
	{
		word32_[1] = temp;
		word32_[1] = word32_[1] >> s;
		byte_[i] |= word32_[1];
		s = s - 8;
	}
}

void byte_to_word32( byte *byte_, word32 *word32_)
{
	memset(word32_, 0, 8);

	for(unsigned int i = 0; i < 4; i++)
	{
		word32_[0] = word32_[0] << 8;
		word32_[0] |= byte_[i];
	}
	for(unsigned int i = 4; i < 8; i++)
	{
		word32_[1] = word32_[1] << 8;
		word32_[1] |= byte_[i];
	}
}
void sync_echo() {
    ip::tcp::socket sock(service);
    sock.connect(ep);
	char buf[1024];
	strcpy_s(buf,"I is client");
	sock.write_some(buffer(buf,1024));
	char destBuff[8];
	memset(destBuff,0,8);

	int bytes_recived = sock.read_some(buffer(destBuff,8));
	 sock.close();
	//std::string server_message(destBuff);
	for(std::size_t i = 0; i < 8; i++)
	{
		std::cout<<destBuff[i];
	}
	std::cout<<std::endl;
	word32 key[8];
	word32 crypt_data[2];
	word32 decrypt_data_word32[2];
	byte decrypt_data_byte[8];
	key[0] = 5; 
	key[1] = 4; 
	key[2] = 3; 
	key[3] = 2; 
	key[4] = 1; 
	key[5] = 0; 
	key[6] = 1; 
	key[7] = 5;
	key_box_init();
	byte_to_word32((byte*)destBuff,crypt_data);
	gostdecrypt(crypt_data,decrypt_data_word32,key);
	word32_to_byte(decrypt_data_word32,decrypt_data_byte);
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