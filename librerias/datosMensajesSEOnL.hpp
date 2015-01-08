#ifndef  DATOS_MENSAJES_H
#define  DATOS_MENSAJES_H
#include <string.h>
#include <sys/socket.h>


/* FUNCION : LEER MENSAJE
 * ENTRADA : int sd --> socket
 * 			 char buffer --> buffer en el cual almacenar
 * 			 int total --> longitud del mensaje recibido
 * SALIDA  : void - modificación del parámetro buffer
 * DESCRIPCION : va leyendo byte por byte el mensaje recibido, y almacenando
 * en el buffer
*/
int leerMensaje ( int sd, char * buffer, int total );

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
 * DESCRIPCION : a partir de la información almacenada en el parámetro buffer,
 * interpreta de la forma  ""user&pass"" y coloca los respectivos valores
 * en los parámetros de entrada
*/
void interpretarDatos_M1 (char* user, char* pass, char* datos);

#endif
