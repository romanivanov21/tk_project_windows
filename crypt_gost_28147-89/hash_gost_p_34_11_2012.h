/*******************************************************************
* ����: has_p_34_11_2012.h										   *
* ��������:�������� ����������� �������							   *
* ��� ���������� ��� ������� �� ��������� ���� P 34.11.2012		   *
* �����: ������ ����� ���������� (c)							   *
* ���: 2015														   *
*																   *
********************************************************************/

#ifndef _HASH_P_34_11_2012_H_
#define _HASH_P_34_11_2012_H_

#define PRINT_DEBUG_INFO 1

#define GOST_HASH_API __declspec(dllexport)
#include"crypt_gost_types.h"

/*******************************************************************
* API functions (������������ �������)							   *
********************************************************************/

/*******************************************************************
* ������� hash_512() ��������� ���-������� �������� 512 ���		   *
*																   *
*  ��������� �������:											   *
*  1. {const byte *message} - ������ ������, ��� ��������		   *
*  ����������� ���												   *
*																   *
*  2. {word64 *length} - ����� ����������� �������				   *
*  ��� ���������� ���											   *
*																   *
*  3. {byte *hash} - ������ �� 64 ��������� ��� ����������		   *
*																   *
********************************************************************/

GOST_HASH_API void hash_512(const byte *message, word64 length, byte *hash);


/*******************************************************************
* ������� hash_256() ��������� ���-������� �������� 256 ���		   *
*																   *
*  ��������� �������:											   *
*  1. {const byte *message} - ������ ������, ��� ��������		   *
*  ����������� ���												   *
*																   *
*  2. {word64 *length} - ����� ����������� �������				   *
*  ��� ���������� ���											   *
*																   *
*  3. {byte *hash} - ������ �� 32 ��������� ��� ����������		   *
*																   *
********************************************************************/
GOST_HASH_API void hash_256(const byte *message, word64 length, byte *hash);

#endif