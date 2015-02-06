#include"crypt_gost_test.h"
#include "..\crypt_gost_28147-89\crypt_gost_types.h"
#include"..\shared_code\gost_include.h"
#include"..\shared_code\gost_types_convert.h"
#include"gost_test_exeption.h"
#include"tinyxml.h"
#include <io.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <chrono>
//отключение warning на функцию fopen_s
#pragma warning (disable: 4996)
static void bin_parser(std::string &vaule)
{
	assert(vaule.length() != 0);
	for(std::size_t i = 0; i < vaule.length(); i++)
	{
		switch(vaule[i])
		{
		case '0':
			vaule[i] = 0x0;
			break;
		case '1':
			vaule[i] = 0x1;
			break;
		case '2':
			vaule[i] = 0x2;
			break;
		case '3':
			vaule[i] = 0x3;
			break;
		case '4':
			vaule[i] = 0x4;
			break;
		case'5':
			vaule[i] = 0x5;
			break;
		case'6':
			vaule[i] = 0x6;
			break;
		case'7':
			vaule[i] = 0x7;
			break;
		case'8':
			vaule[i] = 0x8;
			break;
		case'9':
			vaule[i] = 0x9;
			break;
		case'a':
			vaule[i] = 0xA;
			break;
		case'b':
			vaule[i] = 0xB;
			break;
		case'c':
			vaule[i] = 0xC;
			break;
		case'd':
			vaule[i] = 0xD;
			break;
		case'e':
			vaule[i] = 0xE;
			break;
		case'f':
			vaule[i] = 0xF;
			break;
		}
	}
}
gost_test::gost_test(const std::string &vinit_path, const std::string &test_data_path, const std::size_t &n_test) : 
		vinit_path_(vinit_path), test_data_path_(test_data_path), n_test_(n_test)
{
	assert(vinit_path.length() != 0);
	assert(test_data_path.length() != 0);
	assert(n_test != 0);
#if CONSOLE_APPLICATION
	std::cout<<"GOST 28147-89"<<std::endl;
#endif
	memset(gtype_.byte_decryption_data, 0, sizeof(byte) * SIZE_CRYPT_BUFF_BYTE);
	memset(gtype_.byte_encryption_data, 0, sizeof(byte) * SIZE_CRYPT_BUFF_BYTE);
	memset(gtype_.word_decryption_data, 0, sizeof(word32) * SIZE_CRYPT_BUFF_WORD);
	memset(gtype_.word_encryption_data, 0, sizeof(word32) * SIZE_CRYPT_BUFF_WORD);
}

std::string gost_test::test_data_read(const std::size_t &id_data)
{
	assert(id_data != 0);
	TiXmlDocument *gdata = new TiXmlDocument(test_data_path_.c_str());
	if( !(gdata->LoadFile()))
	{
		delete gdata;
		throw gost_exception("The dataful file for testing didn't manage to be opened");
	}
	TiXmlElement*pElem = gdata->FirstChildElement("cryptgost");
	if (!pElem)
	{
		delete gdata;
		throw new gost_exception("Error read data");
	}
	std::string value = "";
	for(const TiXmlElement *item = pElem->FirstChildElement("data"); item; item = item->NextSiblingElement("data"))
	{
		std::string temp = "";
		std::string id_size_t = std::to_string(id_data);
		temp = item->Attribute("name");
		if(temp == id_size_t)
		{
			value = (item->Attribute("vaule")); bin_parser(value);
		}
	}
	delete gdata;

	return value;
}

std::string gost_test::test_key_read(const std::size_t &id_key)
{
	assert(id_key != 0);
	TiXmlDocument *gkey = new TiXmlDocument(test_data_path_.c_str());
	if(!(gkey->LoadFile()))
	{
		delete gkey;
		throw new gost_exception("The dataful file for testing didn't manage to be opened");
	}
	TiXmlElement *pElem = gkey->FirstChildElement("cryptgost");
	if(!pElem) {
		delete gkey;
		throw new gost_exception("Error read key");
	}

	std::string value = "";
	for(const TiXmlElement *item = pElem->FirstChildElement("gkey"); item; item = item->NextSiblingElement("gkey"))
	{
		std::string temp = "";
		std::string id_size_t = std::to_string(id_key);
		temp = item->Attribute("name");
		if(temp == id_size_t)
		{
			value = (item->Attribute("vaule")); bin_parser(value);
		}
	}
	delete gkey;
	return value;
}

std::string gost_test::test_crypt_data_read(const std::size_t &id_cryprdata)
{
	assert(id_cryprdata != 0);
	TiXmlDocument *cryptdata= new TiXmlDocument(test_data_path_.c_str());
	if(!(cryptdata->LoadFile()))
	{
		delete cryptdata;
		throw new gost_exception("The dataful file for testing didn't manage to be opened");
	}
	TiXmlElement *pElem = cryptdata->FirstChildElement("cryptgost");
	if(!pElem) {
		delete cryptdata;
		throw new std::string("Error read crdata");
	}

	std::string value = "";
	for(const TiXmlElement *item = pElem->FirstChildElement("crdata"); item; item = item->NextSiblingElement("crdata"))
	{
		std::string temp = "";
		std::string id_size_t = std::to_string(id_cryprdata);
		temp = item->Attribute("name");
		if(temp == id_size_t)
		{
			value = (item->Attribute("vaule")); bin_parser(value);
		}
	}
	delete cryptdata;
	return value;
}
bool gost_test::testing(void)
{
	std::size_t size = 1;
	if((n_test_ <= 5) && (n_test_ > 0))
	{
		size = n_test_;
	}
	else
	{
		size = 5;
	}
	std::string data = "";
	try
	{
		data = test_data_read(n_test_);
	}
	catch(gost_exception &ex)
	{
		throw gost_exception(ex.what());
	}
	if(data.length() != SIZE_CRYPT_BUFF_BYTE)
	{
		throw gost_exception("Format data form gdata.xml error");
	}
	for(std::size_t i = 0; i < SIZE_CRYPT_BUFF_BYTE; i++)
	{
		gtype_.byte_encryption_data[i] = data[i];
	}
	std::string key = "";
	try
	{
		key = test_key_read(n_test_);
	}
	catch(gost_exception &ex)
	{
		throw gost_exception(ex.what());
	}
	if(key.length() != SIZE_CRYPT_KEY_BYTE)
	{
		throw gost_exception("Format gkey from hdata.xml error");
	}

	for(std::size_t i = 0; i < SIZE_CRYPT_KEY_BYTE; i++)
	{
		gtype_.byte_key[i] = key[i];
	}

	std::string cryptdata = test_crypt_data_read(1);
	if(cryptdata.length() != SIZE_CRYPT_BUFF_BYTE)
	{
		throw gost_exception("Format gkey from hdata.xml error");
	}
	while(n_test_ != 0)
	{
		try
		{
			if(!(crypt(n_test_)))
			{
				return false;
			}
			n_test_--;
		}
		catch(gost_exception &ex)
		{
			throw gost_exception(ex.what());
		}
	}
#if CONSOLE_APPLICATION
	print_result("OK");
	print_result("----------------------------------------------------------------------------");
#endif
	return true;
}
bool gost_test::crypt(const std::size_t &n)
{
	const std::size_t length = vinit_path_.length();
	if(read_vector_init(vinit_path_.c_str(),&length))
	{
		throw gost_exception("Vector init for GOST 28147-89 error");
	}
#if CONSOLE_APPLICATION 
	print_result("source data:");
	print_result(gtype_.byte_encryption_data,SIZE_CRYPT_BUFF_BYTE);
	print_result("------------------------------------------------------------------------[OK]");
	print_result("key:");
	print_result(gtype_.byte_key,SIZE_CRYPT_KEY_BYTE);
	print_result("------------------------------------------------------------------------[OK]");
#endif
	byte_to_word32_key(gtype_.byte_key,gtype_.word_key);
	byte_to_word32_data(gtype_.byte_encryption_data, gtype_.word_encryption_data);

	gostcrypt(gtype_.word_encryption_data,gtype_.word_decryption_data,gtype_.word_key);
	word32_to_byte_data(gtype_.word_decryption_data,gtype_.byte_decryption_data);
#if CONSOLE_APPLICATION
	print_result("encrypted data:");
	print_result(gtype_.byte_decryption_data,SIZE_CRYPT_BUFF_BYTE);
	print_result("------------------------------------------------------------------------[OK]");
#endif
	std::string temp = "";
	try
	{
		temp = test_crypt_data_read(n);
	}
	catch(gost_exception &ex)
	{
		throw gost_exception(ex.what());
	}
	for(std::size_t i = 0; i < temp.length(); i++)
	{
		if(temp[i] != gtype_.byte_decryption_data[i]) {
			
			return false;
		}
	} byte_to_word32_data(gtype_.byte_decryption_data,gtype_.word_decryption_data);
	gostdecrypt(gtype_.word_decryption_data,gtype_.word_encryption_data, gtype_.word_key);
	word32_to_byte_data(gtype_.word_encryption_data,gtype_.byte_encryption_data);
#if CONSOLE_APPLICATION
	print_result("decrypted data:");
	print_result(gtype_.byte_encryption_data,SIZE_CRYPT_BUFF_BYTE);
	print_result("------------------------------------------------------------------------[OK]");
#endif
	std::string data = "";
	try
	{
		data = test_data_read(n);
	}
	catch(gost_exception &ex)
	{
		throw gost_exception(ex.what());
	}
	for(std::size_t i = 0; i < SIZE_CRYPT_BUFF_BYTE; i++)
	{
		if(data[i] != gtype_.byte_encryption_data[i])
		{
			return false;
		}
	}
	return true;
}

void test::print_result(const std::string &msg)const
{
	assert(msg.length() != 0);
	std::cout<<msg<<std::endl;
}

void test::print_result(const byte* msg, const std::size_t &length)const
{
	assert(length != 0);
	for(std::size_t i = 0; i < length; i++)
	{
		printf("%x",msg[i]);
	}
	printf("\n");
}

void test::print_result(const word32 *msg, const std::size_t &length)const
{
	assert(length != 0);
	for(std::size_t i = 0; i < length; i++)
	{
		printf("%x",msg[i]);
	}
	printf("\n");
}