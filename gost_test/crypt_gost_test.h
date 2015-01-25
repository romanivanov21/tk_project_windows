#ifndef _CRYPT_GOST_TEST_H_
#define _CRYPT_GOST_TEST_H_

#include <iostream>

class test
{
public:
	virtual void print_result()const;
};
class gost_test : test
{
public:
	gost_test(const std::size_t &n);
public:
	virtual void print_result()const;
};
class dh_test : test
{
public:
	dh_test(const std::size_t &n);
public:
	virtual void print_result()const;
};
class hash_test : test
{
public:
	hash_test(const std::size_t &n);
public:
	virtual void print_result()const;
};
#endif