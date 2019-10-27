#ifndef CA_CLIENT_H
#define CA_CLIENT_H

#include "begin.h"

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

typedef struct {
	struct {
		SOCKET tcp_socket,udp_socket;
		struct sockaddr_in si_other;
		int slen,s;
		WSADATA wsa;
	}winsock;

	const char* player_id;
}client_t, *client_ptr;

CA_EXTERN_BEGIN
CA_API init_client(client_ptr* client, const char* address, int port,const char* player_name);
CA_EXTERN_END

#endif