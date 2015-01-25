#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#include "..\shared_code\gost_include.h"
#include "..\shared_code\gost_types_convert.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "osrng.h"
#include "integer.h"
#include "nbtheory.h"
#include "dh.h"
#include "secblock.h"
using namespace boost::asio;
using boost::system::error_code;
io_service service;

ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);

void sync_echo() {
    ip::tcp::socket sock(service);
    sock.connect(ep);
	byte p_destBuff[32];
	byte q_destBuff[32];

	byte A_destBuff[32];
	boost::uint32_t bytes_recived_p = sock.read_some(buffer(p_destBuff,32));
	CryptoPP::Integer p;
	std::cout << "P (" << std::dec << bytes_recived_p << "): ";
	for(std::size_t i = 0; i < 32; i++)
	{
		printf("%x",p_destBuff[i]);
	}
	printf("\n");
	std::cout << "P (" << std::dec << bytes_recived_p << "): ";
	for(std::size_t i = 0; i < 32; i++)
	{
		p.SetByte(i,p_destBuff[i]);
		printf("%x",p.GetByte(i));
	}
	byte p_hash[32];
	hash_256(p_destBuff,32,p_hash);

	printf("\n");
	for(std::size_t i = 0; i < 32; i++)
	{
		printf("%x",p_hash[i]);
	}
	printf("\n");





	boost::uint32_t bytes_recived_q = sock.read_some(buffer(q_destBuff,32));
	std::cout << "Q (" << std::dec << bytes_recived_q << "): ";
	CryptoPP::Integer q;
	byte byte_q[32];
	for(std::size_t i = 0; i < 32; i++)
	{
		printf("%x",q_destBuff[i]);
	}
	printf("\n");
	std::cout << "Q (" << std::dec << bytes_recived_q << "): ";
	for(std::size_t i = 0; i < 32; i++)
	{
		q.SetByte(i,q_destBuff[i]);
		printf("%x",q.GetByte(i));
	}
	printf("\n byte_q = ");
	for(size_t i = 0; i < 32; i++)
	{
		byte_q[i] = q.GetByte(i);
		printf("%x",byte_q[i]);
	}
	byte q_hash[32];
	hash_256(q_destBuff,32,q_hash);

	printf("\n");
	for(std::size_t i = 0; i < 32; i++)
	{
		printf("%x",q_hash[i]);
	}
	printf("\n");

	byte g[1];
	boost::uint32_t bytes_recived_g = sock.read_some(buffer(g, 1));
	std::cout << "G (" << std::dec << bytes_recived_g << "): ";
	printf("%d",g[0]);

	printf("\n");
	std::cout << "G (" << std::dec << bytes_recived_g << "): ";
	CryptoPP::Integer ig;
	ig.SetByte(0,g[0]);
	printf("%d",ig.GetByte(0));
	printf("\n");

	boost::uint32_t bytes_recived_A = sock.read_some(buffer(A_destBuff,32));
	std::cout << "pub_A (" << std::dec << bytes_recived_A << "): ";
	CryptoPP::Integer A;
	for(std::size_t i = 0; i < 32; i++)
	{
		printf("%x",A_destBuff[i]);
	}
	printf("\n");
	std::cout << "pub_A (" << std::dec << bytes_recived_p << "): ";
	for(std::size_t i = 0; i < 32; i++)
	{
		A.SetByte(i, A_destBuff[i]);
		printf("%x",A.GetByte(i));
	}
	printf("\n");

	CryptoPP::DH dhB;
	CryptoPP::AutoSeededRandomPool rnd_B;
	byte B[32];
	memset(B, 0, 32);
	dhB.AccessGroupParameters().Initialize(p, q, ig);
	CryptoPP::SecByteBlock *priv_B = new CryptoPP::SecByteBlock(dhB.PrivateKeyLength());
	CryptoPP::SecByteBlock *pub_B = new CryptoPP::SecByteBlock(dhB.PublicKeyLength());
	dhB.GenerateKeyPair(rnd_B, *priv_B, *pub_B);
	CryptoPP::Integer temp_pub_B;
	temp_pub_B.Decode(pub_B->BytePtr(),pub_B->SizeInBytes());

	printf("B = ");

	for(std::size_t i = 0; i < 32; i++)
	{
		B[i] = temp_pub_B.GetByte(i);
		printf("%x", B[i]);
	}
	printf("\n");
	sock.write_some(buffer(B, 32));
	CryptoPP::SecByteBlock key(dhB.AgreedValueLength());
	CryptoPP::SecByteBlock pub_A(dhB.AgreedValueLength());
	CryptoPP::Integer int_b;
	for(int i = 0; i < 32; i++)
	{
		int_b.SetByte(i,A_destBuff[i]);
	}
	int_b.Encode(pub_A.BytePtr(), pub_A.SizeInBytes());
	dhB.Agree(key, *priv_B, pub_A);
	CryptoPP::Integer key_;
	key_.Decode(key.BytePtr(), key.SizeInBytes());

	byte gost_key[32];
	for(std::size_t i = 0; i < key_.ByteCount(); i++)
	{
		gost_key[i] = key_.GetByte(i);
		printf("%x", gost_key[i]);
	}
	delete priv_B; delete pub_B;
    

	/*for(std::size_t i = 0; i < 32; i++)
	{
		printf("%x",destBuff[i]);
	}
	std::cout<<std::endl;

	sock.close();
	/*word32 key_word32[8];
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
	*/
}

int main() 
{
	try
	{
		sync_echo();
	}
	catch(...)
	{
		std::cout<<"Error"<<std::endl;
	}
	getchar();
	return 0;
}