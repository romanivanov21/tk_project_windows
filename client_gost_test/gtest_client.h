#ifndef _GTEST_CLIENT_H_
#define _GTEST_CLIENT_H_

#include "gtest_network.h"
#include "..\network_server_dll\inc_boost_heders.h"
#include "..\crypt_gost_28147-89\diffy_helman.h"
#include <string>
#include <iostream>

class test_client : private boost::noncopyable
{
public:
	test_client(const std::string &path_data, const std::size_t &port);
	~test_client();
	void testing();
private:
	std::string to_hex(const byte *byte_data, const std::size_t &length);
	void test_data_write(const std::string &key);
private:
	std::string path_data_;
	std::size_t port_;
	client *c_;
	diffy_helm *dh_;
	CLIENT_DH_TYPE client_dh_;
};

#endif