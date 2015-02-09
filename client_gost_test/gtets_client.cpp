#include "gtest_client.h"
#include "tinyxml.h"
test_client::test_client(const std::string &path_data, const std::size_t &port) : 
	path_data_(path_data), port_(port)
{
	assert(!(path_data.empty()) || (port_ != 0));
	memset(client_dh_.p_destBuff, 0, sizeof(byte) * SIZE_DH_BYTE_BUFF);
	memset(client_dh_.q_destBuff, 0, sizeof(byte) * SIZE_DH_BYTE_BUFF);
	client_dh_.g = 0;
	memset(client_dh_.A_destBuff, 0, sizeof(byte) * SIZE_DH_BYTE_BUFF);
	memset(client_dh_.B_destBuff, 0, sizeof(byte) * SIZE_DH_BYTE_BUFF);
}

std::string test_client::to_hex(const byte *byte_data, const std::size_t &length)
{
	assert((byte_data != 0) || (length != 0));
	std::vector<byte> v(&byte_data[0], &byte_data[length - 1]);
	std::ostringstream result;
	result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
	std::copy(v.begin(), v.end(), std::ostream_iterator<unsigned int>(result, ""));
	return result.str();
}
test_client::~test_client()
{
	delete c_; delete dh_;
}

void test_client::testing()
{
	try
	{
	c_ = new client(port_);
	c_->client_connect();
	}
	catch(...)
	{
		throw client_exception("Ñan not connect to the server");
	}
	if(c_->read_data(client_dh_.p_destBuff, SIZE_DH_BYTE_BUFF) != SIZE_DH_BYTE_BUFF)
	{
		throw client_exception("Error get from server p");
	}
	printf("p = ");
	c_->print_result(client_dh_.p_destBuff, SIZE_DH_BYTE_BUFF);
	if(c_->read_data(client_dh_.q_destBuff, SIZE_DH_BYTE_BUFF) != SIZE_DH_BYTE_BUFF)
	{
		throw client_exception("Error get from server q");
	}
	printf("q = ");
	c_->print_result(client_dh_.q_destBuff, SIZE_DH_BYTE_BUFF);
	if(c_->read_data(&client_dh_.g,1) != 1)
	{
		throw client_exception("Error get from server g");
	}
	printf("g = ");
	c_->print_result(&client_dh_.g,1);
	diffy_helm *dh = new diffy_helm(client_dh_.p_destBuff,SIZE_DH_BYTE_BUFF,client_dh_.q_destBuff,SIZE_DH_BYTE_BUFF,client_dh_.g);
	if(c_->read_data(client_dh_.B_destBuff, SIZE_DH_BYTE_BUFF) != SIZE_DH_BYTE_BUFF)
	{
		throw client_exception("Error get from server  A");
	}
	printf("B = ");
	c_->print_result(client_dh_.B_destBuff, SIZE_DH_BYTE_BUFF);
	dh->generate_A(client_dh_.A_destBuff, SIZE_DH_BYTE_BUFF);
	printf("A = ");
	c_->print_result(client_dh_.A_destBuff, SIZE_DH_BYTE_BUFF);
	c_->send_data(client_dh_.A_destBuff, SIZE_DH_BYTE_BUFF);
	dh->generate_K(client_dh_.B_destBuff, SIZE_DH_BYTE_BUFF, client_dh_.key_destBuff, SIZE_DH_BYTE_BUFF);
	printf("K = ");
	c_->print_result(client_dh_.key_destBuff, SIZE_DH_BYTE_BUFF);
	std::string key = to_hex(client_dh_.key_destBuff, SIZE_DH_BYTE_BUFF);
	try
	{
		test_data_write(key);
	}
	catch(client_exception &ex)
	{
		throw client_exception(ex.wath());
	}
}
void test_client::test_data_write(const std::string &key)
{
	TiXmlDocument *data = new TiXmlDocument(&path_data_[0]);
	if(!data->LoadFile())
	{
		throw client_exception("The file dhdata.xml connot find");
	}
	TiXmlElement *pElem = data->FirstChildElement("dh");
	TiXmlElement *pElemKey = pElem->FirstChildElement("key");
	pElemKey->SetAttribute("vaule",&key[0]);
	data->SaveFile();
	delete data;
}