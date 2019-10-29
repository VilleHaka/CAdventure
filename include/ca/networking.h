#ifndef CA_NETWORKING_H
#define CA_NETWORKING_H

#include "begin.h"

#include <process.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#define MAX_CLIENTS 10
#define CHAR_MAX 1000
#define POLL_TIME 100
#define MAN_SIZE (int32_t)sizeof(man_t)

typedef struct {
	double start_time, uptime;
	char name[CHAR_MAX];
	char command[CHAR_MAX];
}man_t, *man_ptr;

typedef struct {
	SOCKET socket;
	fd_set readfds;
	struct sockaddr_in this_address, other_address;
	WSADATA wsa;
}network_t;

typedef struct {
	int player_count;	
	struct sockaddr_in clients[MAX_CLIENTS];
	network_t winsock;
	struct {
		HANDLE client_handle[10];
	}threads;
}server_t, * server_ptr;

typedef struct {
	network_t winsock;
	man_t mani;	
}client_t, * client_ptr;

CA_EXTERN_BEGIN
CA_API int						ca_server(server_ptr* server,int port);
CA_API void						listen_on_clients(server_t* server);
CA_API void						ca_server_loop(server_t* server);
CA_API void						ca_client_loop(client_t* client);
CA_API unsigned __stdcall		listen_thread(void* data);
CA_API unsigned __stdcall		client_thread(void* data);
CA_API int						ca_client(client_ptr* client, const char* address, int port, const char* player_name);
CA_API int						ca_network(network_t* network, long address, int port, int socket_type);
CA_API int						ca_wsa(network_t* netw);
CA_API int						ca_socket(network_t* netw, int socket_type, int protocol);
CA_API int						ca_address(network_t* netw, const char* address, int port);
CA_API int						ca_bind_socket(network_t* netw);
CA_EXTERN_END

#endif