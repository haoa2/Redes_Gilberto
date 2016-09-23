#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> /* the L2 protocols */
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>

unsigned char MACORIGEN[6], MACDESTINO[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char mask[4];
unsigned char ip[4];
unsigned char trama_e[1514];
unsigned char ETHERTYPE[2] = {0x0a,0x0a};


void estructura_trama(unsigned char *trama){
	memcpy(trama+0,MACDESTINO,6);
	memcpy(trama+6,MACORIGEN,6);
	memcpy(trama+12,ETHERTYPE,2);
	memcpy(trama+14,"PEPE PECAS PICA PAPAS", 21);
}

void enviar_trama(int ds, int index, unsigned char *trama){
	struct sockaddr_ll interfaz;
	memset(&interfaz, 0x00, sizeof(interfaz));
	interfaz.sll_family = AF_PACKET;
	interfaz.sll_protocol = htons(ETH_P_ALL);
	interfaz.sll_ifindex = index;
	int size = sendto(ds, trama, 60, 0, (struct sockaddr*)&interfaz, sizeof(interfaz));
	if (size == -1){
		perror("Tu cosa no jala, bruh\n");
		exit(0);
	}else{
		printf("Pos si jalo, bruh\n");
	}
}

int get_index(int ds){
	struct ifreq nic;
	struct sockaddr no;
	char nombre[10];
	int indice,a;
	printf("Introduce el nombre: \t");
	gets(nombre);
	strcpy(nic.ifr_name,nombre);
	// INDEX
	if (ioctl(ds,SIOCGIFINDEX,&nic)==-1){
		perror("errror \n");	
	}else{
		indice = nic.ifr_ifindex;
		printf("Index: %d\n",indice);
	}
	
	//	MAC ADDRESS
	if(ioctl(ds,SIOCGIFHWADDR,&nic)==-1){
		perror("error \n");
	}else{
		memcpy(MACORIGEN,nic.ifr_hwaddr.sa_data,6);
		printf("MAC: \t");
		for(a=0;a<6;a++){
			printf("%.2x:",MACORIGEN[a]);
		}
		printf("\n");
	}

	//	MASK
	if(ioctl(ds,SIOCGIFNETMASK,&nic)==-1){
		perror("error \n");
	}else{
		memcpy(MACORIGEN,nic.ifr_netmask.sa_data+2,4);
		printf("MASK: \t");
		for(a=0;a<4;a++){
			printf((a==3) ? "%d" : "%d.",MACORIGEN[a]);
		}
		printf("\n");
	}
	//	IP
	if(ioctl(ds,SIOCGIFADDR,&nic)==-1){
		perror("error \n");
	}else{
		memcpy(ip,nic.ifr_addr.sa_data+2,4);
		printf("IP: \t");
		for(a=0;a<4;a++){
			printf((a==3) ? "%d" : "%d.",ip[a]);
		}
		printf("\n");
	}	

	return indice;
}

int main(){
	int packet_socket,index;
	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL) );

	if(packet_socket < 0){
		perror("Error al abrir el socket\n");
	} else {
		index = get_index(packet_socket);
		estructura_trama(trama_e);
		enviar_trama(packet_socket, index, trama_e);
		printf("Exito al abrir el socket\n");
	
	}		
	close(packet_socket);
    return 0;
}
