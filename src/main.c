#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	while(1)
	{
		printf("Men\u00FA de programas en la tarea.\n");
		printf("Introduzca la opci\u00F3n que desea ejecutar:\n");
		printf("1\tAplicar m\u00E1scaras sobre datos a nivel de bits.\n");
		printf("E\tSalir.\n")
		fgets(input, 1024, stdin);
		if(!strlen(input))
		{
			printf("Error. Debe introducir una opci\u00F3n\n\n");
			continue;
		}//si se introduce la cadena vacía
		switch(tolower(input[0]))
		{
		case '1' :
			//TODO 
			break;
		case 'e' :
			system("clean");
			exit(EXIT_SUCCESSFULL);
		default :
			printf("Error. Opci\u00F3n inv\u00E1lida: %c\n\n", tolower(input[0]));
		}//actua dependiendo la selección
	}//ejecuta indefinidamente el menú
	return 0;
}//main

