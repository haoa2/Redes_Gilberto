/*
	ARP Scanner with MySQL Logging

	This simple program scans one interface for ARP Datagrams and logs
	its contents onto a simple Database.

	The example Database is attached at the repo.
	
	Humberto Alcocer.
*/
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> 
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <mysql/mysql.h>

/*
	Global Variables.
*/
unsigned char MACorigen[6], MACbroadcast[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char ethertype[2]={0x08,0x06};
unsigned char IPorigen[4];
unsigned char MascRed[4];
unsigned char EnviaTrama[1514];
unsigned char RecibeTrama[1514];
unsigned char tipoDeHw[2]={0x00,0x01};
unsigned char tipoDEProtocolo[2]={0x08,0x00};
unsigned char longDireccionDehw[1]={6};
unsigned char longDirecciondeProtocolo[1]={0x04};
unsigned char DireccionDehwDestino[6]={0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char codigoDeoperacion[2]={0x00,0x01};
unsigned char direccionDelProtocoloDestino[4];
unsigned char DireccionDeMiCelular[4]={0xc0,0xa8,0x64,0x03};


/*
	Printing Functions

	Funciones que ayudan a imprimir adecuadamente la información
*/

// Imprimir en Formato IP xxx.xxx.xxx.xxx
void printIP(int* ip)
{
	// TODO: Validation
	for (int i = 0; i < 3; ++i)
	{
		printf("%d.", ip[i]);
	}
	printf("%d", ip[3]);
}

// Imprimr en Formato Hexadecimal xx:xx:xx:xx:xx
void printHex(unsigned char* hex)
{
	// TODO: Validation
	for (int i = 0; i < 5; ++i)
	{
		printf("%.2x:", hex[i]);
	}
	printf("%.2x", hex[5]);
}

/*
	Obtain Data
*/
// Imprimir la trama
void imprimirTrama(unsigned char *trama, int tam)
{
	for(int i=0; i<tam; i++)
	{
		printf("%.2x ",trama[i] );
	}
}

// Imprime la IP
int imprimirIP(int ds, struct ifreq* nic)
{
	if (ioctl(ds,SIOCGIFADDR, nic)==-1)
	{
			perror("\nError al obtener la IP");
	}
	else
	{
		memcpy(IPorigen,nic->ifr_addr.sa_data+2,4);
		printf("La IP es: ");
		printIP(IPorigen);
	}
}

// Imprime la Máscara de Subred
int imprimirMascSubred(int ds, struct ifreq* nic)
{
	if (ioctl(ds,SIOCGIFNETMASK, nic)==-1)
	{
			perror("\nError al obtener la Mascara de Red");
	}
	else
	{
		// Copy the data from the struct.
		memcpy(MascRed,nic->ifr_netmask.sa_data+2,4);
		printf("La Máscara de Subred es: ");
		printIP(MascRed);
	}
}

// Imprime la dirección MAC
int imprimirMAC(int ds, struct ifreq* nic)
{
	if (ioctl(ds,SIOCGIFHWADDR, nic)==-1){
			perror("\nError al obtener la MAC");
	}
	else{
		memcpy(MACorigen,nic->ifr_hwaddr.sa_data+0,6);
		int i;
		printf("La dirección MAC es: ");
		printHex(MACorigen);
	}
}

void estructuraTrama(unsigned char *trama)//okay
{
	memcpy(trama+0, MACbroadcast,6);
	memcpy(trama+6, MACorigen,6);
	memcpy(trama+12, ethertype,2);
	memcpy(trama+14, tipoDeHw,2);
	memcpy(trama+16,tipoDEProtocolo,2);
	memcpy(trama+18,longDireccionDehw,1);
	memcpy(trama+19,longDirecciondeProtocolo,1);
	memcpy(trama+20,codigoDeoperacion,2);
	memcpy(trama+22,MACorigen,6);
	memcpy(trama+28,IPorigen,4);
	memcpy(trama+32,DireccionDehwDestino,6);
	memcpy(trama+38,DireccionDeMiCelular,4);
	//memcpy(trama+38,direccionDelProtocoloDestino,4);
	//memcpy(trama+14,  "Gerardo S C",19);
}

int obtenDatos(int ds){
	//ds ==> descriptor del socket
	struct ifreq nic;
	char nombre[10];
	int indice;
	printf("\nIngrese un nombre: ");
	gets(nombre);
	//strcpy ==> string copy
	strcpy(nic.ifr_name, nombre);
	if (ioctl(ds,SIOCGIFINDEX,&nic)==-1)//okay
	{
		perror("\nError al obtener el indice");
		exit(0);
	}
	else{
		indice=nic.ifr_ifindex;
		printf("\nEl indice es: %d\n", indice);
		imprimirMAC(ds, &nic);
		imprimirIP(ds, &nic);
		imprimirMascSubred(ds, &nic);
	}
	return indice;
}

void enviaTramaF(int ds, int index, unsigned char *trama)
{
	int tam;
	struct sockaddr_ll interfaz;
	memset (&interfaz,0x00,sizeof(interfaz));
	interfaz.sll_family=AF_PACKET;
	interfaz.sll_protocol=htons(ETH_P_ALL);
	interfaz.sll_ifindex=index;
	tam=sendto(ds,trama,60,0,(struct sockaddr *)&interfaz,sizeof(interfaz));
	if(tam==-1)
	{
		perror("Error al enviar Trama");
		exit(0);
	}
	else
	{
		printf("Éxito al enviar Trama");
	}
}


void recibeTrama (int ds, unsigned char *trama)
{
	int tam;
	while(1)
	{
		printf("entre ala trama \n");
		tam=recvfrom(ds, trama, 1514, 0, NULL, 0);
		if(tam==-1)
		{
			perror("\nError al Enviar");
			exit(0);
		}
		else{ 
			printf("\n");
			if(!memcmp(trama+0, MACorigen, 6) || !memcmp(trama+6, MACorigen, 6)){
			printf("\nJuan Recibe Trama: \n");
			imprimirTrama(trama, tam);
			printf("\n\n");
			//break;
			}
		}
	}
}

int main(int argc, char** argv){
	int a;
	int packet_socket, index,tam;

	MYSQL *con = mysql_init(NULL);
	if (con == NULL)
	{
		return -1;
	}
	
	if (mysql_real_connect("localhost","root","","ARPLogs",0,NULL,0) == NULL)
	{
		return -1;
	}

	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL) );
	
	if(packet_socket < 0)
	{
		perror("Error al abrir el socket");
		return -1;
	}
	else
	{
		index = obtenDatos(packet_socket);
		
		memcpy(direccionDelProtocoloDestino,IPorigen,4);

		direccionDelProtocoloDestino[3]=3;
		estructuraTrama(EnviaTrama);
		printf("\n enviando trama\n");
		enviaTramaF(packet_socket,index,EnviaTrama);
		printf("\n reciviendo \n");
		recibeTrama(packet_socket,RecibeTrama);
	}
	
	mysql_close(con);

	// End of Main
	return 0;
}