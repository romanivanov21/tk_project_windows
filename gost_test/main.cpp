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

void word32_to_byte(word32 *word32_, byte *byte_)
{
	memset(byte_, 0, 8);
	word32 temp = word32_[0];
	int s = 24;
	for(unsigned int i = 0; i < 4; i++)
	{
		word32_[0] = temp;
		word32_[0] = word32_[0] >> s;
		byte_[i] |= word32_[0];
		s = s - 8;
	}
	temp = word32_[1];
	for(unsigned int i = 4; i < 8; i++)
	{
		word32_[1] = temp;
		word32_[1] = word32_[1] >> s;
		byte_[i] |= word32_[1];
		s = s - 8;
	}
}

void byte_to_word32( byte *byte_, word32 *word32_)
{
	memset(word32_, 0, 8);

	for(unsigned int i = 0; i < 4; i++)
	{
		word32_[0] = word32_[0] << 8;
		word32_[0] |= byte_[i];
	}
	for(unsigned int i = 4; i < 8; i++)
	{
		word32_[1] = word32_[1] << 8;
		word32_[1] |= byte_[i];
	}
}
int main(void)
{
	word32 word32_[2];
	byte byte_[8];
	byte_[0] = 1;
	byte_[1] = 2;
	byte_[2] = 3;
	byte_[3] = 4;
	byte_[4] = 5;
	byte_[5] = 6;
	byte_[6] = 7;
	byte_[7] = 8;

	for(int i = 0; i < 8; i++)
	{
		printf("%x",byte_[i]);
	}
	byte_to_word32(byte_,word32_);
	word32_to_byte(word32_,byte_);
	printf("\n");
	for(int i = 0; i < 8; i++)
	{
		printf("%d",byte_[i]);
	}
	/*word32 key[8];	  // 256 бит
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
	*/
	printf("\nAll tests passed.\n");
	getchar();
	return 0;
}