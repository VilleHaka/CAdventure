#include <ca/client_logic.h>
#include <time.h>

CA_API int init_client(client_ptr* client, const char* address, int port, const char* player_name) {
	client_t* tmp = malloc(sizeof(client_t));
	tmp->player_id = player_name;
	
	printf("Initialising Winsock...\n...\t");
	//winsock init
	tmp->winsock.slen = sizeof(tmp->winsock.si_other);
	{

		if (WSAStartup(MAKEWORD(2, 2), &tmp->winsock.wsa) != 0)
		{
			printf("Failed.Error Code : % d\n", WSAGetLastError());
			return 0;
		}
		printf("wsa startup complete\n...\t");
	}

	//create tcp socket for client connection requests and answers
	{
		if ((tmp->winsock.tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		{
			printf("could not create tcp socket : %d\n", WSAGetLastError());
		}
		printf("tcp socket created\n...\t");
	}

	////create udp socket for data transfer
	//{
	//	if ((tmp->winsock.udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	//	{
	//		printf("Could not create udp socket : %d\n", WSAGetLastError());
	//	}
	//	printf("udp socket created\n");
	//}
	printf("winsock init succesful\n");



	//prepare si_other
	{
		memset((char*)& tmp->winsock.si_other, 0, sizeof(tmp->winsock.si_other));
		tmp->winsock.si_other.sin_family = AF_INET;
		tmp->winsock.si_other.sin_port = htons(port);
		tmp->winsock.si_other.sin_addr.S_un.S_addr = inet_addr(address);
	}

	
	//connect to server
	{
		time_t start = clock();
		printf("connecting to: %s:%i...\n", address,port);

		int cres = 99;
		while(1)
		{
			cres = connect(tmp->winsock.tcp_socket, (SOCKADDR*)& tmp->winsock.si_other, sizeof(tmp->winsock.si_other));
			if (cres == 0) break;
			else {
				printf("... \tconnection failed with error: %ld\n", WSAGetLastError());
				Sleep(1000);
			}
			
			if ((clock() - start)/1000 > 25) { 
				closesocket(tmp->winsock.tcp_socket);
				WSACleanup();
				printf("... \ttimed out :(\n");
				return 0; 
			}
		}
		//recv(tmp->winsock.tcp_socket, tmp->winsock.udp_socket, sizeof(tmp->winsock.udp_socket), NULL);
		//printf("%ld\n", WSAGetLastError());
	}
	printf("connection successful.\n");
	Sleep(2000);
	*client = tmp;
}