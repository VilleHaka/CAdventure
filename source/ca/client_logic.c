#include <ca/client_logic.h>

CA_API int init_client(client_ptr* client, const char* address, int port) {
	client_t* tmp = malloc(sizeof(client_t));

	//winsock init
	tmp->winsock.slen = sizeof(tmp->winsock.si_other);
	{
		printf("\nInitialising Winsock...\n");
		if (WSAStartup(MAKEWORD(2, 2), &tmp->winsock.wsa) != 0)
		{
			printf("Failed.Error Code : % d\n", WSAGetLastError());
			return 0;
		}
		printf("Initialised.\n");
	}

	//create socket
	{
		if ((tmp->winsock.socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		{
			printf("Could not create socket : %d\n", WSAGetLastError());
		}
		printf("Socket created.\n");
	}
	
	//prepare si_other
	{
		memset((char*)& tmp->winsock.si_other, 0, sizeof(tmp->winsock.si_other));
		tmp->winsock.si_other.sin_family = AF_INET;
		tmp->winsock.si_other.sin_port = htons(port);
		tmp->winsock.si_other.sin_addr.S_un.S_addr = inet_addr(address);
	}
	printf("Done.\n");
	////Bind socket
	//{
	//	if (bind(tmp->winsock.socket, (struct sockaddr*) &tmp->winsock.server, sizeof(tmp->winsock.server)) == SOCKET_ERROR)
	//	{
	//		printf("Bind failed with error code : %d\n", WSAGetLastError());
	//		return 0;
	//	}
	//	printf("Bind done\n");
	//}

	*client = tmp;
}