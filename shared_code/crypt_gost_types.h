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

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short word16;
typedef unsigned long long word64;

enum 
{ 
	key_size16 = 16, 
	key_size256 = 256,
	key_size32 = 32,
	key_size8 = 8,
	io_size2 = 2,
	SIZE_HASH256_BYTE = 32,
	SIZE_HASH512_BYTE = 64,
	SIZE_CRYPT_BUFF_BYTE = 8,
	SIZE_CRYPT_BUFF_WORD = 2,
	SIZE_CRYPT_KEY_BYTE = 32,
	SIZE_CRYPT_KEY_WORD = 8,
	SIZE_DH_BUFF_BYTE = 32,
};
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