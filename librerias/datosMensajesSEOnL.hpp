#ifndef  DATOS_MENSAJES_H
#define  DATOS_MENSAJES_H
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>



/* FUNCION : LEER MENSAJE
 * ENTRADA : int sd --> socket
 * 			 char buffer --> buffer en el cual almacenar
 * 			 int total --> longitud del mensaje recibido
 * SALIDA  : void - modificación del parámetro buffer
 * DESCRIPCION : va leyendo byte por byte el mensaje recibido, y almacenando
 * en el buffer
*/
int leerMensaje ( int sd, char * buffer, int total );

/* FUNCION : ORDENAR BYTES
 * ENTRADA : struct mensaje m --> mensaje a transformar
 * SALIDA  : struct mensaje m --> mensaje a transformado
 * DESCRIPCION : trabaja sobre los campos codigo, subcodigo y longitud del mensaje y
 * los ordena a travez de las funciones htons y htonl según corresponda. Para poder ser
 * enviados a travez de la red.
*/
void ordenarBytes (struct mensaje* m);

/* FUNCION : REORDENAR BYTES
 * ENTRADA : struct mensaje m --> mensaje a transformar
 * SALIDA  : struct mensaje m --> mensaje a transformado
 * DESCRIPCION : trabaja sobre los campos codigo, subcodigo y longitud del mensaje y
 * los reordena a travez de las funciones ntohs y ntohl según corresponda. Es utilizada
 * luego de recibir datos a travez de la red.
*/
void reordenarBytes (struct mensaje* m);


/* FUNCION : CREAR DATOS
 * ENTRADA : texto,  datos
 * SALIDA  : void - modificación del parámetro datos
 * DESCRIPCION : crea un solo char* a partir del textp ingresado como parametro,
 utilizado para aquellos mensajes que involucran solamente una cadena de texto
 */

void crearDatos (char* texto, char* datos);

/*MENSAJE 0*/
/*   No necesita crear e interpretar la informacion enviada en datos ya que esta
 * se envia con el formato de una estructura alumno.
*/

/*MENSAJE 1*/

/* FUNCION : CREAR DATOS MENSAJE 1
 * ENTRADA : user, pass, datos
 * SALIDA  : void - modificación del parámetro datos
 * DESCRIPCION : crea un solo char* a partir del usuario y contraseña, con el
 * siguiente formato
 * 					user&pass
*/
void crearDatos_M1(char* user, char* pass, char* datos);

/* FUNCION : INTERPRETAR  MENSAJE 1
 * ENTRADA : user, pass, datos
 * SALIDA  : void - modificación de los parámetros user y pass
 * DESCRIPCION : a partir de la información almacenada en el parámetro datos,
 * interpreta de la forma  ""user&pass"" y coloca los respectivos valores
 * en los parámetros de entrada
*/
void interpretarDatos_M1 (char* user, char* pass, char* datos);

#endif
