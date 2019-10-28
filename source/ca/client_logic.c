#include <ca/client_logic.h>
#include <time.h>

CA_API int init_client(client_ptr* client, const char* address, int port, const char* player_name) {
	client_t* tmp = malloc(sizeof(client_t));
	tmp->player_id = player_name;
	
	printf("Initialising Winsock...\n");
	//wsa init
	tmp->winsock.slen = sizeof(tmp->winsock.ReceiverAddr);
	{
		if (WSAStartup(MAKEWORD(2, 2), &tmp->winsock.wsa) != 0)
		{
			printf("!\tFailed.Error Code : % d\n", WSAGetLastError());
			return 0;
		}
		printf(".\twsa startup complete\n");
	}

	//create udp socket for client connection requests and answers
	{
		if ((tmp->winsock.udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
		{
			printf("!\tcould not create udp socket : %d\n", WSAGetLastError());
		}
		printf(".\tudp socket created\n");
	}

	//prepare si_other
	{
		memset((char*)& tmp->winsock.ReceiverAddr, 0, sizeof(tmp->winsock.ReceiverAddr));
		tmp->winsock.ReceiverAddr.sin_family = AF_INET;
		tmp->winsock.ReceiverAddr.sin_port = htons(port);
		tmp->winsock.ReceiverAddr.sin_addr.S_un.S_addr = inet_addr(address);
	}
	printf(".\twinsock init succesful\n");
	Sleep(1000);
	*client = tmp;
}