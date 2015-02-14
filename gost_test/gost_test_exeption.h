/*******************************************************************
* Файл: crypt_gost_test.h										   *
* Описание: новый тип исключения								   *
* тестирования алгоритмов ГОСТ 28147-89, ГОСТ_P_34_11_2012,        *
* обмен ключами по протоколу Диффи - Хелмана				       *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
********************************************************************/

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