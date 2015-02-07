#ifndef _GOST_TEST_EXEPTION_H_
#define _GOST_TEST_EXEPTION_H_
#include <iostream>
class gost_exception : std::exception
{
public:
	explicit gost_exception(const std::string &msg) : msg_(msg) { }
	std::string what(){ return msg_; }
private:
	std::string msg_;
};
#endif