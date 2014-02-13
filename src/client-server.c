#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*
 * Cliente servidor que escucha peticiones en el puerto 10080 y responde en
 * algún puerto por arriba del 10100. El proceso se bifurca y crea un cliente
 * que solicita enviar mensajes al server.
 *
 * Autor: Manuel Ignacio Castillo López; 3-0801743-8.
 * manuel_castillo_cc@ciencias.unam.mx
 * Autor: Mijail Gutiérrez Valdéz; 3-423250-3.
 * mij000@ciencias.unam.mx
 * Version 1, febrero 2014
 */

//prototipos de funciones
void error(const char *);
void execute_client(void);
void execute_server(void);

/*
 * Inicia la ejecución de ambos procesos: El hijo le pregunta al usuario por un
 * mensaje y lo envía al padre para que lo muestre en pantalla.
 */
int main(void)
{
	int pid;
	if((pid = fork()) == -1)
	{
		//error
		printf("Ocurri\u00F3 un error al bifurcar la ejecuci\u00F3n\n");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		//hijo
		execute_client();
	}
	else
	{
		//padre
		execute_server();
	}//actua de acuerdo al proceso ó estado de error
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

/*
 * Ejecuta un cliente de mensajería
 */
void execute_client()
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	portno = 10080;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("(Hijo) ERROR al abrir el socket");
	}//comprueba que se tenga un socket válido
	server = gethostbyname("localhost");
	if (server == NULL) {
	    fprintf(stderr,"(Hijo) ERROR, host inv\u00E1lido\n");
	    exit(0);
	}//comprueba que se haya podido resolver el server
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
	     (char *)&serv_addr.sin_addr.s_addr,
	     server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		error("(Hijo) ERROR al conectar");
	}//establece conexión y comprueba el estado de la misma
	printf("(Hijo) Cliente de env\u00EDo de mensajes.\n\n");
	while(1)
	{
		printf("(Hijo) Introduzca un mensaje para enviar al server.\n");
		printf("(Hijo) Si desea salir introduzca \"EXIT\".");
		printf("Esto enviar\u00E1 una se\u00F1al de apagado al servidor tambi\u00E9n.\n");
		bzero(buffer,256);
	    fgets(buffer,255,stdin);
	    strtok(buffer, "\n");
	    n = write(sockfd,buffer,strlen(buffer));
		if (n < 0)
		{
			error("(Hijo) ERROR al escribir al socket");
		}
		else
		{
			if(strcmp(buffer, "EXIT") == 0)
			{
				close(sockfd);
				printf("(Hijo) Fin del proceso cliente\n");
				exit(EXIT_SUCCESS);
			}//si lo que se introdujo fue el comando de salida
		}//comprueba que la escritura haya sido exitosa
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0)
		{
			error("(Hijo) ERROR al leer el socket");
		}//lee la respuesta del servidor
		printf("Respuesta del server: \"%s\"\n",buffer);
	}//ejecuta indefinidamente preguntando por mensajes a enviar al usuario
}//execute_client

/*
 * Ejecuta un servidor de mensajería
 */
void execute_server()
{
	int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
     {
     	error("(Padre) ERROR al abrir el socket");
     }//si ocurrió un problema al obtener un socket
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = 10080;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
     {
     	error("(Padre) ERROR al enlacar");
     }//enlaza el socket
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0)
     {
     	error("(Padre) ERROR al aceptar");
     }//si el socket de respuesta no es válido
     printf("(Padre) Servidor de mensajes\n");
     while(1)
     {
     	bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0)
		{
			error("(Padre) ERROR al leer el socket");
		}//si se pudo leer el socjet de entrada
		printf("(Padre) Se ha recibido el mensaje: \"%s\"\n",buffer);
		if(strcmp(buffer, "EXIT") == 0)
		{
			close(newsockfd);
	    	close(sockfd);
	    	printf("(Padre) Fin del proceso servidor");
	    	exit(EXIT_SUCCESS);
		}//si se recibió el comando de salida
		n = write(newsockfd,"Mensaje recibido",18);
		if (n < 0)
		{
			error("(Padre) ERROR al escribir al socket");
		}//si ocurre un error al devolver el mensaje
     }//ejecuta indefinidamente
}//execute_server

