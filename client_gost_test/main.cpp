#include"gtest_network.h"
#include "..\crypt_gost_28147-89\crypt_gost_types.h"
#include "..\crypt_gost_28147-89\inc_crypt_pp.h"
#include "..\crypt_gost_28147-89\diffy_helman.h"
#include<iostream>
int main(void)
{
	client *c = new client(8001);
	c->client_connect();
	CLIENT_DH_TYPE client_dh;
	if(c->read_data(client_dh.p_destBuff, SIZE_DH_BYTE_BUFF) != SIZE_DH_BYTE_BUFF)
	{
		std::cout<<"Error read p"<<std::endl;

	}
	c->print_result(client_dh.p_destBuff, SIZE_DH_BYTE_BUFF);
	if(c->read_data(client_dh.q_destBuff, SIZE_DH_BYTE_BUFF) != SIZE_DH_BYTE_BUFF)
	{
		std::cout<<"Error read q"<<std::endl;
	}
	c->print_result(client_dh.q_destBuff, SIZE_DH_BYTE_BUFF);
	if(c->read_data(&client_dh.g,1) != 1)
	{
		std::cout<<"Error read g"<<std::endl;
	}
	c->print_result(&client_dh.g,1);
	diffy_helm *dh = new diffy_helm(client_dh.p_destBuff,SIZE_DH_BYTE_BUFF,client_dh.q_destBuff,SIZE_DH_BYTE_BUFF,client_dh.g);
	if(c->read_data(client_dh.B_destBuff, SIZE_DH_BYTE_BUFF) != SIZE_DH_BYTE_BUFF)
	{
		std::cout<<"Error read A" <<std::endl;
	}
	c->print_result(client_dh.B_destBuff, SIZE_DH_BYTE_BUFF);
	dh->generate_A(client_dh.A_destBuff, SIZE_DH_BYTE_BUFF);
	c->print_result(client_dh.A_destBuff, SIZE_DH_BYTE_BUFF);
	c->send_data(client_dh.A_destBuff, SIZE_DH_BYTE_BUFF);
	dh->generate_K(client_dh.B_destBuff, SIZE_DH_BYTE_BUFF, client_dh.key_destBuff, SIZE_DH_BYTE_BUFF);
	c->print_result(client_dh.key_destBuff,SIZE_DH_BYTE_BUFF);

	delete c;
	getchar();
	return 0;
}