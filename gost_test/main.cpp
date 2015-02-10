/*******************************************************************
* Файл: main.cpp												   *
* Описание: тест функций crypt_gost_28147-89.dll				   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include "..\crypt_gost_28147-89\diffy_helman.h"
#include "..\network_server_dll\network_server_dll.h"
#include "..\shared_code\gost_include.h"
#include "gost_test_exeption.h"
#include "crypt_gost_test.h"

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <boost\shared_ptr.hpp>

int main(int argc, char *argv[])
{
	std::string arg_command = "";
	const std::string path = "F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\crypt_gost_28147-89\\ginit.bin";
	const std::string path_gdata = "F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\gost_test\\test_data\\gdata.xml";
	const std::string path_hdata = "F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\gost_test\\test_data\\hdata.xml";
	const std::string path_dhdata = "F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\gost_test\\test_data\\dhdata.xml";
	if(argv[1] != NULL)
	{
		arg_command = argv[1];
		std::cout<<arg_command<<std::endl;
	}
	else
	{
		arg_command = "-all";
	}
	if(arg_command == "-all")
	{
		try
		{
			boost::shared_ptr<gost_test> g(new gost_test(path, path_gdata, 1));
			if(!(g->testing()))
			{
				std::cout<<"ERROR"<<std::endl;
				return -1;
			}
			boost::shared_ptr<hash_test> h(new hash_test(path_hdata,1));
			if(!(h->testing()))
			{
				std::cout<<"ERROR HASH"<<std::endl;
				return -1;
			}
			boost::shared_ptr<dh_test> dh(new dh_test(path_dhdata,1));
			if(!(dh->testing()))
			{
				std::cout<<"ERROR DH"<<std::endl;
				return -1;
			}
		}
		catch(gost_exception &ex)
		{
			std::cout<<ex.what()<<std::endl;
			return -1;
		}
		printf("\nAll tests passed.\n");
	}
	if(arg_command == "-g")
	{
		try
		{
			boost::shared_ptr<gost_test> g(new gost_test(path, path_gdata, 1));
			if(!(g->testing()))
			{
				std::cout<<"ERROR"<<std::endl;
				return -1;
			}
		}
		catch(gost_exception &ex)
		{
			std::cout<<ex.what()<<std::endl;
			return -1;
		}
		printf("\nAll tests passed.\n");
	}
	if(arg_command == "-h")
	{
		try
		{
			boost::shared_ptr<hash_test> h(new hash_test(path_hdata,1));
			if(!(h->testing()))
			{
				std::cout<<"ERROR HASH"<<std::endl;
				return -1;
			}
		}
		catch(gost_exception &ex)
		{
			std::cout<<ex.what()<<std::endl;
		}
		printf("\nAll tests passed.\n");
	}
	if(arg_command == "-dh")
	{
		try
		{
			boost::shared_ptr<dh_test> dh(new dh_test(path_dhdata,1));
			if(!(dh->testing()))
			{
				std::cout<<"ERROR DH"<<std::endl;
				return -1;
			}
		}
		catch(gost_exception &ex)
		{
			std::cout<<ex.what()<<std::endl;
			return -1;
		}
		printf("\nAll tests passed.\n");
	}
	return 0;
}