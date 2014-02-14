#include "masker_lib.h"

/*
 * Define operaciones para enmascarar enteros de 32 bits signados.
 *
 * En redes, usualmente la máscara utilizada es aplicando el operador bitewise
 * AND (int & int). Sin embargo, incluye definiciones para operar con OR
 * (int | int) y XOR (int ^ int) para hacer el programa más general.
 *
 * Autor: Manuel Ignacio Castillo López; 3-0801743-8.
 * manuel_castillo_cc@ciencias.unam.mx
 * Autor: Mijail Gutiérrez Valdéz; 3-423250-3.
 * mij000@ciencias.unam.mx
 * Version 1, febrero 2014
 */



int andmask(int tomask, int mask)
{
	return mask &tomask;
}//andmask

int ormask(int tomask, int mask)
{
	return mask |tomask;
}//ormask

int xormask(int tomask, int mask)
{
	return mask ^tomask;
}//xormask

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
	/*char bits[32] = "";
	char aux[32] = "";*/
	char *aux = malloc(sizeof(char*) *32);
	unsigned short int i =  31;
	while(number > 1)
	{
		if(number %2)
		{
			strcat(aux, "1");
		}
		else
		{
			strcat(aux, "0");
		}//coloca el dígito binario correspondiente
		number /= 2;
		i--;
	}//reduce el número a su expresión binaria
	if(number %2)
	{
		strcat(aux, "1");
	}
	else
	{
		strcat(aux, "0");
	}//asigna el último resiuo
	while(i > 0)
	{
		strcat(aux, "0");
		i--;
	}//rellena con 0
	strrev(aux);
	if(sign)
	{
		sign = 0;
		char *bits = malloc(sizeof(char*) *32);
		for(i = 31; i >= 0; i--)
		{
			if(aux[i] == '0')
			{
				if(sign)
				{
					strcat(bits, "1");
				}
				else
				{
					strcat(bits, "0");
				}//si ya se encontró el primer 1, invierte el 0
			}
			else
			{
				if(sign)
				{
					strcat(bits, "0");
				}
				else
				{
					sign = 1;
					strcat(bits, "1");
				}//si ya encontró el primer 1, invierte el 1. Si encuentra
				//el primer 1, lo deja tal cual e indica que encontró el
				//prier 1
			}//actua dependiendo si encuentra 1 ó 0
		}//recorre la cadena sacando el complemento a 2
		strrev(bits);
		return bits;
	}
	else
	{
		return aux;
	}//si el signo era negativo, obtiene su complemento a 2
}//dectobin

/*
 * Invierte una cadena
 */
void strrev(char *string)
{
	int length, c;
	char *begin, *end, temp;
	length = strlen(string); 
	begin = string;
	end = string; 
	for ( c = 0 ; c < ( length - 1 ) ; c++ ) end++;
	for ( c = 0 ; c < length/2 ; c++ ) 
	{        
		temp = *end;
		*end = *begin;
		*begin = temp; 
		begin++;
    	end--;
   }//invierte la cadena
}//strrev

