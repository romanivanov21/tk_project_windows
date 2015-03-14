#ifndef _CONFIG_PARSER_H_
#define _CONFIG_PARSER_H_
#include"tinyxml.h"
#include<string>
#include"crypt_gost_types.h"
class config_parser
{
public:
	config_parser(const std::string &path_config);
	~config_parser();
	void get_disconnect_key(unsigned char *d_key, const std::size_t &key_length);
	bool find_id_client(const word16 &id_client)const;
private:
	void str_to_byte_hex(std::string &str, unsigned char *byte_data, const std::size_t &byte_length);
	std::string path_config_;
	TiXmlDocument *config_;
	TiXmlElement *pElem_;
};

#endif