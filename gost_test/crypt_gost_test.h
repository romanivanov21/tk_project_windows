/*******************************************************************
* Файл: crypt_gost_test.h										   *
* Описание:содержит обяъявления классов							   *
* тестирования алгоритмов ГОСТ 28147-89, ГОСТ_P_34_11_2012,        *
* обмен ключами по протоколу Диффи - Хелмана				       *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
********************************************************************/

#ifndef _TEST_CRYPT_H_
#define _TEST_CRYPT_H_

#include"crypt_gost_test_types.h"
#include"crypt_gost_types.h"
#include"..\crypt_gost_28147-89\diffy_helman.h"
#include <boost\thread\thread.hpp>
#include <boost\noncopyable.hpp>
#include <vector>
#include <string>
#include <iostream>

void create_process_client();

class test : private boost::noncopyable
{
public:
	explicit test() 
	{
#if CONSOLE_APPLICATION
		std::cout<<"Tested the algoritm "; 
#endif
	};
	virtual bool testing() = 0;
protected:
	void bin_parser(std::string &vaule);
	void print_result(const std::string &msg)const;
	void print_result(const byte* msg, const std::size_t &length)const;
	void print_result(const word32 *msg, const std::size_t &length)const;
	std::string to_hex(const byte *byte_data, const std::size_t &length);
};
class gost_test : public test
{
public:
	explicit gost_test(const std::string &vinit_path, const std::string &test_data_path, const std::size_t &n_test);
	bool testing();
private:
	std::string test_data_read(const std::size_t &id_data);
	std::string test_key_read(const std::size_t &id_key);
	std::string test_crypt_data_read(const std::size_t &id_cryptdata);
	bool crypt(const std::size_t &n);
private:
	const std::string vinit_path_;
	const std::string test_data_path_;
	std::size_t n_test_;
	GOST_TYPE gtype_;
};
class dh_test : public test
{
public:
	explicit dh_test(const std::string &test_data_path, const std::size_t &n_test);
	~dh_test();
	bool testing(void);
private:
	std::string key_read();
	bool keycmp();
	void client_start();
private:
	std::string test_data_path_;
	std::size_t n_test_;
	PTR_DH_TYPE dh_type_;
	diffy_helm *dh_;
	boost::thread thrd_;
};
class hash_test : public test
{
public:
	explicit hash_test(const std::string &ghash_path, const std::size_t &n_test);
	bool testing(void);
private:
	std::string test_data256_read(const std::size_t &id_data);
	std::string test_data512_read(const std::size_t &id_data);
	std::string test_hash512_read(const std::size_t &id_hash);
	std::string test_hash256_read(const std::size_t &id_hash);
	bool hashcmp256(const std::size_t &n);
	bool hashcmp512(const std::size_t &n);
private:
	std::string ghash_path_;
	std::size_t n_test_;
	HASH_TYPE ghash_;
};
#endif