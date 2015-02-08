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

int main(int argc, char *argv[])
{
	const std::string path = "F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\crypt_gost_28147-89\\ginit.bin";
	const std::string path_data = "F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\gost_test\\test_data\\gdata.xml";
	try
	{
		gost_test *g = new gost_test(path, path_data, 1);
		if(!(g->testing()))
		{
			std::cout<<"ERROR"<<std::endl;
		}
		hash_test *h = new hash_test("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\gost_test\\test_data\\hdata.xml",1);
		if(!(h->testing()))
		{
			std::cout<<"ERROR HASH"<<std::endl;
		}
		dh_test *dh = new dh_test("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\gost_test\\test_data\\dhdata.xml",1);
		if(!(dh->testing()))
		{
			std::cout<<"ERROR DH"<<std::endl;
		}
		delete g;
		delete h;
	}
	catch(gost_exception &ex)
	{
		std::cout<<ex.what()<<std::endl;
	}
	printf("\nAll tests passed.\n");
	getchar();
	return 0;
}