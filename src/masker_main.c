#include "masker_lib.h"
#include <stdlib.h>

/*
 * Aplica una máscara de valor dado como argumentos de consola a un número
 * aleatoreo de 32 bits; o bien, uno dado como segundo argumento.
 * Aplica 3 máscaras: una con OR, otra con AND  y otra con XOR; mostrando
 * siempre el número binario original en pantalla, la máscara y los resultados
 * de las 3 operaciones.
 *
 * Autor: Manuel Ignacio Castillo López; 3-0801743-8.
 * manuel_castillo_cc@ciencias.unam.mx
 * Autor: Mijail Gutiérrez Valdéz; 3-423250-3.
 * mij000@ciencias.unam.mx
 * Version 1, febrero 2014
 */

/*
 * Ejecuta el programa: crea un número a enmascarar, muestra sus bits, los de
 * la máscara y de los resultados al aplicar las máscaras
 */
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Debe proporcionar un n\u00FAmero a enmascarar\n");
		printf("Ejemplo: masker 20011992\n");
		printf("Puede incluir una m\u00E1scara como segundo argumento\n");
		printf("Ejemplo: masker 20011992 13022014");
		printf("ERROR Vuelva a llamar el programa con un n\u00FAmero a enmascarar\n");
		return 1;
	}//comprueba que se haya pasado un argumento
	int mask;
	if(argc == 2)
	{
		mask = (unsigned int) ale0a(mask);
	}
	else
	{
		mask = atoi(argv[2]);
	}//si no se le dió un número a enmascarar, genera uno aleatoreamente
	unsigned int to_mask = atoi(argv[1]);
	int result;
	printf("Se va a enmascarar: (En decimal)\t%i\n", to_mask);
	printf("(En binario)\t%s\n\n", dectobin(to_mask));
	printf("Se va a usar la m\u00E1scara: (En decimal)\t%i\n", mask);
	printf("(En binario)\t%s\n\n", dectobin(mask));
	printf("Se aplica la m\u00E1scara con AND\n\n");
	result = andmask(to_mask, mask);
	printf("El resultado es: (En decimal)\t%i\n", result);
	printf("(En binario)\t%s\n\n", dectobin(result));
	printf("Se aplica la m\u00E1scara con OR\n\n");
	result = ormask(to_mask, mask);
	printf("El resultado es: (En decimal)\t%i\n", result);
	printf("(En binario)\t%s\n\n", dectobin(result));
	printf("Se aplica la m\u00E1scara con XOR\n\n");
	result = xormask(to_mask, mask);
	printf("El resultado es: (En decimal)\t%i\n", result);
	printf("(En binario)\t%s\n\n", dectobin(result));
	char nothing[1024];
	printf("Presione intro para salir...\n");
	fgets(nothing, 1024, stdin);
	system("clear");
	return 0;
}//main

