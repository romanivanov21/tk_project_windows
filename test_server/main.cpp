#include <iostream>
#include "netowtk_server_dll_include.h"
#include "..\network_server_dll\network_server_exception.h"
#include <boost\thread\thread.hpp>
#include <boost\bind\bind.hpp>
int main() {
	try
	{
		server_start(8001);
		//boost::thread start_thread(&server_start,8001);
		//_sleep(1000);
		//boost::thread shut_dwon_thread(&server_shut_dwon);
		//start_thread.join();
		//shut_dwon_thread.join();
	}
	catch(server::server_network_exception &ex)
	{
		std::cout<<ex.what()<<std::endl;
	}

	return 0;
}