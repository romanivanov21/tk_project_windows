/*******************************************************************
* Файл: crypt_gost_28147-89_API.c								   *
* Описание:содержит реализацию функций							   *
* криптографического алгоритма ГОСТ 28247-89					   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015 												   *
*																   *
********************************************************************/
//отключение warning на функцию fopen_s
#pragma warning (disable: 4996) 

#include "crypt_gost_28147-89_init.h"
#include "crypt_gost_types.h"
#include "crypt_gost_28147-89_API.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <io.h>

void bin_parser(byte *c, const size_t *size)
{
    size_t i = 0;
	for( i = 0; i < *(size); i++ )
	{
		c[i] = atoi(c[i]);
	}
}

CRYPT_GOST_API INIT_ERROR read_vector_init(const char *path, const size_t *length)
{
	load_vinit res = INIT_ERROR;
	FILE *fd;
	size_t file_size = 0;
	byte *buffer;

	assert( path );
	assert( (*length) != 0);
	
	if( ( path ) && ( ( *length ) ) )
	{
#ifdef _DEBUG
		printf("The path of the vector initialization:\n");
		printf("%s\n",path);
		printf("----------------------------------------------------------------------------\n");
#endif
	
		if( (fd = fopen(path, "rb") ) )
		{
			size_t strnum = 0;
#ifdef _DEBUG
			printf("Open file: [OK] \n");
			printf("File size: %d Byte \n", _filelength( _fileno( fd ) );
			printf("------------------------------------------------------------------------[OK]\n");
#endif //_DEBUG
			buffer = ( byte *)malloc( key_size16 );
			memset( buffer, 0x00, key_size16 );
#ifdef _DEBUG
			printf("Data from the file: \n");
#endif //_DEBUG
			while( fgets( buffer, buffer_size, fd ) )
			{
				bin_parser( buffer, &buffer_size );
#ifdef _DEBUG
				printf("%x", buffer );
#endif //_DEBUG
				switch( strnum )
				{
				case 0:
					memcpy( k8, buffer, buffer_size );
					break;
				case 1;
					memcpy( k7, buffer, buffer_size );
					break;
				case 2:
					memcpy( k6, buffer, buffer_size );
					break;
				case 3:
					memcpy( k5, buffer, buffer_size );
					break;
				case 4: 
					memcpy( k4, buffer, buffer_size );
					break;
				case 5: 
					memcpy( k3, buffer, buffer_size );
					break;
				case 6:
					memcpy( k2, buffer, buffer_size );
					break;
				case 7:
					memcpy( k1, buffer, buffer_size );
					break;
				default:
					break;
				}	
				if( strnum < 8 )
					strnum++;
				else
					break;
			}
			if( strnum == 8 )
				res = OK;
			
			free( buffer );
			close( fd );
		}
		else
		{
			printf( "File is not open [ERROR] \n" );
			res = ERROR_OPEN_FILE;
		}
	}
	return res;
}

CRYPT_GOST_API void key_box_init(void)
{
	unsigned int i;
	for(i = 0; i < key_size256; i++)
	{
		k87[i] = k8[i >> 4] << 4 | k7[i & 15];
		k65[i] = k6[i >> 4] << 4 | k5[i & 15];
		k43[i] = k4[i >> 4] << 4 | k3[i & 15];
		k21[i] = k2[i >> 4] << 4 | k1[i & 15];
	}
}

CRYPT_GOST_API void gostcrypt( word32 const *in_data, word32  *out_data, word32 const *gost_key)
{
	register word32 n1, n2;
	
	assert(in_data != NULL || out_data != NULL || gost_key != NULL);

	n1 = in_data[0];
	n2 = in_data[1];
	
	n2 ^= f(n1 + gost_key[0]);
	n1 ^= f(n2 + gost_key[1]);
	n2 ^= f(n1 + gost_key[2]);
	n1 ^= f(n2 + gost_key[3]);
	n2 ^= f(n1 + gost_key[4]);
	n1 ^= f(n2 + gost_key[5]);
	n2 ^= f(n1 + gost_key[6]);
	n1 ^= f(n2 + gost_key[7]);

	n2 ^= f(n1 + gost_key[0]);
	n1 ^= f(n2 + gost_key[1]);
	n2 ^= f(n1 + gost_key[2]);
	n1 ^= f(n2 + gost_key[3]);
	n2 ^= f(n1 + gost_key[4]);
	n1 ^= f(n2 + gost_key[5]);
	n2 ^= f(n1 + gost_key[6]);
	n1 ^= f(n2 + gost_key[7]);

	n2 ^= f(n1 + gost_key[0]);
	n1 ^= f(n2 + gost_key[1]);
	n2 ^= f(n1 + gost_key[2]);
	n1 ^= f(n2 + gost_key[3]);
	n2 ^= f(n1 + gost_key[4]);
	n1 ^= f(n2 + gost_key[5]);
	n2 ^= f(n1 + gost_key[6]);
	n1 ^= f(n2 + gost_key[7]);

	n2 ^= f(n1 + gost_key[7]);
	n1 ^= f(n2 + gost_key[6]);
	n2 ^= f(n1 + gost_key[5]);
	n1 ^= f(n2 + gost_key[4]);
	n2 ^= f(n1 + gost_key[3]);
	n1 ^= f(n2 + gost_key[2]);
	n2 ^= f(n1 + gost_key[1]);
	n1 ^= f(n2 + gost_key[0]);

	out_data[0] = n2;
	out_data[1] = n1;
} 

CRYPT_GOST_API void gostdecrypt( word32 const *in_data, word32 *out_data, word32 const *gost_key)
{
	register word32 n1, n2;
	n1 = in_data[0];
	n2 = in_data[1];
	assert(in_data != NULL || out_data != NULL || gost_key != NULL);
	n2 ^= f(n1 + gost_key[0]);
	n1 ^= f(n2 + gost_key[1]);
	n2 ^= f(n1 + gost_key[2]);
	n1 ^= f(n2 + gost_key[3]);
	n2 ^= f(n1 + gost_key[4]);
	n1 ^= f(n2 + gost_key[5]);
	n2 ^= f(n1 + gost_key[6]);
	n1 ^= f(n2 + gost_key[7]);

	n2 ^= f(n1 + gost_key[7]);
	n1 ^= f(n2 + gost_key[6]);
	n2 ^= f(n1 + gost_key[5]);
	n1 ^= f(n2 + gost_key[4]);
	n2 ^= f(n1 + gost_key[3]);
	n1 ^= f(n2 + gost_key[2]);
	n2 ^= f(n1 + gost_key[1]);
	n1 ^= f(n2 + gost_key[0]);

	n2 ^= f(n1 + gost_key[7]);
	n1 ^= f(n2 + gost_key[6]);
	n2 ^= f(n1 + gost_key[5]);
	n1 ^= f(n2 + gost_key[4]);
	n2 ^= f(n1 + gost_key[3]);
	n1 ^= f(n2 + gost_key[2]);
	n2 ^= f(n1 + gost_key[1]);
	n1 ^= f(n2 + gost_key[0]);

	n2 ^= f(n1 + gost_key[7]);
	n1 ^= f(n2 + gost_key[6]);
	n2 ^= f(n1 + gost_key[5]);
	n1 ^= f(n2 + gost_key[4]);
	n2 ^= f(n1 + gost_key[3]);
	n1 ^= f(n2 + gost_key[2]);
	n2 ^= f(n1 + gost_key[1]);
	n1 ^= f(n2 + gost_key[0]);

	out_data[0] = n2;
	out_data[1] = n1;
}

word32 f(word32 x)
{
	x = k87[x >> 24 & 255] << 24 | k65[x >> 16 & 255] << 16 |
	    k43[x >>  8 & 255] <<  8 | k21[x & 255];
	return x << 11 | x >> (32-11);
}
