NOMBRE PRACTICA O TAREA
REDES DE COMPUTADORAS 2014-1
Manuel Ignacio Castillo López; 3-0801743-8
Mijail Gutiérrez Valdéz; 3-423250-3.
Profr. José Luis Torres Rodríguez
Ayudante de laboratorio: Luis Enrique Serrano Gutiérrez

MODO DE EJECUCION DEL PROGRAMA
Por medio de la consola de comandos de su preferencia, nos desplazamos hacia el
directorio donde ha guardado el programa; y debemos llegar hasta la carpeta del
mismo:
$tarea-lab3

Para compilar el código fuente que se proporciona, basta con ingresar el comando
'make':
$tarea-lab3 make

Para ejecutar el programa; ingresamos 'bin/tarea-lab3':
$tarea-lab3 bin/tarea-lab3

SOBRE EL DESPLIEGE EN PANTALLA
En pantalla nos aparece un menú que nos pregunta qué de los 4 programas
a iimplementar en la tarea deseamos correr. La primera opción nos permite
enmascarar un entero de 32 bits que deseemos con un número aleatoreo entre 0 y
el número que indiquemos.

La segunda opcion nos permite iniciar un cliente de mensajería que espera hacer
una negociación con el servidor para obtener un número de puerto nuevo al
original (10080) y mantener una comunicación por ese puerto nuevo, de modo que
el servidor lo libere y pueda usarlo para atender otros clientes. El servidor
envía mensajes en texto y recibe una confirmación de entrega; todo ésto gracias
a que utiliza un socket TCP.

La tercera nos permite instanciar un servidor para el servicio de mensajes
mencionado anteriormente; el cual crea diferentes instancias para atender a
todos los clientes que el sistema permita.

La última nos perite instancias una versión alternativa del servidor de
mensajes que nos permite guardar en un archivo log los carácteres recibidos en
mayúsucula o minúscula (cada tipo de caracteres en un archivo diferente) de
acuerdo a lo que se especifique (sólo se va a guardar alguno de los dos tipos
de caracteres por ejecución)

DETALLE DE VERSIONES UTILIZADAS
Núcleo de Linux: 3.2.0-4-686-pae
Compilado con: GNU C Compiler (GCC), versión 4.7.2 (Debian 4.7.2-5)
Plataforma: Debian 7.3 <<Wheezy>> para Intel-x86 (32 bits)

