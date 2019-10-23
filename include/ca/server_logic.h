#ifndef CA_SERVER_H
#define CA_SERVER_H

#include "begin.h"

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

typedef struct {
	int player_count;

	struct {
		SOCKET socket;
		struct sockaddr_in server, si_other;
		int slen, recv_len;
		WSADATA wsa;
	}winsock;
}server_t, * server_ptr;

CA_EXTERN_BEGIN
CA_API int init_server(server_ptr* server,int port);
CA_EXTERN_END

#endif