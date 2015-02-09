#include"gtest_client.h"
#include<iostream>

int main(void)
{
	test_client *test = new test_client("F:\\Диплом\\Рабочий репозиторий\\tk_project_windows\\gost_test\\test_data\\dhdata.xml",8001);
	try
	{
		test->testing();
		delete test;
	}
	catch( client_exception &ex)
	{
		delete test;
		std::cout<<ex.wath()<<std::endl;
	}
	getchar();
	system("exit");
	return 0;
}