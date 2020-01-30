//THis program is designed to receive raw ethernet packets

//Headers
#include <sys/ioctl.h>
#include <linux/if_ether.h>
#include <netdb.h>
#include <linux/if_packet.h>
#include <netinet/ether.h>
#include <stdlib.h>

void RxfromBBB()
{
    int saddr_size , data_size, bytes_sent;
    struct sockaddr_ll saddr, daddr;
    unsigned char *buffer=malloc(65535);

    int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ; //For receiving

    memset(&saddr, 0, sizeof(struct sockaddr_ll));
    saddr.sll_family = AF_PACKET;
    saddr.sll_protocol = htons(ETH_P_ALL);
    saddr.sll_ifindex = if_nametoindex("eth0");
    if (bind(sock_raw, (struct sockaddr*) &saddr, sizeof(saddr)) < 0) 
	{
        perror("bind failed\n");
        close(sock_raw);
    }

    saddr_size = sizeof (struct sockaddr);
    
	//while (1) {
		//Receive a packet
		data_size = recvfrom(sock_raw, buffer, 65536, 0, (struct sockaddr*) & saddr, (socklen_t*)& saddr_size);

		if (data_size < 0)
		{
			printf("Recvfrom error , failed to get packets\n");
		}
		else
		{
			struct ethhdr* eth = (struct ethhdr*)buffer;
			if ((unsigned char)eth.h_dest[0] == 0xBB && (unsigned char)eth.h_dest[1] == 0x40 && (unsigned char)eth.h_dest[2] == 0x20)
			{
				printf("Received %d bytes\n", data_size);
			}
		}
	//}
    close(sock_raw);
    return 0;
}
