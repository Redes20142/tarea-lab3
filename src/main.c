#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Muestra un menú principal que permite ejecutar diferentes módulos de la
 * práctica
 *
 * Autor: Manuel Ignacio Castillo López; 3-0801743-8.
 * manuel_castillo_cc@ciencias.unam.mx
 * mij000@ciencias.unam.mx
 * Version 1, febrero 2014
 */

/*
 * Muestra un menú y ejecuta un módulo de acuerdo a la selección del usuario
 */
int main(void)
{
	char input[1024];
	printf("REDES DE COMPUTADORAS 2014-2, FACULTAD DE CIENCIAS UNAM\n");
	printf("Profr. Jos\u00E9 Luis Torres Rodr\u00EDguez\n");
	printf("Laboratorista: Luis Enrique Serrano Guti\u00E9rrez\n");
	printf("Ayudante: Ana Laura Reyes Bola\u00F1os\n\n");
	printf("Alumnos:\nManuel Ignacio Castillo L\u00F3pez\n");
	printf("Mijail Guti\u00E9rrez Vald\u00E9s\n\n");
	printf("TAREA DE LABORATORIO 3\n");
	int pid;
	char *args[3];
	while(1)
	{
		printf("Men\u00FA de programas en la tarea.\n");
		printf("Introduzca la opci\u00F3n que desea ejecutar:\n");
		printf("1\tAplicar m\u00E1scaras sobre datos a nivel de bits.\n");
		printf("2\tIniciar el cliente de mensajes.\n");
		printf("3\tIniciar el servidor.\n");
		printf("4\tIniciar el servidor con registro de mensajes.\n");
		printf("E\tSalir.\n");
		fgets(input, 1024, stdin);
		if(!strlen(input))
		{
			printf("Error. Debe introducir una opci\u00F3n\n\n");
			continue;
		}//si se introduce la cadena vacía
		switch(tolower(input[0]))
		{
		case '1' :
			args[0] = "./bin/masker";
			printf("Introduzca un entero de 32 bits a utilizar como m\u00E1scara\n");
			fgets(input, 256, stdin);
			args[1] = input;
			break;
		case '2' :
			args[0] = "./bin/client";
			printf("Especifique el server\n");
			fgets(input, 256, stdin);
			args[1] = input;
			break;
		case '3' :
			args[0] = "./bin/server";
			args[1] = "0";
			execvp(args[0], args);
			break;
		case '4' :
			args[0] = "./bin/logger-server";
			printf("\u00BFDesea filtrar may\u00FAsculas o minusculas? (0/1)\n");
			printf("Por omisi\u00F3n se filtrar\u00E1n may\u00FAsculas.\n");
			fgets(input, 256, stdin);
			if(!strlen(input) || input[0] != '1')
			{
				args[1] = "-M";
			}
			else
			{
				args[1] = "-m";
			}//indica el tipo de enmascaramiento a utilizar
			execvp(args[0], args);
			break;
		case 'e' :
			system("clear");
			exit(EXIT_SUCCESS);
		default :
			printf("Error. Opci\u00F3n inv\u00E1lida: %c\n\n", tolower(input[0]));
			continue;
		}//actua dependiendo la selección
		args[2] = NULL;
		if((pid = fork()) == -1)
		{
			//error
			printf("Ocurri\u00F3 un error al invocar el programa\n");
		}
		else if(pid == 0)
		{
			//hijo
			execvp(args[0], args);
			printf("No se pudo cargar el programa\n");
		}
		else
		{
			//padre
			int status = 0;
			wait(&status);
			if(status)
			{
				printf("Ocurri\u00F3 un error al terminar la ejecuci\u00F3n del programa anterior\n");
			}//indica el resultado de la ejecución
		}//realiza una acción de acuerdo al proceso ó estado de error
	}//ejecuta indefinidamente el menú
	return 0;
}//main

