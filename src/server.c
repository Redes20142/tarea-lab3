#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*
 * Servidor que escucha peticiones en el puerto 10080 y responde en
 * algún puerto por arriba del 10100. El proceso se bifurca y crea un servidor
 * exclusivo para el último cliente que solicitó conexión.
 *
 * Autor: Manuel Ignacio Castillo López; 3-0801743-8.
 * manuel_castillo_cc@ciencias.unam.mx
 * Autor: Mijail Gutiérrez Valdéz; 3-423250-3.
 * mij000@ciencias.unam.mx
 * Version 1, febrero 2014
 */

//prototipos de funciones
void error(const char *);
void server(int, int);
void setupserver(int);

//variables globales
int sockfd, newsockfd, portno, auxport;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;
int n;

/*
 * Ejecuta un servidor de mensajería
 * Se le pasa el PID con propósito de poderlo identificar en monitoreos de red.
 * Instancia un nuevo proceso para atender a cada cliente que llega.
 */
int main(void)
{
    char buffer[256];
    portno = 10080;
    auxport = 10100;
    printf("(Servidor) Servidor de mensajes\n");
    setupserver(portno);
    /*
     * al escuchar un cliente; se le dá un socket nuevo. Éste programa tiene
     * un defecto: si el cliente por alguna razón no constesta o no se recibe
     * su respuesta; el server lo va a esperar siempre que el proceso se
     * ejecute sin darle un límite de tiempo
     */
    char aux[256];
    int pid;
    int pidaux;
    while(1)
    {
    	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
		{
			error("(Servidor) ERROR al aceptar\n");
		}//si el socket de respuesta no es válido
		bzero(buffer, 256);
		sprintf(aux, "%d", auxport);
		n = write(newsockfd, aux, strlen(aux));
		if(auxport < 65535)
		{
			auxport++;
		}
		else
		{
			auxport = 10100;
		}//asigna un número de puerto
		printf("Se asigna el puerto %i al nuevo cliente\n", auxport -1);
		if(n < 0)
		{
			error("(Servidor) ERROR al asignar un nuevo puerto al nuevo cliente\n");
		}//si pudo escribir en el socket
		if((pid = fork()) < 0)
		{
			error("(Servidor) ERROR al bifurcar la ejecuci\u00F3n para asignar su propio server al nuevo cliente\n");
		}
		else if(pid == 0)
		{
			pidaux = getpid();
			printf("(Servidor PID %i) Preparando...\n", pidaux);
			close(newsockfd);
			close(sockfd);
			setupserver(auxport -1);
			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
			if (newsockfd < 0)
			{
				error("(Servidor) ERROR al aceptar\n");
			}//si el socket de respuesta no es válido
			printf("(Servidor PID %i) Listo para atender\n", getpid());
			server(auxport -1, pidaux);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(newsockfd);
		}//actua de acuerdo a bifurcación del proceso o estado de e-lol
    }//asigna nuevos procesos hijos para atender al nuevo cliente
	return 0;
}//main

/*
 * Atiende a un cliente
 */
void server(int sock, int pid)
{
	char buffer[256];
	while(1)
    {
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);
		if (n < 0)
		{
			error("(Servidor) ERROR al leer el socket\n");
		}//si se pudo leer el socjet de entrada
		if(strcmp(buffer, "EXIT") == 0)
		{
			close(newsockfd);
		   	printf("(Servidor PID %i: SOCK:%i) Fin de proceso servidor\n", pid, sock);
		   	exit(EXIT_SUCCESS);
		}
		else
		{
			printf("(Servidor PID %i: SOCK:%i) Se ha recibido el mensaje: \"%s\"\n", pid, sock, buffer);
		}//si se recibió el comando de salida
		n = write(newsockfd, "Mensaje recibido", 18);
		if (n < 0)
		{
			error("(Servidor) ERROR al escribir al socket\n");
		}//si ocurre un error al devolver el mensaje
	}//ejecuta indefinidamente
}//server

/*
 * Inicializa un server
 */
void setupserver(int port)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
    	error("(Servidor) ERROR al abrir el socket\n");
    }//si ocurrió un problema al obtener un socket
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
    	error("(Servidor) ERROR al enlazar\n");
    }//enlaza el socket
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
}//setupserver

