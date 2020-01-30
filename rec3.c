#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h>
#include <netdb.h>
#include <linux/if_packet.h>
#include <netinet/ether.h>
#include <stdlib.h>

int main()
{
    int saddr_size , data_size, daddr_size, bytes_sent;
    struct sockaddr_ll saddr, daddr;
    unsigned char *buffer=malloc(65535);

    int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ; //For receiving
   // int sock = socket( PF_PACKET , SOCK_RAW , IPPROTO_RAW) ;            //For sending

    memset(&saddr, 0, sizeof(struct sockaddr_ll));
    saddr.sll_family = AF_PACKET;
    saddr.sll_protocol = htons(ETH_P_ALL);
    saddr.sll_ifindex = if_nametoindex("eth0");
    if (bind(sock_raw, (struct sockaddr*) &saddr, sizeof(saddr)) < 0) 
	{
        perror("bind failed\n");
        close(sock_raw);
    }
/*The next two blocks of code seem to be used for sending packets*/
/*    memset(&daddr, 0, sizeof(struct sockaddr_ll));
    daddr.sll_family = AF_PACKET;
    daddr.sll_protocol = htons(ETH_P_ALL);
    daddr.sll_ifindex = if_nametoindex("eth1");
    if (bind(sock, (struct sockaddr*) &daddr, sizeof(daddr)) < 0) {
      perror("bind failed\n");
      close(sock);
    }
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "eth1");
    if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        perror("bind to eth1");
        }*/

    while(1)
    {
        saddr_size = sizeof (struct sockaddr);
      //  daddr_size = sizeof (struct sockaddr);
        //Receive a packet
        data_size = recvfrom(sock_raw , buffer , 65536 , 0 ,(struct sockaddr *) &saddr , (socklen_t*)&saddr_size);
        //printf(write(sock,buffer,data_size));
        if(data_size <0 )
        {
            printf("Recvfrom error , failed to get packets\n");
            return 1;
        }
        else
		{
			printf("Received %d bytes\n",data_size);


			/*
			//Send the same packet out
			bytes_sent=write(sock,buffer,data_size);
			printf("Sent %d bytes\n",bytes_sent);
			if (bytes_sent < 0) 
			 {
				perror("sendto");
				exit(1);
			 }*/
        }
    }
    close(sock_raw);
    return 0;
}
