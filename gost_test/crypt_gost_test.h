#ifndef _TEST_CRYPT_H_
#define _TEST_CRYPT_H_

#include"..\crypt_gost_28147-89\crypt_gost_types.h"
#include <boost\noncopyable.hpp>
#include <vector>
#include <string>
#include <iostream>

#define SIZE_CRYPT_BUFF_BYTE 8
#define SIZE_CRYPT_BUFF_WORD 2

#define SIZE_CRYPT_KEY_BYTE 32
#define SIZE_CRYPT_KEY_WORD 8

#define CONSOLE_APPLICATION 1

typedef struct
{
	byte byte_encryption_data[SIZE_CRYPT_BUFF_BYTE];
	word32 word_encryption_data[SIZE_CRYPT_BUFF_WORD];
	
	byte byte_key[SIZE_CRYPT_KEY_BYTE];
	word32 word_key[SIZE_CRYPT_KEY_WORD];

	byte byte_decryption_data[SIZE_CRYPT_BUFF_BYTE];
	word32 word_decryption_data[SIZE_CRYPT_BUFF_WORD];
	
} GOST_TYPE, *PTR_GOST_TYPE;

static void bin_parser(std::string &vaule);

class test : private boost::noncopyable
{
public:
	explicit test(void) { std::cout<<"Tested the algoritm "; };
	virtual bool testing(void) = 0;
	virtual void print_result(const std::string &msg)const = 0;
	virtual void print_result(const byte* msg, const std::size_t &length)const = 0;
	virtual void print_result(const word32 *msg, const std::size_t &length)const = 0;
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
	void print_result(const std::string &msg)const;
	void print_result(const byte* msg, const std::size_t &length)const;
	void print_result(const word32 *msg, const std::size_t &length)const;
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
	void print_result(const std::string &msg)const;
	virtual void print_result(const byte* msg, const std::size_t &length)const;
	virtual void print_result(const word32 *msg, const std::size_t &length)const;
private:
	void test_data_read(std::vector<byte> *data);
private:
	const std::string test_data_path_;
	const std::size_t n_test_;
};
class hash_test : public test
{
public:
	explicit hash_test(void);
	~hash_test();
	bool testing(void);
	void print_result(const std::string &msg)const;
	virtual void print_result(const byte* msg, const std::size_t &length)const;
	virtual void print_result(const word32 *msg, const std::size_t &length)const;
private:
	void test_data_read(std::vector<byte> *data);
private:
	
};
#endif