/*******************************************************************
* Файл: main.cpp												   *
* Описание: тест функций crypt_gost_28147-89.dll				   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014 - 2015												   *
*																   *
********************************************************************/

#include <iostream>
typedef unsigned long word32;
typedef unsigned char byte;
extern "C" void key_box_init();
extern "C" void gostcrypt( word32 const *in_data, word32 *out_data, word32 const *gost_key);
extern "C" void gostdecrypt(word32 const *in_data, word32 *out_data, word32 const *gost_key);

int main(void)
{
	word32 key[8];	  // 256 бит
	word32 input[2];  // 64 бит
	word32 output[2]; // 64 бит
	word32 output1[2]; 

	key_box_init();
	key[0] = 5; key[1] = 4; key[2] = 3; key[3] = 2; key[4] = 1; key[5] = 0; key[6] = 1; key[7] = 5;

	input[0] = 9;
	input[1] = 5;

	gostcrypt(input, output, key);
	printf("%x ",output[0]);
	printf("%x \n", output[1]);


	gostdecrypt(output,output1,key);

	printf("%d ",output1[0]);
	printf("%d \n",output1[1]);

	printf("All tests passed.\n");
	getchar();
	return 0;
}