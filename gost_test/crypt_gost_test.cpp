#include"crypt_gost_test.h"
#include "..\crypt_gost_28147-89\crypt_gost_types.h"
#include"..\shared_code\gost_include.h"
#include"..\shared_code\gost_types_convert.h"
#include"..\network_server_dll\network_server_dll.h"
#include"gost_test_exeption.h"
#include"tinyxml.h"
#include <io.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iomanip>
//отключение warning на функцию fopen_s
#pragma warning (disable: 4996)
void test::bin_parser(std::string &vaule)
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
std::string test::to_hex(const byte *byte_data, const std::size_t &length)
{
	assert((byte_data != 0) || (length != 0));
	std::vector<byte> v(&byte_data[0], &byte_data[length - 1]);
	std::ostringstream result;
	result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
	std::copy(v.begin(), v.end(), std::ostream_iterator<unsigned int>(result, ""));
	return result.str();
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
	assert((n_test_ > 0) || (n_test_ <= 5));
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

dh_test::dh_test(const std::string &test_data_path, const std::size_t &n_test)
{
	assert(test_data_path.length() != 0);
	assert(n_test != 0);
#if CONSOLE_APPLICATION 
	std::cout<<"DIFFY_HELMAN"<<std::endl;
#endif
	test_data_path_ = test_data_path;
	n_test_ = n_test;
	dh_type_ = new DH_TYPE();
	dh_ = 0;
}
dh_test::~dh_test()
{
	delete dh_type_; delete dh_;
}

bool dh_test::testing()
{
	dh_ = new diffy_helm();
	boost::uint32_t port = 8001;
	server_netw::server *s = new server_netw::server(port);
	s->start();

	dh_->get_p(dh_type_->p_byte, SIZE_DH_BUFF_BYTE);
	s->send_bytes(dh_type_->p_byte, SIZE_DH_BUFF_BYTE);

	dh_->get_q(dh_type_->q_byte, SIZE_DH_BUFF_BYTE);
	s->send_bytes(dh_type_->q_byte, SIZE_DH_BUFF_BYTE);

	dh_->get_g(dh_type_->g_byte);
	s->send_bytes(&dh_type_->g_byte, 1);

	dh_->generate_A(dh_type_->keyA, SIZE_DH_BUFF_BYTE);
	s->send_bytes(dh_type_->keyA, SIZE_DH_BUFF_BYTE);
	if(s->read_bytes(dh_type_->keyB, SIZE_DH_BUFF_BYTE) != SIZE_DH_BUFF_BYTE)
	{
		print_result("Error read B");
	}
#if CONSOLE_APPLICATION
	print_result(dh_type_->keyB, SIZE_DH_BUFF_BYTE);
#endif
	dh_->generate_K(dh_type_->keyB,SIZE_DH_BUFF_BYTE, dh_type_->gkey, SIZE_DH_BUFF_BYTE);
#if CONSOLE_APPLICATION
	print_result(dh_type_->gkey, SIZE_DH_BUFF_BYTE);
#endif
	delete s;
	if(!keycmp())
	{
		return false;
	}
	return true;
}
std::string dh_test::key_read()
{
	std::string value = "";
	TiXmlDocument *gkey = new TiXmlDocument(test_data_path_.c_str());
	if(!(gkey->LoadFile()))
	{
		delete gkey;
		throw new gost_exception("The dataful file for testing didn't manage to be opened dhdata.xml");
	}
	TiXmlElement *pElem = gkey->FirstChildElement("dh");
	if(!pElem) {
		delete gkey;
		throw new gost_exception("Error read key from dhdata.xml");
	}
	for(const TiXmlElement *item = pElem->FirstChildElement("key"); item; item = item->NextSiblingElement("key"))
	{
		value = (item->Attribute("vaule"));
	}
	delete gkey;
	return value;
}
bool dh_test::keycmp()
{
	std::string temp = "";
	try
	{
		temp = key_read();
	}
	catch(gost_exception &ex)
	{
		throw gost_exception(ex.what());
	}
	if(temp.length() == 0)
	{
		throw gost_exception("Error read key from dhdata.xml");
	}
	std::string value = to_hex(dh_type_->gkey, SIZE_DH_BUFF_BYTE);
	for(std::size_t i = 0; i < value.length(); i++)
	{
		if(temp[i] != value[i])
		{
			return false;
		}
	}
	return true;
}
hash_test::hash_test(const std::string &ghash_path, const std::size_t &n_test)
{
	assert(ghash_path.length() != 0);
	assert(n_test != 0);
	
	ghash_path_ = ghash_path;
	n_test_ = n_test;
#if CONSOLE_APPLICATION
	print_result("HASH_GOST_P_34_11_2012");
#endif
	memset(ghash_.data256, 0, sizeof(byte) * SIZE_HASH256_BYTE);
	memset(ghash_.data512, 0, sizeof(byte) * SIZE_HASH512_BYTE);
	memset(ghash_.hash256, 0, sizeof(byte) * SIZE_HASH256_BYTE);
	memset(ghash_.hash512, 0, sizeof(byte) * SIZE_HASH512_BYTE);
}
std::string hash_test::test_data256_read(const std::size_t &id_data)
{
	assert(id_data != 0);
	TiXmlDocument *gdata = new TiXmlDocument(ghash_path_.c_str());
	if( !(gdata->LoadFile()))
	{
		delete gdata;
		throw gost_exception("The dataful file for testing didn't manage to be opened");
	}
	TiXmlElement*pElem = gdata->FirstChildElement("crypthash");
	if (!pElem)
	{
		delete gdata;
		throw gost_exception("Error read data256 form crypthash");
	}
	std::string value = "";
	for(const TiXmlElement *item = pElem->FirstChildElement("data256"); item; item = item->NextSiblingElement("data256"))
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
std::string hash_test::test_data512_read(const std::size_t &id_data)
{
	assert(id_data != 0);
	TiXmlDocument *gdata = new TiXmlDocument(ghash_path_.c_str());
	if( !(gdata->LoadFile()))
	{
		delete gdata;
		throw gost_exception("The dataful file for testing didn't manage to be opened");
	}
	TiXmlElement*pElem = gdata->FirstChildElement("crypthash");
	if (!pElem)
	{
		delete gdata;
		throw gost_exception("Error read data512 form crypthash");
	}
	std::string value = "";
	for(const TiXmlElement *item = pElem->FirstChildElement("data512"); item; item = item->NextSiblingElement("data512"))
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
std::string hash_test::test_hash512_read(const std::size_t &id_hash)
{
	assert(id_hash != 0);
	TiXmlDocument *gdata = new TiXmlDocument(ghash_path_.c_str());
	if( !(gdata->LoadFile()))
	{
		delete gdata;
		throw gost_exception("The dataful file for testing didn't manage to be opened");
	}
	TiXmlElement*pElem = gdata->FirstChildElement("crypthash");
	if (!pElem)
	{
		delete gdata;
		throw gost_exception("Error read hash512 form crypthash");
	}
	std::string value = "";
	for(const TiXmlElement *item = pElem->FirstChildElement("hash512"); item; item = item->NextSiblingElement("hash512"))
	{
		std::string temp = "";
		std::string id_size_t = std::to_string(id_hash);
		temp = item->Attribute("name");
		if(temp == id_size_t)
		{
			value = (item->Attribute("vaule"));
		}
	}
	delete gdata;
	return value;
}
std::string hash_test::test_hash256_read(const std::size_t &id_hash)
{
	assert((id_hash > 0) || (id_hash <= 5));
	TiXmlDocument *gdata = new TiXmlDocument(ghash_path_.c_str());
	if( !(gdata->LoadFile()))
	{
		delete gdata;
		throw gost_exception("The dataful file for testing didn't manage to be opened");
	}
	TiXmlElement*pElem = gdata->FirstChildElement("crypthash");
	if (!pElem)
	{
		delete gdata;
		throw gost_exception("Error read hash256 form crypthash");
	}
	std::string value = "";
	for(const TiXmlElement *item = pElem->FirstChildElement("hash256"); item; item = item->NextSiblingElement("hash256"))
	{
		std::string temp = "";
		std::string id_size_t = std::to_string(id_hash);
		temp = item->Attribute("name");
		if(temp == id_size_t)
		{
			value = (item->Attribute("vaule"));
		}
	}
	delete gdata;
	return value;
}

bool hash_test::testing()
{
	assert((n_test_ > 0) || (n_test_ <= 5));
	while (n_test_ != 0)
	{
		if(!(hashcmp256(n_test_)) || !(hashcmp512(n_test_)))
		{
			return false;
		}
		n_test_--;
	}
	return true;
}
bool hash_test::hashcmp256(const std::size_t &n)
{
	assert(n != 0);
	try 
	{
		std::string temp = "";
		temp = test_data256_read(n);
		bin_parser(temp);
		if(temp.length() != SIZE_HASH256_BYTE)
		{
			throw gost_exception("Format data256 form ghash.xml error");
		}
		for(std::size_t i = 0; i < temp.length(); i++)
		{
			ghash_.data256[i] = temp[i];
		}
	}
	catch(gost_exception &ex)
	{
		throw gost_exception (ex.what());
	}
#if CONSOLE_APPLICATION 
	print_result("source data for hash256 (string): ");
	print_result(ghash_.data256, SIZE_HASH256_BYTE);
	print_result("------------------------------------------------------------------------[OK]");
#endif

	hash_256(ghash_.data256, SIZE_HASH256_BYTE, ghash_.hash256);
	std::string str = to_hex(ghash_.hash256, SIZE_HASH256_BYTE + 1);
#if CONSOLE_APPLICATION 
	print_result("hash256(HEX): ");
	print_result(str);
	print_result("------------------------------------------------------------------------[OK]");
#endif
	try
	{
		std::string temp = "";
		temp = test_hash256_read(n);
		if(temp.length() == 0)
		{
			throw gost_exception("Format hash256 form ghash.xml error");
		}
		for(std::size_t i = 0; i < str.length(); i++)
		{
			if(temp[i] != str[i])
			{
				return false;
			}
		}
	}
	catch(gost_exception &ex)
	{
		throw gost_exception(ex.what());
	}
	return true;
}

bool hash_test::hashcmp512(const std::size_t &n)
{
	assert(n != 0);
	try 
	{
		std::string temp = "";
		temp = test_data512_read(n);
		if(temp.length() != SIZE_HASH512_BYTE)
		{
			throw gost_exception("Format data512 form ghash.xml error");
		}
		for(std::size_t i = 0; i < SIZE_HASH512_BYTE; i++)
		{
			ghash_.data512[i] = temp[i];
		}
	}
	catch(gost_exception &ex)
	{
		throw gost_exception (ex.what());
	}
#if CONSOLE_APPLICATION 
	print_result("source data for hash512: ");
	print_result(ghash_.data512, SIZE_HASH512_BYTE);
	print_result("------------------------------------------------------------------------[OK]");
#endif

	hash_512(ghash_.data512, SIZE_HASH512_BYTE, ghash_.hash512);

	std::string str = to_hex(ghash_.hash512, SIZE_HASH512_BYTE + 1);

#if CONSOLE_APPLICATION 
	print_result("hash512(HEX): ");
	print_result(str);
	print_result("------------------------------------------------------------------------[OK]");
#endif
	try
	{
		std::string temp = "";
		temp = test_hash512_read(n);
		if(temp.length() == 0)
		{
			throw gost_exception("Format hash512 form ghash.xml error");
		}
		for(std::size_t i = 0 ; i < temp.length(); i++)
		{
			if(temp[i] != str[i])
			{
				return false;
			}
		}
	}
	catch(gost_exception &ex)
	{
		throw gost_exception(ex.what());
	}
	return true;
}