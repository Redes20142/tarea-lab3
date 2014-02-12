#include "random_lib.h"
#include <stdlib.h>

/*
 * Aplica una máscara de valor constante a un número aleatoreo de 32 bits.
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

// máscara constante
unsigned int mask = 20011992;

// prototipos de funciones
char *dectobin(int);

/*
 * Ejecuta el programa: crea un número a enmascarar, muestra sus bits, los de
 * la máscara y de los resultados al aplicar las máscaras
 */
int main(void)
{
	unsigned int to_mask = (unsigned int) ale0a(mask);
	unsigned int result;
	printf("Se va a enmascarar: (En decimal)\t%i\n", to_mask);
	printf("(En binario)\t%s\n\n", dectobin(to_mask));
	printf("Se va a usar la m\u00E1scara: (En decimal)\t%i\n", mask);
	printf("(En binario)\t%s\n\n", dectobin(mask));
	printf("Se aplica la m\u00E1scara con AND\n\n");
	result = mask &to_mask;
	printf("El resultado es: (En decimal)\t%i\n", result);
	printf("(En binario)\t%s\n\n", dectobin(result));
	printf("Se aplica la m\u00E1scara con OR\n\n");
	result = mask |to_mask;
	printf("El resultado es: (En decimal)\t%i\n", result);
	printf("(En binario)\t%s\n\n", dectobin(result));
	printf("Se aplica la m\u00E1scara con XOR\n\n");
	result = mask ^to_mask;
	printf("El resultado es: (En decimal)\t%i\n", result);
	printf("(En binario)\t%s\n\n", dectobin(result));
	printf("Se aplica la m\u00E1scara con XOR\n\n");
	char nothing[1024];
	printf("Presione una tecla para salir...\n");
	fgets(nothing, 1024, stdin);
	system("clear");
	return 0;
}//main

/*
 * Imprime en pantalla los bits de un número de 32 bits
 */
char *dectobin(int number)
{
	unsigned short int sign;
	if(number >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
		number *= -1;
	}//recuerda el signo original del número y usa su valor absoluto
	char* bits = "00000000000000000000000000000000";
	unsigned short int i =  31;
	while(number > 1)
	{
		if(number %2)
		{
			bits[i] = '1';
		}
		else
		{
			bits[i] = '0';
		}//coloca el dígito binario correspondiente
		number /= 2;
		i--;
	}//reduce el número a su expresión binaria
	bits[i] = number %2;
	if(sign)
	{
		sign = 0;
		for(i = 31; i >= 0; i--)
		{
			if(bits[i] == '0')
			{
				if(sign)
				{
					bits[i] = '1';
				}//si ya se encontró el primer 1, invierte el 0
			}
			else
			{
				if(sign)
				{
					bits[i] = '0';
				}
				else
				{
					sign = 1;
				}//si ya encontró el primer 1, invierte el 1. Si encuentra
				//el primer 1, lo deja tal cual e indica que encontró el
				//prier 1
			}//actua dependiendo si encuentra 1 ó 0
		}//recorre la cadena sacando el complemento a 2
	}//si el signo era negativo, obtiene su complemento a 2
	return bits;
}//dectobin

