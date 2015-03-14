#include"config_parser.h"
#include"tinyxml.h"
#include"crypt_gost_types.h"
#include"network_server_exception.h"
#include"gost_include.h"
#include"boost\shared_ptr.hpp"
config_parser::config_parser(const std::string &path_config) : path_config_(path_config)
{
	try
	{
		config_ = new TiXmlDocument(path_config_.c_str());
	}
	catch(...)
	{
		throw config_parser_exception("Cannot find config.xml");
	}
	pElem_ = 0;
}

config_parser::~config_parser()
{
	delete config_;
}
void config_parser::str_to_byte_hex(std::string &str, byte *byte_data, const std::size_t &byte_length)
{
	assert(!(str.empty()) || byte_data != NULL || byte_length != 0);
	if((str.size() % 2))
	{
		str += " ";
	}
	std::size_t str_it = 0;
	for(std::size_t i = 0; i < byte_length; i++)
	{
		if(str_it <= str.size())
		{
			byte_data[i] = str[str_it];
			byte_data[i] = byte_data[i] << 4;
			if(str_it == str.size())
			{
				byte_data[i] = 0x0;
			}
			else
			{
				byte_data[i] |= str[str_it + 1];
				str_it = str_it + 2;
			}
		}
	}
}
void config_parser::get_disconnect_key(byte *d_key, const std::size_t &key_length)
{
	assert(d_key != NULL || key_length == SIZE_CRYPT_KEY_BYTE);
	try
	{
		if(!(config_->LoadFile()))
		{
			throw config_parser_exception("Error load config.xml");
		}
	}
	catch(...)
	{
		throw config_parser_exception("Error load config.xml");
	}
	pElem_ = config_->FirstChildElement("server");
	if(!pElem_)
	{
		throw config_parser_exception("Not found <server> </server>");
	}
	std::string value = "";
	for(const TiXmlElement *item = pElem_->FirstChildElement("disconnect_key"); item; item = item->NextSiblingElement("disconnect_key"))
	{
		value = item->Attribute("vaule");
	}
	if(value.empty())
	{
		throw config_parser_exception("disconnect_key is empty");
	}
	str_to_byte_hex(value, d_key, key_length);
}
bool config_parser::find_id_client(const word16 &id_client)const
{
	assert(id_client != 0);
	throw config_parser_exception("no implementation!");
}