#ifndef _NETWORK_SERVER_DLL_INCLUDE_H_
#define _NETOWRK_SERVER_DLL_INCLUDE_H_

extern void server_start(const std::size_t &port);

extern void server_shut_dwon();

extern void read_command();

extern void write_command();
#endif