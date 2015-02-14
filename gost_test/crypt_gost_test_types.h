/*******************************************************************
* Файл: crypt_gost_tests.h										   *
* Описание:содержит обяъявления констант и структур				   *
* тестирования алгоритмов ГОСТ 28147-89, ГОСТ_P_34_11_2012,        *
* обмен ключами по протоколу Диффи - Хелмана				       *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
********************************************************************/

#ifndef _CRYPT_GOST_TEST_H_
#define _CRYPT_GOST_TEST_H_

#define SIZE_CRYPT_BUFF_BYTE 8
#define SIZE_CRYPT_BUFF_WORD 2

#define SIZE_CRYPT_KEY_BYTE 32
#define SIZE_CRYPT_KEY_WORD 8

#define SIZE_HASH256_BYTE 32
#define SIZE_HASH512_BYTE 64

#define SIZE_DH_BUFF_BYTE 32

#define CONSOLE_APPLICATION 1

#include"..\crypt_gost_28147-89\crypt_gost_types.h"

#pragma pack(push,1)
typedef struct
{
	byte data256[SIZE_HASH256_BYTE];
	byte data512[SIZE_HASH512_BYTE];
	
	byte hash256[SIZE_HASH256_BYTE];
	byte hash512[SIZE_HASH512_BYTE];
}HASH_TYPE, *PTR_HASH_TYPE;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
	byte byte_encryption_data[SIZE_CRYPT_BUFF_BYTE];
	word32 word_encryption_data[SIZE_CRYPT_BUFF_WORD];
	
	byte byte_key[SIZE_CRYPT_KEY_BYTE];
	word32 word_key[SIZE_CRYPT_KEY_WORD];

	byte byte_decryption_data[SIZE_CRYPT_BUFF_BYTE];
	word32 word_decryption_data[SIZE_CRYPT_BUFF_WORD];
	
} GOST_TYPE, *PTR_GOST_TYPE;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
	byte p_byte[SIZE_DH_BUFF_BYTE];
	byte q_byte[SIZE_DH_BUFF_BYTE];
	byte g_byte;

	byte keyA[SIZE_DH_BUFF_BYTE];

	byte keyB[SIZE_DH_BUFF_BYTE];

	byte gkey[SIZE_DH_BUFF_BYTE];

}DH_TYPE, *PTR_DH_TYPE;
#pragma pack(pop)

#endif