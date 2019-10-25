#ifndef CA_SERVER_H
#define CA_SERVER_H

#include "begin.h"

#include <process.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

typedef struct {
	int player_count;

	struct {
		SOCKET socket;
		SOCKET listen;
		struct sockaddr_in server, si_other;
		int slen, recv_len;
		WSADATA wsa;
	}winsock;

	struct {
		HANDLE thread_handles[10];
	}threads;
}server_t, * server_ptr;

CA_EXTERN_BEGIN
CA_API int init_server(server_ptr* server,int port);
CA_API void  listen_on_clients(server_t* server);
CA_API unsigned __stdcall	listen_thread(void* data);
CA_API unsigned __stdcall  client_thread(void* data);
CA_EXTERN_END

#endif