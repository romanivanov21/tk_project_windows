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
	for(i = 0; i < *size; i++)
	{
		switch(c[i])
		{
		case '0':
			c[i] = 0x0;
			break;
		case '1':
			c[i] = 0x1;
			break;
		case '2':
			c[i] = 0x2;
			break;
		case '3':
			c[i] = 0x3;
			break;
		case '4':
			c[i] = 0x4;
			break;
		case'5':
			c[i] = 0x5;
			break;
		case'6':
			c[i] = 0x6;
			break;
		case'7':
			c[i] = 0x7;
			break;
		case'8':
			c[i] = 0x8;
			break;
		case'9':
			c[i] = 0x9;
			break;
		case'a':
			c[i] = 0xA;
			break;
		case'b':
			c[i] = 0xB;
			break;
		case'c':
			c[i] = 0xC;
			break;
		case'd':
			c[i] = 0xD;
			break;
		case'e':
			c[i] = 0xE;
			break;
		case'f':
			c[i] = 0xF;
			break;
		}
	}
}

void data_to_k(const byte *data)
{
	size_t i = 0;
	size_t j = 0;

	for(i = 0; i < 16; i++)
	{
		k8[j] = data[i];
		j++;
	}
	j = 0;
	for(i = 18; i < 34; i++ )
	{
		k7[j] = data[i];
		j++;
	}
	j = 0;
	for(i = 36; i < 52; i++)
	{
		k6[j] = data[i];
		j++;
	}
	j = 0;
	for(i = 54; i < 70; i++)
	{
		k5[j] = data[i];
		j++;
	}
	j = 0;
	for(i = 72; i < 88; i++)
	{
		k4[j] = data[i];
		j++;
	}
	j = 0;
	for(i = 90; i < 106; i++)
	{
		k3[j] = data[i];
		j++;
	}
	j = 0;
	for(i = 108; i < 124; i++)
	{
		k2[j] = data[i];
		j++;
	}
	j = 0;
	for(i = 126; i < 142; i++)
	{
		k1[j] = data[i];
		j++;
	}
}

CRYPT_GOST_API word32 read_vector_init(const char *path, const size_t *size_path)
{
	size_t i = 0;
	FILE *file;
	byte *data;
	size_t file_size = 0; 

	if((path == NULL) || (*size_path == 0))
	{
		return PATCH_EMPTY;
	}

#if DEBUG_INFO_PRINT
	printf("The path to the vector initialization:\n");
	for(i = 0; i < *size_path; i++)
	{
		printf("%c",path[i]);
	}
	printf("\n");
	printf("----------------------------------------------------------------------------\n");
#endif
	if((file = fopen(path, "rb")) != NULL)
	{
#if DEBUG_INFO_PRINT
		printf("Open file: [OK] \n");
#endif
		file_size = _filelength(_fileno(file));
#if DEBUG_INFO_PRINT
		printf("File size: %d",file_size);
		printf(" Byte \n");
		printf("------------------------------------------------------------------------[OK]\n");
#endif
		if(file_size != 0)
		{
			size_t read_byte;
			data = (byte*)malloc((file_size * sizeof(byte)));
			memset(data,0,(file_size * sizeof(byte)));
			read_byte = fread(data, sizeof(byte), file_size/sizeof(byte), file);
			if(read_byte == 0)
			{
#if DEBUG_INFO_PRINT 
				printf("File is empty [ERROR]");
#endif
				fclose(file);
				return FILE_IS_EMPTY;
			}
			fclose(file);
#if DEBUG_INFO_PRINT
			printf("Data from the file: \n");
#endif
			bin_parser(data,&file_size);

#if DEBUG_INFO_PRINT
			for(i = 0; i < 16; i++)
			{
				printf("%x",data[i]);
			}
			printf("\n");
			for(i = 18; i < 34; i++)
			{
				printf("%x",data[i]);
			}
			printf("\n");
			for(i = 36; i < 52; i++)
			{
				printf("%x",data[i]);
			}
			printf("\n");
			for(i = 54; i < 70; i++)
			{
				printf("%x",data[i]);
			}
			printf("\n");
			for(i = 72; i < 88; i++)
			{
				printf("%x",data[i]);
			}
			printf("\n");
			for(i = 90; i < 106; i++)
			{
				printf("%x",data[i]);
			}
			printf("\n");
			for(i = 108; i < 124; i++)
			{
				printf("%x",data[i]);
			}
			printf("\n");
			for(i = 126; i < 142; i++)
			{
				printf("%x",data[i]);
			}
			printf("\n");
			printf("------------------------------------------------------------------------[OK]\n");
#endif
			data_to_k(data);
			i = 0;
#if DEBUG_INFO_PRINT 
			printf("Vector init:\n");
			for(i = 0; i < key_size16; i++)
			{
				printf("%x", k8[i]);
			}
			printf("\n");
			for(i = 0; i < key_size16; i++)
			{
				printf("%x", k7[i]);
			}
			printf("\n");
			for(i = 0; i < key_size16; i++)
			{
				printf("%x", k6[i]);
			}
			printf("\n");
			for(i = 0; i < key_size16; i++)
			{
				printf("%x", k5[i]);
			}
			printf("\n");
			for(i = 0; i < key_size16; i++)
			{
				printf("%x", k4[i]);
			}
			printf("\n");
			for(i = 0; i < key_size16; i++)
			{
				printf("%x", k3[i]);
			}
			printf("\n");
			for(i = 0; i < key_size16; i++)
			{
				printf("%x", k2[i]);
			}
			printf("\n");
			for(i = 0; i < key_size16; i++)
			{
				printf("%x", k1[i]);
			}
			printf("\n");
			printf("------------------------------------------------------------------------[OK]\n");
			free(data);
#endif
			return OK;
		}
		else
		{
#if DEBUG_INFO_PRINT
			printf("File size is null [ERROR]");
#endif
			return FILE_SIZE_IS_NULL;
		}
	}
	else
	{
#if DEBUG_INFO_PRINT
		printf("File is not open [ERROR]");
#endif
		return ERROR_OPEN_FILE;
	}
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
