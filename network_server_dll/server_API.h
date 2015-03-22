#ifndef _SERVER_API_H_
#define _SERVER_API_H_

#define SERVER_API __declspec(dllexport)

#include"network_server_dll.h"
#include"server_timer.h"

SERVER_API void server_start(const std::size_t &port);

SERVER_API void server_shut_dwon();

SERVER_API void read_command();

SERVER_API void write_command();

#endif