/*******************************************************************
* Файл: crypt_gost_types.h										   *
* Описание:содержит обяъявление типов и структур для 			   *
* криптографического алгоритма ГОСТ 28147-89					   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#ifndef _CRYPT_GOST_TYPES_H_
#define _CRYPT_GOST_TYPES_H_

#ifdef __alpha
typedef unsigned int word32;
#else
typedef unsigned long word32;
#endif

typedef unsigned char key;

enum 
{ 
	key_size16 = 16, 
	key_size256 = 256,
	key_size8 = 8,
	io_size2 = 2
};

#endif