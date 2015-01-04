#include <iostream>
#include <Windows.h>

void extern server_start(byte *data, std::size_t size);

int main() {
	char data_sending[8];
	strcpy_s(data_sending,"1234567");
	server_start((byte*)data_sending,8);
	getchar();

	return 0;
}