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

/*
 * Ejecuta un servidor de mensajería
 * Se le pasa el PID con propósito de poderlo identificar en monitoreos de red.
 * Instancia un nuevo proceso para atender a cada cliente que llega.
 */
int main(void)
{
	int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
    	error("(Servidor) ERROR al abrir el socket\n");
    }//si ocurrió un problema al obtener un socket
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 10080;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
    	error("(Servidor) ERROR al enlazar\n");
    }//enlaza el socket
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
    {
    	error("(Servidor) ERROR al aceptar\n");
    }//si el socket de respuesta no es válido
    printf("(Servidor PID %i) Servidor de mensajes\n", pid);
    while(1)
    {
    	bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0)
		{
			error("(Servidor) ERROR al leer el socket\n");
		}//si se pudo leer el socjet de entrada
		printf("(Servidor PID %d) Se ha recibido el mensaje: \"%s\"\n", pid, buffer);
		if(strcmp(buffer, "EXIT") == 0)
		{
			close(newsockfd);
		   	close(sockfd);
		   	printf("(Servidor PID %d) Fin del proceso servidor\n", pid);
		   	exit(EXIT_SUCCESS);
		}//si se recibió el comando de salida
		n = write(newsockfd,"Mensaje recibido",18);
		if (n < 0)
		{
			error("(Servidor) ERROR al escribir al socket\n");
		}//si ocurre un error al devolver el mensaje
    }//ejecuta indefinidamente
	return 0;
}//main

