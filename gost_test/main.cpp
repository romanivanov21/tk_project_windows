/*******************************************************************
* ����: main.cpp												   *
* ��������: ���� ������� crypt_gost_28147-89.dll				   *
* �����: ������ ����� ���������� (c)							   *
* ���: 2014 - 2015												   *
*																   *
********************************************************************/

#include "gost_API_test.h"
#include <iostream>

int main(void)
{
	char data[8];
	strcpy_s(data, "Roman21");
	init_gost(data);
	printf("\nAll tests passed.\n");
	getchar();
	return 0;
}