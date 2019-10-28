#ifndef CA_SERVER_H
#define CA_SERVER_H

#include "begin.h"

#include <process.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

typedef struct {
	int player_count;	
	struct {
		SOCKET udp_socket;
		fd_set readfds;
		struct sockaddr_in server_address, client_address[10];
		struct addrinfo *result, hints;
		int slen, recv_len;
		WSADATA wsa;
	}winsock;

	struct {
		HANDLE listen_handle;
		HANDLE client_handle[10];
	}threads;
}server_t, * server_ptr;

CA_EXTERN_BEGIN
CA_API int						init_server(server_ptr* server,int port);
CA_API void						listen_on_clients(server_t* server);
CA_API void						server_loop(server_t* server);
CA_API unsigned __stdcall		listen_thread(void* data);
CA_API unsigned __stdcall		client_thread(void* data);
CA_EXTERN_END

#endif