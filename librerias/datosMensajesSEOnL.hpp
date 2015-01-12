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

/*MENSAJE 1*/

/* FUNCION : CREAR DATOS MENSAJE 0
 * ENTRADA : legajo, nombre, user, datos
 * SALIDA  : void - modificación del parámetro datos
 * DESCRIPCION : crea un solo char* a partir del legajo, nombre y user, con el
 * siguiente formato
 * 					legajo&nombre&yuser
*/
void crearDatos_M0(char* user, char* pass, char* datos);

/* FUNCION : INTERPRETAR  MENSAJE 0
 * ENTRADA :  legajo, nombre, user, datos
 * SALIDA  : void - modificación de los parámetros legajo, nombre y user
 * DESCRIPCION : a partir de la información almacenada en el parámetro datos,
 * interpreta de la forma  "legajo&nombre&yuser" y coloca los respectivos valores
 * en los parámetros de entrada
*/
void interpretarDatos_M0 (char* user, char* pass, char* datos);


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
