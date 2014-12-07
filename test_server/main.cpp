#include "..\network_server_dll\network_server_dll.h"

#include <iostream>
#include <Windows.h>

extern void WINAPI server_start();

int main() {
	server_start();
	getchar();

	return 0;
}