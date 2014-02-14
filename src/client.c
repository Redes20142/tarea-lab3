#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*
 * Cliente que solicita conexión al servidor de mensajes por medio del puerto;
 * 10080 pero espera que sea reasignado al iniciar conexión
 *
 * Autor: Manuel Ignacio Castillo López; 3-0801743-8.
 * manuel_castillo_cc@ciencias.unam.mx
 * Autor: Mijail Gutiérrez Valdéz; 3-423250-3.
 * mij000@ciencias.unam.mx
 * Version 1, febrero 2014
 */

//prototipos de funciones
void error(const char *);

/*
 * Inicia el cliente y espera establecer una conexión con el servidor para
 * comenzar a enviar mensajes.
 * Se le pasa el PID con propósito de poderlo identificar en monitoreos de red
 */
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		error("(Cliente) ERROR debe proporcionar un servidor.\nPor ejemplo \"localhost\"");
	}//comprueba que almenos se le pasó un argumento
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	portno = 10080;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("(Cliente) ERROR al abrir el socket\n");
	}//comprueba que se tenga un socket válido
	server = gethostbyname(argv[1]);
	if (server == NULL) {
	    fprintf(stderr,"(Cliente) ERROR, host inv\u00E1lido\n");
	    exit(0);
	}//comprueba que se haya podido resolver el server
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
		server -> h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		error("(Cliente) ERROR al conectar\n");
	}//establece conexión y comprueba el estado de la misma
	/*
	 *si el server a aceptado nuestra solicitud de conexión, esperamos que nos
	 * haya contestado con un nuevo número de puerto al que nos vamos a
	 * conectar comunicar con él
	 */
	bzero(buffer, 256);
	n = read(sockfd, buffer, 255);
	if(n < 0)
	{
		error("(Cliente) ERROR al teminar la negociaci\u00F3n con el servidor: No se ha podido recuperar el nuevo n\u00FAmero de puerto\n");
	}//comprueba que la comunicación haya sido exitosa
	portno = atoi(buffer);
	// cerrar conexión vieja y crear nueva con el nuevo puerto
	printf("(Hijo) Cliente de env\u00EDo de mensajes.\n\n");
	while(1)
	{
		printf("(Cliente) Introduzca un mensaje para enviar al server.\n");
		printf("(Cliente) Si desea salir introduzca \"EXIT\".");
		printf(" Esto enviar\u00E1 una se\u00F1al de apagado al servidor tambi\u00E9n.\n");
		bzero(buffer,256);
	    fgets(buffer,255,stdin);
	    strtok(buffer, "\n");
	    n = write(sockfd,buffer,strlen(buffer));
		if (n < 0)
		{
			error("(Cliente) ERROR al escribir al socket\n");
		}//comprueba que la comunicación haya sido exitosa
		else
		{
			if(strcmp(buffer, "EXIT") == 0)
			{
				close(sockfd);
				printf("(Cliente) Fin del proceso cliente\n");
				exit(EXIT_SUCCESS);
			}//si lo que se introdujo fue el comando de salida
		}//comprueba que la escritura haya sido exitosa
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0)
		{
			error("(Cliente) ERROR al leer el socket\n");
		}//lee la respuesta del servidor
		printf("Respuesta del server: \"%s\"\n", buffer);
	}//ejecuta indefinidamente preguntando por mensajes a enviar al usuario
	return 0;
}//main

/*
 * Levanta un error y termina el proceso
 */
void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}//error

